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

@property ZendriveStarRating phoneHandlingRating;
@property ZendriveStarRating hardBrakeRating;
@property ZendriveStarRating hardTurnRating;
@property ZendriveStarRating speedingRating;
@property ZendriveStarRating aggressiveAccelerationRating;

- (instancetype)init;
@end
