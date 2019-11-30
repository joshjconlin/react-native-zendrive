//
//  ZendriveAccidentInfo.h
//  Zendrive
//
//  Created by Sumant Hanumante on 20/03/15.
//  Copyright (c) 2015 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Confidence measure of the detected accident.
 */
typedef NS_ENUM(int, ZendriveAccidentConfidence) {
    /**
     * Accident was detected with a high confidence. The application might inform
     * emergency services directly after waiting for some time for user feedback.
     */
    ZendriveAccidentConfidenceHigh,

    /**
     * Accident was detected, but with a low confidence. The application might ask
     * the user for feedback before notifying any emergency services.
     */
    ZendriveAccidentConfidenceLow
};

@class ZendriveLocationPoint;

/**
 * ZendriveAccidentInfo
 *
 * Wrapper for meta-information related to an accident detected by the SDK.
 */
@interface ZendriveAccidentInfo : NSObject

/**
 * The unique Id of drive during which the accident occured
 */
@property (nonatomic, readonly, nonnull) NSString *driveId;

/**
 * The location of the accident.
 */
@property (nonatomic, readonly, nonnull) ZendriveLocationPoint *accidentLocation;

/**
 * The timestamp of the accident in milliseconds since epoch.
 */
@property (nonatomic, readonly) long long timestamp;

/**
 * The session that was in progress when the accident occured, if a session
 * was started in the SDK.
 *
 * @see `+[Zendrive startSession:]`
 */
@property (nonatomic, readonly, nullable) NSString *sessionId;

/**
 * The tracking id of the ongoing drive when the accident occured.
 *
 * @see `+[Zendrive startManualDrive:completionHandler]`
 */
@property (nonatomic, readonly, nullable) NSString *trackingId;

/**
 * The confidence of detected accident.
 *
 */
@property (nonatomic, readonly) ZendriveAccidentConfidence confidence;

/**
 * A unique identifier of this accident.
 */
@property (nonatomic, readonly, nonnull) NSString* accidentId;

/**
 *  Initializer for `ZendriveAccidentInfo`.
 *
 *  @param location The location of the accident
 *  @param timestamp The timestamp of the accident in milliseconds since epoch
 *  @param trackingId The tracking id of the ongoing drive when the accident occured
 *  @param sessionId The session that was in progress when the accident
 *                   occured, if a session was started in the SDK
 *  @param confidence Confidence measure of the detected accident
 *  @param accidentId A unique identifier of this accident
 *  @param driveId The unique Id of drive during which the accident occured
 *  @return `ZendriveAccidentInfo` object
 */
- (nonnull id)initWithLocation:(nonnull ZendriveLocationPoint *)location
                     timestamp:(long long)timestamp
                    trackingId:(nullable NSString *)trackingId
                     sessionId:(nullable NSString *)sessionId
                    confidence:(ZendriveAccidentConfidence)confidence
                    accidentId:(nonnull NSString *)accidentId
                       driveId:(nonnull NSString*)driveId;

/**
 * Returns a dictionary that represents the `ZendriveAccidentInfo` object.
 */
- (nonnull NSDictionary *)toDictionary;

/**
 * Returns a JSON formatted string that represents the `ZendriveAccidentInfo` object.
 */
- (nonnull NSString *)toJson;

@end
