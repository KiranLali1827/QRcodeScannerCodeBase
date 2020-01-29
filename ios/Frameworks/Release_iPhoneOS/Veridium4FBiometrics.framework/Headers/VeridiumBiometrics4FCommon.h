//
//  VeridiumBiometrics4FCommon.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 HoyosLabs. All rights reserved.
//


//@import VeridiumCore;
#import <VeridiumCore/VeridiumCore.h>
#import "Constants.h"


/*!
 Subprotocol of BiometricsUIDelegate which is the base of 4F UI protocols.
 
 Contains the methods & props common to both enrollment & authentication UI delegates */
@protocol Veridium4FUIDelegate <VeridiumBiometricsUIDelegate>

/*!
 Ask UI to provide a view for displaying camera preview
 
 @return an initialized UIView
 */
-(UIView* _Nonnull) fourFPreviewView;

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
-(void) handleHandFoundForVideo:(Veridium4FFingersInfo* _Nonnull) fingersInfo;

/*!
 Ask UI to handle the ROI info & assessment for a found hand during photo capture phase after the photo has been captured and fingers have been found in the captured image
 
 In this case the UI should use the information in the roisInfo param to display the finger ROIs and the assessment message
 
 @param fingersInfo ROIsInfo instance that the UI should use to display the found fingers feedback during photo capture
 */
-(void) handleHandFoundForPhoto:(Veridium4FFingersInfo* _Nonnull) fingersInfo;

/*!
 Ask UI to handle the start of 4F photo capturing phase (usually by displaying a message like 'Capturing fingerprints. Please keep your hand still.')
 */
-(void) handleCapturing;
/*!
   Ask UI to handle the image processing event (usually by displaying a message like 'Processing. Please wait.')
 */
-(void) handleProcessing;


@optional

/*!
 Ask UI to handle any capture error. If method is not implemented the SDK will provide feedback for any occurred errors.

 @param error       the error callback holding the infomation regarding the capture error.
 @param retryBlock  the block which restarts the hole biometric process.
 @param cancelBlock the block which cancels the biometric process.
 */
-(void) handleCaptureError:(NSError*_Nullable)error withRetry:(voidBlock _Nonnull) retryBlock cancel:(voidBlock _Nonnull)cancelBlock;

@end

/*!
 The Veridium4FUIDelegate subprotocol with UI delegate methods & props specific to 4F enrollment
 */
@protocol Veridium4FEnrollerUIDelegate <Veridium4FUIDelegate>

/*!
 By calling this function the engine provides a callback block to be called by the UI when the user wants to switch between left and right hand (e.g. when the user taps on switch button).
 
 This method is called during the initialization of the engine (inside the enroll function)
 
 The block is to be stored by the implementor of the protocol and used later when the user performs that action.

 This will only have effect before the first template has been captured. Afterwards it will be ignored (because all templates must be from the same hand)
 
 @param userWantsToUseLeftHandActionBlock The callback block to be stored by the UI and called when the user wants to switch hands (eg. taps on a button)
 */
-(void) connectSwitchHandActionBlock:(boolBlock _Nonnull) userWantsToUseLeftHandActionBlock;

/*!
 Ask UI to update for the left or right enrolling hand
 
 @param useLeftHand `true` if user is enrolling the left hand `false` otherwise
 @param canSwitch   `true` if the user can still switch hands `false` otherwise
 */
-(void) handleUpdateUIForLeftHand:(BOOL)useLeftHand canStillSwitch:(BOOL) canSwitch;

/*!
 Ask the to confirm the captured picture
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not the capture
 */
-(void) handleTakeVerifyPicture:(boolBlock _Nonnull)accepted;

/*!
 
 Ask the user to confirm enrollment completion
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not
 */
-(void) handleEnrollDone:(boolBlock _Nonnull)accepted;

/*!
 Ask UI to update the progress of the enrolled 4F templates over the total number of 4F templates to enroll
 
 @param numberOfEnrolledTEmplates the number of enrolled templates
 @param total                     the total number of templates to enroll
 */
-(void) handleEnrollProgress:(NSInteger)numberOfEnrolledTEmplates totalNumberOfTemplates:(NSInteger) total;

/*!
 Ask UI to handle updates for a specific forced hand by config.
 
 @param hand  the hand
 */
-(void)updateUIForEnrollmentHand:(Veridium4FHandChoiceEnroll)hand;

@optional

/*!
 Ask UI to promt the user to decide the hand configuration for enrolment.
 
 @param handChoiceBlock callback for when the user decides to pick hand for enrolment
 @param cancelBlock     callback for when the user decides to cancel the enrollment
 */
-(void) handleHandConfigurationForEnrollment:(void (^_Nonnull)(Veridium4FHandChoiceEnroll)) handChoiceBlock cancel:(voidBlock _Nonnull) cancelBlock;

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

/*!
 Ask UI to update the fingers guide 
 (Only if the enroller is configured to use the custom handguide)
 
 @param image the new handguide image
 */
-(void) updateFingersGuide:(UIImage* _Nonnull) image;
@end


/*!
 The Veridium4FUIDelegate subprotocol with UI delegate methods & props specific to 4F authentication
 */
@protocol Veridium4FAuthenticatorUIDelegate <Veridium4FUIDelegate>

/**
 *  This function will handle the update of the UI to left hand/right hand for 4F authentication depending on what hand has been used on enrollment
 *
 *  @param useLeftHand If this parameter is set to true the standard template for left hand 4f authentication is used.
 */

/*!
 Ask UI to update when the engine has successfuly set the authentication hand
 
 @param useLeftHand `true` if user will use the left hand when authenticating, `false` otherwise
 */
-(void) handleUpdateUIForLeftHand:(BOOL)useLeftHand;

/*!
 Ask UI to update itself for the authentication reason (e.g. update a label)
 
 @param reason the authentication reason
 */
-(void) handleUpdateUIForAuthReason:(NSString* _Nonnull) reason;

/*!
 Engine will ask UI to update itself for a specific hand when the hand is specified from the enrollment config.

 @param hand the hand to be enrolled
 */
-(void) updateUIForAuthenticationHand:(Veridium4FAuthenticationHand)hand;

@optional

/*!
 Ask UI to update the handguide image overlay
 (Only if the authenticator is configured to use the custom handguide)
 
 @param handGuide the handguide image
 */
-(void) handleUpdateUIForHandGuide:(UIImage* _Nonnull) handGuide;

/*!
 Ask UI to update the handguide for 4F Liveness
 (Only if the authenticator is configured to use 4F Liveness)
 
 @param doneBlock the block to be called when the UI updates are done
 */
-(void) handleUpdateUIFor4FLiveness:(voidBlock _Nonnull)doneBlock;


@end

/*!
 Common abstract class parent for the VeridiumBiometrics4FAuthenticator & VeridiumBiometrics4FEnroller
 */
@interface VeridiumBiometrics4FCommon : NSObject

@end
