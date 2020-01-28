//
//  VeridiumSDK+4FEx.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
@import VeridiumCore;
#import "VeridiumBiometrics4FExAuthenticator.h"
#import "VeridiumBiometrics4FExEnroller.h"
#import "VeridiumBiometrics4FExExporter.h"
#import "VeridiumBiometrics4FExService.h"

/*!
 SDK 4FEx additions
 */
@interface VeridiumSDK (FourFAdditions)

/*!
 Property returning 4FEx Library version as NSString
 */
@property (readonly, nonnull) NSString* lib4FExVersion;


/*!
 Helper method which prints in the DebugConsole the version of the 4FEx Library
 */
-(void)log4FExBiometricsVersion;

@property (class, readonly) BOOL isDevice4FExCapable;

/*!
 Setup 4F Export with a licence
 
 @param licence 4F licence that includes export
 */
-(Veridium4FExLicenseStatus *_Nullable)setup4FExportWithLicence:(NSString *)licence;

/*!
 Register a 4FEx authenticator with a custom UI
 
 @param ui the custom UI
 */
-(void)register4FExAuthenticator:(id<Veridium4FExAuthenticatorUIDelegate> _Nonnull)ui;
/*!
 Register a 4FEx enroller with a custom UI
 
 @param ui the custom UI
 */
-(void) register4FExEnroller:(id<Veridium4FExEnrollerUIDelegate> _Nonnull)ui;

/*!
 Register a 4FEx exporter with a custom UI
 
 @param ui the custom UI
 */
-(void) register4FExExporter:(id<Veridium4FExExporterUIDelegate> _Nonnull)ui;


/*!
 Helper method to configure the registered 4FEx authenticator
 
 @param config the config
 */
-(void)configure4FExAuthenticator:(Veridium4FExAuthenticationConfig* _Nonnull)config;

/*!
 Helper method for grabbing the registered 4FEx authenticator
 
 @return the registered 4FEx authenticator (or nil if not registered)
 */
-(VeridiumBiometrics4FExAuthenticator* _Nullable) authenticator4FEx;

/*!
 Helper method to configure the registered 4FEx enroller
 
 @param config the config
 */
-(void)configure4FExEnroler:(Veridium4FExEnrollConfig * _Nonnull)config;

/*!
 Helper method for grabbing the registered 4FEx enroller
 
 @return the registered 4FEx enroller (or nil if not registered)
 */
-(VeridiumBiometrics4FExEnroller* _Nullable) enroller4FEx;

/*!
 Helper method to configure the registered 4FEx exporter
 
 @param config the config
 */
-(void)configure4FExExporter:(Veridium4FExExportConfig * _Nonnull)config;

/*!
 Helper method for grabbing the registered 4FEx explorter
 
 @return the registered 4FEx exporter (or nil if not registered)
 */
-(VeridiumBiometrics4FExExporter* _Nullable) exporter4FEx;

/*!
 Helper method for creating a 4FEx enroller and configure it in one single call
 
 @param config the config
 
 @return the created and configured 4FEx enroller
 */
-(VeridiumBiometrics4FExEnroller* _Nonnull) create4FExEnrollerWithConfig:(Veridium4FExEnrollConfig * _Nonnull) config;

/*!
 Helper method for creating a 4FEx authenticator and configure it in one single call
 
 @param config the config
 
 @return the created and configured 4FEx authenticator
 */
-(VeridiumBiometrics4FExAuthenticator* _Nonnull) create4FExAuthenticatorWithConfig:(Veridium4FExAuthenticationConfig * _Nonnull) config;


@end
