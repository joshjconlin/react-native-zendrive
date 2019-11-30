//  Zendrive React Native MVP
//
//  Created by Cade Beller, Josh Conlin on 8/19/19.
//

package com.jconlin.rnzendrive;

import android.content.Context;
import android.os.Build;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;

import com.zendrive.sdk.ZendriveNotificationContainer;
import com.zendrive.sdk.ZendriveNotificationProvider;

/**
 * Used to provide the Zendrive SDK with notifications that are triggered when
 * the SDK goes into foreground mode.
 *
 * NOTE: The OS might kill the Zendrive service if it's under high pressure.
 * This can occasionally result in split or missing trips. The notification is
 * visible to the user and should contain an appropriate message for them.
 */
public class ZendriveSdkNotificationProvider implements ZendriveNotificationProvider {

    @NonNull
    @Override
    @RequiresApi(Build.VERSION_CODES.O)
    public ZendriveNotificationContainer getMaybeInDriveNotificationContainer(@NonNull Context context) {
        return new ZendriveNotificationContainer(ZendriveSdkNotificationUtility.FOREGROUND_MODE_NOTIFICATION_ID,
                ZendriveSdkNotificationUtility.createMaybeInDriveNotification(context));
    }

    @NonNull
    @Override
    public ZendriveNotificationContainer getInDriveNotificationContainer(@NonNull Context context) {
        return new ZendriveNotificationContainer(ZendriveSdkNotificationUtility.FOREGROUND_MODE_NOTIFICATION_ID,
                ZendriveSdkNotificationUtility.createInDriveNotification(context));
    }
}
