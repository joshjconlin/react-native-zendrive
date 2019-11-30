//
//  RNZendriveManager.m
//  RNZendrive
//
//  Created by Cade Beller, Josh Conlin on 8/19/19.
//

//  Zendrive React Native MVP

#import <objc/runtime.h>
#import "RNZendrive.h"
#import <ZendriveSDK/Zendrive.h>
#import <React/RCTLog.h>
#import "ZendriveDelegateManager.h"
#import <ZendriveSDK/ZendriveInsurance.h>
#import <Foundation/NSError.h>
#import <Foundation/NSBundle.h>

/**
 *
 * This native module bridges the native Zendrive SDK to work with our RN
 * codebase. This is not a complete implementation of their SDK but rather an
 * MVP that suits our needs specifically.
 *
 * Usage Example:
 *
 * import { NativeModules } from 'react-native';
 *
 * const ZendriveManager = NativeModules.ZenDriveHeader; ...
 * ZendriveManger.enableZendrive(driverID);
 */

@implementation RNZendrive

// makes it easier to return Zendrive NSObject types
- (NSDictionary *) dictionaryWithPropertiesOfObject:(id)obj
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    unsigned count;
    objc_property_t *properties = class_copyPropertyList([obj class], &count);

    for (int i = 0; i < count; i++) {
        NSString *key = [NSString stringWithUTF8String:property_getName(properties[i])];
        if ([obj valueForKey:key] != nil) {
            // if value is NSString or NSNumber set value, else assume is another NSObject and recursively get keys
            if ([[obj valueForKey: key] isKindOfClass: [NSString class]] || [[obj valueForKey: key] isKindOfClass: [NSNumber class]]) {
                [dict setObject:[obj valueForKey:key] forKey:key];
            } else {
                NSDictionary *lower = [self dictionaryWithPropertiesOfObject: [obj valueForKey: key]];
                [dict setObject: lower forKey: key];
            }
        }
    }

    free(properties);

    return [NSDictionary dictionaryWithDictionary:dict];
}

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(enableZendrive: (NSString *)driverID
        enableZendriveWithResolver:(RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    id<ZendriveDelegateProtocol> zdDelegate = [[ZendriveDelegateManager alloc] init];

    ZendriveConfiguration *configuration = [[ZendriveConfiguration alloc] init];

    NSString *path = [[NSBundle mainBundle] pathForResource: @"Info" ofType: @"plist"];
    NSDictionary *dict = [NSDictionary dictionaryWithContentsOfFile: path];
    id ZendriveKey = [dict objectForKey: @"ZendriveKey"];

    configuration.applicationKey = ZendriveKey; // API KEY FROM ZENDRIVE DASHBOARD
    configuration.driverId = driverID; // REQUIRED myDriverID
    configuration.driveDetectionMode = ZendriveDriveDetectionModeAutoOFF;
    NSMutableDictionary *response = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"setup_success", @"error", nil];

    [Zendrive setupWithConfiguration:configuration
                            delegate:zdDelegate // Can be nil
                   completionHandler:^(BOOL success, NSError *error) {
                       if(success) {
                           RCTLog(@"ZenDrive Setup Success");
                           // This insures all drives start in period 1
                           [response setObject:@(success) forKey:@"setup_success"];
                           [response setObject: [NSNull null] forKey: @"error"];
                           [ZendriveInsurance startDriveWithPeriod1:^(BOOL isSuccess, NSError * _Nullable error) {
                               RCTLog(@"Zendrive startDriveWithPeriod1");
                               resolve(response);
                           }];
                       } else {
                           RCTLog(@"ZenDrive Setup Failure");
                           reject(@"error", @"setup zendrive error", error);
                       }
                   }];
}

RCT_EXPORT_METHOD(disableZendrive: (RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableDictionary *response = [NSMutableDictionary dictionaryWithObjectsAndKeys: @"error", @"teardown_success", nil];
    // Calling the teardown in an ongoing period can result in malformed data
    [ZendriveInsurance stopPeriod:^(BOOL isSuccess, NSError * _Nullable apiError) {
        if (isSuccess) {
            [response setObject: [NSNull null] forKey: @"error"];
            RCTLog(@"Zendrive stopPeriod success");
            [Zendrive teardownWithCompletionHandler:^{
                [response setObject:@(true) forKey: @"teardown_success"];
                RCTLog(@"Zendrive Teardown Success");
                resolve(response);
            }];
        } else {
            reject(@"error", @"teardown error, can't stop period", apiError);
            RCTLog(@"Zendrive stopPeriod error");
        }
    }];
}

RCT_EXPORT_METHOD(getIsSDKSetup: (RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    NSNumber *setup = [NSNumber numberWithBool: Zendrive.isSDKSetup];
    resolve(setup);
}

RCT_EXPORT_METHOD(getZendriveState: (RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    [Zendrive getZendriveState: ^(ZendriveState *_Nullable zendriveState) {
        if (zendriveState == nil) {
            resolve(zendriveState);
        } else {
            NSDictionary *response = [self dictionaryWithPropertiesOfObject: zendriveState];
            resolve(response);
        }
    }];
}

RCT_EXPORT_METHOD(getActiveDriveInfo: (RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    if (Zendrive.activeDriveInfo == nil) {
        resolve(Zendrive.activeDriveInfo);
    } else {
        NSDictionary *response = [self dictionaryWithPropertiesOfObject: Zendrive.activeDriveInfo];
        resolve(response);
    }
}

RCT_EXPORT_METHOD(startPeriod1: (RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableDictionary *response = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"start_period1_success", @"error", nil];
    [ZendriveInsurance startDriveWithPeriod1:^(BOOL isSuccess, NSError * _Nullable error) {
        if (isSuccess) {
            RCTLog(@"Zendrive startDriveWithPeriod1");
            [response setObject: @(isSuccess) forKey: @"start_period1_success"];
            [response setObject: [NSNull null] forKey: @"error"];
            resolve(response);
        } else {
            RCTLog(@"Zendrive starteDriveWithPeriod1 error");
            reject(@"error", @"start period 1 error", error);
        }
    }];
}

RCT_EXPORT_METHOD(startPeriod2: (NSString *)trackingID
        startPeriod2WithResolver:(RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableDictionary *response = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"start_period2_success", @"error", nil];
    [ZendriveInsurance startDriveWithPeriod2:trackingID
                           completionHandler:^(BOOL isSuccess, NSError *_Nullable apiError) {
                               if (isSuccess) {
                                   RCTLog(@"Zendrive startDriveWithPeriod2 Success");
                                   [response setObject: @(isSuccess) forKey: @"start_period2_success"];
                                   [response setObject: [NSNull null] forKey: @"error"];
                                   resolve(response);
                               } else {
                                   RCTLog(@"Zendrive starteDriveWithPeriod2 error");
                                   reject(@"error", @"start period 2 error", apiError);
                               }
                           }];
}

RCT_EXPORT_METHOD(startPeriod3: (NSString *)trackingID
        startPeriod3WithResolver:(RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableDictionary *response = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"start_period3_success", @"error", nil];
    [ZendriveInsurance startDriveWithPeriod3:trackingID
                           completionHandler:^(BOOL isSuccess, NSError *_Nullable apiError) {
                               if (isSuccess) {
                                   RCTLog(@"Zendrive startDriveWithPeriod3 Success");
                                   [response setObject: @(isSuccess) forKey: @"start_period3_success"];
                                   [response setObject: [NSNull null] forKey: @"error"];
                                   resolve(response);
                               } else {
                                   RCTLog(@"Zendrive startDriveWithPeriod3 error");
                                   reject(@"error", @"start period 3 error", apiError);
                               }
                           }];
}

RCT_EXPORT_METHOD(stopPeriod: (RCTPromiseResolveBlock)resolve
        rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableDictionary *response = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"stop_period_success", @"error", nil];
    [ZendriveInsurance stopPeriod:^(BOOL isSuccess, NSError * _Nullable apiError) {
        if (isSuccess) {
            RCTLog(@"Zendrive stopPeriod Success");
            [response setObject: @(isSuccess) forKey: @"stop_period_success"];
            [response setObject: [NSNull null] forKey: @"error"];
            resolve(response);
        } else {
            RCTLog(@"Zendrive stopPeriod error");
            reject(@"error", @"stop period error", apiError);
        }
    }];
}

@end
