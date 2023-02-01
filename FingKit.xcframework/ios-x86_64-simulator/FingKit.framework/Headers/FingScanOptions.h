//
//  FingScanOptions.h
//  FingEngine
//
//  Created by Marco De Angelis on 19/08/16.
//  Copyright © 2016 Domotz Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, FingScanResultLevel) {
    FingScanResultNone,             // Don't send any data.
    FingScanResultSummary,          // Return only a summary of the scan.
    FingScanResultFull,             // Full results of the scan.
};

@interface FingScanOptions : NSObject<NSCopying>

@property (nonatomic) BOOL bonjourEnabled;
@property (nonatomic) BOOL netbiosEnabled;
@property (nonatomic) BOOL reverseDnsEnabled;
@property (nonatomic) BOOL snmpEnabled;
@property (nonatomic) BOOL upnpEnabled;
@property (nonatomic) NSInteger maxNetworkSize;
@property (nonatomic) FingScanResultLevel resultLevelScanInProgress;
@property (nonatomic) FingScanResultLevel resultLevelScanCompleted;
@property (nonatomic) NSString *outputFormat;

- (FingScanOptions *)copyOptions __attribute__((deprecated("Use name NSCopying protocol instead")));
+ (FingScanOptions *)systemDefault;

@end
