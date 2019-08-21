//
//  ZendriveDriveInfo.h
//  Zendrive
//
//  Created by Sumant Hanumante on 25/06/14.
//  Copyright (c) 2014 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * The type of the drive returned from `ZendriveDriveInfo.driveType`.
 *
 * This decides what other `ZendriveDriveInfo` parameters will be populated.
 * A drive callback can be sent as a false alarm or when we detect that the user was not
 * actually driving but moved using other means of transport.
 */
typedef NS_ENUM(int, ZendriveDriveType) {
    /**
     * Sometimes, the SDK detects that a trip is invalid after it has been started.
     * In these cases, the values for `ZendriveDriveInfo.waypoints`, `ZendriveDriveInfo.events`,
     * `ZendriveDriveInfo.score`, `ZendriveDriveInfo.maxSpeed` and `ZendriveDriveInfo.averageSpeed`
     * will have invalid values.
     */
    ZendriveDriveTypeInvalid = 0,

    /**
     * This was not a driving trip. For e.g bike and train rides will fall under this trip type.
     * The `ZendriveDriveInfo` will have `ZendriveDriveInfo.waypoints`, `ZendriveDriveInfo.maxSpeed`
     * and `ZendriveDriveInfo.averageSpeed` but `ZendriveDriveInfo.events` and
     * `ZendriveDriveInfo.score` will have invalid values.
     */
    ZendriveDriveTypeNonDriving = 1,

    /**
     * This trip was taken in a car.
     *
     * If the SDK determined the user to be a driver or a passenger, the value
     * will be available in `ZendriveDriveInfo.userMode`
     *
     * The `ZendriveDriveInfo` will have `ZendriveDriveInfo.waypoints`, `ZendriveDriveInfo.maxSpeed`,
     * `ZendriveDriveInfo.averageSpeed`, `ZendriveDriveInfo.events` and `ZendriveDriveInfo.score`.
     */
    ZendriveDriveTypeDrive = 2
};


/**
 * The value return from `ZendriveDriveInfo.userMode`. Indicates whether user
 * was a driver or passenger.
 */
typedef NS_ENUM(int, ZendriveUserMode) {
    /**
     * Indicates that the user was in the driver seat.
     * All values in `ZendriveDriveInfo` will be set.
     */
    ZendriveUserModeDriver = 0,

    /**
     * Indicates that the user was in the passenger seat.
     * `ZendriveDriveInfo.score` will have default value. All other values will be set.
     */
    ZendriveUserModePassenger = 1,

    /**
     * Indicates that either `ZendriveDriveInfo.driveType` is not
     * `ZendriveDriveTypeDrive` or `Zendrive` was not able to determine user mode.
     * All values in `ZendriveDriveInfo` will be set.
     */
    ZendriveUserModeUnavailable = 2
};

/**
 * The types of insurance period in `Zendrive`
 *
 * Each drive belongs to exactly one of these insurance periods.
 */
typedef NS_ENUM(int, ZendriveInsurancePeriod) {
    /**
     * Applications that do not use insurance APIs will have drives with
     * this value for insurance period
     */
    ZendriveInsuranceNoPeriod = 0,
    /**
     * Drives detected in insurance period 1 will have this value.
     * Refer: `+[ZendriveInsurance startPeriod1:]`
     */
    ZendriveInsurancePeriod1 = 1,
    /**
     * Drives undertaken with insurance period 2 will have this value.
     * Refer: `+[ZendriveInsurance startDriveWithPeriod2:error:]`
     */
    ZendriveInsurancePeriod2 = 2,
    /**
     * Drives undertaken with insurance period 3 will have this value.
     * Refer: `+[ZendriveInsurance startDriveWithPeriod3:error:]`
     */
    ZendriveInsurancePeriod3 = 3
};

/**
 * The types of phone positions during a trip.
 *
 */
typedef NS_ENUM(int, ZendrivePhonePosition) {
    /**
     * The case when `Zendrive` was unable to determine the position of the phone during a trip.
     */
    ZendrivePhonePositionUnknown = 0,
    /**
     * The case when `Zendrive` was able to determine confidently that the phone was on mount during a trip.
     */
    ZendrivePhonePositionMount = 1,
};

@class ZendriveDriveScore;
@class ZendriveEventRatings;
@class ZendriveTripWarning;
/**
 * ZendriveDriveInfo
 *
 * Wrapper for meta-information related to a drive.
 */
@interface ZendriveDriveInfo : NSObject

/**
 * The unique Id for this drive
 */
@property (nonatomic, readonly, nonnull) NSString *driveId;

/**
 * The type of the drive. This decides what other info parameters will be populated.
 *
 * A drive callback will be sent even for falsely detected drives or for non
 * automobile trips (Eg. biking, public transport).
 */
@property (nonatomic, assign) ZendriveDriveType driveType;

/**
 * Whether the user was a driver or a passenger.
 *
 * Driver/Passenger detection is disabled by default. Talk to your
 * contact in `Zendrive` to enable this feature. Only present when `driveType` is
 * `ZendriveDriveTypeDrive` and the SDK was able to determine with confidence
 * whether the user was a driver or a passenger.
 *
 * If the SDK was not able to determine the user mode, this field is
 * `ZendriveUserModeUnavailable`.
 */
@property (nonatomic, assign) ZendriveUserMode userMode;

/**
 * The insurance period for this drive
 */
@property (nonatomic, assign) ZendriveInsurancePeriod insurancePeriod;

/**
 * The start timestamp of trip in milliseconds since epoch.
 */
@property (nonatomic, assign) long long startTimestamp;

/**
 * The end timestamp of trip in milliseconds since epoch
 */
@property (nonatomic, assign) long long endTimestamp;

/**
 * The average speed of trip in metres/second
 */
@property (nonatomic, assign) double averageSpeed;

/**
 * The maximum speed of trip in metres/second
 *
 * If we do not receive any accurate location data during the drive, this
 * property would be set to -1
 */
@property (nonatomic, assign) double maxSpeed;

/**
 * The distance of the trip in metres
 */
@property (nonatomic, assign) double distance;

/**
 * A list of `ZendriveLocationPoint` objects corresponding to this trip in
 * increasing order of timestamp. The first point corresponds to trip start location
 * and last to trip end location.
 *
 * This is a sampled approximation of the drive which gives an indication of
 * the path taken by the driver. It is not the full detailed location data of the drive.
 * If no waypoints are recorded during the drive, this is an empty array.
 */
@property (nonatomic, strong, nonnull) NSArray *waypoints;

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
 * record a session using `+[Zendrive startSession:]`
 *
 * sessionId will be nil if there is no session associated with that drive.
 */
@property (nonatomic, strong, nullable) NSString *sessionId;

/**
 * A list of `ZendriveEvent` objects for this trip in increasing order of timestamp.
 *
 * In case of no events in the trip an empty list is returned.
 */
@property (nonatomic, strong, nonnull) NSArray *events;

/**
 * The driving behaviour score for this trip.
 */
@property (nonatomic, strong, nonnull) ZendriveDriveScore *score;

/**
 * The ratings of individual events for this trip
 */
@property (nonatomic, strong, nonnull) ZendriveEventRatings *eventRatings;

/**
 * The position of the phone during this trip.
 */
@property (nonatomic, assign) ZendrivePhonePosition phonePosition;

/**
 * A list of `ZendriveTripWarning` objects for this trip.
 *
 * In case of no warnings in the trip an empty list is returned.
 */
@property (nonatomic, strong, nonnull) NSArray<ZendriveTripWarning *> *tripWarnings;

@end
