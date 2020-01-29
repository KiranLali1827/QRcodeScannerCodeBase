//
//  VeridiumSDK+Veridium4FExportUI.h
//  Veridium4FExportUI
//
//  Created by Lewis Carney on 13/04/2018.
//  Copyright © 2018 veridium. All rights reserved.
//

#import <Foundation/Foundation.h>

@import VeridiumCore;
@import Veridium4FExportBiometrics;

@interface VeridiumSDK (Custom4FExAdditions)

-(void) registerCustom4FExAuthenticator;

-(void) registerCustom4FExEnroller;

-(void) registerCustom4FExExporter;

@end


