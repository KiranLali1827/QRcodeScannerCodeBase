//
//  VeridiumDefault4FAuthViewController.h
//  Default4FUI
//
//  Created by razvan on 10/9/15.
//  Copyright © 2015 HoyosLabs. All rights reserved.
//
@import VeridiumCore;
@import Veridium4FBiometrics;
@import VeridiumAnalytics;

/*!
 The default 4F authentication View Controller
 */
@interface VeridiumDefault4FAuthViewController : UIViewController <Veridium4FAuthenticatorUIDelegate>

/*!
 Static method which initializes the customized ViewController for the 4F authentication UI.

 @param storyboard the storyboard which contains the customized default ViewController
 @param identifier the identifier of the customized default 4F Authentication ViewController
 @return self
 */
+(instancetype _Nullable) createFromStoryboard:(UIStoryboard* _Nullable)storyboard withIdentifier:(NSString* _Nullable)identifier;

/*!
 Static method which initializes the VeridiumDefault4FAuthViewController aka the default 4F authentication UI.

 @return VeridiumDefault4FAuthViewController
 */
+(instancetype _Nullable) createDefault;

@end
