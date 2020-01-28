//
//  VeridiumKeyValueStore.h
//  VeridiumCore
//
//  Created by razvan on 3/14/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 Protocol abstracting a key-value storage
 */
@protocol VeridiumKeyValueStore <NSObject>



/*!
 Key subscripting getter
 
 For complex objects you will need to either deserialize yourself from the string value or you can use the coveninent [NSString JSONArray] and [NSString JSONDictionary] extensions declared in VeridiumUtils (if you used the same serialization when the value was stored
 
 @param key the key
 @return the stored value
 */
- (NSString* _Nullable)objectForKeyedSubscript:(NSString* _Nonnull)key;


/*!
 Key subscripting setter
 
 For complex objects you will need to store either your custom serialization into a string or you can use the coveninent [NSArray JSONString] and [NSDictionary JSONString] extensions declared in VeridiumUtils
 
 @param string the string to store (if `nil` the currently stored value - if existing - will be wiped)
 @param key the key
 */
- (void)setObject:(NSString* _Nullable)string forKeyedSubscript:(NSString* _Nonnull)key;


/*!
 Stores a string in the store under the specified key

 For complex objects you will need to store either your custom serialization into a string or you can use the coveninent [NSArray JSONString] and [NSDictionary JSONString] extensions declared in VeridiumUtils

 @param value The value.
 @param key   The key.
 
 */
-(void) store:(id _Nullable)value forKey:(NSString* _Nonnull)key __attribute__((deprecated("use the key-value subscripting instead (eg. store[@\"key\"] = newValue)")));


/*!
 Retrieves a string stored under the specified key (if available)

 For complex objects you will need to handle the deserialization yourself, i.e. using the [NSString JSONArray], [NSString JSONDictionary] extensions declared in VeridiumUtils (or your custom method if you serialized the string yourself using your own custom way)
 
 @param key The key.
 
 @return the stored value or nil if not found.
 
 */
-(id _Nullable) get:(NSString* _Nonnull) key  __attribute__((deprecated("use the key-value subscripting instead (eg. var = store[@\"key\"])")));


/*!
 Clears all data from the store
 
 __Use with care!__
 */
-(void)clearAllData;

@end
