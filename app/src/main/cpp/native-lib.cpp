#include <jni.h>
#include <string>
#include <stdio.h>

#ifdef ANDROID_ARM_NEON
#include <arm_neon.h>
#endif

extern "C" JNIEXPORT jstring JNICALL
Java_com_realxie_neontest_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */)
{
#ifdef ANDROID_ARM_NEON
    float data1[2] = {1, 2};
    float data2[2] = {3, 4};

    float32x2_t d1 = vld1_f32(data1);
    float32x2_t d2 = vld1_f32(data2);

    auto a = vmul_f32(d1, d2);

    float a1, a2;

    vst1_lane_f32(&a1, a, 0);
    vst1_lane_f32(&a2, a, 1);

    char buffer[128] = {0};

    sprintf(buffer, "%f, %f", a1, a2);
    return env->NewStringUTF(buffer);
#else
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
#endif
}
