//
// Created by lzh on 2018/10/17.
//
#include "pureCpp.h"
#include <android/log.h>

#define  LOG_TAG    "native-lig"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)

int jni2cpp(int msg){
    LOGE("这里是C++，收到一个消息msg=%d",msg);
    msg++;
    cpp2jni(msg * 2);//实现调用Java方法
    return msg;
}

