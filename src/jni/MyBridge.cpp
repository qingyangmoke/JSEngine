#include <jni.h>   // JNI header provided by JDK
#include <stdio.h> // C Standard IO Header
#include "include/jsengine_bridge.h"
#include "MyBridge.h"

int _printToAndroid(JNIEnv *env, int contextId, const char *tag, const char *message)
{
    jclass JSEngine = env->FindClass("com/jnibridge/JSEngine");
    if (JSEngine == NULL)
    {
        printf("JSEngine not found");
        return 1;
    }

    jmethodID logMethod = env->GetStaticMethodID(JSEngine, "log", "(ILjava/lang/String;Ljava/lang/String;)V");
    if (logMethod == NULL)
    {
        printf("log Method not found");
        // 删除局部引用
        env->DeleteLocalRef(JSEngine);
        return 2;
    }

    jstring _tagName = env->NewStringUTF(tag);
    jstring _message = env->NewStringUTF(message);
    env->CallStaticVoidMethod(JSEngine, logMethod, contextId, _tagName, _message);
    
    env->DeleteLocalRef(_tagName);
    env->DeleteLocalRef(_message);

    // 删除局部引用
    env->DeleteLocalRef(JSEngine);
    return 0;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_createScope(JNIEnv *env, jobject obj, int contextId)
{
    JSEngineNS::Engine::instance()->createScope(contextId);
    return contextId;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_evaluateJavaScript(JNIEnv *env, jobject obj, int contextId, jstring sourceCode, jstring sourceURL, int startLine)
{
    int result = 0;

    const char *_sourceCode = env->GetStringUTFChars(sourceCode, 0);
    const char *_sourceURL = env->GetStringUTFChars(sourceURL, 0);
    JSEngineNS::EngineScope *scope = JSEngineNS::Engine::instance()->getScope(contextId);
    if (scope != NULL)
    {
        try
        {
            result = scope->evaluateJavaScript(_sourceCode, _sourceURL, 0);
        }
        catch (const std::exception &e)
        {
            _printToAndroid(env, contextId, "error", e.what());
        }
        scope = NULL;
    }
    else
    {
        _printToAndroid(env, contextId, "error", "scope not found");
    }

    env->ReleaseStringUTFChars(sourceCode, _sourceCode);
    env->ReleaseStringUTFChars(sourceURL, _sourceURL);
    
    return result;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_initEngine(JNIEnv *env, jobject obj)
{
    if (JSEngineNS::EngineNativeMethods::instance()->invokeModulePointer != NULL)
    {
        return 0;
    }

    JSEngineNS::EngineNativeMethods::instance()->invokeModulePointer = [env](int contextId, int callId, const char *moduleName, const char *methodName, const char *args) -> const char *
    {
        _printToAndroid(env, contextId, "log", "invokeModule");

        jclass JSEngine = env->FindClass("com/jnibridge/JSEngine");
        if (JSEngine == NULL)
        {
            _printToAndroid(env, contextId, "error", "com.jnibridge.JSEngine Class not found");
            return NULL;
        }

        jmethodID invokeModuleMethod = env->GetStaticMethodID(JSEngine, "invokeModule", "(IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
        if (invokeModuleMethod == NULL)
        {
            _printToAndroid(env, contextId, "error", "invokeModule Method not found");
            // 删除局部引用
            env->DeleteLocalRef(JSEngine);
            return NULL;
        }

        jstring _moduleName = env->NewStringUTF(moduleName);
        jstring _methodName = env->NewStringUTF(methodName);
        jstring _args = env->NewStringUTF(args);
        jstring result = NULL;
        try
        {
            result = (jstring)env->CallStaticObjectMethod(JSEngine, invokeModuleMethod, contextId, callId, _moduleName, _methodName, _args);
        }
        catch (const std::exception &e)
        {
            _printToAndroid(env, contextId, "error", e.what());
        }

        
        env->DeleteLocalRef(_moduleName);
        env->DeleteLocalRef(_methodName);
        env->DeleteLocalRef(_args);

        // 删除局部引用
        env->DeleteLocalRef(JSEngine);

        if (result != NULL)
        {
            const char *message = env->GetStringUTFChars(result, 0);
            env->ReleaseStringUTFChars(result, message);
            env->DeleteLocalRef(result);
            return message;
        }
        else
        {
            return NULL;
        }
    };

    JSEngineNS::EngineNativeMethods::instance()->logPointer = [env](int contextId, const char *tagName, const char *message)
    {
        _printToAndroid(env, contextId, tagName, message);
    };

    // JSEngineNS::EngineNativeMethods::instance()->invokeModulePointer(1, 2, "consoleM2", "print2", "args2");
    // JSEngineNS::EngineNativeMethods::instance()->invokeModule(1, "consoleM2", "print2", "args2", NULL);
    return 0;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_invokeModuleEvent(JNIEnv *env, jobject obj, int contextId, int callId, int errorCode, jstring result)
{
    const char *_result = env->GetStringUTFChars(result, 0);
    try
    {
        JSEngineNS::EngineNativeMethods::instance()->invokeModuleEvent(contextId, callId, errorCode, _result);
    }
    catch (const std::exception &e)
    {
        _printToAndroid(env, contextId, "error", e.what());
    }

    env->ReleaseStringUTFChars(result, _result);
    return 1;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_invokeJSModule(JNIEnv *env, jobject obj, int contextId, jstring moduleName, jstring methodName, jstring args)
{
    JSEngineNS::EngineScope *scope = JSEngineNS::Engine::instance()->getScope(contextId);
    if (scope != NULL)
    {
        const char *_moduleName = env->GetStringUTFChars(moduleName, 0);
        const char *_methodName = env->GetStringUTFChars(methodName, 0);
        const char *_args = env->GetStringUTFChars(args, 0);
        scope->invokeJSModule(_moduleName, _methodName, _args);
        env->ReleaseStringUTFChars(moduleName, _moduleName);
        env->ReleaseStringUTFChars(methodName, _methodName);
        env->ReleaseStringUTFChars(args, _args);
        scope = NULL;
    }
    return 0;
}