#include <jni.h>
#include <string>
#include <string.h>


extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessStaticMethod(JNIEnv *env, jobject instance) {

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
Java_com_shengmingji_jnidemotest_MainActivity_get(JNIEnv *env, jobject instance) {
    printf("invoke set in c++\n");


    return env->NewStringUTF("Hello From JNI!!");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_set(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    printf("invoke set in c++\n");
    env->ReleaseStringUTFChars(str_, str);
}

/**
 * native static
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_print(JNIEnv *env, jclass jclaz) {
    return env->NewStringUTF("hahahaha");
}


/**
 * 访问非静态属性
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_shengmingji_jnidemotest_MainActivity_accessField(JNIEnv *env, jobject instance) {

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
Java_com_shengmingji_jnidemotest_MainActivity_accessStaticField(JNIEnv *env, jobject instance) {
    jclass jcz = env->GetObjectClass(instance);

    jfieldID jfield = env->GetStaticFieldID(jcz, "count", "I");

    jint i = env->GetStaticIntField(jcz, jfield);

    env->SetStaticIntField(jcz, jfield, i + 10);

}

