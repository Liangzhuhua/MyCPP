package com.shizhuangyuan.mycpp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    JniApis jniApis;
    String TAG = "shizhuangyuan";
    Button btn_jni2cpp;//java调用JNI层，然后再调用C++，接着C++函数调用Java方法

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        jniApis = new JniApis();

        initView();
    }

    private void initView(){
        TextView tv = (TextView) findViewById(R.id.sample_text);
        btn_jni2cpp = findViewById(R.id.btn1);

        tv.setText(jniApis.stringFromJNI());

        btn_jni2cpp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int text_value = 1;
                Log.e(TAG,"Java调用JNI层，然后JNI里调用C++，返回值为" + jniApis.jni2CPP(text_value));
            }
        });

    }

    /**
     * C++函数实现调用此Java方法
     * @param msg C++函数传过来的一个形参
     */
    public void cpp2JavaTest(int msg){
        Log.e(TAG,"C++调用Java实例，C++传过来值为:" + msg);
    }


}
