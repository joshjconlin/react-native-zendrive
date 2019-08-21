//
//  ZendriveStarRating.h
//  ZendriveSDK
//
//  Created by Arpit Panda on 28/02/19.
//  Copyright © 2019 Zendrive Inc. All rights reserved.
//

/**
 * Zendrive follows the star rating system, under which five star defined as the best rating with
 * one being the worst.
 */
typedef NS_ENUM(int, ZendriveStarRating) {
    ZendriveStarRatingOne = 1,

    ZendriveStarRatingTwo = 2,

    ZendriveStarRatingThree = 3,

    ZendriveStarRatingFour = 4,

    ZendriveStarRatingFive = 5,

    /**
     * Reported when rating is absent.
     */
    ZendriveStarRatingNA = -1,
};
