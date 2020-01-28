//
//  VeridiumDefault4FExLivenessViewController.h
//  VeridiumDefault4FExportUI
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface VeridiumDefault4FExLivenessViewController : UIViewController

@property (strong, nonatomic) voidBlock onOk;
@property (strong, nonatomic) voidBlock onCancel;
@property BOOL isHorz;
@end
