#include <jni.h>
#include <GLES2/gl2.h>

extern "C" {
JNIEXPORT void JNICALL
Java_com_example_bluegl_MyGLRenderer_nativeInit(JNIEnv* env, jobject obj) {

}

JNIEXPORT void JNICALL
Java_com_example_bluegl_MyGLRenderer_nativeResize(JNIEnv *env, jobject obj, jint width, jint height) {
    glViewport(0, 0, width, height);
}

JNIEXPORT void JNICALL
Java_com_example_bluegl_MyGLRenderer_nativeRender(JNIEnv *env, jobject obj) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

}