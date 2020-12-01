package com.jocloud.rtc.demo;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;

import com.facebook.react.PackageList;
import com.facebook.react.ReactApplication;
import com.facebook.react.ReactInstanceManager;
import com.facebook.react.ReactNativeHost;
import com.facebook.react.ReactPackage;
import com.facebook.soloader.SoLoader;

import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.util.List;

import androidx.core.content.ContextCompat;
import androidx.multidex.MultiDexApplication;
import tv.athena.core.axis.Axis;
import tv.athena.crash.api.ICrashService;
import tv.athena.klog.api.ILogConfig;
import tv.athena.klog.api.ILogService;
import tv.athena.klog.api.LogLevel;
import tv.athena.util.FP;
import tv.athena.util.ProcessorUtils;
import tv.athena.util.RuntimeInfo;

/**
 * Jocloud RN项目
 *
 * @author huangcanbin@yy.com
 * @date 2020年9月24日
 */
public class ThunderApplication extends MultiDexApplication implements ReactApplication {

    private final ReactNativeHost mReactNativeHost =
            new ReactNativeHost(this) {
                @Override
                public boolean getUseDeveloperSupport() {
                    return BuildConfig.DEBUG;
                }

                @Override
                protected List<ReactPackage> getPackages() {
                    @SuppressWarnings("UnnecessaryLocalVariable")
                    List<ReactPackage> packages = new PackageList(this).getPackages();
                    packages.add(new FeedbackPackage());
                    return packages;
                }

                @Override
                protected String getJSMainModuleName() {
                    return "index";
                }
            };

    @Override
    public ReactNativeHost getReactNativeHost() {
        return mReactNativeHost;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        SoLoader.init(this, /* native exopackage */ false);
        initializeFlipper(this, getReactNativeHost().getReactInstanceManager());

        initPrivate();
    }

    /**
     * 公司内部代码，第三方无需关注
     */
    private void initPrivate() {
        String processName = ProcessorUtils.INSTANCE.getMyProcessName();
        RuntimeInfo.INSTANCE.appContext(this)
                .packageName(this.getPackageName())
                .processName((null != processName) ? processName : "")
                .isDebuggable(true)
                .isMainProcess(FP.eq(RuntimeInfo.sPackageName, RuntimeInfo.sProcessName));

        // 初始化 Log 服务
        ILogService logService = Axis.Companion.getService(ILogService.class);
        if (null != logService) {
            ILogConfig iLogConfig = logService.config()
                    .logCacheMaxSiz(100 * 1024 * 1024)
                    .singleLogMaxSize(4 * 1024 * 1024)
                    .logLevel(LogLevel.INSTANCE.getLEVEL_VERBOSE())
                    .processTag(ThunderConst.FEEDBACK_CRASHLOGID);

            if (ContextCompat.checkSelfPermission(this,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE) ==
                    PackageManager.PERMISSION_GRANTED) {
                File file = getExternalFilesDir(ThunderConst.LOG_NAME);
                if (file != null) {
                    iLogConfig.logPath(file.getAbsolutePath());
                }
            } else {
                File file = new File(getFilesDir(), ThunderConst.LOG_NAME);
                iLogConfig.logPath(file.getAbsolutePath());
            }

            iLogConfig.apply();
        }

        // 初始化 Crash 服务
        ICrashService crashService = Axis.Companion.getService(ICrashService.class);
        if (null != crashService) {
            crashService.start(ThunderConst.FEEDBACK_CRASHLOGID, "");
        }
    }

    /**
     * Loads Flipper in React Native templates. Call this in the onCreate method with something like
     * initializeFlipper(this, getReactNativeHost().getReactInstanceManager());
     *
     * @param context
     * @param reactInstanceManager
     */
    private static void initializeFlipper(
            Context context, ReactInstanceManager reactInstanceManager) {
        if (BuildConfig.DEBUG) {
            try {
        /*
         We use reflection here to pick up the class that initializes Flipper,
        since Flipper library is not available in release mode
        */
                Class<?> aClass = Class.forName("com.jocloud.rtc.demo.ReactNativeFlipper");
                aClass
                        .getMethod("initializeFlipper", Context.class, ReactInstanceManager.class)
                        .invoke(null, context, reactInstanceManager);
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
        }
    }
}
