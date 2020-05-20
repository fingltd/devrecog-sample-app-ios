//
//  FingScanInput.h
//  FingKit
//
//  Created by Marco De Angelis on 16/12/2019.
//  Copyright © 2019 Domotz Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// FingScanDeviceEntry will be defined afterwards
@class FingScanDeviceEntry;

@interface FingScanInput : NSObject<NSCopying>

@property (nonatomic, strong) NSArray<FingScanDeviceEntry*> *deviceEntries;

@end

@interface FingScanDeviceEntry : NSObject<NSCopying>

@property (nonatomic, strong) NSString *ipAddress;
@property (nonatomic, strong) NSString *macAddress;
@property (nonatomic, strong) NSString *hostName;

@end

NS_ASSUME_NONNULL_END
