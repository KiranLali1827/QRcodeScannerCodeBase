//
//  VeridiumCancelConfirmerViewController.h
//  Veridium4FUI
//
//  Created by Paul Paul on 2/20/18.
//  Copyright © 2018 VeridiumID. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface VeridiumCancelConfirmerViewController : UIViewController

+(instancetype)initiate;

@property NSString* message;
@property voidBlock onOK;
@property voidBlock onCancel;

@end
