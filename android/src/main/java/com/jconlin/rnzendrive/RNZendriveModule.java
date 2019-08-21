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

import com.zendrive.sdk.*;
import com.zendrive.sdk.insurance.ZendriveInsurance;

import java.util.Map;
import java.util.HashMap;

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

        ZendriveInsurance.startDriveWithPeriod1(this.getReactApplicationContext(), new ZendriveOperationCallback() {
            @Override
            public void onCompletion(ZendriveOperationResult result) {
                if (result.isSuccess()) {
                    promise.resolve(result.createSuccess());
                } else {
                    promise.reject(result.getErrorMessage());
                }
            }
        });
    }

    @ReactMethod
    public void startPeriod2(String trackingID, final Promise promise) {

        ZendriveInsurance.startDriveWithPeriod2(this.getReactApplicationContext(), trackingID,
                new ZendriveOperationCallback() {
                    @Override
                    public void onCompletion(ZendriveOperationResult result) {
                        if (result.isSuccess()) {
                            promise.resolve(result.createSuccess());
                        } else {
                            promise.reject(result.getErrorMessage());
                        }
                    }
                });
    }

    @ReactMethod
    public void startPeriod3(String trackingID, final Promise promise) {
        ZendriveInsurance.startDriveWithPeriod3(this.getReactApplicationContext(), trackingID,
                new ZendriveOperationCallback() {
                    @Override
                    public void onCompletion(ZendriveOperationResult result) {
                        if (result.isSuccess()) {
                            promise.resolve(result.createSuccess());
                        } else {
                            promise.reject(result.getErrorMessage());
                        }
                    }
                });
    }

    @ReactMethod
    public void stopPeriod(final Promise promise) {
        ZendriveInsurance.stopPeriod(this.getReactApplicationContext(), new ZendriveOperationCallback() {
            @Override
            public void onCompletion(ZendriveOperationResult result) {
                if (result.isSuccess()) {
                    promise.resolve(result.createSuccess());

                } else {
                    promise.reject(result.getErrorMessage());
                }
            }
        });
    }

    @ReactMethod
    public void enableZendrive(String driverID, final Promise promise) {

        ZendriveConfiguration zendriveConfiguration = new ZendriveConfiguration(SDK_KEY, driverID,
                ZendriveDriveDetectionMode.AUTO_ON);

        Zendrive.setup(this.getReactApplicationContext(), zendriveConfiguration, null,
                ZendriveSdkNotificationProvider.class, new ZendriveOperationCallback() {

                    @Override
                    public void onCompletion(ZendriveOperationResult result) {
                        if (result.isSuccess()) {
                            startOne();
                            promise.resolve(result.createSuccess());
                        } else {
                            promise.reject(result.getErrorMessage());
                        }
                    }
                });

    }

    @ReactMethod
    public void disableZendrive(final Promise promise) {

        ZendriveInsurance.stopPeriod(this.getReactApplicationContext(), new ZendriveOperationCallback() {

            @Override
            public void onCompletion(ZendriveOperationResult result) {
                if (result.isSuccess()) {
                    tearDown();
                    promise.resolve(result.createSuccess());
                } else {
                    promise.reject(result.getErrorMessage());
                }
            }
        }); // Calling the teardown in an ongoing period can result in malformed data

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
