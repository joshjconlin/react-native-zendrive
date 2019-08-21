//
//  ZendriveTripWarning.h
//  ZendriveSDK
//
//  Created by Arpit Panda on 03/04/19.
//  Copyright © 2019 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * The value return from `ZendriveTripWarning.warning`.
 * Enum representing warnings detected for the current drive.
 */
typedef NS_ENUM(int, ZendriveTripWarningType) {
    /**
     * The trip duration is unexpectedly large and signifies a possible integration issue.
     */
    ZendriveTripWarningTypeUnexpectedTripDuration = 0
};

@interface ZendriveTripWarning : NSObject

/**
 * The type of the trip warning.
 **/
@property (nonatomic) ZendriveTripWarningType tripWarningType;

- (instancetype)initWithWarning:(ZendriveTripWarningType)tripWarningType;
@end

