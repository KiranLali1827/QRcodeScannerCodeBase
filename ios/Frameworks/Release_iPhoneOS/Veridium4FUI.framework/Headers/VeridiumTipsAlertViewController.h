//
//  VeridiumTipsAlertViewController.h
//  Veridium4FUI
//
//  Created by Paul Paul on 1/29/18.
//  Copyright © 2018 VeridiumID. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface VeridiumTipsAlertViewController : UIViewController

+(instancetype)initiate;

@property (weak, nonatomic) IBOutlet UIView *holderView;

@property voidBlock onOk;

@end
