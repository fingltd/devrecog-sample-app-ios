//
//  FGKUtils.m
//  FingKitTestApp
//
//  Copyright © 2019 Fing Ltd. All rights reserved.
//

#import "FGKUtils.h"

@interface FGKUtils ()

@end

@implementation FGKUtils

/*!
 * Extract a value from the given JSON string.
 *
 * @param   json    The JSON string
 * @param   key     The key to use for the retrieval of the value.
 * @return  NSString
 */
+ (id)extractFromJSON:(NSString *)json forKey:(NSString *)key {
    // No JSON string given.
    if (json == nil)
        return nil;
    // Parse the given JSON string.
    NSError *error = nil;
    id object = [NSJSONSerialization
            JSONObjectWithData:[json dataUsingEncoding:NSUTF8StringEncoding]
                       options:0
                         error:&error];
    // JSON was malformed, act appropriately here
    if (error)
        return nil;
    // The originating poster wants to deal with dictionaries;
    // Assuming you do too then something like this is the first validation step:
    if ([object isKindOfClass:[NSDictionary class]]) {
        return object[key];
    }
    // There's no guarantee that the outermost object in a JSON
    // packet will be a dictionary; if we get here then it wasn't,
    // so 'object' shouldn't be treated as an NSDictionary; probably
    // you need to report a suitable error condition
    return nil;
}

/*!
 * Returns formatted result ready to be printed on the UI.
 *
 * @param   result      The result to format.
 * @param   error       An optional error to display, in place of the result.
 * @return  NSString
 */
+ (id)formatResult:(NSString *)result orError:(NSError *)error {
    if (error != nil)
        return error.userInfo[NSLocalizedFailureReasonErrorKey];
    return result != nil ? result : @"";
}

@end
