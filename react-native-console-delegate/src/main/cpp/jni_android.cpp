//
// Created by aaapei on 2024/2/28.
//

#include "jni_android.h"
#include <jni.h>
#include <sys/prctl.h>
#include <android/log.h>

namespace rnlogdelegate{
    JavaVM* g_jvm = NULL;

    JNIEnv* AttachCurrentThread() {
        JNIEnv* env = nullptr;
        jint ret = g_jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_4);
        if (ret == JNI_EDETACHED || !env) {
            JavaVMAttachArgs args;
            args.version = JNI_VERSION_1_2;
            args.group = nullptr;
            char thread_name[16];
            int err = prctl(PR_GET_NAME, thread_name);
            if (err < 0) {
                __android_log_print(ANDROID_LOG_ERROR, "AttachCurrentThread",
                                    "prctl(PR_GET_NAME)");
                args.name = nullptr;
            } else {
                args.name = thread_name;
            }
            ret = g_jvm->AttachCurrentThread(&env, &args);
        }
        return env;
    }

    void bindVM(JavaVM* vm){
        g_jvm = vm;
    }
}