//
//  VeridiumBiometrics4FExAuthenticator.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import "VeridiumBiometrics4FExCommon.h"

/*!
 Data class for holding the 4FEx authentication config params
 */
@interface Veridium4FExAuthenticationConfig : NSObject

/*!
 Whether to use the left or right hand (defaults to TRUE)
 */
@property Veridium4FExAuthenticationHand authenticationHand;

/*!
 The allowed number of retries in case the authentication fails (defaults to 0)
 */
@property NSInteger numberOfRetries;

/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;


/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

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
 Whether liveness is done horizonatally (defaults to TRUE)
 We still use this in order to do enrol and export
 */
@property (readonly) BOOL livenessIsHorizontal;

/*!
DEPRICATED
 Use a lower pass requirment for liveness (defaults to FALSE)
 */
@property (readonly) BOOL laxLiveness;


/*!
 The UI
 */
@property (nullable) id<Veridium4FExAuthenticatorUIDelegate> uiDelegate;


@end

/*!
 The 4FEx biometric authenticator.
 */
@interface VeridiumBiometrics4FExAuthenticator : VeridiumBiometrics4FExCommon <VeridiumBioAuthenticator>

/*!
 Configure the authentication
 
 @param config the Authenticate4FExBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)configure:(Veridium4FExAuthenticationConfig * _Nonnull)config;

/*!
 Update enrollment config
 
 @param config the Authenticate4FExBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)captureConfigUpdate:(Veridium4FExAuthenticationConfig * _Nonnull)config;


/*!
 The configured Authenticate4FExBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property(readonly, nonnull) Veridium4FExAuthenticationConfig* config;


/*!
 Query which hand is configured for authentication -> dependant on the enrollment.
 */
-(BOOL)useLeftHand;


@end

