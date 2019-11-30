package com.jconlin.rnzendrive;

import android.app.Activity;
import android.os.Bundle;

class NotificationActivity extends Activity {
    private Activity activityReference;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        activityReference = this;
    }

}
