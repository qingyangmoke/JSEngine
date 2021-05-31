#include <jni.h>   // JNI header provided by JDK
#include <stdio.h> // C Standard IO Header
#include "include/my_bridge.h"
#include "MyBridge.h"

int _printToAndroid(JNIEnv *env, int contextId, const char *tag, const char *message)
{
    jclass JSEngine = env->FindClass("com/jnibridge/JSEngine");
    if (JSEngine == NULL)
    {
        _printToAndroid(env, contextId, "error", "com.jnibridge.JSEngine Class not found");
        return 1;
    }

    jmethodID logMethod = env->GetStaticMethodID(JSEngine, "log", "(ILjava/lang/String;Ljava/lang/String;)V");
    if (logMethod == NULL)
    {
        printf("log Method not found");
        return 2;
    }
    
    jstring _tagName = env->NewStringUTF(tag);    
    jstring _message = env->NewStringUTF(message);
    env->CallStaticVoidMethod(JSEngine, logMethod, contextId, _tagName, _message);

    // 删除局部引用
    env->DeleteLocalRef(JSEngine);
    env->DeleteLocalRef(_tagName);
    env->DeleteLocalRef(_message);
    return 0;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_createScope(JNIEnv *env, jobject obj, int contextId)
{
    CPlusDemo::Engine::instance()->createScope(contextId);
    return contextId;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_evaluateJavaScript(JNIEnv *env, jobject obj, int contextId, jstring sourceCode, jstring sourceURL, int startLine)
{
    _printToAndroid(env, contextId, "log", "Java_com_jnibridge_JSEngine_evaluateJavaScript");
    int result = 0;

    const char *_sourceCode = env->GetStringUTFChars(sourceCode, 0);
    const char *_sourceURL = env->GetStringUTFChars(sourceURL, 0);
    CPlusDemo::EngineScope *scope = CPlusDemo::Engine::instance()->getScope(contextId);
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
    if (CPlusDemo::EngineNativeMethods::instance()->invokeModulePointer != NULL)
    {
        return 0;
    }

    CPlusDemo::EngineNativeMethods::instance()->invokeModulePointer = [env](int contextId, int callId, const char *moduleName, const char *methodName, const char *args) -> const char *
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
        
        // 删除局部引用
        env->DeleteLocalRef(JSEngine);
        env->DeleteLocalRef(_moduleName);
        env->DeleteLocalRef(_methodName);
        env->DeleteLocalRef(_args);

        if(result != NULL) {
            const char *message = env->GetStringUTFChars(result, 0);
            env->ReleaseStringUTFChars(result, message);
            env->DeleteLocalRef(result);
            return message;
        } else {
            return NULL;
        }
    };

    CPlusDemo::EngineNativeMethods::instance()->logPointer = [env](int contextId, const char *tagName, const char *message)
    {
        _printToAndroid(env, contextId, tagName, message);
    };

    // CPlusDemo::EngineNativeMethods::instance()->invokeModulePointer(1, 2, "consoleM2", "print2", "args2");
    // CPlusDemo::EngineNativeMethods::instance()->invokeModule(1, "consoleM2", "print2", "args2", NULL);
    return 0;
}

JNIEXPORT int JNICALL Java_com_jnibridge_JSEngine_invokeModuleEvent(JNIEnv *env, jobject obj, int contextId, int callId, int errorCode, jstring result)
{
    const char *_result = env->GetStringUTFChars(result, 0);
    try
    {
        CPlusDemo::EngineNativeMethods::instance()->invokeModuleEvent(contextId, callId, errorCode, _result);
    }
    catch (const std::exception &e)
    {
        _printToAndroid(env, contextId, "error", e.what());
    }

    env->ReleaseStringUTFChars(result, _result);
    return 1;
}