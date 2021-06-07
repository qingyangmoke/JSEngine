
#include "JavaScriptCore.h"

#include "include/jsengine_bridge.h"
#include <iostream>
#include <string>
#include "JSCoreModule.h"
#include "JSCoreHelper.h"
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
    callbackObjectRef = JSValueToObject(ctx, arguments[3], exception);
  }
  EngineInvokeModuleCallback callback = nullptr;
  if (JSObjectIsFunction(ctx, callbackObjectRef))
  {
    callback = [ctx, callbackObjectRef, thisObject, exception](int errorCode, const char *result)
    {
      EngineNativeMethods::instance()->log(JSCoreEngineContext::getContext(ctx)->getContextId(), "info", "JSCoreModule.invokeModuleCallback");
      JSStringRef callbackArgs_result = JSStringCreateWithUTF8CString(result);
      JSValueRef callbackArgs[2];
      callbackArgs[0] = JSValueMakeNumber(ctx, errorCode);
      callbackArgs[1] = JSValueMakeString(ctx, callbackArgs_result);
      JSObjectCallAsFunction(ctx, callbackObjectRef, thisObject, 2, callbackArgs, exception);
      JSStringRelease(callbackArgs_result);
    };
  }
  const char *result = EngineNativeMethods::instance()->invokeModule(context->getContextId(), moduleName.c_str(), methodName.c_str(), args.c_str(), callback);

  EngineNativeMethods::instance()->log(context->getContextId(), "info", "JSCoreModule.invokeModule");
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

void JSCoreModule::initModule(JSGlobalContextRef jscContext, JSObjectRef global)
{
  JSClassDefinition module_def = kJSClassDefinitionEmpty;
  JSStaticFunction module_funcs[] = {
      {"invokeModule", invokeModule, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {} // null termination
  };
  module_def.staticFunctions = module_funcs;
  JSClassRef module_class = JSClassCreate(&module_def);

  JSStringRef moduleName = JSStringCreateWithUTF8CString("__module__");
  JSObjectRef moduleObject = JSObjectMake(jscContext, module_class, NULL);
  JSObjectSetProperty(jscContext, global, moduleName, moduleObject, kJSPropertyAttributeNone, NULL);

  JSStringRelease(moduleName);
}
