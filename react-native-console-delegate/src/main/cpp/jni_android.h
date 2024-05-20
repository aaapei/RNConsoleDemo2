//
// Created by aaapei on 2024/2/28.
//

#ifndef RN_LOG_JNI_ANDROID_H
#define RN_LOG_JNI_ANDROID_H

#include <jni.h>

namespace rnlogdelegate{
    void bindVM(JavaVM* vm);
    JNIEnv* AttachCurrentThread();
}


#endif //RN_LOG_JNI_ANDROID_H
