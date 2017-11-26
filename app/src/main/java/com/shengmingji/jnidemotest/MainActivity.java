package com.shengmingji.jnidemotest;

import android.os.Build;
import android.os.Bundle;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
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

    @RequiresApi(api = Build.VERSION_CODES.N)
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

        Log.i("TAG", "accessStaticMethod: " + accessStaticMethod());

        Log.i("TAG", "accessConstructor: " + accessConstructor());

        Log.i("TAG", "chineseChar: " + chineseChar("哈啊哈"));
        int nums[] = {10, 15, 2, 6, 8, 8, 5, 20};

        accessArray(nums);
        Log.i("TAG", "accessArray: ");

        String[] stringArray = accessStringArray(10);
        for (int i = 0; i < stringArray.length; i++) {
            Log.i("TAG", "accessStringArray: >>>  " + stringArray[i]);
        }

        globalRef();
        String globalRef = getGlobalRef();
        Log.i("TAG", "getGlobalRef: " + globalRef);
        delGlobalRef();

        Log.i("TAG", "weakGlobalRef: " + weakGlobalRef());

        try {

            exception();
        }catch (Exception e){
            Log.i("TAG", "exception: "+e.getMessage());
        }

        Log.i("TAG", "exception: --------------------");
    }

    public native String stringFromJNI();

    public native String accessField();

    public native void accessStaticField();

    public native int accessMethod();

    public native String accessStaticMethod();

    public native long accessConstructor();

    public native String chineseChar(String str);

    public native void accessArray(int[] arr);

    public native String[] accessStringArray(int arr);

    public native void localRef();

    public native void globalRef();

    public native String getGlobalRef();

    public native void delGlobalRef();

    public native String weakGlobalRef();

    public native String exception();

    public native void set(String str);

    public static native String print();

    int getRandom(int max) {
        return new Random().nextInt(max);
    }

    static String getRandomUUID() {
        return UUID.randomUUID().toString();
    }
}
