//
//  ZendriveInsurance.h
//  ZendriveSDK
//
//  Created by Yogesh on 7/14/17.
//  Copyright © 2017 Zendrive Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *
 * Block type used to define blocks called by `ZendriveInsurance` public api calls on completion
 *
 * If api call succeeds, success is set to YES and error is nil. If api call fails,
 * success is set to NO and error contains details for why api call failed. Refer to
 * `ZendriveError` for a list of error codes.
 */
typedef void (^ZendriveInsuranceApiCallHandler)(BOOL success, NSError * __nullable error);

/**
 * Applications which want to record Fairmatic insurance periods for a driver may use these APIs.
 *
 * All drives (automatically detected or manually started) when a period is in progress
 * will be tagged with the period id. This period id will be made available in the reports and API
 * that Fairmatic provides via `Zendrive`.
 *
 * Only one period can be active at a time.
 * Switching periods or calling `+stopPeriod:completionHandler:` stops any active drives (automatic or manual).
 * A drive with multiple insurance periods will be split into multiple trips for different
 * insurance periods.
 */
@interface ZendriveInsurance : NSObject

/**
 * Start Fairmatic insurance period 1 in the SDK.
 *
 * Trips in this period will be detected automatically.
 *
 *
 * @param completionHandler A block object to be executed when the task finishes.
 * This block has no return value and two arguments:
 * isSuccess, A boolean that suggests successful completion of the call
 * the error, A valid error of `ZendriveErrorDomain.kZendriveErrorDomain` (`ZendriveError`) is
 * returned in case of a failure.
 * Possible error codes returned: kZendriveErrorNotSetup, kZendriveErrorInsurancePeriodSame.
 * Refer to `ZendriveError` for more details on the errors.
 *
 * @warning This is deprecated. Please contact Zendrive team if you are an existing Fairmatic
 * customer and you use startPeriod1: API.
 */
+ (void)startPeriod1:(nullable ZendriveInsuranceApiCallHandler)completionHandler __deprecated;

/**
 * Start Fairmatic insurance period 1 in the SDK.
 *
 * A manual trip of id trackingId will be started immediately on this call.
 * The entire duration in this period will be recorded as a single trip.
 * If period 1 is already in progress with the same trackingId, this call will be a no-op.
 *
 * @param completionHandler A block object to be executed when the task finishes.
 * This block has no return value and two arguments:
 * isSuccess, A boolean that suggests successful completion of the call
 * the error, A valid error of `ZendriveErrorDomain.kZendriveErrorDomain` (`ZendriveError`) is
 * returned in case of a failure.
 * Possible error codes returned: `kZendriveErrorNotSetup`, `kZendriveErrorInsurancePeriodSame`,
 * Refer to `ZendriveError` for more details on the errors.
 */
+ (void)startDriveWithPeriod1:(nullable ZendriveInsuranceApiCallHandler)completionHandler;

/**
 * Start Fairmatic insurance period 2 in the SDK.
 *
 * A manual trip of id trackingId will be started immediately on this call.
 * The entire duration in this period will be recorded as a single trip.
 * If period 2 is already in progress with the same trackingId, this call will be a no-op.
 *
 * @param trackingId An identifier which allows identifying this drive uniquely.
 * This drive identifier must be unique for the user.
 *
 * @param completionHandler A block object to be executed when the task finishes.
 * This block has no return value and two arguments:
 * isSuccess, A boolean that suggests successful completion of the call
 * the error, A valid error of `ZendriveErrorDomain.kZendriveErrorDomain` (`ZendriveError`) is
 * returned in case of a failure.
 * Possible error codes returned: `kZendriveErrorNotSetup`, `kZendriveErrorInsurancePeriodSame`,
 * `kZendriveErrorInvalidTrackingId`. Refer to `ZendriveError` for more details on the errors.
 */
+ (void)startDriveWithPeriod2:(nonnull NSString *)trackingId completionHandler:(nullable ZendriveInsuranceApiCallHandler)completionHandler;

/**
 * Start Fairmatic insurance period 3 in the SDK.
 *
 * A manual trip of id trackingId will be started immediately on this call.
 * The entire duration in this period will be recorded as a single trip.
 * If period 3 is already in progress with the same trackingId, this call will be a no-op.
 *
 * @param trackingId An identifier which allows identifying this drive uniquely.
 * This drive identifier must be unique for the user.
 *
 * @param completionHandler A block object to be executed when the task finishes.
 * This block has no return value and two arguments:
 * isSuccess, A boolean that suggests successful completion of the call
 * the error, A valid error of `ZendriveErrorDomain.kZendriveErrorDomain` (`ZendriveError`) is
 * returned in case of a failure.
 * Possible error codes returned: `kZendriveErrorNotSetup`, `kZendriveErrorInsurancePeriodSame`,
 * `kZendriveErrorInvalidTrackingId`. Refer to `ZendriveError` for more details on the errors.
 */
+ (void)startDriveWithPeriod3:(nonnull NSString *)trackingId completionHandler:(nullable ZendriveInsuranceApiCallHandler)completionHandler;

/**
 * Stop currently ongoing Fairmatic insurance period if any.
 *
 * Ongoing trips at the time of this call will be stopped.
 * Auto trip detection is turned off on this call.
 *
 * @param completionHandler A block object to be executed when the task finishes.
 * This block has no return value and two arguments:
 * isSuccess, A boolean that suggests successful completion of the call
 * the error, A valid error of `ZendriveErrorDomain.kZendriveErrorDomain` (`ZendriveError`) is
 * returned in case of a failure.
 * Possible error codes returned: `kZendriveErrorNotSetup`.
 * Refer to ZendriveError for more details on the errors.
 */

+ (void)stopPeriod:(nullable ZendriveInsuranceApiCallHandler)completionHandler;
@end
