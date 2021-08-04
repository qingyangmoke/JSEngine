#include <jni.h>
/* Header for class test2_Food */

#ifndef _Included_test2_Food
#define _Included_test2_Food

#ifdef __cplusplus
extern "C"
{
#endif

  JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_createScope(JNIEnv *env, jobject obj, int contextId);

  // 指定scope中执行js代码
  JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_evaluateJavaScript(JNIEnv *env, jobject obj, int contextId, jstring sourceCode, jstring sourceURL, int startLine);

  // 初始化引擎
  JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_initEngine(JNIEnv *env, jobject obj);

  // invokeModule回调
  JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_invokeModuleEvent(JNIEnv *env, jobject obj, int contextId, int callId, int errorCode, jstring result);

  // native 调用js方法
  JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_invokeJSModule(JNIEnv *env, jobject obj, int contextId, jstring moduleName, jstring methodName, jstring args);
 
#ifdef __cplusplus
}
#endif

#endif