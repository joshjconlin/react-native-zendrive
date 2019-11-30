//
//  ZendriveEventRatings.h
//  ZendriveSDK
//
//  Created by Arpit Panda on 27/02/19.
//  Copyright © 2019 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZendriveStarRating.h"

/**
 * Represents ratings associated with the various event types for a trip. Higher rating for an event
 * represents safe driving behaviour with respect to that event. For cases where rating is absent,
 * `ZendriveStarRatingNA` is reported.
 *
 * @see `ZendriveStarRating`
 */

@interface ZendriveEventRatings : NSObject

/**
 * Represents rating associated with phone handling behavior while driving.
 */
@property ZendriveStarRating phoneHandlingRating;

/**
 * Represents rating associated with hard braking while driving.
 */
@property ZendriveStarRating hardBrakeRating;

/**
 * Represents rating associated with hard turning while driving.
 */
@property ZendriveStarRating hardTurnRating;

/**
 * Represents rating associated with speeding while driving.
 */
@property ZendriveStarRating speedingRating;

/**
 * Represents rating associated with aggressively accelerating while driving.
 */
@property ZendriveStarRating aggressiveAccelerationRating;

/**
 * Initializer for `ZendriveEventRatings`.
 */
- (instancetype)init;
@end
