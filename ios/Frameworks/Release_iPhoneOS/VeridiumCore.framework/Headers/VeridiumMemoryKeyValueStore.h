//
//  VeridiumMemoryKeyValueStore.h
//  VeridiumCore
//
//  Created by razvan on 5/10/16.
//  Copyright © 2016 HoyosLabs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VeridiumKeyValueStore.h"

/*!
 NSDictionary implementation of KeyValueStore protocol
 */
@interface VeridiumMemoryKeyValueStore : NSObject  <VeridiumKeyValueStore>

-(NSDictionary * _Nonnull) getMemoryDictionary;

/*!
 Loads data from another dictionary
 
 @param dict the data dictionary
 */
-(void) initWithDictionary: (NSDictionary* _Nonnull) dict;


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
