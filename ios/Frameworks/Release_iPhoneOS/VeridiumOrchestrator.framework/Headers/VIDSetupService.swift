//
//  VeridiumQRPresenter.swift
//  VeridiumAuthenticator
//
//  Created by Catalin Stoica on 04/01/2018.
//  Copyright © 2018 VeridiumIP. All rights reserved.
//

import UIKit
import VeridiumQRReader
import VeridiumCore
import VeridiumBOPS
import VeridiumBiometricsOnly


public class VIDSetupService: VeridiumQRViewProtocol {
    
    private lazy var completionHandler: ((_ userToken: String?, _ error: VIDError?) -> ()) = { (_, _) in print ("ERROR: completion handler not supplied in pairing")  }

    private static let kStorePairingsKey: String               = "BOPSPairings"
    private let kIdentifierQRCodeViewController: String = "veridiumQrReader"

    private final let kOtpPairingUrl: String = "otpauth://"
    public static let kOtpIntegrationExternalId: String = "OTP"

    private static let kADIntegrationExternalId: String = "AD"
    private static let kADMSEIntegrationExternalId: String = "ADv2MultiStepEnrollment"

    public init() {
        
    }
    
    func pairWithQRCode(completion: @escaping (_ userToken: String?, _ error: VIDError?) -> ()) {
        // start workflow by scanning the QR. The delegate will continue the workflow
        completionHandler = completion
        
        let QRCodeReader = UIStoryboard(name: "ModalViewControllers", bundle: Bundle(identifier: "com.veridiumid.VeridiumOrchestrator")).instantiateViewController(withIdentifier: kIdentifierQRCodeViewController) as! VeridiumQrReaderViewController
        QRCodeReader.delegate = self
        QRCodeReader.descriptionText = "Your account provider will display a QR code for you to scan"
        QRCodeReader.helpText = "If you do not have a QR code, enable two-step verification on your account."
        VeridiumUtils.topmostViewController().present(QRCodeReader, animated: true, completion: nil)
    }
    
    func pairOtp(uri: String, issuer: String?, accountName: String?, completion: (_ userToken: String?, _ error: VIDError?) -> ()) {
        guard !uri.isEmpty else {
            completion(nil, VIDError(errorCode: 1019))
            return
        }

        let pairingData = VeridiumBOPSPairingData().parse([
            "websecUrl": kOtpPairingUrl,
            "definition": NSDictionary(dictionary: [
                "externalId": VIDSetupService.kOtpIntegrationExternalId,
                "availableBiometricMethods":["4F","TOUCHID"]
                ])
            ]);

        
        if VIDSetupService.bopsPairings.count != 0,
            VIDSetupService.bopsPairings.first?.value.url != pairingData.url {
            print("Mixed mode with OTP and VeridiumID integrations is not allowed.")
            completion(nil, VIDError(errorCode: 1100))
            return
        }

        // refresh local authenticators
        _ = VeridiumSDK.shared.laStatus

        let alreadyHaveAccount = VIDSetupService().defaultAccountService?.activeAccount != nil
        VeridiumSDK.shared.registerLocalAccountService()
        if (!alreadyHaveAccount) {
            // cleanup the accout data that may be from previous enrollments in the keychain
            print("Clean-up: delete old data related to current pairing.  \(Thread.callStackSymbols)")
            VeridiumUserDefaultsKeyValueStore.global.clearAllData()
            VeridiumSDK.shared.localAccountService?.unregisterAllAccounts()
            VeridiumKeychainKeyValueStore.global.clearAllData()
        }
        
        var pairings = VIDSetupService.bopsPairings
        pairings[kOtpPairingUrl] = pairingData
        if VIDSetupService.bopsPairings.count == 0 {
            VIDSetupService.bopsPairings = pairings
        }
        integrationForOngoingBopsRegistration = pairingData.integration
        
        _ = VIDRevocationService.shared()
        
        //TODO: should we enable this?
//        let health = VIDInitializerService.shared().checkEnvHealth()
//        if health != nil {
//            completion?(VIDError(error: NSError(domain: "com.authenticator", code: 1052, userInfo: [NSLocalizedDescriptionKey: health!])))
//            return
//        }
        
        completion(uri, nil)
    }
    

    
    func pair(b64Token: String, completion: @escaping (_ userToken: String?, _ error: VIDError?) -> ()) {
        if b64Token.isEmpty {
            completion(nil, VIDError(errorCode: 1019))
            return
        }
        
        VIDMobileSDK.shared().didStartLongProcess(status: SDKStatus.PAIRING, processDescription: SDKStatusDescription[SDKStatus.PAIRING]!) {
            
            VeridiumSDK.shared.getBOPSPairingInfo(withToken: b64Token, withCompletion: { (pairingData, error) in
                
                VIDMobileSDK.shared().didFinishLongProcess(status: SDKStatus.PAIRING) {
                    
                    if let decoded = (b64Token as NSString).base64ToData {
                        if let s = ((decoded as NSData).toString as NSString).jsonDictionary {
                            if ((s["memberDefinitionExtId"] as! String) == "veridiumadmin") {
                                completion(nil, VIDError(errorCode: 1019))
                                return
                            }
                        }
                    }
                    else {
                        BasicDialogViewController.selfClosingAlert(titleText: "Pairing error", descriptionText: "Base64 token decode failed").presentInTopmost()
                    }
                    
                    if let error = error {
                        let errorText = error.localizedDescription
                        print("🚫🚫🚫🚫 Get BOPS Pairning Info 🚫🚫🚫🚫 \n \(errorText)")
                        let errorCode = error.toNSError.code == 1032 ? 1032 : 1015
                        completion(nil, VIDError(errorCode: errorCode))
                        return
                    }
                    
                    guard let pairingData = pairingData else {
                        print("🚫🚫🚫🚫 Get BOPS Pairning Info 🚫🚫🚫🚫 \n \(error?.localizedDescription ?? "Unknown Error")")
                        completion(nil, VIDError(errorCode: 1003))
                        return
                    }
                    
                    guard let defaultCertData = (pairingData.defaultCertificate as NSString).base64ToData else {
                        print("Invalid client cert data")
                        completion(nil, VIDError(errorCode: 1015))
                        return
                    }
                    
//                    guard !pairingData.pinnedServerPublicKeyHashes.isEmpty else {
//                        print("Invalid public key data")
//                        completion(nil, VIDError(errorCode: 1015))
//                        return
//                    }
                    
                    if VIDSetupService.bopsPairings.count != 0,
                        VIDSetupService.bopsPairings.first?.value.url != pairingData.url {
                        print("This is from another server.")
                        completion(nil, VIDError(errorCode: 1002))
                        return
                    }
                    
                    if VIDSetupService.bopsPairings.count != 0,
                        VIDSetupService.bopsPairings.first?.value.integration.authenticatorType != pairingData.integration.authenticatorType {
                        print("Profile has different auth type")
                        completion(nil, VIDError(errorCode: 1049))
                        return
                    }
                    
                    // check if locally all required biometries are supported
                    if (pairingData.integration.biometricMethods != nil) {
                        for method in pairingData.integration.biometricMethods! {
                            if !VeridiumSDK.shared.registeredAuthenticationBiometricMethods.contains(method) {
                                completion(nil, VIDError(errorCode: 1038))
                                return
                            }
                        }
                    }
                    
                    // refresh local authenticators
                    _ = VeridiumSDK.shared.laStatus
                    // check if any of the available biometries are supported locally
                    // (there should be at least one biometry set on the server)
                    let availableBiometrics = pairingData.integration.availableBiometricMethods
                    if nil == availableBiometrics || availableBiometrics?.count == 0 {
                        completion(nil, VIDError(errorCode: 1039))
                        return
                    }
                    var foundOne = false
                    for method in availableBiometrics! {
                        if VeridiumSDK.shared.registeredAuthenticationBiometricMethods.contains(method) {
                            foundOne = true
                            break
                        }
                    }
                    if foundOne == false {
                        let error = VeridiumBOPSError(domain:VeridiumBOPSErrorDomain,
                                                      code:-1022,
                                                      userInfo:[
                                                        NSLocalizedDescriptionKey:"Account registration error",
                                                        NSLocalizedFailureReasonErrorKey:"None of the integration's available biometries are present of the device.",
                                                        NSLocalizedRecoverySuggestionErrorKey:"Please contact the administrator."
                            ])
                        
                        completion(nil, VIDError(error: error))
                        return
                    }
                    
                    
                    if !self.isValid(loginDefinition: pairingData.integration.loginDefinition) {
                        completion(nil, VIDError(errorCode: -1020))
                        return
                    }
                    
                    var error: VIDError?
                    if !self.checkSecureEnclaveSupport(systemSettings: pairingData.systemSettings, maybeError: &error) {
                        completion(nil, error)
                        return
                    }
                    
                    let settlePairing = {
                        
                        let requiredMinVersion = pairingData.integration.loginDefinition?.minimumRequirements?.iOS
                        if (requiredMinVersion != nil && (requiredMinVersion!.compare("0") == .orderedSame || VeridiumUtils.getDeviceOsVersion().compare(requiredMinVersion!, options: .numeric, range: nil, locale: nil) == .orderedAscending)) {
                            print("Device operting system version does not meet the requirements set by your administrator.")
                            completion(nil, self.getCustomIntegrationError(pairingData: pairingData, systemError: VIDError(errorCode: 1070)))
                            return
                        }

                        
                        let alreadyHaveAccount = VIDSetupService().defaultAccountService?.activeAccount != nil
                        
                        if(VeridiumSDK.shared.setupBOPSAccountService(withURL: pairingData.url, defaultClientCertificate: defaultCertData, defaultClientCertificatePass: pairingData.defaultCertificatePassword, pinnedServerPublicKeyHashes: pairingData.pinnedServerPublicKeyHashes, systemSettings: pairingData.systemSettings)) {
                            
                            if (!alreadyHaveAccount) {
                                // cleanup the accout data that may be from previous enrollments in the keychain
                                print("Clean-up: delete old data related to current pairing.  \(Thread.callStackSymbols)")
                                VeridiumUserDefaultsKeyValueStore.global.clearAllData()
                                VIDSetupService().defaultAccountService?.activeAccount?.clearAllData()
                                VIDSetupService().defaultAccountService?.unregisterAllAccounts()
                                VeridiumKeychainKeyValueStore.global.clearAllData()
                            }
                            
                            var pairings = VIDSetupService.bopsPairings
                            pairings[pairingData.url] = pairingData
                            if VIDSetupService.bopsPairings.count == 0 {
                                VIDSetupService.bopsPairings = pairings
                            }
                            integrationForOngoingBopsRegistration = pairingData.integration
                            
                            HelpService.putDisclaimer(pairing: pairingData)
                            
                            _ = VIDRevocationService.shared()
                            if (LocationServiceForServerReporting.isLocationEnabled(settings: pairingData.systemSettings)) {
                                _ = LocationService.shared()    // request permission
                            }
                            let health = VIDInitializerService.shared().checkEnvHealth()
                            if health != nil {
                                completion(nil, VIDError(error: NSError(domain: "com.authenticator", code: 1052, userInfo: [NSLocalizedDescriptionKey: health!])))
                                return
                            }
                            
                            completion(nil, nil)
                        } else {
                            completion(nil, VIDError(errorCode: 1003))
                            return
                        }
                    }
                    
                    let disclaimerText = pairingData.integration.loginDefinition?.disclaimer
                    if  disclaimerText != nil && !disclaimerText!.isEmpty {
                        VeridiumUIAlertController.initiate(withTitle: "Disclaimer", message: disclaimerText!, okButton: ("Agree", {
                            
                            settlePairing()
                            
                        }), cancelButton: ("Decline",{
                            // nothing to do
                        })).presentInTopmost()
                    }
                    else {
                        settlePairing()
                    }
                }
            })
        }
    }
    
    func pairUpdateServerSettings(b64Token: String, completion: ((_ error: VIDError?) -> ())?) {
        guard !b64Token.isEmpty else {
            completion?(VIDError(errorCode: 1019))
            return
        }
        
        guard (b64Token as NSString).base64ToData != nil else {
            completion?(VIDError(errorCode: 1003))
            return
        }
        
        VeridiumSDK.shared.getBOPSPairingInfo(withToken: b64Token, withCompletion: { (pairingData, error) in
            
            if let error = error {
                let errorText = error.toNSError.userInfo.count > 0 ? error.toNSError.userInfo.description : "Get BOPS Pairning Info error \(error.toNSError.code) \(error.localizedDescription)";
                print("🚫🚫🚫🚫 Get BOPS Pairning Info 🚫🚫🚫🚫 \n \(errorText)")
                let errorCode = error.toNSError.code == 1032 ? 1032 : 1015
                completion?(VIDError(errorCode: errorCode))
                return
            }
            
            guard let pairingData = pairingData else {
                print("🚫🚫🚫🚫 Get BOPS Pairning Info 🚫🚫🚫🚫 \n \(error?.localizedDescription ?? "Unknown Error")")
                completion?(VIDError(errorCode: 1003))
                return
            }
            
            guard (pairingData.defaultCertificate as NSString).base64ToData != nil else {
                print("Invalid client cert data")
                completion?(VIDError(errorCode: 1015))
                return
            }
            
            guard !pairingData.pinnedServerPublicKeyHashes.isEmpty else {
                print("Invalid public key data")
                completion?(VIDError(errorCode: 1015))
                return
            }
            
            if VIDSetupService.bopsPairings.count != 0,
                VIDSetupService.bopsPairings.first?.value.url != pairingData.url {
                print("This is from another server.")
                completion?(VIDError(errorCode: 1002))
                return
            }
            
            var pairings = VIDSetupService.bopsPairings
            pairings[pairingData.url] = pairingData
            VIDSetupService.bopsPairings = pairings
            
            completion?(nil)
            
        })
    }
    
    func isValid(loginDefinition:VeridiumBOPSLoginDefinitionData?) -> Bool {
        if nil == loginDefinition || nil == loginDefinition?.registrationModes {
            return false
        }
        for item in loginDefinition!.registrationModes {
            if item.outputStatuses.count == 0 {
                return false
            }
        }
        return true
    }
    
    
    private func getCustomIntegrationError(pairingData: VeridiumBOPSPairingData, systemError: VIDError) -> VIDError {
        // custom error is on Registration Modes inside the Login Definition.
        // Ugly, but this is what they wanted.
        if ((pairingData.integration.loginDefinition?.registrationModes.count ?? -1) > 0) {
            if let customErrString = pairingData.integration.loginDefinition?.registrationModes[0].enforcedErrorMessage, customErrString.isEmpty == false {
                return VIDError(error: NSError(domain: systemError.domain, code: systemError.code, userInfo: [NSLocalizedFailureReasonErrorKey: customErrString]))
            }
        }
        
        return systemError
    }
    
    #if targetEnvironment(simulator)
    func checkSecureEnclaveSupport(systemSettings: [AnyHashable : Any]?, maybeError: inout VIDError?) -> Bool {
        return true;
    }
    #else
    func checkSecureEnclaveSupport(systemSettings: [AnyHashable : Any]?, maybeError: inout VIDError?) -> Bool {
        
        guard let systemSettings = systemSettings else { return true }
        
        if systemSettings["is-hardware-encryption-required"] != nil && (systemSettings["is-hardware-encryption-required"] as! String).caseInsensitiveCompare("true") == ComparisonResult.orderedSame {
            
            do {
                try VeridiumSecureEnclaveWrapper.checkSecureEnclaveSupport()
            }
            catch {
                if(error.toNSError.code != 0) {
                    maybeError = VIDError(error: NSError(domain: error.toNSError.domain, code: 1050, userInfo: error.toNSError.userInfo))
                }
                return false
            }
            
        }
        
        return true;
    }
    #endif
    
    //MARK: -
    
    //MARK: - pairings
    public static var bopsPairings:[String:VeridiumBOPSPairingData] {
        get{
            if nil != VeridiumUserDefaultsKeyValueStore.global[kStorePairingsKey] {
                
                if let pairingStr = VeridiumUserDefaultsKeyValueStore.global[kStorePairingsKey] as NSString? {
                    
                    if let jsonDict = pairingStr.jsonDictionary {
                        var pairings = [String:VeridiumBOPSPairingData]()
                        for (key, dict) in jsonDict as! [String:NSDictionary] {
                            pairings[key] = VeridiumBOPSPairingData().parse(dict as! [AnyHashable:Any])
                        }
                        return pairings
                    }
                }
            }
            return [:]
        }
        set {
            let pairingsDict = NSMutableDictionary()
            for (key, pairing) in newValue {
                pairingsDict[key] = pairing.serialize
            }
            VeridiumUserDefaultsKeyValueStore.global[kStorePairingsKey] = pairingsDict.jsonString
        }
    }
    
    public static func firstPairing() -> VeridiumBOPSPairingData? {
        return VIDSetupService.bopsPairings.first?.value
    }
    
    public var defaultAccountService : VeridiumAccountService? {
        get {
            if VeridiumSDK.shared.localAccountService != nil {
                return VeridiumSDK.shared.localAccountService
            }
            else {
                return VeridiumSDK.shared.defaultBOPSAccountService
            }
        }
    }
    //MARK: -
    
    //MARK: VeridiumQrView delegate methods
    public func onQrViewWillAppear(viewController: VeridiumQrReaderViewController) {}
    
    public func onPairingQR(token: String) {
        self.pair(b64Token: token, completion: self.completionHandler)
    }

    public func onOtpQR(uri: String, issuer: String?, accountName: String?) {
        self.pairOtp(uri: uri, issuer: issuer, accountName: accountName, completion: self.completionHandler)
    }

    public func onAuthenticationQR(sessionId: String, integrationId: String) {
        BasicDialogViewController.getPrematureAuthenticationQRAlert(onOk: {
            self.completionHandler(nil, VIDError(errorCode: 1004))
        }).presentInTopmost()
    }
    
    public func onOfflineAuthenticationQR(profileExternalId: String, salt: String) {
        BasicDialogViewController.getByErrorCode(errorCode: 1009, onOk: {
            self.completionHandler(nil, VIDError(errorCode: 1009))
        }).presentInTopmost()
    }
    
    public func onInvalidQr() {
        BasicDialogViewController.getInvalidQRAlert(onOk: {
            self.completionHandler(nil, VIDError(errorCode: 1019))
        }).presentInTopmost()
    }
    
    
    public func onScanCancelled() {
        
    }
    //MARK: -
    
    //MARK: helper functions
    public func isADIntegration(integrationExtID: String) -> Bool {
        return integrationExtID.compare(VIDSetupService.kADMSEIntegrationExternalId, options: .caseInsensitive) == ComparisonResult.orderedSame ||
            integrationExtID.starts(with: VIDSetupService.kADIntegrationExternalId)
    }
    
    public func isOTPIntegration(integrationExtID: String) -> Bool {
        return integrationExtID.compare(VIDSetupService.kOtpIntegrationExternalId, options: .caseInsensitive) == ComparisonResult.orderedSame
    }

}
