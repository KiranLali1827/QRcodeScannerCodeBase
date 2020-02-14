//
//  AppDelegate.swift
//  qrcodescanner
//
//  Created by Pri Tam on 2/14/20.
//  Copyright © 2020 Veridium IP Ltd. All rights reserved.
//



import UIKit
import VeridiumCore
import Veridium4FExportBiometrics
import VeridiumDefault4FExportUI // Alternatively you could use import VeridiumCustom4FUI if you want to alter the interface.


@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    
    var window: UIWindow?
    

    let licenseSDK = NetworkContants.license
    
  internal func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        VeridiumUtils.showWaitingAlert("Initializing SDK")
        VeridiumSDK.setup(withOnlineLicensing: licenseSDK,
                          onSdkLicenseCompletion: { sdkStatus, error in
                            if (error != nil) {
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
    
    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    }
    
    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }
    
    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    }
    
    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }
    
    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }
    
    
}

