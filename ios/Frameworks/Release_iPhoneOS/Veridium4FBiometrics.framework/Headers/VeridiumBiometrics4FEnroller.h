//
//  VeridiumBiometrics4FEnroller.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 HoyosLabs. All rights reserved.
//

#import "VeridiumBiometrics4FCommon.h"

/*!
 Data class for holding the 4F enrollment config params
 */
@interface Veridium4FEnrollConfig : NSObject

/*!
 Number of templates to enroll (defaults to 2)
 
 **_Note:_** Cannot be lower than 2
 */
@property NSInteger templatesToEnroll;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;
/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;


/*!
 Whether to reset timing after each successfully captured template 
 (defaults to TRUE)
 */
@property BOOL resetTimeoutAfterSuccessfulCapture;

/*!
 **EXPERIMENTAL** Whether to compute a custom handguide based on the user's fingers pattern after first enrolled template
 */
@property BOOL computeCustomHandGuide;

/*!
 The photo capture mode used when taking a picture, defaults to `Veridium4FPhotoCaptureModeTorch`. 
 See `Veridium4FPhotoCaptureMode` enum.
 */
@property Veridium4FPhotoCaptureMode captureMode;

/*!
 The UI
 */
@property id<Veridium4FEnrollerUIDelegate> uiDelegate;

/*!
 Defaults to `Veridium4FHandChoiceEitherHandEnroll`.
 */
@property Veridium4FHandChoiceEnroll enrollHand;

@end


/*!
 The 4F biometric enroller.
 */
@interface VeridiumBiometrics4FEnroller : VeridiumBiometrics4FCommon <VeridiumBioEnroller>

/*!
 Configure the enrollment
 
 @param config the Enroll4FBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype)configure:(Veridium4FEnrollConfig *)config;

/*!
 The configured Enroll4FBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property (readonly) Veridium4FEnrollConfig* config;

@end



