//
//  FingScanInput.h
//  FingKit
//
//  Created by Marco De Angelis on 16/12/2019.
//  Copyright © 2019 Domotz Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class FingScanDeviceEntry;

@interface FingScanInput : NSObject<NSCopying>
@property (nonatomic) NSArray<FingScanDeviceEntry *> *deviceEntries;
@end

@interface FingScanDeviceEntry : NSObject<NSCopying>
@property (nonatomic) NSString *ipAddress;
@property (nonatomic) NSString *macAddress;
@property (nonatomic) NSString *hostName;
@end

NS_ASSUME_NONNULL_END
