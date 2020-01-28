//
//  VeridiumDefault4FExViewController.h
//  VeridiumDefault4FExportUI
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#ifndef VeridiumDefault4FExViewController_h
#define VeridiumDefault4FExViewController_h

@import VeridiumCore;
@import Veridium4FExportBiometrics;

@interface VeridiumDefault4FExViewController : UIViewController <Veridium4FExEnrollerUIDelegate, Veridium4FExExporterUIDelegate, Veridium4FExAuthenticatorUIDelegate>{
    
@public BOOL viewControllerIsForAuth;
@public BOOL viewControllerIsForExport;
@public BOOL viewControllerIsForEnroll;
    
}

+(__weak instancetype _Nullable) createFromStoryboard:(UIStoryboard* _Nullable)storyboard withIdentifier:(NSString* _Nonnull)identifier forAuthMode:(bool)isForAuth;

+(instancetype _Nullable) createDefaultAuthenticator;
+(instancetype _Nullable) createDefaultEnroller;
+(instancetype _Nullable) createDefaultExporter;


//New methods to override
+(UIStoryboard* _Nullable) getMain4FExStoryboard;

-(UIStoryboard*) getIntro4FExStoryboard;

-(UIStoryboard*) getProcessing4FExStoryboard;

-(UIStoryboard*) getDialogStoryboard;

-(UIStoryboard*) getIndividualIntroStoryboard;

-(UIStoryboard*) getThumbIntroStoryboard;

-(UIStoryboard*) getLivenessFailedStoryboard;

-(void)handleHandThumbForVideo: (BOOL) isThumbFound forROI:(CGRect)rectThumb forIndividualROI:(CGRect)rectIndividual isThumb:(BOOL) isThumb;

-(void)handleHandFoundForVideo:(Veridium4FExFingersInfo *)roisInfo;

-(void) drawROI:(NSInteger) roiIndex inView:(UIView*) view rect:(CGRect) rect withColor:(UIColor*) color;

-(void) drawThumbROI:(UIView *)view forThumbFound:(BOOL) isThumbFound forROI:(CGRect)rect;

-(GuideDesign) handGuideType;


-(BOOL) useMeter;

-(BOOL) useArrows;

-(BOOL) useIndividualFingerIndicatorImage;

@end

#endif /* VeridiumDefault4FExViewController_h */
