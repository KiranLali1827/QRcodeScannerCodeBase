//
//  Veridium4FIntroViewController.h
//  Veridium4FUI
//
//  Created by Paul Paul on 2/20/18.
//  Copyright © 2018 VeridiumID. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface Veridium4FIntroViewController : UIViewController

+(instancetype)initiate;

@property voidBlock onGetStarted;
@property BOOL useLeftHand;
@property voidBlock onCancel;

@end
