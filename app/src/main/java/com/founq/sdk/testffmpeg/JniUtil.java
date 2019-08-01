package com.founq.sdk.testffmpeg;

import android.util.Base64;

import java.nio.charset.StandardCharsets;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

/**
 * Created by ring on 2019/7/31.
 */
public class JniUtil {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String sayHello();

    public native static String encrypt(String source);

    public native static String decrypt(String source);

    public static String decrypt(String data, byte[] key, byte[] py, String desType, String desMode) throws Exception {
        byte[] raw = InsecureSHA1PRNGKeyDerivator.deriveInsecureKey(key, 32);
        SecretKeySpec secretKeySpec = new SecretKeySpec(raw, desType);
        Cipher cipher = Cipher.getInstance(desMode);
        IvParameterSpec iv = new IvParameterSpec(py);
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, iv);//解密模式
        byte[] encrypted = cipher.doFinal(Base64.decode(data, Base64.DEFAULT));
        return new String(encrypted);
    }

    public static String encrypt(String data, byte[] key, byte[] py, String desType, String desMode) throws Exception {
        byte[] raw = InsecureSHA1PRNGKeyDerivator.deriveInsecureKey(key, 32);
        SecretKeySpec secretKeySpec = new SecretKeySpec(raw, desType);
        Cipher cipher = Cipher.getInstance(desMode);
        IvParameterSpec iv = new IvParameterSpec(py);
        cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec, iv);//加密模式
        byte[] encrypted = cipher.doFinal(data.getBytes(StandardCharsets.UTF_8));
        return Base64.encodeToString(encrypted, Base64.DEFAULT);
    }
}
