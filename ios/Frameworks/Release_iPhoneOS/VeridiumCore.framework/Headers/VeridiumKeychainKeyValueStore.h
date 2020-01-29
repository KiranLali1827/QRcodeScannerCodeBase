//
//  VeridiumKeychainKeyValueStore.h
//  VeridiumCore
//
//  Created by razvan on 3/14/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#import "VeridiumKeyValueStore.h"

/*!
 Keychain implementation of KeyValueStore protocol
 */
@interface VeridiumKeychainKeyValueStore : NSObject <VeridiumKeyValueStore>

-(instancetype _Nonnull)init NS_UNAVAILABLE;
-(instancetype _Nonnull)alloc NS_UNAVAILABLE;
+(instancetype _Nonnull)new NS_UNAVAILABLE;

/*!
 Designated initializer
 
 @param masterKey the master key of the instance (all values will be stored as sub keys of this key)
 */
-(instancetype _Nonnull)initWithMasterKey:(NSString* _Nonnull)masterKey NS_DESIGNATED_INITIALIZER;


/*!
 Static initializer

 @param masterKey the master key of the instance (all values will be stored as sub keys of this key) 
 @return the initialized instance
 */
+(instancetype _Nonnull)newWithMasterKey:(NSString * _Nonnull)masterKey;



/*!
 Helper property for quick access to the global Veridium Keychain store
 */
@property (class, readonly, nonnull) VeridiumKeychainKeyValueStore* global;


/*!
 Key subscripting getter
 
 (redeclaration needed for swift visibility)
 For complex objects you will need to either deserialize yourself from the string value or you can use the coveninent [NSString JSONArray] and [NSString JSONDictionary] extensions declared in VeridiumUtils (if you used the same serialization when the value was stored
 
 @param key the key
 @return the stored value
 */
- (NSString* _Nullable)objectForKeyedSubscript:(NSString* _Nonnull)key;


/*!
 Key subscripting setter
 
 (redeclaration needed for swift visibility)
 For complex objects you will need to store either your custom serialization into a string or you can use the coveninent [NSArray JSONString] and [NSDictionary JSONString] extensions declared in VeridiumUtils
 
 @param string the string to store (if `nil` the currently stored value - if existing - will be wiped)
 @param key the key
 */
- (void)setObject:(NSString* _Nullable)string forKeyedSubscript:(NSString* _Nonnull)key;

@end
