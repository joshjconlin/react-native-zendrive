//  Zendrive React Native MVP
//
//  Created by Cade Beller, Josh Conlin on 8/19/19.
//

#import <ZendriveSDK/ZendriveDriveStartInfo.h>
#import <ZendriveSDK/ZendriveDriveResumeInfo.h>
#import <ZendriveSDK/ZendriveDriveInfo.h>
#import "ZendriveDelegateManager.h"
#import <React/RCTLog.h>

// Callback logs for testing

@implementation ZendriveDelegateManager

- (void)processStartOfDrive:(ZendriveDriveStartInfo *)startInfo {
  RCTLog(@"Zendrive Start");
}

- (void)processResumeOfDrive:(ZendriveDriveResumeInfo *)drive {
  RCTLog(@"Zendrive Resume");
}

- (void)processEndOfDrive:(ZendriveDriveInfo *)drive {
  RCTLog(@"Zendrive End");
}

- (void)processLocationDenied {
  RCTLog(@"Zendrive User denied Location to Zendrive SDK.");
}

- (void)processLocationApproved   {
  RCTLog(@"Zendrive User approved Location to Zendrive SDK.");
}

- (void)processAccidentDetected:(ZendriveAccidentInfo *)accidentInfo {
  RCTLog(@"Zendrive Accident detected by Zendrive SDK.");
}

@end
