//
//  VeridiumDefault4FExViewController.h
//  VeridiumDefault4FExportUI
//
//  Created by Josiah Kane on 23/03/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumDefault4FExViewController_h
#define VeridiumDefault4FExViewController_h

@import VeridiumDefault4FExportUI;

@interface Veridium4FExportUIViewController : VeridiumDefault4FExViewController

+(__weak instancetype _Nullable) createFromStoryboard:(UIStoryboard* _Nullable)storyboard withIdentifier:(NSString* _Nonnull)identifier forAuthMode:(bool)isForAuth;

+(instancetype _Nullable) createCustomAuthenticator;
+(instancetype _Nullable) createCustomEnroller;
+(instancetype _Nullable) createCustomExporter;


@end

#endif /* VeridiumDefault4FExViewController_h */
