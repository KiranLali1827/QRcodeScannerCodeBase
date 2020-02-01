//
//  ViewControllerPolicy.m
//  VeridiumExportEnrollDemo
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//


#import "ViewControllerPolicy.h"
@import VeridiumCore;
@import Veridium4FExportBiometrics;

@interface ViewControllerPolicy () {
}

@property (weak, nonatomic) IBOutlet UIView *backgroundExportView;
@property (weak, nonatomic) IBOutlet UITextView *scrollableExportText;

@end

@implementation ViewControllerPolicy

- (void)viewDidLoad {
    [super viewDidLoad];
    [_scrollableExportText setEditable:NO];
    _backgroundExportView.backgroundColor = [UIColor colorWithRed:0/255.0 green:0/255.0 blue:0/255.0 alpha:0.7];
    
}

- (void)viewDidLayoutSubviews {
    [self.scrollableExportText setContentOffset:CGPointZero animated:NO];
}

- (IBAction)onContinuePrivacyExportPressed{
    _backgroundExportView.backgroundColor = [UIColor colorWithRed:0/255.0 green:0/255.0 blue:0/255.0 alpha:0];
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
