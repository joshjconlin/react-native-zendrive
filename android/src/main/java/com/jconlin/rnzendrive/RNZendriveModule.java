//  Zendrive React Native
//
//  Created by Josh Conlin, Cade Beller on 8/19/19.
//

package com.jconlin.rnzendrive;

import android.content.pm.ApplicationInfo;
import android.util.Log;

import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.Arguments;

import com.zendrive.sdk.*;
import com.zendrive.sdk.insurance.ZendriveInsurance;


import java.util.Map;
import java.util.HashMap;
import java.util.function.Function;

public class RNZendriveModule extends ReactContextBaseJavaModule {

    private final ReactApplicationContext reactContext;
    private final String SDK_KEY; // API KEY FROM ZENDRIVE DASHBOARD
    private static final String TAG = "Zendrive";

    private String trackingID;

    public RNZendriveModule(ReactApplicationContext reactContext, String sdkKey) {
        super(reactContext);
        this.reactContext = reactContext;
        this.SDK_KEY = sdkKey;
    }

    @Override
    public String getName() {
        return "RNZendrive";
    }

    @ReactMethod
    public void startPeriod1(final Promise promise) {
        try {
            ZendriveInsurance.startDriveWithPeriod1(this.getReactApplicationContext(), new ZendriveOperationCallback() {
                @Override
                public void onCompletion(ZendriveOperationResult result) {
                    if (result.isSuccess()) {
                        WritableMap resultObj = Arguments.createMap();
                        resultObj.putBoolean("start_period1_success", true);
                        resultObj.putBoolean("error", false);
                        promise.resolve(resultObj);
                    } else {
                        promise.reject(result.getErrorMessage());
                    }
                }
            });
        } catch (Exception e) {
            promise.reject("START_PERIOD1_ERROR", e);
        }
    }

    @ReactMethod
    public void startPeriod2(String trackingID, final Promise promise) {
        try {
            ZendriveInsurance.startDriveWithPeriod2(this.getReactApplicationContext(), trackingID,
                    new ZendriveOperationCallback() {
                        @Override
                        public void onCompletion(ZendriveOperationResult result) {
                            if (result.isSuccess()) {
                                WritableMap resultObj = Arguments.createMap();
                                resultObj.putBoolean("start_period2_success", true);
                                resultObj.putBoolean("error", false);
                                promise.resolve(resultObj);
                            } else {
                                promise.reject(result.getErrorMessage());
                            }
                        }
                    });
        } catch (Exception e) {
            promise.reject("START_PERIOD2_ERROR", e);
        }
    }

    @ReactMethod
    public void startPeriod3(String trackingID, final Promise promise) {
        try {
            ZendriveInsurance.startDriveWithPeriod3(this.getReactApplicationContext(), trackingID,
                    new ZendriveOperationCallback() {
                        @Override
                        public void onCompletion(ZendriveOperationResult result) {
                            if (result.isSuccess()) {
                                WritableMap resultObj = Arguments.createMap();
                                resultObj.putBoolean("start_period3_success", true);
                                resultObj.putBoolean("error", false);
                                promise.resolve(resultObj);
                            } else {
                                promise.reject(result.getErrorMessage());
                            }
                        }
                    });
        } catch (Exception e) {
            promise.reject("START_PERIOD3_ERROR", e);
        }
    }

    @ReactMethod
    public void stopPeriod(final Promise promise) {
        try {
            ZendriveInsurance.stopPeriod(this.getReactApplicationContext(), new ZendriveOperationCallback() {
                @Override
                public void onCompletion(ZendriveOperationResult result) {
                    if (result.isSuccess()) {
                        WritableMap resultObj = Arguments.createMap();
                        resultObj.putBoolean("stop_period_success", true);
                        resultObj.putBoolean("error", false);
                        promise.resolve(resultObj);

                    } else {
                        promise.reject(result.getErrorMessage());
                    }
                }
            });
        } catch (Exception e) {
            promise.reject("STOP_PERIOD_ERROR", e);
        }
    }

    @ReactMethod
    public void getIsSDKSetup(Promise promise) {
        try {
            boolean isSetup = Zendrive.isSDKSetup(this.getReactApplicationContext());
            promise.resolve(isSetup);
        } catch (Exception e) {
            promise.reject(e);
        }
    }

    @ReactMethod
    public void getZendriveState(final Promise promise) {
        try {
            Zendrive.getZendriveState(this.getReactApplicationContext(), new ZendriveStateCallback() {
                @Override
                public void onComplete(ZendriveState state) {
                    try {
                        if (state == null) {
                            promise.resolve(null);
                        } else {
                            Map stateMap = MapUtil.classToMap(state);
                            WritableMap result = MapUtil.toWritableMap(stateMap);
                            promise.resolve(result);
                        }
                    } catch (Exception e) {
                        promise.reject(e);
                    }
                }
            });
        } catch (Exception e) {
            promise.reject(e);
        }
    }

    @ReactMethod
    public void getActiveDriveInfo(final Promise promise) {
        try {
            ActiveDriveInfo driveInfo = Zendrive.getActiveDriveInfo(this.getReactApplicationContext());
            if (driveInfo == null) {
                promise.resolve(null);
            } else {
                Map driveInfoMap = MapUtil.classToMap(driveInfo);
                WritableMap result = MapUtil.toWritableMap(driveInfoMap);
                promise.resolve(result);
            }
        } catch (Exception e) {
            promise.reject(e);
        }
    }

    @ReactMethod
    public void enableZendrive(String driverID, final Promise promise) {
        try {
            ZendriveConfiguration zendriveConfiguration = new ZendriveConfiguration(SDK_KEY, driverID,
                    ZendriveDriveDetectionMode.AUTO_ON);

            Zendrive.setup(this.getReactApplicationContext(), zendriveConfiguration, null,
                    ZendriveSdkNotificationProvider.class, new ZendriveOperationCallback() {

                        @Override
                        public void onCompletion(ZendriveOperationResult result) {
                            if (result.isSuccess()) {
                                startOne();
                                WritableMap resultObj = Arguments.createMap();
                                resultObj.putBoolean("enable_zendrive_success", true);
                                resultObj.putBoolean("error", false);
                                promise.resolve(resultObj);
                            } else {
                                promise.reject(result.getErrorMessage());
                            }
                        }
                    });
        } catch (Exception e) {
            promise.reject("ENABLE_ZENDRIVE_ERROR", e);
        }
    }

    @ReactMethod
    public void disableZendrive(final Promise promise) {
        try {
            ZendriveInsurance.stopPeriod(this.getReactApplicationContext(), new ZendriveOperationCallback() {

                @Override
                public void onCompletion(ZendriveOperationResult result) {
                    if (result.isSuccess()) {
                        tearDown();
                        WritableMap resultObj = Arguments.createMap();
                        resultObj.putBoolean("disable_zendrive_success", true);
                        resultObj.putBoolean("error", false);
                        promise.resolve(resultObj);
                    } else {
                        promise.reject(result.getErrorMessage());
                    }
                }
            }); // Calling the teardown in an ongoing period can result in malformed data
        } catch (Exception e) {
            promise.reject("DISABLE_ZENDRIVE_ERROR", e);
        }
    }

    private void startOne() {
        ZendriveInsurance.startDriveWithPeriod1(this.getReactApplicationContext(), new ZendriveOperationCallback() {
            public void onCompletion(ZendriveOperationResult result) {

            }
        });
    }

    private void tearDown() {
        Zendrive.teardown(this.getReactApplicationContext(), new ZendriveOperationCallback() {
            public void onCompletion(ZendriveOperationResult result) {

            }
        });
    }
}
