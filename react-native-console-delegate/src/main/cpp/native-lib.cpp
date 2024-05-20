#include <jni.h>
#include <android/dlext.h>
#include <dlfcn.h>
#include <android/log.h>
#include <sys/prctl.h>
#include "log/reactnative_console_log.h"
#include "jni_android.h"


typedef void (*LogHandler)(int priority, const char *tag, const char *message);

extern "C"
JNIEXPORT jint JNICALL
Java_com_github_aaapei_RNConsoleDelegate_nativeInit(
        JNIEnv *env, jclass clazz, jobject delegate) {


    void *fb_handler = android_dlopen_ext("libfb.so", RTLD_NOW | RTLD_LOCAL, nullptr);
    if (fb_handler != nullptr) {
        jclass delegrate_clazz = env->GetObjectClass(delegate);
        rnlogdelegate::SetupAndroidLogFunc(env,delegrate_clazz,delegate);
        void (*setLogHandlerFunc)(LogHandler) = (void (*)(LogHandler)) dlsym(fb_handler,
                                                                             "setLogHandler");
        if (setLogHandlerFunc == nullptr) {
            __android_log_print(ANDROID_LOG_ERROR, "LocalConsoleDelegate",
                                "Failed to get setLogHandler function pointer: %s", dlerror());
            return -1;
        }

        LogHandler customLogHandler = [](int priority, const char *tag, const char *message) {
            rnlogdelegate::printMsg(priority,message);
        };
        setLogHandlerFunc(customLogHandler);
        dlclose(fb_handler);
        return 0;
    }
    return -4;
}



jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    rnlogdelegate::bindVM(vm);
    return JNI_VERSION_1_6;
}


