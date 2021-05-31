
#ifdef __APPLE__
#include <JavaScriptCore/JavaScriptCore.h>
#else
#include <JavaScriptCore/JavaScript.h>
#endif

#include "include/my_bridge.h"
#include <iostream>
#include <string>
#include "AlitaGlobalObject.h"
#include "utils.h"
#include "JSCoreContext.h"

using namespace CPlusDemo;
using namespace jsc;

JSValueRef invokeModule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  JSCoreEngineContext *context = JSCoreEngineContext::getContext(ctx);
  std::string moduleName = jsc::JSValueToStdString(ctx, arguments[0], exception);
  std::string methodName = jsc::JSValueToStdString(ctx, arguments[1], exception);
  std::string args = "";
  if (argumentCount > 2 && !JSValueIsNull(ctx, arguments[2]))
  {
    JSStringRef argsStringRef = JSValueCreateJSONString(ctx, arguments[2], 0, exception);
    args = jsc::JSStringToStdString(argsStringRef);
    JSStringRelease(argsStringRef);
  }

  JSObjectRef callbackObjectRef = NULL;
  if (argumentCount > 3 && JSValueIsObject(ctx, arguments[3]))
  {
    std::cout << "【AlitaGlobalObject】JSValueToObject" << std::endl;
    callbackObjectRef = JSValueToObject(ctx, arguments[3], exception);
  }
  EngineInvokeModuleCallback callback = nullptr;
  if (JSObjectIsFunction(ctx, callbackObjectRef))
  {
    callback = [ctx, callbackObjectRef, thisObject, exception](int errorCode, const char *result)
    {
      std::cout << "【AlitaGlobalObject】EngineInvokeModuleCallback" << std::endl;
      JSStringRef callbackArgs_result = JSStringCreateWithUTF8CString(result);
      JSValueRef callbackArgs[2];
      callbackArgs[0] = JSValueMakeNumber(ctx, errorCode);
      callbackArgs[1] = JSValueMakeString(ctx, callbackArgs_result);
      JSObjectCallAsFunction(ctx, callbackObjectRef, thisObject, 2, callbackArgs, exception);
      JSStringRelease(callbackArgs_result);
    };
  }
  const char *result = EngineNativeMethods::instance()->invokeModule(context->getContextId(), moduleName.c_str(), methodName.c_str(), args.c_str(), callback);

  std::cout << "【AlitaGlobalObject】moduleName=" << moduleName << ", methodName=" << methodName << ", args=" << args << argumentCount << std::endl;
  if (result != NULL)
  {
    JSStringRef callbackArgs_result = JSStringCreateWithUTF8CString(result);
    JSValueRef jsResult = JSValueMakeString(ctx, callbackArgs_result);
    JSStringRelease(callbackArgs_result);
    return jsResult;
  }
  else
  {
    return JSValueMakeUndefined(ctx);
  }
}

void AlitaGlobalObject::initAlitaGlobalObject(JSGlobalContextRef jscContext, JSObjectRef global)
{
  JSClassDefinition alita_def = kJSClassDefinitionEmpty;
  JSStaticFunction alita_funcs[] = {
      {"invokeModule", invokeModule, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {} // null termination
  };
  alita_def.staticFunctions = alita_funcs;
  JSClassRef alita_class = JSClassCreate(&alita_def);

  JSStringRef alitaName = JSStringCreateWithUTF8CString("__alita__");
  JSObjectRef alitaObject = JSObjectMake(jscContext, alita_class, NULL);
  JSObjectSetProperty(jscContext, global, alitaName, alitaObject, kJSPropertyAttributeNone, NULL);

  JSStringRelease(alitaName);
}
