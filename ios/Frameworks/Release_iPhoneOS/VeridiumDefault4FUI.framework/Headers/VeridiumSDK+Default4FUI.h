//
//  Default4FAdditions.h
//  Default4FUI
//
//  Created by Paul Paul on 6/14/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@import VeridiumCore;
@import Veridium4FBiometrics;

/*!
 SDK default 4F UI additions
 */
@interface VeridiumSDK (Default4FAdditions)

/*!
 Method which registers the Default 4F UI and VeridiumBiometrics4FAuthenticator
 */
-(void) registerDefault4FAuthenticator;

/*!
 Method which registers the Default 4F UI and VeridiumBiometrics4FEnroller
 */
-(void) registerDefault4FEnroller;


@end
