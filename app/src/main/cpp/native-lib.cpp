#include <jni.h>
#include <string>
//秘钥（自定义）
#define KEY "12345678"
//偏移量(自定义)
#define PY "qwertyuiopasdfgh"
//加密方式
const char *AES_TYPE = "AES";
//AES加密填充方式（也可以选择PKCS5Padding）
const char *AES_MODE = "AES/CBC/PKCS5Padding";

jbyteArray getBytes(JNIEnv *env, const char *source);

jstring
getArray(JNIEnv *env, _jclass *type, const _jstring *source_, const char *name, const char *sig);

extern "C" JNIEXPORT jstring JNICALL
Java_com_founq_sdk_testndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_founq_sdk_testffmpeg_JniUtil_sayHello(JNIEnv *env, jclass type) {
    return env->NewStringUTF("HelloWorld!");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_founq_sdk_testffmpeg_JniUtil_decrypt__Ljava_lang_String_2(JNIEnv *env, jclass type, jstring source_) {
    //调用的方法名
    const char *name = "decrypt";
    //调用方法的变量，[B代表byte类型，object类型通过L...;来表示
    const char *sig = "(Ljava/lang/String;[B[BLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;";

    jstring result = getArray(env, type, source_, name, sig);

    name = NULL;
    sig = NULL;
    return result;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_founq_sdk_testffmpeg_JniUtil_encrypt__Ljava_lang_String_2(JNIEnv *env, jclass type, jstring source_) {
    const char *name = "encrypt";
    const char *sig = "(Ljava/lang/String;[B[BLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;";
    jstring result = getArray(env, type, source_, name, sig);
    name = NULL;
    sig = NULL;
    return result;
}

jstring
getArray(JNIEnv *env, _jclass *type, const _jstring *source_, const char *name, const char *sig) {
    jstring desType_, desMode_;
    jbyteArray keyArray, pyArray;
    jmethodID encryptMid;

    desType_ = env->NewStringUTF(AES_TYPE);
    desMode_ = env->NewStringUTF(AES_MODE);
    //将key转转成jbyteArray
    keyArray = getBytes(env, KEY);
    //将偏移量转成jbyteArray
    pyArray = getBytes(env, PY);

    encryptMid = env->GetStaticMethodID(type, name,
                                        sig);
    //调用JniUtil类中的加密方法
    jstring result = (jstring) env->CallStaticObjectMethod(type, encryptMid, source_,
                                                           keyArray, pyArray, desType_,
                                                           desMode_);
    //释放
    env->DeleteLocalRef(desType_);
    env->DeleteLocalRef(desMode_);
    env->DeleteLocalRef(keyArray);
    env->DeleteLocalRef(pyArray);
    return result;
}

jbyteArray getBytes(JNIEnv *env, const char *source) {
    jstring str = env->NewStringUTF(source);
    jstring utf8 = env->NewStringUTF("UTF-8");
    jclass stringClazz = env->FindClass("java/lang/String");//寻找 java里面String.class
    jmethodID stringMid = env->GetMethodID(stringClazz, "getBytes", "(Ljava/lang/String;)[B");
    return (jbyteArray) env->CallObjectMethod(str, stringMid, utf8);
}
