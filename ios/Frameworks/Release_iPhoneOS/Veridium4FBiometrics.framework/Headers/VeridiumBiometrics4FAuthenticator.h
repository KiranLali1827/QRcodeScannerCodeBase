//
//  VeridiumBiometrics4FAuthenticator.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 HoyosLabs. All rights reserved.
//

#import "VeridiumBiometrics4FCommon.h"
/*!
 Data class for holding the 4F authentication config params
 */
@interface Veridium4FAuthenticationConfig : NSObject

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
 The photo capture mode used when taking a picture, defaults to `Veridium4FPhotoCaptureModeTorch`. See `Veridium4FPhotoCaptureMode` enum.
 */
@property Veridium4FPhotoCaptureMode captureMode;

/*!
 Whether that the engine is using 4FLiveness for authentication (defaults to FALSE)
 */
@property BOOL useLiveness;

/*!
 Property indicating whether the 4F Authentication Engine should send force UI update to the UI delegate.
 This should be used only when enrolling both hands and want to force the authentication on either hand.
 Defaults to `Veridium4FAuthenticationFromMatchingStrategy`.
 */
@property Veridium4FAuthenticationHand authenticationHand;

/*!
 The UI
 */
@property (nullable) id<Veridium4FAuthenticatorUIDelegate> uiDelegate;



@end

/*!
 The 4F biometric authenticator.
 */
@interface VeridiumBiometrics4FAuthenticator : VeridiumBiometrics4FCommon <VeridiumBioAuthenticator>

/*!
 Configure the authentication
 
 @param config the Authenticate4FBioEngineConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)configure:(Veridium4FAuthenticationConfig * _Nonnull)config;

/*!
 The configured Authenticate4FBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property(readonly, nonnull) Veridium4FAuthenticationConfig* config;


@end

