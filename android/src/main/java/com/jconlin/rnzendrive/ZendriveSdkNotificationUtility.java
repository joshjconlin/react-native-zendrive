//  Zendrive React Native MVP
//
//  Created by Cade Beller, Josh Conlin on 8/19/19.
//

package com.jconlin.rnzendrive;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import com.google.android.gms.location.LocationSettingsResult;

// These notification attributes can be changed

public class ZendriveSdkNotificationUtility {
    public static final int FOREGROUND_MODE_NOTIFICATION_ID = 98;

    private static final String FOREGROUND_CHANNEL_KEY = "Foreground";
    private static final String SETTINGS_CHANNEL_KEY = "Settings";
    private static NotificationManagerCompat notificationManager;

    public static Notification createMaybeInDriveNotification(Context context) {
        createNotificationChannels(context);
        return new NotificationCompat.Builder(context, FOREGROUND_CHANNEL_KEY)
                .setPriority(NotificationCompat.PRIORITY_MIN).setCategory(NotificationCompat.CATEGORY_SERVICE)
                .setContentText("Application is tracking your location.")
                .setContentIntent(getNotificationClickIntent(context)).build();
    }

    public static Notification createInDriveNotification(Context context) {
        createNotificationChannels(context);
        return new NotificationCompat.Builder(context, FOREGROUND_CHANNEL_KEY)
                .setCategory(NotificationCompat.CATEGORY_SERVICE).setContentText("Application is tracking your location.")
                .setContentIntent(getNotificationClickIntent(context)).build();
    }

    private static void createNotificationChannels(Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
            NotificationChannel lowPriorityNotificationChannel = new NotificationChannel(FOREGROUND_CHANNEL_KEY,
                    "Application trip tracking", NotificationManager.IMPORTANCE_MIN);
            lowPriorityNotificationChannel.setShowBadge(false);
            manager.createNotificationChannel(lowPriorityNotificationChannel);

            NotificationChannel defaultNotificationChannel = new NotificationChannel(SETTINGS_CHANNEL_KEY, "Problems",
                    NotificationManager.IMPORTANCE_HIGH);
            defaultNotificationChannel.setShowBadge(true);
            manager.createNotificationChannel(defaultNotificationChannel);

        }
    }

    private static PendingIntent getNotificationClickIntent(Context context) {
        Intent notificationIntent = new Intent(context.getApplicationContext(), NotificationActivity.class);
        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        return PendingIntent.getActivity(context.getApplicationContext(), 0, notificationIntent, 0);
    }
}
