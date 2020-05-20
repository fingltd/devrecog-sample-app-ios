//
//  FGKUtils.h
//  FingKitTestApp
//
//  Copyright © 2019 Fing Ltd. All rights reserved.
//

#ifndef FGKUtils_h
#define FGKUtils_h

#import <Foundation/Foundation.h>

@interface FGKUtils : NSObject

/*!
 * Extract a value from the given JSON string.
 *
 * @param   json    The JSON string
 * @param   key     The key to use for the retrieval of the value.
 * @return  NSString
 */
+ (nullable id)extractFromJSON:(nullable NSString *)json forKey:(nullable NSString *)key;

/*!
 * Returns formatted result ready to be printed on the UI.
 *
 * @param   result      The result to format.
 * @param   error       An optional error to display, in place of the result.
 * @return  NSString
 */
+ (nullable id)formatResult:(nullable NSString *)result orError:(nullable NSError *)error;

@end

#endif /* FGKUtils_h */
