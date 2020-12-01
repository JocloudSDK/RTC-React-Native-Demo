package com.jocloud.rtc.demo;

import android.os.Bundle;
import android.view.WindowManager;

import com.facebook.react.ReactActivity;

/**
 * 主页
 *
 * @author huangcanbin@yy.com
 * @date 2020年9月24日
 */
public class MainActivity extends ReactActivity {

    /**
     * Returns the name of the main component registered from JavaScript. This is used to schedule
     * rendering of the component.
     */
    @Override
    protected String getMainComponentName() {
        return "JocloudRTC";
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onBackPressed() {
        moveTaskToBack(false);
    }
}
