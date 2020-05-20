//
//  FingScanOptions.h
//  FingEngine
//
//  Created by Marco De Angelis on 19/08/16.
//  Copyright © 2016 Domotz Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

// Enumerated value that indicates the source of Remote Config data. Data can come from
// the Remote Config service, the DefaultConfig that is available when the app is first installed,
// or a static initialized value if data is not available from the service or DefaultConfig.
typedef NS_ENUM(NSInteger, FingScanResultLevel) {
    FingScanResultNone,             // Don't send any data.
    FingScanResultSummary,          // Return only a summary of the scan.
    FingScanResultFull,             // Full results of the scan.
};

@interface FingScanOptions : NSObject<NSCopying>

@property (nonatomic, assign) BOOL reverseDnsEnabled;
@property (nonatomic, assign) BOOL upnpEnabled;
@property (nonatomic, assign) BOOL bonjourEnabled;
@property (nonatomic, assign) BOOL netbiosEnabled;
@property (nonatomic, assign) BOOL snmpEnabled;
@property (nonatomic, assign) NSInteger maxNetworkSize;

@property (nonatomic, assign) FingScanResultLevel resultLevelScanInProgress;
@property (nonatomic, assign) FingScanResultLevel resultLevelScanCompleted;
@property (nonatomic, strong) NSString *outputFormat;

- (FingScanOptions *)copyOptions;
+ (FingScanOptions *)systemDefault;

@end
