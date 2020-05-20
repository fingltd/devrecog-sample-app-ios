//
//  FingAccountProfile.h
//  FingEngine
//
//  Created by Marco De Angelis on 07/11/16.
//  Copyright © 2016 Domotz Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FingAccountProfile : NSObject <NSCopying>

@property (nonatomic, strong) NSString *accountId;
@property (nonatomic, strong) NSString *accountFullName;
@property (nonatomic, strong) NSString *accountEmail;

- (FingAccountProfile *)copyProfile;

@end
