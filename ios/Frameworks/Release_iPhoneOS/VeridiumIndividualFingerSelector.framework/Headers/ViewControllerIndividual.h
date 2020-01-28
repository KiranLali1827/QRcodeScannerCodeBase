//
//  ViewControllerIndividual.h
//  VeridiumTouchlessShowcase
//
//  Created by Lewis Carney on 27/09/2017.
//  Copyright © 2018 Veridium Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@import Veridium4FExportBiometrics;

@class ViewControllerIndividual;

@protocol ViewControllerIndividualDelegate <NSObject>
- (void)getItemsFromViewControllerAndStartIndividual:(ViewControllerIndividual *)controller withExportConfig:(VeridiumBiometrics4FConfig *)config ;
@end



@interface ViewControllerIndividual: UIViewController

@property (nonatomic, weak) id <ViewControllerIndividualDelegate> delegate;
@property (nonatomic) VeridiumBiometrics4FConfig* exportConfig;
@property (nonatomic) bool thumbIndividual;
@property (nonatomic) bool indexIndividual;
@property (nonatomic) bool middleIndividual;
@property (nonatomic) bool ringIndividual;
@property (nonatomic) bool littleIndividual;
@property (nonatomic) bool isRightHand;

+(UIImage*) colorizeImage:(UIImage *)baseImage color:(UIColor *)theColor;
+(UIImage*) imageByName:(NSString*)imageName withBundleIndentifier:(NSString *)bundleID;

@end
