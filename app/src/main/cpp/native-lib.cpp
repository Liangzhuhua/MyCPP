#include <jni.h>
#include <string>
#include "pureCpp.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_shizhuangyuan_mycpp_JniApis_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_shizhuangyuan_mycpp_JniApis_jni2CPP(JNIEnv *env, jobject /* this */, jint msg){
    int ret = jni2cpp(msg);//在C++函数里做自加1后返回
    return ret;
}

JavaVM* jvm = NULL;
jclass myClass = NULL;
jclass global_class = NULL;
jmethodID mid_method;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm,void* reserved){
    if (vm == NULL)
    {
        return JNI_ERR;
    }

    JNIEnv *env = NULL;
    jvm = vm;

    if(vm->GetEnv((void**)&env,JNI_VERSION_1_4)!=JNI_OK){
        return JNI_ERR;
    }

    myClass = (env)->FindClass("com/shizhuangyuan/mycpp/MainActivity");

    global_class = (jclass)env->NewGlobalRef(myClass);

    mid_method = (env)->GetMethodID(global_class,"cpp2JavaTest","(I)V");

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return;
    }
    env->DeleteGlobalRef(global_class);
    return;
}

/**
 * C++调用Java方法，函数里必须包含JNIEnv和jobject
 * @param msg
 * @return 返回数值，实现自加1的逻辑
 */
void cpp2jni(int msg){
    JNIEnv *env = NULL;
    int status;
    bool isAttached = false;
    status = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    if (status < 0) {
        if (jvm->AttachCurrentThread(&env, NULL))////将当前线程注册到虚拟机中
        {
            return;
        }
        isAttached = true;
    }
    //实例化该类
    jobject jobject = env->AllocObject(global_class);//分配新 Java 对象而不调用该对象的任何构造函数。返回该对象的引用。
    //调用Java方法
    (env)->CallVoidMethod(jobject, mid_method,msg);

    if (isAttached) {
        jvm->DetachCurrentThread();
    }
}