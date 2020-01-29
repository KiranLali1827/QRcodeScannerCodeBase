//
//  VerdiumBOPSErrors.h
//  VeridiumBOPS
//
//  Created by razvan on 4/4/17.
//  Copyright © 2017 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
 @enum VeridiumBOPSErrorCode
 @abstract
 Constants for the BOPS Calls error codes

 @constant VeridiumBOPSMissingOrMalformedResponseDataError
 Invalid body request
 @constant VeridiumBOPSRemoteBiometricVectorsNotFoundError
 Biometrics not found on the server
 @constant VeridiumBOPSInvalidOrMissingProfileError
 Profile is missing or information provided are invalid
 @constant VeridiumBOPSMissingDataForBOPSCallError
 Missing data for BOPS call
 @constant VeridiumBOPSAccountLockedError
 Bops account is locked
 @constant VeridiumBOPSUnknownAuthenticationTypeError
 Unknown authentication type
 @constant VeridiumBOPSInvalidInputError
 Missing profile information
 @constant VeridiumBOPSAccountRegistrationError
 Account generic registration error
 @constant VeridiumBOPSInvalidAuthenticationTypeError
 Invalid authentication type generic error
 @constant VeridiumBOPSNoAccountRegisteredError
 No account registered
 @constant VeridiumBOPSServerConnectionError
 Bops server is offline
 @constant VeridiumBOPSServerMalformedResponseError
 Server response is malformed
 @constant VeridiumBOPSAuthenticationFailedError
 Bops authentication was failed
 */
typedef NS_ENUM(NSInteger, VeridiumBOPSErrorCode) {
  VeridiumBOPSMissingOrMalformedResponseDataError = -1000,
  VeridiumBOPSInvalidOrMissingProfileError = -1002,
  //VeridiumBOPSMissingDataForBOPSCallError = -1003,
  VeridiumBOPSAccountLockedError = -1004,
  VeridiumBOPSUnknownAuthenticationTypeError = -1020,
  VeridiumBOPSInvalidSessionInputError = -1021,
  VeridiumBOPSAccountRegistrationError = -1022,
  VeridiumBOPSInvalidAuthenticationTypeError = -1023,
  VeridiumBOPSNoAccountRegisteredError = -1024,
  VeridiumBOPSServerConnectionError = -1025,
  VeridiumBOPSServerMalformedResponseError = -1026,
  VeridiumBOPSAuthenticationFailedError = -1027,
  VeridiumBOPSClientCertificateRejectedError = -1205,
  VeridiumBOPSUntrustedServer = 1032,
  VeridiumBOPSSslHandshakeErrorPeer = 1033,
  VeridiumBOPSSslHandshakeErrorClient = 1034,
};


/*!
 @enum VeridiumBOPSServerInternalErrorCode
 @abstract
 Constants for the BOPS internal error codes

 @constant VeridiumBOPSServerGenericError
 Bops generic server error
 @constant VeridiumBOPSServerDeviceNotFoundError
 Device not found on Bops server
 @constant VeridiumBOPSServerAccountNotFoundError
 Account not found on Bops server
 @constant VeridiumBOPSServerUserNotFoundError
 User not found on Bops server
 @constant VeridiumBOPSServerInvalidUserCredentialsError
 Provided credentials are invalid
 @constant VeridiumBOPSServerInvalidIntrusionDetectionValuesError
 Invalid intrusion detection error
 @constant VeridiumBOPSServerInvalidUnlockPasswordError
 Account password sent was invalid
 @constant VeridiumBOPSServerInvalidUnlockSeedError
 Seed sent to bops was invalid
 @constant VeridiumBOPSServerInvalidAccountStateError
 Invalid server account state
 @constant VeridiumBOPSServerInvalidDeviceDataError
 The device data on server is invalid
 @constant VeridiumBOPSServerInvalidSessionOpportunityStateError
  Invalid session opportunity state
 @constant VeridiumBOPSServerProfileAlreadyRegisteredError
 Profile already registered
 @constant VeridiumBOPSServerInvalidParameterError
 Invalid parameter
 */
typedef NS_ENUM(NSInteger, VeridiumBOPSServerInternalErrorCode) {
  
  VeridiumBOPSServerGenericError        = 100,
  VeridiumBOPSServerDeviceNotFoundError = 118,
  VeridiumBOPSServerAccountNotFoundError = 138,
  
  VeridiumBOPSServerUserNotFoundError = 145,
  VeridiumBOPSServerInvalidUserCredentialsError = 141,
  
  VeridiumBOPSServerInvalidIntrusionDetectionValuesError = 303,
  
  VeridiumBOPSServerInvalidUnlockPasswordError = 153,
  VeridiumBOPSServerInvalidUnlockSeedError = 154,
  
  VeridiumBOPSServerInvalidAccountStateError = 164,
  VeridiumBOPSServerInvalidDeviceDataError = 165,
  VeridiumBOPSServerInvalidSessionOpportunityStateError = 111,
  
  VeridiumBOPSServerProfileAlreadyRegisteredError = 606,
  VeridiumBOPSServerInvalidParameterError = 101
};


FOUNDATION_EXPORT NSString *const _Nonnull VeridiumBOPSErrorDomain;
#define kVeridiumBopsCustomIntegrationTranslationTable @"BopsCustomIntegrationErrorMessages"


FOUNDATION_EXPORT NSString *const _Nonnull VeridiumBOPSServerInternalErrorDescriptionKey;
FOUNDATION_EXPORT NSString *const _Nonnull VeridiumBOPSRequestURLKey;
FOUNDATION_EXPORT NSString *const _Nonnull VeridiumBOPSPayloadSent;
FOUNDATION_EXPORT NSString *const _Nonnull VeridiumBOPSOperationNameKey;


/*!
 Abstract class of Bops errors
 */
@interface VeridiumBOPSError : NSError

/*!
 The operationName.
 */
@property (readonly, nullable) NSString* operationName;

@end


/*!
 Subclass of VeridiumBOPSError, for generic BOPS calls error
 */
@interface VeridiumBOPSCallError : VeridiumBOPSError

/*!
 The original request URL.
 */
@property (readonly, nullable) NSURL* requestURL;

@end


/*!
 Subclass of VeridiumBOPSCallError, for internal errors
 */
@interface VeridiumBOPSServerInternalError : VeridiumBOPSCallError

/*!
 The localized server error message
 */
@property (readonly,nullable) NSString* localizedServerErrorMessage;


/*!
 Server's raw response error message
 */
@property (readonly,nullable) NSString* rawServerErrorMessage;

@end


/*!
 Subclass of VeridiumBOPSServerInternalError, for integration specific errors
 */
@interface VeridiumBOPSIntegrationCustomError : VeridiumBOPSServerInternalError

/*!
 The localized server error message
 */
@property (readonly,nullable) NSString* localizedServerErrorMessage;

/*!
 Server's raw response error message
 */
@property (readonly,nullable) NSString* rawServerErrorMessage;

@end
