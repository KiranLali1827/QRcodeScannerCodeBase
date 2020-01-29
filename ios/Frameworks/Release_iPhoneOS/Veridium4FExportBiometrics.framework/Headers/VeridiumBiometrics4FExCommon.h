//
//  VeridiumBiometrics4FExCommon.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import <VeridiumCore/VeridiumCore.h>
#import "Constants4FEx.h"


/*!
 Subprotocol of BiometricsUIDelegate which is the base of 4FEx UI protocols.
 
 Contains the methods & props common to enrollment, authentication, and export UI delegates */
@protocol Veridium4FExUIDelegate <VeridiumBiometricsUIDelegate>

/*!
 Ask the UI to present itself and waits for completion
 Show call must speciify what type of capture we are doing
 */
-(void) show:(voidBlock _Nonnull) doneBlock withThumb:(BOOL)captureThumb andIndividualCapture:(BOOL)individualCapture andIndividualThumb:(BOOL)thumbPresent andIndividualIndex:(BOOL)indexPresent andIndividualMiddle:(BOOL)middlePresent andIndividualRing:(BOOL)ringPresent andIndividualLittle:(BOOL)littlePresent;

/*!
 Ask UI to provide a view for displaying camera preview
 
 @return an initialized UIView
 */
-(UIView* _Nonnull) fourFPreviewView;

-(GuideDesign) handGuideType;


/*!
 Ask UI to handle the event of a photo beeing captured (by displaying it) and on the same time get from the UI the size of the view that displays the image.
 
 @param photoImage the capture photo UIImage
 */
-(void) handlePhotoCaptureUpdate:(UIImage* _Nullable) photoImage;

/*!
 Ask UI to handle finger finding.
 
 The most basic implementation should display a message like 'Searching for hand'
 */
-(void) handleSearchingForHand;

/*!
 Ask UI to handle the ROI info & assessment for a found hand during finger fingind phase
 
 In this case the UI should use the information in the roisInfo param to display the finger ROIs and the assessment message
 
 @param fingersInfo ROIsInfo instance that the UI should use to display the found fingers feedback during finger finding
 */
-(void) handleHandFoundForVideo:(Veridium4FExFingersInfo* _Nonnull) fingersInfo;


-(void)handleHandThumbForVideo: (BOOL) isThumbFound forROI:(CGRect)rect forIndividualROI:(CGRect)rectIndividual isThumb:(BOOL) isThumb;
-(void)handleHandThumbForPhoto:(CGRect)rect;

/*!
 Ask UI to handle the ROI info & assessment for a found hand during photo capture phase after the photo has been captured and fingers have been found in the captured image
 
 In this case the UI should use the information in the roisInfo param to display the finger ROIs and the assessment message
 
 @param fingersInfo ROIsInfo instance that the UI should use to display the found fingers feedback during photo capture
 */
-(void) handleHandFoundForPhoto:(Veridium4FExFingersInfo* _Nonnull) fingersInfo;


-(void) handleRetryCapture;


/*!
 Ask UI to handle the start of 4FEx photo capturing phase (usually by displaying a message like 'Capturing fingerprints. Please keep your hand still.')
 */
-(void) handleCapturing;
/*!
 Ask UI to handle the image processing event (usually by displaying a message like 'Processing. Please wait.')
 */
-(void) handleProcessing;

/*!
 Ask UI to ask your move their hand for liveness second shot
 */
-(void) handleTakeTwoShotLivenessSecond;

/*!
 Ask UI to update for the left or right hand
 
 @param useLeftHand `true` if user is exporting the left hand `false` otherwise
 @param takeSecondShot `true` if ask user for take second shot image for liveness
 @param targetFinger suitable enum value for target finger.
 @param canSwitch   `true` if the user can still switch hands `false` otherwise
 */
//-(void) handleUpdateUIForLeftHand:(BOOL)useLeftHand takeLivenessSecondShot:(BOOL) takeLivenessShiftShot targetFinger:(VeridiumFingerTargets)targetFinger canStillSwitch:(BOOL) canSwitch;

/*!
 Ask UI to update for the left or right hand
 
 @param guide image to display for the hand guide
 @param useLeftHand `true` if user is exporting the left hand `false` otherwise
 @param canSwitch   `true` if the user can still switch hands `false` otherwise
 */
-(void) handleUpdateUIWithHandGuide:(UIImage* _Nullable)guide isLeftHand:(BOOL)useLeftHand canStillSwitch:(BOOL) canSwitch;

-(void) turnOnThumbOverlaysForIsLeftHand:(BOOL)useLeftHand;

-(void) turnOnIndividualOverlaysFoIsLeftHand:(BOOL)useLeftHand forIndividualFingerCode:(int)fingerCode;

/*!
 Ask UI to handle a fail with error code
 
 @param code Code describing the error
 @param doneBlock
 */
-(void) handleFailwithCode:(int)code whenDone:(voidBlock _Nonnull )doneBlock;

@optional

-(void)handleShowProcessingScreen;

-(void)handleEndProcessingScreen: (voidBlock _Nonnull) completeBlock;

@end

/*!
 The Veridium4FExUIDelegate subprotocol with UI delegate methods & props specific to 4FEx enrollment
 */
@protocol Veridium4FExEnrollerUIDelegate <Veridium4FExUIDelegate>

/*!
 By calling this function the engine provides a callback block to be called by the UI when the user wants to switch between left and right hand (e.g. when the user taps on switch button).
 
 This method is called during the initialization of the engine (inside the enroll function)
 
 The block is to be stored by the implementor of the protocol and used later when the user performs that action.
 
 This will only have effect before the first template has been captured. Afterwards it will be ignored (because all templates must be from the same hand)
 
 @param userWantsToUseLeftHandActionBlock The callback block to be stored by the UI and called when the user wants to switch hands (eg. taps on a button)
 */
-(void) connectSwitchHandActionBlock:(boolBlock _Nonnull ) userWantsToUseLeftHandActionBlock;

/*!
 Ask the to confirm the captured picture
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not the capture
 */
-(void) handleTakeVerifyPicture:(boolBlock _Nonnull) accepted;


/*!
 Ask the user to confirm enrollment completion
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not
 */
-(void) handleEnrollDone:(boolBlock _Nonnull)accepted;

/*!
 Ask UI to update the progress of the enrolled 4FEx templates over the total number of 4FEx templates to enroll
 
 @param numberOfEnrolledTEmplates the number of enrolled templates
 @param total                     the total number of templates to enroll
 */
-(void) handleEnrollProgress:(NSInteger)numberOfEnrolledTEmplates totalNumberOfTemplates:(NSInteger) total;

@optional

/*!
 Ask UI to prompt the user to decide what action to continue with in case of a enrollment validation failure (ie. on of the enrolled templates failed to verify against the already enrolled ones)
 
 The UI should present a 3-way choice: 
 1. Retry - for retrying the last validation
 2. Restart - for restarting the entire enrollment process
 3. Cancel - for cancelling the enrollment
 
 @param retryBlock   callback for when the user decides to retry the validation
 @param restartBlock callback for when the user decides to restart enrollment
 @param cancelBlock  callback for when the user decides to cancel the enrollment
 */
-(void) handleVerifyFailDecisionWithRetry:(voidBlock _Nonnull) retryBlock restart:(voidBlock _Nonnull) restartBlock cancel:(voidBlock _Nonnull) cancelBlock;

- (NSString * _Nullable) className;

@end


/*!
 The Veridium4FExUIDelegate subprotocol with UI delegate methods & props specific to 4FEx authentication
 */
@protocol Veridium4FExAuthenticatorUIDelegate <Veridium4FExUIDelegate>

@optional
- (NSString * _Nullable) className;
@end


/*!
 The Veridium4FExUIDelegate subprotocol with UI delegate methods & props specific to 4FEx export
 */
@protocol Veridium4FExExporterUIDelegate <Veridium4FExUIDelegate>

/*!
 By calling this function the engine provides a callback block to be called by the UI when the user wants to switch between left and right hand (e.g. when the user taps on switch button).
 
 This method is called during the initialization of the engine (inside the export function)
 
 The block is to be stored by the implementor of the protocol and used later when the user performs that action.
 
 This will only have effect before the first template has been captured. Afterwards it will be ignored (because all templates must be from the same hand)
 
 @param userWantsToUseLeftHandActionBlock The callback block to be stored by the UI and called when the user wants to switch hands (eg. taps on a button)
 */
-(void) connectSwitchHandActionBlock:(boolBlock _Nonnull) userWantsToUseLeftHandActionBlock;

/*
 Ask the UI to instruct the user to switch hand.
 */
-(void) handleRequestUserSwitchHand:(voidBlock _Nonnull)onNext onCancel:(voidBlock _Nonnull)onCancel;

/*!
 
 Ask the user to confirm exportment completion
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not
 */
-(void) handleExportDone:(boolBlock _Nonnull)accepted;



-(void)handleShowIndividualFingerNextWithFingerCode:(int)fingerCode andBlock:(voidBlock _Nonnull)blockToProgress;

/*!
 Ask UI to update the progress of the exported 4FEx templates over the total number of 4FEx templates to export
 
 @param numberOfExportedTemplates the number of exported templates
 @param total                     the total number of templates to export
 */
-(void) handleExportProgress:(NSInteger)numberOfExportedTemplates totalNumberOfTemplates:(NSInteger) total;

@optional

- (NSString * _Nullable) className;

@end

/*!
 Common abstract class parent for the VeridiumBiometrics4FExAuthenticator & VeridiumBiometrics4FExEnroller
 */
@interface VeridiumBiometrics4FExCommon : NSObject

+(NSString * _Nonnull)libVersion;

+(BOOL)checkIfSuppressingAllScreens;

@property NSMutableDictionary* _Nullable resourceDict;

@end
