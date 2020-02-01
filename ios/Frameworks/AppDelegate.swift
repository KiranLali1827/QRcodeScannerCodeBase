//
//  AppDelegate.swift
//  qrcodescanner
//
//  Created by Pri Tam on 1/29/20.
//  Copyright © 2020 Facebook. All rights reserved.
//

import UIKit
import VeridiumCore
import Veridium4FExportBiometrics
import VeridiumDefault4FExportUI


@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {


  
  var window: UIWindow?
  let license: String = NetworkContants.license
  
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool
    {
        // Override point for customization after application launch.
      
      
      /*
    //check online
      VeridiumSDK.setup(withOnlineLicensing: license, onSdkLicenseCompletion: { (status, error) in
        print("the online status = \(status)")
      }) { (lincsstarts, error) in
        print("the online lincsstarts = \(lincsstarts)")
      }
      */
        
      
      
      
        VeridiumUtils.showWaitingAlert("Initializing SDK")
        VeridiumSDK.setup(withOnlineLicensing: license,
                          onSdkLicenseCompletion: { sdkStatus, error in
                            print("the sdk status = \(sdkStatus.debugDescription)")
                            print("error is = \(error?.localizedDescription)")
                    if (error != nil)
                    {
                        DispatchQueue.main.async {
                            VeridiumUtils.hideWaitingAlert {
                                VeridiumUtils.alert("Licence enforcer error: \(error?.localizedDescription ?? "")", title: "Licence")
                            }
                        }
                        return
                    }
                    
                    guard let sdkStatus = sdkStatus else {
                        DispatchQueue.main.async {
                            VeridiumUtils.hideWaitingAlert {
                                VeridiumUtils.alert("The SDK licence is invalid", title: "Licence")
                            }
                        }
                        return
                    }
                    
                    // Check the result of the license system
                    if(!sdkStatus.initSuccess){
                        DispatchQueue.main.async {
                            VeridiumUtils.hideWaitingAlert {
                                VeridiumUtils.alert("The SDK licence is invalid", title: "Licence")
                            }
                        }
                        return
                    }
                    
                    if(sdkStatus.isInGracePeriod) {
                        DispatchQueue.main.async {
                            VeridiumUtils.hideWaitingAlert {
                                VeridiumUtils.alert("Your SDK licence will expire soon. Please contact your administrator for a new licence", title: "Licence")
                            }
                        }
                    }
                    
                    VeridiumSDK.shared.registerDefault4FExExporter(); // Alternatively you could use VeridiumSDK.shared.registerCustom4FExporter() if using the custom ui.
                    VeridiumSDK.shared.registerDefault4FExEnroller();
                    VeridiumSDK.shared.registerDefault4FExAuthenticator();
        }, onBiolibsCompletion: {licenseStatusDict, error in
            if let licenseStatusDict = licenseStatusDict {
                DispatchQueue.main.async {
                    VeridiumUtils.hideWaitingAlert {
                        for (bioLibName, licenseStatus) in licenseStatusDict {
                            if (!licenseStatus.initSuccess) {
                                VeridiumUtils.alert("Your \(bioLibName) license is invalid", title: "License")
                                return
                            }
                            
                            if (licenseStatus.isInGracePeriod) {
                                VeridiumUtils.alert("Your \(bioLibName) license will expire soon", title: "License")
                            }
                        }
                    }
                }
            }
        })
        
        return true
    }

    // MARK: UISceneSession Lifecycle
    @available(iOS 13.0, *)
    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    @available(iOS 13.0, *)
    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
    }



}


