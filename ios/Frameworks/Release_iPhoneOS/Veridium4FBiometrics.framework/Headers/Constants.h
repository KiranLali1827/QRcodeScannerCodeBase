//
//  Constants.h
//  Veridium4FBiometrics
//
//  Created by razvan on 9/12/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#import <Foundation/Foundation.h>
#import <VeridiumCore/VeridiumCore.h>

#define kVeridiumBiometricEngineName4F @"4F"

/*!
 Constants for the hand the engine should use for authentication. When this is set to the authentication config the authenticator will call UI updates to the UI delegate for the specified hand.
 */
typedef NS_ENUM(NSInteger, Veridium4FAuthenticationHand) {
  Veridium4FAuthenticationLeftHand = 0,
  Veridium4FAuthenticationRightHand,
  Veridium4FAuthenticationFromMatchingStrategy
};

/*!
 Constants for the hand the engine should use for enrollment. The 4F engine will call UI updates accordingly with the chosen value.
 */
typedef NS_ENUM(NSInteger, Veridium4FHandChoiceEnroll) {
  Veridium4FHandChoiceForceLeftHandEnroll = 0,
  Veridium4FHandChoiceForceRightHandEnroll,
  Veridium4FHandChoiceEitherHandEnroll,
  Veridium4FHandChoiceBothHands
};


/*!
 @enum Veridium4FPhotoCaptureMode
 @abstract
 Constants for the 4F photo capture mode and forced captured mode on devices with no Flash/Torch hardware support.
 Usage of `Veridium4FPhotoCaptureModeTorchIfAvailable` and `Veridium4FPhotoCaptureModeTorchIfAvailable` are only for iPad/iPod device(s) which usually don't have Flash/Torch hardware support.
 
 @constant Veridium4FPhotoCaptureModeTorch
 Use capture the picture using Torch, exclusively on devices with Flash/Torch hardware support.
 @constant Veridium4FPhotoCaptureModeFlash
 Use capture the picture using Flash, exclusively on devices with Flash/Torch hardware support.
 @constant Veridium4FPhotoCaptureModeTorchIfAvailable
 Use capture the picture using Torch, exclusively on devices without Flash/Torch hardware support.
 @constant Veridium4FPhotoCaptureModeFlashIfAvailable
 Use capture the picture using Flash, exclusively on devices without Flash/Torch hardware support.
 */
typedef NS_ENUM(NSInteger, Veridium4FPhotoCaptureMode) {
  Veridium4FPhotoCaptureModeTorch = 1,
  Veridium4FPhotoCaptureModeFlash,
  Veridium4FPhotoCaptureModeTorchIfAvailable,
  Veridium4FPhotoCaptureModeFlashIfAvailable,
};

/*!
 @enum Veridium4FFingersAssessment
 @abstract
 Constants for the 4F finger assesment results.
 
 @constant Veridium4FFingersAssessmentNotOK
 Fingers not found
 @constant Veridium4FFingersAssessmentOutOfFocus
 Fingers out of focus
 @constant Veridium4FFingersAssessmentStable
 Fingers are stable, picture can be taken.
 @constant Veridium4FFingersAssessmentTooClose
 Fingers are too close
 @constant Veridium4FFingersAssessmentTooFar
 Fingers are too far from the camera
 @constant Veridium4FFingersAssessmentTooFarApart
 Fingers are too far apart from each other
 @constant Veridium4FFingersAssessmentTooHigh
 Fingers are at the top of the preview
 @constant Veridium4FFingersAssessmentTooLow
 Fingers are at the bottom of the preview
 @constant Veridium4FFingersAssessmentTooFarLeft
 Fingers are at on left side of the preview
 @constant Veridium4FFingersAssessmentTooFarRight
 Fingers are at on right side of the preview
 */
typedef enum : NSUInteger {
  Veridium4FFingersAssessmentNotOK = 0,
  Veridium4FFingersAssessmentOutOfFocus,
  Veridium4FFingersAssessmentStable,
  Veridium4FFingersAssessmentTooClose,
  Veridium4FFingersAssessmentTooFar,
  Veridium4FFingersAssessmentTooFarApart,
  Veridium4FFingersAssessmentTooHigh,
  Veridium4FFingersAssessmentTooLow,
  Veridium4FFingersAssessmentTooFarLeft,
  Veridium4FFingersAssessmentTooFarRight
} Veridium4FFingersAssessment;

typedef enum : NSUInteger {
    TargetFingerNone = 0,
    TargetFingerInvalid = 1,
    TargetFingerIndexMiddle = 2,
    TargetFingerRingLittle= 3,
    TargetFingerMiddleRing = 4,
    TargetFingerThumb = 5,
    TargetFingerIndividual = 6
} VeridiumFingerTargets;

typedef enum : NSUInteger {
    CoarseGrainSweep = 0,
    FineGrainSweep
} VeridiumFocusSweepStage;


#define Veridium4FFingersAssessmentStrings @[\
NSLocalizedStringFromTable(@"Please keep your hand still with the fingers inside the guide", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your fingers are out of focus.\nPlease adjust your hand distance from the camera", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Perfect.\nKeep your hand still.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your hand is too close to the camera.\nPlease move your hand farther.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your hand is too far from the camera.\nPlease move you hand closer.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Please keep your fingers closer together.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your hand is too high.\nPlease move your hand towards the center.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your hand is too low.\nPlease move your hand towards the center.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your hand is too far to the left.\nPlease move your hand towards the center.", @"Veridium4F", nil),\
NSLocalizedStringFromTable(@"Your hand is too far to the right.\nPlease move your hand towards the center.", @"Veridium4F", nil)]

#define Veridium4FFingersAssessmentColors @[\
[UIColor colorWithRed:0 green:0 blue:1 alpha:0.5],\
[UIColor colorWithWhite:0 alpha:0.5],\
[UIColor colorWithRed:0 green:1 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:1 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:1 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:1 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:1 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:1 alpha:0.5]]

@interface Veridium4FFingerCoordinates: NSObject

/*!
 The 2D coordinates for the 1st finger.
 */
@property CGRect finger1;
/*!
 The 2D coordinates for the 2nd finger.
 */
@property CGRect finger2;
/*!
 The 2D coordinates for the 3rd finger.
 */
@property CGRect finger3;
/*!
 The 2D coordinates for the 4th finger.
 */
@property CGRect finger4;

@end

/*!
 Data class used by 4F to send the finger ROIs (Region Of Interest) and additional info during the finger finding phase and in the capture phase to its UI delegate.
 
 The UI should use this information to display the fingers information and display finger overlays
 
 */

@interface Veridium4FFingersInfo: NSObject

/*!
 The recommended color for the finger rectangles ROI display.
 */
@property (nonnull) UIColor* color;
/*!
 Finger ROIs assesment mesage to provide hints to the user (hand to close, hand too far, etc.)
 */
@property (nullable) NSString* assessmentMessage;

/*!
 A constant value of finger finder assessment on the capture
 */
@property Veridium4FFingersAssessment assessment;

/*!
 The hand distance from the camera. The value range is -250 to 250. Values between -100 and 100 are good, outside that are bad.
 Negative values indicate the hand is too far, positive values otherwise.
 */
@property NSInteger distanceInfo;

/*!
 The size of the image the finger data is based upon
 */
@property CGSize handPictureSize;

/*!
 Class initializer

 @param rois an array with the rois
 @param assessment the assesment
 @param handPictureSize the hand picture size
 @return constructed object
 */
-(instancetype _Nonnull)initWithFingerROIs:(NSArray<NSNumber*>* _Nonnull) rois //int[16]
                         fingersAssessment:(Veridium4FFingersAssessment) assessment
                           handPictureSize:(CGSize) handPictureSize
                              distanceInfo:(NSInteger)distance;


/*!
 Returns the finger rects converted from the coordinates of the source picture (handPictureSize) to coordinates in the frame of the target view size (i.e. the view that displays the picture and the finger overlays)
 
 This method should be used by the UI delegates to display the finger overlays on both video and picture updates.
 
 @param targetSize the size of the target view's frame
 
 @return an instance of the Veridium4FFingerCoordinates with the finger rects coordinates in the target view's frame
 */
-(Veridium4FFingerCoordinates* _Nonnull) fingerCoordinatesForTargetSize:(CGSize) targetSize;

@end

@interface Veridium4FLicenseStatus : VeridiumLicenseStatus

/*!
 Whether the 4F library is allowed to perform liveness authentication.
 */
@property (readonly) BOOL isLivenessCapable;

/*!
 Whether the 4F library has liveness mandatory.
 */
@property (readonly) BOOL isLivenessMandatory;


@end  

#endif /* Constants_h */
