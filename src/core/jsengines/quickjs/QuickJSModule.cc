#include <iostream>
#include <string>
#include "QuickJSModule.h"

using namespace JSEngineNS;
using namespace quickjs;

JSValue invokeModule(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  JSValue global = JS_GetGlobalObject(ctx);
  int contextId;
  JS_ToInt32(ctx, &contextId, JS_GetPropertyStr(ctx, global, "contextId"));
  EngineInvokeModuleCallback callback = nullptr;
  const char *moduleName = JS_ToCString(ctx, argv[0]);
  const char *methodName = JS_ToCString(ctx, argv[1]);
  const char *args = JS_ToCString(ctx, JS_JSONStringify(ctx, argv[2], JS_UNDEFINED, JS_UNDEFINED));
  JSValue jsCallback = JS_UNDEFINED;
  if (argc > 3)
  {
    jsCallback = argv[3];
  }

  callback = [ctx, jsCallback, this_val, contextId](int errorCode, const char *result)
  {
    EngineNativeMethods::instance()->log(contextId, "info", "QuickJSEngineContext.callback");
    if (JS_IsFunction(ctx, jsCallback))
    {
      JSValue callbackArgs[2];
      callbackArgs[0] = JS_NewInt32(ctx, errorCode);
      callbackArgs[1] = JS_NewString(ctx, result);
      JS_Call(ctx, jsCallback, this_val, 2, callbackArgs);
    }
    else
    {
      EngineNativeMethods::instance()->log(contextId, "error", "QuickJSEngineContext.callback not found");
    }
  };
  EngineNativeMethods::instance()->log(contextId, "info", "QuickJSEngineContext.invokeModule");
  const char *result = EngineNativeMethods::instance()->invokeModule(contextId, moduleName, methodName, args, callback);
  return JS_NewString(ctx, result);
}

void QuickJSModule::initModule(JSContext *context)
{
  JSValue global = JS_GetGlobalObject(context);
  JSValue console = JS_NewObject(context);

  JS_SetPropertyStr(context, global, "__module__", console);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "invokeModule"),
      JS_DupValue(context, JS_NewCFunction(context, invokeModule, "invokeModule", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);
}
