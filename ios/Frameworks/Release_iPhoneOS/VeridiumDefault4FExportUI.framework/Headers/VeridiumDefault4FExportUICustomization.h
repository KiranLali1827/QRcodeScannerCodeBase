//
//  VeridiumDefault4FExportUICustomization.h
//  VeridiumDefault4FExportUI
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#ifndef VeridiumDefault4FExportUICustomization_h
#define VeridiumDefault4FExportUICustomization_h

@class VeridiumDefault4FExportUICustomization;


@interface VeridiumDefault4FExportUICustomization : NSObject
+ (UIColor *)getBackgroundColor;
+ (UIColor *)getForegroundColor;
+ (UIColor *)getDialogColor;
+ (UIColor *)getDialogTextColor;
+ (UIImage *)getBackgroundImage;


+ (UIColor *)defaultBackgroundColor;
+ (UIColor *)defaultForegroundColor;
+ (UIColor *)defaultDialogColor;
+ (UIColor *)defaultDialogTextColor;


+ (void)setBackgroundColor:(UIColor *)newColor;
+ (void)setForegroundColor:(UIColor *)newColor;
+ (void)setDialogColor:(UIColor *)newColor;
+ (void)setDialogTextColor:(UIColor *)newColor;
+ (void)setBackgroundImage:(UIImage *)newImage;

@end

#endif /* VeridiumDefault4FExportUICustomization_h */
