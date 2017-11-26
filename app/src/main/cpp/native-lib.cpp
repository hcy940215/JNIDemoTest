#include <jni.h>
#include <string>
#include <string.h>
#include <android/log.h>
#include "wchar.h"

#define TAG "TAG"
#define LOGI(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessStaticMethod
        (JNIEnv *env, jobject instance) {

    jclass jclz = env->GetObjectClass(instance);
    jmethodID jmid = env->GetStaticMethodID(jclz, "getRandomUUID", "()Ljava/lang/String;");

    jstring uuid = (jstring) env->CallStaticObjectMethod(jclz, jmid);

    //jstring ->char *
    char *uuid_c = (char *) env->GetStringUTFChars(uuid, NULL);


    return uuid;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessMethod(JNIEnv *env, jobject instance) {


    jclass jclz = env->GetObjectClass(instance);

    jmethodID jmid = env->GetMethodID(jclz, "getRandom", "(I)I");

    //调用
    jint i = env->CallIntMethod(instance, jmid, 200);

    return i;

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_get
        (JNIEnv *env, jobject instance) {
    printf("invoke set in c++\n");


    return env->NewStringUTF("Hello From JNI!!");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_set
        (JNIEnv *env, jobject instance, jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    printf("invoke set in c++\n");
    env->ReleaseStringUTFChars(str_, str);
}

/**
 * native static
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_print
        (JNIEnv *env, jclass jclaz) {
    return env->NewStringUTF("hahahaha");
}


/**
 * 访问非静态属性
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessField
        (JNIEnv *env, jobject instance) {

    jclass jclz = env->GetObjectClass(instance);
    jfieldID jfield = env->GetFieldID(jclz, "key", "Ljava/lang/String;");
    jstring obj = (jstring) env->GetObjectField(instance, jfield);
    char *c_str = (char *) env->GetStringUTFChars(obj, NULL);
    char text[30] = "huang";
    strcat(text, c_str);

    jstring new_str = env->NewStringUTF(text);

    env->SetObjectField(instance, jfield, new_str);
    env->ReleaseStringChars(new_str, (const jchar *) c_str);
    return new_str;
}

/*
 * 访问静态属性
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessStaticField
        (JNIEnv *env, jobject instance) {
    jclass jcz = env->GetObjectClass(instance);

    jfieldID jfield = env->GetStaticFieldID(jcz, "count", "I");

    jint i = env->GetStaticIntField(jcz, jfield);

    env->SetStaticIntField(jcz, jfield, i + 10);

}

/**
 * 访问构造方法
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessConstructor
        (JNIEnv *env, jobject instance) {

    //通过路径找到对应的类
    jclass jclz = env->FindClass("java/util/Date");
    //构造方法名 都用<init>
    jmethodID jmId = env->GetMethodID(jclz, "<init>", "()V");

    //实例化 Date对象 jni引用都返回jobject
    jobject jobjDate = env->NewObject(jclz, jmId);

    jmethodID time_mid = env->GetMethodID(jclz, "getTime", "()J");

    jlong time = env->CallLongMethod(jobjDate, time_mid);

    return time;

}

/**
 *  访问字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_chineseChar
        (JNIEnv *env, jobject instance, jstring jstr) {

    char *c_str = (char *) env->GetStringUTFChars(jstr, NULL);
    // LOGI(c_str, "%s", c_str);
    return env->NewStringUTF(c_str);
}

/**
 * 访问基本类型数组
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessArray
        (JNIEnv *env, jobject instance, jintArray arr_) {

    //对java层数据转化
    jint *arr = env->GetIntArrayElements(arr_, NULL);

    if (arr == NULL) {
        return;
    }

    //数组长度
    int len = env->GetArrayLength(arr_);
//    for (int i = 0; i < len; i++) {
//        __android_log_print(ANDROID_LOG_VERBOSE, TAG, "%d", arr[i]);
//    }

    env->ReleaseIntArrayElements(arr_, arr, 0);
}

/**
 * 访问引用型数组
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessStringArray
        (JNIEnv *env, jobject instance, jint size) {

    jclass jclaz = env->FindClass("java/lang/String");
    if (jclaz == NULL) {
        return NULL;
    }

    //创建数组 VS中NewObjectArray(size, jclaz, instance);
    jobjectArray jobjArr = env->NewObjectArray(size, jclaz, NULL);
    if (jobjArr == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        //c 字符串
        char *c_str = new char[256];
        memset(c_str, 0, 256);

        sprintf(c_str, "hello %d", i);
        //c->String
        jstring str = env->NewStringUTF(c_str);
        if (str == NULL) {
            return NULL;
        }

        //将jstring复制给数组
        env->SetObjectArrayElement(jobjArr, i, str);
        delete (c_str);
    }

    return jobjArr;
}

/**
 * 局部引用 不能多进程
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_localRef
        (JNIEnv *env, jobject instance) {


    for (int i = 0; i < 5; ++i) {
        jclass jclaz = env->FindClass("java/util/Date");
        jmethodID jmid = env->GetMethodID(jclaz, "<init>", "()V");

        //创建一个局部引用 方式FindClass  NewObject GetObjectClass
        jobject jobj = env->NewObject(jclaz, jmid);

        //释放引用
        //方式 JVM自动释放
        //②手动释放
        env->DeleteLocalRef(jobj);
    }

}

/**
 * 全局引用 能多进程 跨方法使用
 * NewGlobalRef唯一方式
 */

jstring str;
extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_globalRef
        (JNIEnv *env, jobject instance) {
    jobject obj = env->NewStringUTF("JNI global Ref");
    str = (jstring) env->NewGlobalRef(obj);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_getGlobalRef
        (JNIEnv *env, jobject instance) {
    return str;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_delGlobalRef
        (JNIEnv *env, jobject instance) {
    env->DeleteGlobalRef(str);
    __android_log_print(ANDROID_LOG_VERBOSE, TAG, "释放");
}

//弱全局引用
jstring g_week_clas;
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_weakGlobalRef
        (JNIEnv *env, jobject instance) {

    jobject obj = env->NewStringUTF("JNI WeakGlobalRef Ref");
    g_week_clas = (jstring) env->NewWeakGlobalRef(obj);
    return g_week_clas;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_exception
        (JNIEnv *env, jobject instance) {

    jclass jclaz = env->GetObjectClass(instance);
    jfieldID jfid = env->GetFieldID(jclaz, "ke", "Ljava/lang/String;");

    jthrowable ex = env->ExceptionOccurred();
    if (ex != NULL) {
        env->ExceptionClear();
        jclass newExc = env->FindClass("java/lang/IllegalArgumentException");

        if (newExc==NULL){
            __android_log_print(ANDROID_LOG_VERBOSE,TAG,"jni exception");
            return NULL;
        }
        env->ThrowNew(newExc,"Throw exception from JNI: GetFieldID ");
    }
    return NULL;
}