//
//  VeridiumDefault4FEnrollViewController.h
//  Default4FUI
//
//  Created by razvan on 3/14/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;
@import Veridium4FBiometrics;
@import VeridiumAnalytics;

/*!
 The default 4F enrollment View Controller.
 */
@interface VeridiumDefault4FEnrollViewController : UIViewController <Veridium4FEnrollerUIDelegate>

/*!
 Static method which initializes the customized ViewController for the 4F enrollment UI.

 @param storyboard the storyboard which contains the customized default ViewController
 @param identifier the identifier of the customized default 4F Authentication ViewController
 @return self
 */
+(instancetype _Nullable) createFromStoryboard:(UIStoryboard* _Nullable)storyboard withIdentifier:(NSString* _Nullable)identifier;

/*!
 Static method which initializes the VeridiumDefault4FEnrollViewController aka the default 4F enrollment UI.

 @return VeridiumDefault4FEnrollViewController
 */
+(instancetype _Nullable) createDefault;

@end
