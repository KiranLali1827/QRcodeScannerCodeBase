//
//  VeridiumBiometrics4FExService.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#ifndef VeridiumBiometrics4FExService_h
#define VeridiumBiometrics4FExService_h

#import <Foundation/Foundation.h>
#import "VeridiumBiometrics4FExCommon.h"
#import "VeridiumBiometrics4FConfig.h"
#import "VeridiumBiometrics4FExAuthenticator.h"
#import "VeridiumBiometrics4FExEnroller.h"
#import "VeridiumBiometrics4FExExporter.h"

@interface VeridiumBiometrics4FExService : NSObject

/*!
 Exports data using the requested biometric export methods
 
 @param config       VeridiumExportConfig filled in with the export information
 @param successBlock success callback biometricVectorBlock
 @param failBlock    fail callback voidBlock
 @param cancelBlock  cancel callback
 @param errorBlock   error callback errorBlock; receives the error as an NSError
 */
+(void)exportTemplate:(VeridiumBiometrics4FConfig * _Nonnull)config
            onSuccess:(biometricFullVectorBlock _Nonnull) successBlock
               onFail:(voidBlock _Nonnull) failBlock
             onCancel:(voidBlock _Nullable) cancelBlock
              onError:(errorBlock _Nonnull) errorBlock;


+(void)enrollAndExportTemplate:(VeridiumBiometrics4FConfig * _Nonnull)config
                     onSuccess:(void (^)(VeridiumBiometricFullVector * _Nonnull, VeridiumBiometricFullVector* _Nonnull)) successBlock
                        onFail:(voidBlock _Nonnull) failBlock
                      onCancel:(voidBlock _Nullable) cancelBlock
                       onError:(errorBlock _Nonnull) errorBlock;



+(void)authenticateAndExportTemplate:(VeridiumBiometrics4FConfig * _Nonnull)config
                           onSuccess:(biometricFullVectorBlock _Nonnull) successBlock
                              onFail:(voidBlock _Nonnull) failBlock
                            onCancel:(voidBlock _Nullable) cancelBlock
                             onError:(errorBlock _Nonnull) errorBlock;


+(BOOL)checkIfSuppressingAllScreens;

@end


#endif /* VeridiumBiometrics4FExService_h */
