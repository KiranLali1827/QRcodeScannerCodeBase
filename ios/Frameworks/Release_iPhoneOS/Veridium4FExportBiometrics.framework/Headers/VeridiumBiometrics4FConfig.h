//
//  VeridiumBiometrics4FConfig.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#ifndef VeridiumBiometrics4FConfig_h
#define VeridiumBiometrics4FConfig_h

#import "VeridiumBiometrics4FExCommon.h"

typedef float WSQCompressRatio;
extern WSQCompressRatio const COMPRESS_15to1;
extern WSQCompressRatio const COMPRESS_10to1;
extern WSQCompressRatio const COMPRESS_5to1;

typedef int NistType;
extern NistType const Nist_type_T14_9;
extern NistType const Nist_type_T4_9;

// This is a general configuration object that covers enrol, auth and export
// Interanlly, auth, enrol, export, convert this to specific configs
@interface VeridiumBiometrics4FConfig : NSObject


/*!
 Whether to use the left or right hand for enrol / export (defaults to Veridium4FExExportHandDefaultLeft)
 */
@property Veridium4FExHandChoiceEnroll chosenHand;

/*!
 Whether to use the left or right hand for authentication (defaults to Veridium4FExExportHandDefaultLeft)
 */
@property Veridium4FExAuthenticationHand authenticationHand;

/*!
 Number of templates to enroll (defaults to 2)
 
 **_Note:_** Cannot be lower than 2
 */
@property NSInteger templatesToEnroll;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;
/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;

/*!
 Whether to reset timing after each successfully captured template
 (defaults to TRUE)
 */
@property BOOL resetTimeoutAfterSuccessfulCapture;

/*!
 **EXPERIMENTAL** Whether to compute a custom handguide based on the user's fingers pattern after first enrolled template
 */
@property BOOL computeCustomHandGuide;

/*!
 **EXPERIMENTAL** Whether to compute a custom handguide based on the fov
 */
@property BOOL computeDefaultHandGuide;


/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

/*!
 The UI for enroll
 */
@property id<Veridium4FExEnrollerUIDelegate> _Nullable uiDelegateEnroll;

/*!
 The UI for auth
 */
@property id<Veridium4FExAuthenticatorUIDelegate> _Nullable uiDelegateAuth;

/*!
 The UI for export
 */
@property id<Veridium4FExExporterUIDelegate> _Nullable uiDelegateExport;

/*!
 Whether that the engine is using 4F Liveness (defaults to FALSE)
 */
@property BOOL useLiveness;

/*!
 DEPRICATED read only
 Whether that the engine is using 2 shot 4FLiveness for authentication (defaults to FALSE)
 */
@property (readonly) BOOL twoShotLiveness;

/*!
 DEPRECATED read only
 Use passive liveness methods. (defaults to FALSE)
 */
@property (readonly) BOOL passiveLiveness;

/*!
 DEPRECATED read only
 Whether liveness is done horizonatally (defaults to TRUE)
 */
@property (readonly) BOOL livenessIsHorizontal;

/*!
 DEPRECATED read only
 Use a lower pass requirment for liveness (defaults to FALSE)
 */
@property (readonly) BOOL laxLiveness;



@property VeridiumTemplateFormat exportFormat;

@property BOOL record8F;

@property BOOL keepResource;


@property BOOL pack_debug_data;

@property BOOL pack_wsq;

@property WSQCompressRatio wsq_compression_ratio;

@property BOOL pack_raw;

@property BOOL pack_png;

@property BOOL calculate_nfiq;
@property BOOL background_remove;
@property BOOL extra_scaled_image;
@property BOOL pack_audit_image;
@property BOOL reliability_mask;
@property int nist_type;

@property int fixed_print_width;
@property int fixed_print_height;


@property int padding_width;
@property int padding_height;

@property BOOL targetIndexFinger;
@property BOOL targetLittleFinger;
@property VeridiumThumbMode captureThumb;

@property BOOL individualThumb;
@property BOOL individualIndex;
@property BOOL individualMiddle;
@property BOOL individualRing;
@property BOOL individualLittle;
@property BOOL individualCapture;


-(BOOL) supports4F;
-(BOOL) supports8F;
-(BOOL) supports2Thumb;
-(BOOL) supportsAllFinger;
-(NSString* _Nonnull) formatName;
-(NSString* _Nonnull) formatExtension;


@end

#endif /* VeridiumBiometrics4FConfig_h */
