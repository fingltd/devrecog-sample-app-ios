//
//  FingAccountProfile.h
//  FingEngine
//
//  Created by Marco De Angelis on 07/11/16.
//  Copyright © 2016 Domotz Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FingAccountProfile : NSObject <NSCopying>

@property (nonatomic) NSString *accountId;
@property (nonatomic) NSString *accountFullName;
@property (nonatomic) NSString *accountEmail;

- (FingAccountProfile *)copyProfile __attribute__((deprecated("Use name NSCopying protocol instead")));

@end
