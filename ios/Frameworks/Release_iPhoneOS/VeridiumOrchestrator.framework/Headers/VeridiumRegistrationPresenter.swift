//
//  VeridiumRegistrationPresenter.swift
//  VeridiumAuthenticator
//
//  Created by Catalin Stoica on 11/01/2018.
//  Copyright © 2018 VeridiumIP. All rights reserved.
//

import UIKit
import VeridiumBOPS
import Veridium4FBiometrics

protocol VeridiumRegistrationPresenterProtocol {
    func submit()
    func advanceEnrollment()
    func renderPageForProfile(_ profile:VeridiumProfileData?)
    func generateFormForView(view:UIView)
    func onResend()
    func lastRenderedFrame() -> CGRect
}

class VeridiumRegistrationPresenter: AbstractPresenter<VeridiumRegisterViewController>, VeridiumRegistrationPresenterProtocol, VeridiumDynamicFormsGeneratorDelegate {
    
    var theIntegration:VeridiumBOPSIntegrationDefinitionData = VeridiumBOPSIntegrationDefinitionData()
    var theForm:VeridiumDynamicFormsGenerator? = nil
    var theRegistrationMode:VeridiumBOPSRegistrationModeDefinitionData = VeridiumBOPSRegistrationModeDefinitionData()
    
    override func setView(view: VeridiumRegisterViewController) {
        self.genericView = view
        if let profileIntegration = self.genericView.profile?.integration {
            theIntegration = profileIntegration
        } else {
            theIntegration = (integrationForOngoingBopsRegistration != nil ? integrationForOngoingBopsRegistration : VIDSetupService.firstPairing()?.integration)!
        }
    }
    
    func renderPageForProfile(_ profile:VeridiumProfileData?) {
        
        let (_, registrationMode) = hasExtraEnrollmentStep(integration: theIntegration, status: profile?.status)
            if let registrationMode = registrationMode {
                self.genericView.updatePageForDescription(description: registrationMode.title.uppercased(),
                                                      nextButton: registrationMode.enrollmentStepActionName ?? "NEXT",
                                                      resendButton: registrationMode.restartEnrollmentStepActionName,
                                                      hint: registrationMode.hint)
                theRegistrationMode = registrationMode
            }
        
    }
    
    func generateFormForView(view: UIView) {
        theForm = VeridiumDynamicFormsGenerator(view: view, registrationMode: theRegistrationMode, delegate:self)
    }
    
    func lastRenderedFrame() -> CGRect {
        return theForm!.lastRenderedFrame
    }
    
    func handleFormDataSubmited() {
        if nil != self.genericView.profile {
            self.advanceEnrollment()
            return;
        }
        self.submit()
    }
    
    func advanceEnrollment() {
        self.theForm?.dismissKeyboard(sender: nil)
        let profile = self.genericView.profile!
        let requestBody = ["profileId" : profile.profileId, "loginData": self.theForm!.collectSubmitedData().toNSDictoinary.jsonString!] as [String : Any]
        self.genericView.showProcessing() {
            VeridiumSDK.shared.defaultBOPSAccountService?.activeBopsAccount?.bopsAdvanceEnrollment(forProfileId: profile.profileId, params: requestBody, withCompletion: { (profile, error) in
                guard error == nil else {
                    print("BOPS AdvancedEnrollment \n \(error!.localizedDescription)")
                    self.genericView.onAdvancedEnrollmentFailed(error: error!)
                    return
                }
                
                if nil != profile {
                    VIDSetupService().defaultAccountService?.activeAccount?.refreshProfiles(withForce: true, completion: { (error) in
                        if let error = error {
                            print("BOPS Refresh Profiles error: \n\(error.localizedDescription)")
                        }
                        self.genericView.onAdvancedEnrollmentSuccessfull(profile: profile!)
                    })
                }
            })
        }
    }
    
    func submit() {
        DispatchQueue.main.async {
            self.theForm?.dismissKeyboard(sender: nil)
            if self.theForm!.validateData() == true {
                if VIDSetupService().defaultAccountService?.activeAccount != nil {
                    self.registerProfile(profileData: self.theForm!.collectSubmitedData())
                } else {
                    self.registerAccount(accountData: self.theForm!.collectSubmitedData())
                }
            }
        }
    }
    
    func submit(userEnrollToken: String) {
        DispatchQueue.main.async {
            var jsonDictionary: [String: String]?
            if let data = userEnrollToken.data(using: .utf8) {
                do {
                    jsonDictionary = try JSONSerialization.jsonObject(with: data, options: []) as? [String: String]
                } catch {
                    print(error.localizedDescription)
                    // fall back to raw token
                    jsonDictionary = ["raw":userEnrollToken]
                }

                if VIDSetupService().defaultAccountService?.activeAccount != nil {
                    self.registerProfile(profileData: jsonDictionary!)
                }
                else {
                    self.registerAccount(accountData: jsonDictionary!)
                }
            }
        }
    }
    
    func cancelEnrollment() {
        self.genericView.showProcessing(whenShown: {
            
            // The if below translates to:
            // if this is the first account errolled ||\
            // the account was enrolled && it is in 'advance enrollment' state && this is the first profile enrolled
            // then wipe the account and start over.
            if (VIDSetupService().defaultAccountService?.activeAccount == nil) ||
                (VIDSetupService().defaultAccountService?.activeAccount != nil && self.genericView.profile != nil && VIDSetupService().defaultAccountService?.activeAccount?.privateProfilesCount == 1) {

                VIDRevocationService.shared().wipeAccount {
                    self.genericView.onRegisterCancelled()
                }
            }
            else {
                self.genericView.onRegisterCancelled()
            }
        })
    }
    
    func registerAccount(accountData:[String: String]) {
        VeridiumKeychainKeyValueStore.global.clearAllData()
        if let service = VIDSetupService().defaultAccountService {
            self.genericView.showProcessing() { [unowned self] in
                service.register(with: nil,
                                 integration: self.theIntegration,
                                 registrationMode: "form",
                                 loginData: accountData,
                                 txSignProtectionLevel: VeridiumTXSigningProtectionNone,
                                 withCompletion: { (account, error) in
                                    
                                    if let account = account {
                                        
                                        let profile = account.profiles[0]
                                        let image = UIImage(named: "profile-icon", in: Bundle(for: GetBundle.self), compatibleWith: nil)
                                        let alias: String = profile.getDefaultAlias()
                                        profile.updateProfile(alias: alias,
                                                              image: image!,
                                                              integration: self.theIntegration,
                                                              authenticationHand: nil)
                                        
                                        forceReenrollData = VeridiumRemoteConfigForceEnrollData.newFomJson(json: ["lastUpdatedAppVersion" : Bundle.main.object(forInfoDictionaryKey: "CFBundleShortVersionString") as! String,
                                                                                                                  "isForceEnrolled"       : isForceReenrollNeeded.stringValue()].toNSDictoinary.jsonString!)
                                        

                                        account.fetchLicenseAndValidate(withForce: true, completion: { (error) in
                                            if nil != error {
                                                self.genericView.onRegisterAccountInvalidLicense(error: error!)
                                                return;
                                            }
                                            self.genericView.onAccountRegistrationSuccess()

                                            if let account = (account as? VeridiumBOPSAccount) {
                                                if account.is4FInGracePeriod {
                                                    VeridiumUtils.alert("Your license will expire soon. Please contact your administrator for a new license.", title: "Info")
                                                }
                                            }
                                        })

                                        return
                                    }
                                    print(error?.localizedDescription ?? "")
                                    self.genericView.onRegisterFail(error: error!)
                })
            }
        } else {
            self.genericView.onRegisterFail(error: NSError(domain: "com.authenticator", code: 1051, userInfo: nil))
        }
        
    }
    
    func registerProfile(profileData:[String: String]) {
        self.genericView.showProcessing() { [unowned self] in
            if let account = VIDSetupService().defaultAccountService?.activeAccount {
                account.registerProfile(self.theIntegration,
                                            registrationMode: "form",
                                            credentials: profileData,
                                            txSignProtectionLevel: VeridiumTXSigningProtectionNone,
                                            withCompletion: { (profile, error) in
                                                guard error == nil else {
                                                    self.genericView.onRegisterFail(error: error!)
                                                    return
                                                }
                                                if let profile = profile {
                                                    let alias: String = profile.getDefaultAlias()
                                                    let image = UIImage(named: "profile-icon", in: Bundle(for: GetBundle.self), compatibleWith: nil)
                                                    profile.updateProfile(alias: alias,
                                                                          image: image!,
                                                                          integration: self.theIntegration,
                                                                          authenticationHand: AuthHand(enrolledHand: EnrollHand(hand: account.enrolledHand)))
                                                    self.genericView.onProfileRegistrationSuccess(profile: profile)
                                                }
                })
            }
        }
    }
    
    func onResend() {
        self.genericView.showProcessing() { [unowned self] in
            VeridiumSDK.shared.defaultBOPSAccountService?.activeBopsAccount?.bopsRestartEnrollmentStep(forProfileId: self.genericView.profile!.profileId, withCompletion: { (profile, error) in
                self.genericView.dismissProcessing(onDismiss: {
                    if let error = error {
                        print(error)
                        self.genericView.onRegisterFail(error: error)
                        return
                    }
                })
            })
        }
    }
    
}
