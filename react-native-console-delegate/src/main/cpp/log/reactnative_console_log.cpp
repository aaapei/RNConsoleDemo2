//
// Created by aaapei on 2024/2/28.
//

#include "reactnative_console_log.h"
#include "../jni_android.h"
#include <jni.h>
#include <android/log.h>
namespace rnlogdelegate {
    static jobject log_delegate;
    static jmethodID debug_log_mid_;
    static jmethodID warn_log_mid_;
    static jmethodID error_log_mid_;
    static jmethodID verbose_log_mid_;
    static jmethodID info_log_mid_;

    void SetupAndroidLogFunc(JNIEnv *env, jclass log_delegate_class, jobject delegate) {

        log_delegate = env->NewGlobalRef(delegate);
        debug_log_mid_ = env->GetMethodID(log_delegate_class, "d",
                                          "(Ljava/lang/String;Ljava/lang/String;)V");
        warn_log_mid_ = env->GetMethodID(log_delegate_class, "w",
                                         "(Ljava/lang/String;Ljava/lang/String;)V");
        error_log_mid_ = env->GetMethodID(log_delegate_class, "e",
                                          "(Ljava/lang/String;Ljava/lang/String;)V");
        verbose_log_mid_ = env->GetMethodID(log_delegate_class, "v",
                                          "(Ljava/lang/String;Ljava/lang/String;)V");
        info_log_mid_ = env->GetMethodID(log_delegate_class, "i",
                                          "(Ljava/lang/String;Ljava/lang/String;)V");

    }

    jstring ConvertUTF16ToJavaString(JNIEnv*env,const char* msg){
        jstring result =
                env->NewStringUTF(msg);
        return result;
    }

    void printMsg(int priority, const char *msg) {
        JNIEnv *env = rnlogdelegate::AttachCurrentThread();
        if (env == NULL) {
            return;
        }
        jmethodID target_mid;
        switch (priority) {
            case ANDROID_LOG_WARN:
                target_mid = warn_log_mid_;
                break;
            case ANDROID_LOG_ERROR:
                target_mid = error_log_mid_;
                break;
            case ANDROID_LOG_DEBUG:
                target_mid = debug_log_mid_;
                break;
            case ANDROID_LOG_VERBOSE:
                target_mid = verbose_log_mid_;
                break;
            case ANDROID_LOG_INFO:
                target_mid = info_log_mid_;
                break;
            default:
                target_mid = debug_log_mid_;
                break;
        }

        env->CallVoidMethod(log_delegate, target_mid,
                            ConvertUTF16ToJavaString(env, "NativeConsoleDelegate"),
                            ConvertUTF16ToJavaString(env, msg), false);
    }
}