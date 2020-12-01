package com.jocloud.rtc.demo;

import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.text.TextUtils;
import android.view.View;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;

import org.jetbrains.annotations.NotNull;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import androidx.annotation.NonNull;

import tv.athena.core.axis.Axis;
import tv.athena.feedback.api.FeedbackData;
import tv.athena.feedback.api.IFeedbackService;

/**
 * 意见反馈模块
 *
 * @author huangcanbin@yy.com
 * @date 2020年9月24日
 */
public class FeedbackModule extends ReactContextBaseJavaModule {

    public FeedbackModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    /**
     * 默认反馈只会上传主目录下的日志，不能上传文件夹下面日志，所以需要我们手动添加。
     */
    private void addFiles(@NonNull List<File> files, @NonNull File fileDirectory) {
        if (fileDirectory.exists()) {
            if (fileDirectory.isDirectory()) {
                File[] listFiles = fileDirectory.listFiles();
                if (listFiles == null) {
                    return;
                }

                for (File file : listFiles) {
                    if (file.exists()) {
                        if (file.isDirectory()) {
                            addFiles(files, file);
                        } else {
                            files.add(file);
                        }
                    }
                }
            } else {
                files.add(fileDirectory);
            }
        }
    }

    @ReactMethod
    public void doFeedback(ReadableMap map, Promise promise) {
        String appId = "RtcRNdemo-android";
        String uid = map.getString("uid");
        String feedbackMsg = map.getString("feedbackMsg");

        File fileLogs = new File(ThunderConst.LOG_PATH);
        List<File> files = new ArrayList<>();
        addFiles(files, fileLogs);

        if (feedbackMsg == null) {
            feedbackMsg = "";
        }
        FeedbackData.Builder builder =
                new FeedbackData.Builder(appId, 0, feedbackMsg)
                        .setExternPathlist(files)
                        .setFeedbackStatusListener(new FeedbackData.FeedbackStatusListener() {
                            @Override
                            public void onFailure(@NotNull FailReason failReason) {
                                promise.resolve(-1);
                            }

                            @Override
                            public void onComplete() {
                                promise.resolve(0);
                            }

                            @Override
                            public void onProgressChange(int i) {

                            }
                        });
        FeedbackData feedbackData = builder.create();
        feedbackData.setUid(uid);
        Axis.Companion.getService(IFeedbackService.class).sendNewLogUploadFeedback(feedbackData);
    }

    @ReactMethod
    public void getAppVersionName(ReadableMap map, Promise promise) {
        PackageManager packageManager = getReactApplicationContext().getPackageManager();
        try {
            PackageInfo packageInfo =
                    packageManager.getPackageInfo(getReactApplicationContext().getPackageName(), 0);
            if (packageInfo == null) {
                return;
            }

            String version = packageInfo.versionName + "-" + packageInfo.versionCode;
            promise.resolve(version);
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
    }

    @ReactMethod
    public void getLogPath(ReadableMap map, Promise promise) {
        ThunderConst.LOG_PATH = FileUtil.getLog(getReactApplicationContext());
        promise.resolve(ThunderConst.LOG_PATH);
    }

    @ReactMethod
    public void getABI(ReadableMap map, Promise promise) {
        String cpuABI = "";
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            String[] cpuABIs = android.os.Build.SUPPORTED_ABIS;
            if (cpuABIs != null) {
                cpuABI = TextUtils.join(",", cpuABIs);
            }
        } else {
            cpuABI = android.os.Build.CPU_ABI;
        }
        promise.resolve(cpuABI);
    }

    @ReactMethod
    public void crashTest(ReadableMap map, Promise promise) {
        View view = null;
        view.getId();
    }

    @NonNull
    @Override
    public String getName() {
        return FeedbackModule.class.getSimpleName();
    }
}
