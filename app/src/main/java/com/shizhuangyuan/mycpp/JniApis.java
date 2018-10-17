package com.shizhuangyuan.mycpp;

/**
 * Created by lzh on 2018/10/17.
 */

public class JniApis {
    static {
        System.loadLibrary("native-lib");
    }
    public native String stringFromJNI();

    public native int jni2CPP(int msg);//JNI层调用CPP函数
}
