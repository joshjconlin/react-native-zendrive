//
//  ZendriveStarRating.h
//  ZendriveSDK
//
//  Created by Arpit Panda on 28/02/19.
//  Copyright © 2019 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Zendrive follows the star rating system, under which five star defined as the best rating with
 * one being the worst.
 */
typedef NS_ENUM(int, ZendriveStarRating) {
    /**
     * Indicates worst rating.
     */
    ZendriveStarRatingOne = 1,
    /**
     * Indicates bad rating.
     */
    ZendriveStarRatingTwo = 2,
    /**
     * Indicates an average rating.
     */
    ZendriveStarRatingThree = 3,
    /**
     * Indicates good rating.
     */
    ZendriveStarRatingFour = 4,
    /**
     * Indicates best rating.
     */
    ZendriveStarRatingFive = 5,

    /**
     * Reported when rating is absent.
     */
    ZendriveStarRatingNA = -1,
};
