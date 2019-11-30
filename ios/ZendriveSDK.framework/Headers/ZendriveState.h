//
//  ZendriveState.h
//  ZendriveSDK
//
//  Created by Arpit Panda on 27/02/19.
//  Copyright © 2019 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZendriveConfiguration.h"

/**
 * Represents the current state of the Zendrive SDK.
 */
@interface ZendriveState : NSObject

/**
 * The current configuration of the SDK.
 * Refer to `ZendriveConfiguration` for further details.
 */
@property ZendriveConfiguration *zendriveConfiguration;

/**
 * Is the SDK currently tracking a drive?
 */
@property BOOL isDriveInProgress;

@end

