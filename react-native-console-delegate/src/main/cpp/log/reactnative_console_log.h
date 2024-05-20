//
// Created by aaapei on 2024/2/28.
//

#ifndef REACTNATIVE_CONSOLE_LOG_H
#define REACTNATIVE_CONSOLE_LOG_H

#include <jni.h>

namespace rnlogdelegate {
    void printMsg(int level, const char *msg);
    void SetupAndroidLogFunc(JNIEnv *env, jclass log_delegate_class, jobject delegate);
}


#endif //REACTNATIVE_CONSOLE_LOG_H
