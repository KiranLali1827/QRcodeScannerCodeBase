//
//  VeridiumPushManager.swift
//  VeridiumAuthenticator
//
//  Created by Catalin Stoica on 02/02/2018.
//  Copyright © 2018 VeridiumIP. All rights reserved.
//

import UIKit
import VeridiumCore
import VeridiumBOPS
import UserNotifications

public class VeridiumPushManager: NSObject, VeridiumPushHandlerProtocol, UIApplicationDelegate {
  public static let shared = VeridiumPushManager()
  var pendingPushes:[String:voidBlock] = [:]
  var authDoneBlock:voidBlock? = nil
  public var isAuthInProgress:Bool = false
  var pushTSforOngoingAuthentication: String? = ""
  
  private override init() {
    
  }
    
    func updatePushMechanisms() {
        
        if VIDSetupService().defaultAccountService?.activeAccount != nil  &&
            !(VIDSetupService().defaultAccountService?.activeAccount?.isLocked)! {
            VIDSetupService().defaultAccountService?.activeAccount?.refreshNotifications(completion: { (error) in
                if self.pendingPushes.count > 0 {
                    VIDMobileSDK.shared().pushDelegate?.pushesPending()
                }
            })
        }
        
        VeridiumSDK.shared.canRegister(forPushes: { (canRegisterForPushes, canRequestAuthorization) in
            
            if canRegisterForPushes == true {
                VeridiumSDK.shared.defaultBOPSAccountService?.stopPolling()
                VeridiumSDK.shared.enablePushNotifications(true)
            }
            else {
                VeridiumSDK.shared.enablePushNotifications(false)
                DispatchQueue.main.async {
                    VeridiumSDK.shared.defaultBOPSAccountService?.startPolling(withInterval: 10.0, fireEvenWhenAPNSAvailable: false)
                }
            }
        })
    }
    
    public func setRemoteNotificationsToken(pushTokenData: Data?) {
        if pushTokenData != nil {
            VeridiumSDK.shared.defaultBOPSAccountService?.stopPolling()
            VeridiumSDK.shared.registerPushToken(pushTokenData)
        }
        else {
            VeridiumSDK.shared.registerPushToken(nil)
            VeridiumSDK.shared.defaultBOPSAccountService?.stopPolling()
            VeridiumSDK.shared.defaultBOPSAccountService?.startPolling(withInterval: 10.0, fireEvenWhenAPNSAvailable: false)
        }
    }
  
  public func handlePush(_ pushData: [String : Any]!, isAPNS: Bool) {
    if let push = self.parsePush(pushData: pushData, isAPNS: isAPNS) {
      push.treat()
    }
//    consumeDeliveredPushes(isAPNS: isAPNS)
  }
  
  func parsePush(pushData: [String: Any], isAPNS: Bool) -> VAPushNotification? {
    if let pushAction: String = pushData["actionName"] as? String {
      switch pushAction {
      case "auth":
        return VAPNAuthentication(pushData, isAPNS: isAPNS)
      case "revoke_access":
        return VAPNRevokeAccess(pushData)
      case "revalidate_device":
        return VAPNRevalidateDevice(pushData)
      case "refresh_secrets":
        return VAPNRefreshSecrets(pushData)
      case "refresh_profiles":
        return VAPNRefreshProfiles(pushData)
      default:
        return nil
      }
    } else {
      return nil
    }
  }

//  func consumeDeliveredPushes(isAPNS: Bool) {
//    if #available(iOS 10.0, *) {
//      UNUserNotificationCenter.current().getDeliveredNotifications { (pushNotifications) in
//        var treatedDeliveredPushes:[String] = [String]()
//        var didTreatLastAuthPush = false
//        for push in pushNotifications {
//          if let pushData = push.request.content.userInfo as? [String: Any] {
//            if let vaPush = self.parsePush(pushData: pushData, isAPNS: true) { //check
//              treatedDeliveredPushes.append(push.request.identifier)
//              if vaPush.type == .Auth {
//                if !didTreatLastAuthPush {
//                  vaPush.treat()
//                }
//                didTreatLastAuthPush = true
//                continue
//              }
//              vaPush.treat()
//            }
//          }
//        }
//        UNUserNotificationCenter.current().removeDeliveredNotifications(withIdentifiers: treatedDeliveredPushes)
//      }
//    } else {
//      UIApplication.shared.applicationIconBadgeNumber = 1
//      UIApplication.shared.applicationIconBadgeNumber = 0
//      UIApplication.shared.cancelAllLocalNotifications()
//    }
//  }

  public func consumePendigPushes() {
    DispatchQueue.main.async {
      if VeridiumUtils.topmostViewController().isKind(of: ProcessingViewController.classForCoder()) {
        print("Push handling obstructed by Processing controller");
        return
      }
      if (self.isAuthInProgress) {
          print("Already treating another push. Postponing current push treat.");
      }
        
      if self.pendingPushes.count > 0  && !self.isAuthInProgress {
        let lastPushKey = self.pendingPushes.keys.sorted().last
        self.pendingPushes[lastPushKey!]!()
        self.authDoneBlock = {
          DispatchQueue.main.async {
            if self.pendingPushes.count > 0 {
              self.isAuthInProgress = false
              self.pendingPushes.removeValue(forKey: self.pushTSforOngoingAuthentication!)
              self.consumePendigPushes()
            }
          }
        }
      }
    }
  }
  
  
}
