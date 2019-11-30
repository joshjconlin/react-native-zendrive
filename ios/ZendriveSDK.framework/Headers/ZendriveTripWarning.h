//
//  ZendriveTripWarning.h
//  ZendriveSDK
//
//  Created by Arpit Panda on 03/04/19.
//  Copyright © 2019 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * The value return from `ZendriveTripWarning.tripWarningType`.
 * Enum representing warnings detected for the current drive.
 */
typedef NS_ENUM(int, ZendriveTripWarningType) {
    /**
     * The trip duration is unexpectedly large and signifies a possible integration issue.
     */
    ZendriveTripWarningTypeUnexpectedTripDuration = 0
};

/**
 * Represents a single warning that might have occurred during your trip.
 * A collection of these warnings are provided using the `-[ZendriveDelegateProtocol processAnalysisOfDrive:]` callback.
 */
@interface ZendriveTripWarning : NSObject

/**
 * The type of the trip warning.
 **/
@property (nonatomic) ZendriveTripWarningType tripWarningType;
/**
 * Initializer for creating a `ZendriveTripWarning`.
 * @param tripWarningType Type of warning detected for the current drive.
 **/
- (instancetype)initWithWarning:(ZendriveTripWarningType)tripWarningType;
@end

