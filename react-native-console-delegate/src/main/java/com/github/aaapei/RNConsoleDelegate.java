package com.github.aaapei;


import android.util.Log;

public class RNConsoleDelegate {
    private static final String TAG = "RNConsoleDelegate";
    private static volatile boolean sInited = false;

    public static int init(RNLogDelegate delegate) {
        if (!sInited) {
            sInited = true;
            try {
                System.loadLibrary("rnLogDelegate");
                return nativeInit(delegate);
            } catch (Throwable e) {
                Log.d(TAG, "load rnLogDelegate failed", e);
            }
        }

        return -3;
    }

    public static native int nativeInit(RNLogDelegate delegate);

}
