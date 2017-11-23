package com.shengmingji.jnidemotest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.Random;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    String key = "key";
    static int count = 9;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        set("have param method()");

        Log.i("TAG", "StaticMethod: " + print());

        Log.i("TAG", "accessField: " + accessField());

        accessStaticField();
        Log.i("TAG", "accessStaticField: " + count);


        Log.i("TAG", "accessMethod: " + accessMethod());

        Log.i("TAG", "accessStaticMethod: "+accessStaticMethod());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();


    public native String accessField();

    public native void accessStaticField();

    public native int accessMethod();

    public native String accessStaticMethod();

    public native void set(String str);

    public static native String print();

    int getRandom(int max){
        return new Random().nextInt(max);
    }

    static String getRandomUUID(){
        return UUID.randomUUID().toString();
    }
}
