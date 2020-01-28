//
//  Default4FExAdditions.h
//  Default4FExUI
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@import VeridiumCore;
@import Veridium4FExportBiometrics;

@interface VeridiumSDK (Default4FExAdditions)

-(void) registerDefault4FExAuthenticator;

-(void) registerDefault4FExEnroller;

-(void) registerDefault4FExExporter;

@end
