//
//  VeridiumBiometrics4FExEnroller.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import "VeridiumBiometrics4FExCommon.h"

/*!
 Data class for holding the 4FEx enrollment config params
 */
@interface Veridium4FExEnrollConfig : NSObject

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
 **EXPERIMENTAL** Whether to compute a custom handguide based on the fov
 */
@property BOOL computeDefaultHandGuide;


/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

/*!
 The UI
 */
@property id<Veridium4FExEnrollerUIDelegate> _Nullable uiDelegate;


/*!
 Whether to use the left or right hand (defaults to Veridium4FExExportHandDefaultLeft)
 */
@property Veridium4FExHandChoiceEnroll enrollHand;

/*!
 Whether that the engine is using 4F Liveness (defaults to FALSE)
 */
@property BOOL useLiveness;

/*!
DEPRICATED
 Whether that the engine is using 2 shot 4FLiveness for authentication (defaults to FALSE)
 */
@property (readonly) BOOL twoShotLiveness;

/*!
 DEPRECATED
 Use passive liveness methods. (defaults to FALSE). //FIXME remove
 */
@property (readonly) BOOL passiveLiveness;

/*!
DEPRICATED
 Whether liveness is done horizonatally (defaults to TRUE)
 */
@property (readonly) BOOL livenessIsHorizontal;

/*!
DEPRICATED
 Use a lower pass requirment for liveness (defaults to FALSE)
 */
@property (readonly) BOOL laxLiveness;

/*!
 Tell 4F to keep its resources for a fast addional capture (defaults to FALSE) //FIXME remove this flag from here
 */
@property BOOL keepResource;

@end

/*!
 The 4FEx biometric enroller.
 */
@interface VeridiumBiometrics4FExEnroller : VeridiumBiometrics4FExCommon <VeridiumBioEnroller>

///*!
// Ask the biometric engine to perform biometric enrollment
// 
// @param setting   cpature setting
// @param onSuccess the success callback voidBlock
// @param onFail    the fail callback stringBlock; receives the failure reason
// @param onCancel  the cancell callback voidBlock
// @param onError   the error callback stringBlock; receives the error message
// */
//-(void) enrollWithConfig: (Veridium4FExEnrollConfig*) setting
//               onSuccess:(biometricVectorBlock _Nonnull) onSuccess
//                  onFail:(stringBlock _Nonnull) onFail
//                onCancel:(voidBlock _Nonnull) onCancel
//                 onError:(stringBlock _Nonnull) onError;


/*!
 Configure the enrollment
 
 @param config the Enroll4FExBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype)configure:(Veridium4FExEnrollConfig *)config;

/*!
 Update enrollment config
 
 @param config the Enroll4FExBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype)captureConfigUpdate:(Veridium4FExEnrollConfig *)config;

/*!
 The configuration for export
 */
@property (readonly) Veridium4FExEnrollConfig * _Nullable config;


@end



