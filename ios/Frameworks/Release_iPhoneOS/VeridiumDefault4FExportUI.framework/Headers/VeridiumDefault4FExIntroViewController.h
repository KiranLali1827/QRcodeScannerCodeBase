//
//  VeridiumDefault4FExIntroViewController.h
//  VeridiumBiometricsUI
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface VeridiumDefault4FExIntroViewController : UIViewController

@property (nonatomic) NSString* headingText;
@property (strong, nonatomic) voidBlock onOk;
@property (strong, nonatomic) voidBlock onCancel;

@end
