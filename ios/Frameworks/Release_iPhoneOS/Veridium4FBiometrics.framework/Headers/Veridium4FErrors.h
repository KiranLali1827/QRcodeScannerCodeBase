//
//  Veridium4FErrors.h
//  Veridium4FBiometrics
//
//  Created by razvan on 4/7/17.
//  Copyright © 2019 Veridium IP Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSString *const _Nonnull Veridium4FErrorDomain;
FOUNDATION_EXPORT NSString *const _Nonnull Veridium4FInternalErrorKey;

#define FF_TR_TABLE @"4FSDKErrorMessages"

/*!
 @enum Veridium4FErrorCode
 @abstract Constants for the Veridium4F errors

 @constant Veridium4FUnknownError
 an unknown error
 @constant Veridium4FLibError
 an internal Veridium4FError
 @constant Veridium4FUIIntegrationError
 an integration error
 @constant Veridium4FInitError
 an initialization error
 @constant Veridium4FFatalError
 a fatal error, i.e device is not compatibile
 @constant Veridium4FEnrollError
 an enroll error.
 @constant Veridium4FEnrollFailed
 an enroll fail error
 @constant Veridium4FEnrollCanceled
 an enroll cancel error
 @constant Veridium4FCaptureError
 a capture error
 @constant Veridium4FLivenessFailed
 4F liveness authentication failed error
 */
typedef NS_ENUM(NSInteger, Veridium4FErrorCode) {
  Veridium4FUnknownError = -1,
  Veridium4FLibError = -2,
  Veridium4FUIIntegrationError = -3,
  Veridium4FInitError = -4,
  Veridium4FFatalError = -5,
  Veridium4FEnrollError = -6,
  Veridium4FEnrollFailed = -7,
  Veridium4FEnrollCanceled = -8,
  Veridium4FCaptureError = -9,
  Veridium4FLivenessFailed = 200
};

/*!
 The veridium 4FError class.
 */
@interface Veridium4FError : NSError

@end
