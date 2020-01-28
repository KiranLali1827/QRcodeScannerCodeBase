//
//  VeridiumSDK+4F.h
//  Veridium4FBiometrics
//
//  Created by Catalin Stoica on 04/07/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
@import VeridiumCore;
#import "VeridiumBiometrics4FAuthenticator.h"
#import "VeridiumBiometrics4FEnroller.h"

/*!
 SDK 4F additions
 */
@interface VeridiumSDK (FourFAdditions)

/*!
 Property returning 4F Library version as NSString
 */
@property (readonly, nonnull) NSString* lib4FVersion;


/*!
 Helper method which prints in the DebugConsole the version of the 4F Library
 */
-(void)log4FBiometricsVersion;

/*!
 Property will return YES if the decive is 4F capable NO otherwise
 */
@property (class, readonly) BOOL isDevice4FCapable;

/*!
 Register a 4F authenticator with a custom UI
 
 @param ui the custom UI
 */
-(void)register4FAuthenticator:(id<Veridium4FAuthenticatorUIDelegate> _Nonnull)ui;

/*!
 Register a 4F enroller with a custom UI
 
 @param ui the custom UI
 */
-(void) register4FEnroller:(id<Veridium4FEnrollerUIDelegate> _Nonnull)ui;

/*!
 Helper method to configure the registered 4F authenticator
 
 @param config the config
 */
-(void)configure4FAuthenticator:(Veridium4FAuthenticationConfig* _Nonnull)config;

/*!
 Helper method for grabbing the registered 4F authenticator
 
 @return the registered 4F authenticator (or nil if not registered)
 */
@property (readonly, nullable) VeridiumBiometrics4FAuthenticator* authenticator4F;

/*!
 Helper method to configure the registered 4F enroller
 
 @param config the config
 */
-(void)configure4FEnroler:(Veridium4FEnrollConfig * _Nonnull)config;

/*!
 Helper method for grabbing the registered 4F enroller
 
 @return the registered 4F enroller (or nil if not registered)
 */
@property (readonly, nullable) VeridiumBiometrics4FEnroller* enroller4F;


/*!
 Helper method for creating a 4F enroller and configure it in one single call
 
 @param config the config
 
 @return the created and configured 4F enroller
 */
-(VeridiumBiometrics4FEnroller* _Nonnull) create4FEnrollerWithConfig:(Veridium4FEnrollConfig * _Nonnull) config;

/*!
 Helper method for creating a 4F authenticator and configure it in one single call
 
 @param config the config
 
 @return the created and configured 4F authenticator
 */
-(VeridiumBiometrics4FAuthenticator* _Nonnull) create4FAuthenticatorWithConfig:(Veridium4FAuthenticationConfig * _Nonnull) config;

/*!
 4F Library setup helper.

 @param license the license
 @param torchOrFlash whether the 4F library should use torch or flash. 1 is for torch 0 is for flash.
 @return the setup status.
 */
-(Veridium4FLicenseStatus* _Nonnull)setupLib4FWithLicense:(NSString* _Nonnull)license
                                          useTorchOrFlash:(int)torchOrFlash;

@end

@interface VeridiumBiometrics4FEnroller (Additions)

/*!
  Helper method for merging two 4F Biometrics enrollment vectors.

 @param firstVector   the first vector
 @param secondVector  the second vector
 @return the new vector if operation was successful, nil otherwise.
 */
+(VeridiumBiometricFullVector * _Nullable)mergeVectors:(VeridiumBiometricFullVector * _Nonnull)firstVector secondVector:(VeridiumBiometricFullVector * _Nonnull)secondVector;

@end
