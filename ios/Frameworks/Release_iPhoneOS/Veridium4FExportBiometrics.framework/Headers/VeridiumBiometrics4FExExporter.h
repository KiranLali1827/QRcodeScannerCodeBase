//
//  VeridiumBiometrics4FExExporter.h
//  Veridium4FExportBiometrics
//
//  Copyright © 2018 Veridium IP Ltd. All rights reserved.
//

#import "VeridiumBiometrics4FExCommon.h"

#import "VeridiumBiometrics4FConfig.h" // Import to get WSQCompressionRatio definition

/*!
 Data class for holding the 4FEx authentication config params
 */
@interface Veridium4FExExportConfig : NSObject<VeridiumBiometricExportConfig>


@property (nonatomic, nonnull) NSString* engineName;

/*!
 Whether to use the left or right hand (defaults to Veridium4FExExportHandDefaultLeft)
 */
@property Veridium4FExHandChoiceEnroll exportHand;

/*!
 The allowed number of retries in case the authentication fails (defaults to 0)
 */
@property NSInteger numberOfRetries;

/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;



/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

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
@property int fixed_print_width;
@property int fixed_print_height;
@property BOOL pack_audit_image;
@property BOOL reliability_mask;
@property int nist_type; // choose to output either Type-14 records or type-4 for NIST.
@property int padding_width;
@property int padding_height;
@property BOOL targetIndexFinger;
@property BOOL targetLittleFinger;
@property int captureThumb; //TODO: should be an enum ie. VeridiumThumbMode
@property BOOL individualThumb;
@property BOOL individualIndex;
@property BOOL individualMiddle;
@property BOOL individualRing;
@property BOOL individualLittle;
@property BOOL individualCapture;

/*!
 Whether that the engine is using 4F Liveness (defaults to FALSE)
 */
@property BOOL useLiveness;

/*!
DEPRICATED
 Whether that the engine is using 2 shot 4FLiveness for authentication (defaults to FALSE)
  We still use this in order to do enrol and export
 */
@property BOOL twoShotLiveness;

/*!
 DEPRECATED
 Use passive liveness methods. (defaults to FALSE). //FIXME remove
 */
@property (readonly) BOOL passiveLiveness;

/*!
DEPRICATED
 Whether liveness is done horizonatally (defaults to TRUE)
 */
@property (readonly) BOOL livenessIsHorizontal;

/*!
DEPRICATED
 Use a lower pass requirment for liveness (defaults to FALSE)
 */
@property (readonly) BOOL laxLiveness;



@property (nonnull) NSMutableDictionary *formatConfig;

-(BOOL) supports4F;
-(BOOL) supports8F;
-(NSString* _Nonnull) formatName;
-(NSString* _Nonnull) formatExtension;

/*!
 The UI
 */
@property (nullable) id<Veridium4FExExporterUIDelegate> uiDelegate;



@end

/*!
 The 4FEx biometric exporter.
 */
@interface VeridiumBiometrics4FExExporter : VeridiumBiometrics4FExCommon <VeridiumBioExporter> //is it necessary to add method in the core?




/*!
 Configure the exporter
 
 @param config the Veridium4FExExportConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)configure:(Veridium4FExExportConfig * _Nonnull)config;


/*!
 Update the 4F export configuration
 
 @param config the Veridium4FExExportConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)exportConfigUpdate:(Veridium4FExExportConfig * _Nonnull)config;


/*!
 Check the export setting is valid
 
 @param config the Veridium4FExExportConfig instance
 
 @return BOOL  is valid for not
 */
-(BOOL) verifyConfig:(Veridium4FExExportConfig* _Nonnull)config;


/*!
 The configured Authenticate4FExBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property(readonly, nonnull) Veridium4FExExportConfig* config;

/*!
 Check weather has left or right hand record for enroller
 */
-(BOOL) recordHasLeft;

-(BOOL) recordHasRight;

@end


