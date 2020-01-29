//
//  Veridium4FViewController.h
//  Veridium4FUI
//
//  Created by Paul Paul on 1/26/18.
//  Copyright © 2018 VeridiumID. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;
@import Veridium4FBiometrics;
@import VeridiumAnalytics;

@interface Veridium4FViewController : UIViewController <Veridium4FUIDelegate, Veridium4FEnrollerUIDelegate, Veridium4FAuthenticatorUIDelegate>

+(instancetype)initiate;

@end
