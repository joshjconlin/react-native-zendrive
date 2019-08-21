//
//  ZendriveActiveDriveInfo.h
//  ZendriveSDK
//
//  Created by Yogesh on 9/10/15.
//  Copyright (c) 2015 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZendriveDriveInfo.h"

/**
 *  Information about the active drive if any.
 */
@interface ZendriveActiveDriveInfo : NSObject

/**
 * The unique Id for this drive
 */
@property (nonatomic, readonly, nonnull) NSString *driveId;

/**
 * The start timestamp of trip in milliseconds since epoch.
 */
@property (nonatomic, assign) long long startTimestamp;

/**
 * The insurance period for this drive
 */
@property (nonatomic, assign) ZendriveInsurancePeriod insurancePeriod;

/**
 * The current speed of vehicle in metres/second.
 */
@property (nonatomic, assign) double currentSpeed;

/**
 * The distance covered so far in this trip in meters.
 */
@property (nonatomic, assign) double distance;

/**
 * Tracking id is specified by the enclosing application when it
 * wants to start a drive manually by calling `+[Zendrive startManualDrive:completionHandler]`
 *
 * This may be the case for example in a taxi cab application that would
 * know when to start a drive based on when a meter gets flagged. trackingId will be
 * nil in case of auto detected drives.
 */
@property (nonatomic, strong, nullable) NSString *trackingId;

/**
 * Session id is specified by the enclosing application when it wants to
 * record a session using [Zendrive startSession:]
 *
 * sessionId will be nil if there is no session associated with that drive.
 */
@property (nonatomic, strong, nullable) NSString *sessionId;
@end
