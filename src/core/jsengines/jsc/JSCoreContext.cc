#include "JavaScriptCore.h"
#include <iostream>
#include <string>
#include <vector>
#include "include/jsengine_bridge.h"
#include "JSCoreContext.h"
#include "JSCoreHelper.h"
#include "JSCoreConsole.h"
#include "JSCoreModule.h"

using namespace CPlusDemo;
using namespace CPlusDemo::jsc;

JSValueRef delayCall(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
                     const JSValueRef *arguments, JSValueRef *exception)
{
  JSCoreEngineContext *context = static_cast<JSCoreEngineContext *>(JSObjectGetPrivate(JSContextGetGlobalObject(ctx)));

  const JSValueRef &callbackValueRef = arguments[0];
  const JSValueRef &timeoutValueRef = arguments[1];

  if (!JSValueIsObject(ctx, callbackValueRef))
  {
    throwJSError(ctx, "Failed to execute 'setTimeout': parameter 1 (callback) must be a function.", exception);
    return nullptr;
  }

  JSObjectRef callbackObjectRef = JSValueToObject(ctx, callbackValueRef, exception);

  if (!JSObjectIsFunction(ctx, callbackObjectRef))
  {
    throwJSError(ctx, "Failed to execute 'setTimeout': parameter 1 (callback) must be a function.", exception);
    return nullptr;
  }

  int32_t timeout;

  if (argumentCount < 2 || JSValueIsUndefined(ctx, timeoutValueRef))
  {
    timeout = 0;
  }
  else if (JSValueIsNumber(ctx, timeoutValueRef))
  {
    timeout = JSValueToNumber(ctx, timeoutValueRef, exception);
  }
  else
  {
    throwJSError(ctx, "Failed to execute 'setTimeout': parameter 2 (timeout) only can be a number or undefined.",
                 exception);
    return nullptr;
  }

  JSValueRef args[2];
  args[0] = JSValueMakeNumber(ctx, 1);
  args[1] = JSValueMakeNumber(ctx, 2);

  JSObjectCallAsFunction(ctx, callbackObjectRef, thisObject, 2, args, exception);

  std::cout << "delayCall timeout=" << timeout << std::endl;

  int timerId = 1;

  return JSValueMakeNumber(ctx, timerId);
}

JSCoreEngineContext::JSCoreEngineContext(int contextId) : EngineContext(contextId)
{
  JSStaticFunction globalFunctions[] = {
      "delayCall", delayCall, kJSPropertyAttributeNone, {nullptr} // null termination
  };

  JSStaticValue globalValues[] = {
      {nullptr} // null termination
  };

  JSClassDefinition contextDefinition = kJSClassDefinitionEmpty;
  contextDefinition.staticFunctions = globalFunctions;
  contextDefinition.staticValues = globalValues;
  JSClassRef contextClass = JSClassCreate(&contextDefinition);

  _jscContext = JSGlobalContextCreate(contextClass);

  JSObjectRef global = JSContextGetGlobalObject(_jscContext);
  JSObjectSetPrivate(global, this);

  JSStringRef windowName = JSStringCreateWithUTF8CString("window");
  JSStringRef globalThis = JSStringCreateWithUTF8CString("globalThis");
  JSObjectSetProperty(_jscContext, global, windowName, global, kJSPropertyAttributeNone, nullptr);
  JSObjectSetProperty(_jscContext, global, globalThis, global, kJSPropertyAttributeNone, nullptr);

  JSStringRelease(windowName);
  JSStringRelease(globalThis);

  JSStringRef contextIdJSString = JSStringCreateWithUTF8CString("contextId");
  JSObjectSetProperty(_jscContext, global, contextIdJSString, JSValueMakeNumber(_jscContext, contextId), kJSPropertyAttributeNone, nullptr);
  JSStringRelease(contextIdJSString);

  JSCoreConsole::initConsole(_jscContext, global);
  JSCoreModule::initModule(_jscContext, global);
}

JSGlobalContextRef JSCoreEngineContext::context()
{
  return _jscContext;
}

JSObjectRef JSCoreEngineContext::global()
{
  return JSContextGetGlobalObject(this->context());
}

bool JSCoreEngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  JSStringRef sourceRef = JSStringCreateWithUTF8CString(sourceCode);
  JSStringRef sourceURLRef = NULL;
  if (sourceURL != NULL)
  {
    sourceURLRef = JSStringCreateWithUTF8CString(sourceURL);
  }

  JSValueRef exception = NULL; // exception
  JSEvaluateScript(this->context(), sourceRef, NULL /*null means global*/, sourceURLRef, startLine, &exception);

  JSStringRelease(sourceRef);

  if (sourceURLRef != NULL)
  {
    JSStringRelease(sourceURLRef);
  }
  return handleException(exception);
}

bool JSCoreEngineContext::handleException(JSValueRef exc)
{
  // if (JSC_UNLIKELY(exc))
  // {
  //   HANDLE_JSC_EXCEPTION(this->context(), exc, _handler);
  //   return false;
  // }
  return exc == NULL;
}

JSCoreEngineContext *JSCoreEngineContext::getContext(JSContextRef context)
{
  return reinterpret_cast<JSCoreEngineContext *>(JSObjectGetPrivate(JSContextGetGlobalObject(context)));
}

/**
 * 调用js module
 * */
void JSCoreEngineContext::invokeJSModule(const char *moduleName, const char *methodName, const char *args)
{
  if (moduleName == NULL || methodName == NULL)
  {
    return;
  }
  JSObjectRef global = this->global();
  JSValueRef exception = NULL;
  JSStringRef moduleNameRef = JSStringCreateWithUTF8CString(moduleName);
  JSValueRef moduleValueRef = JSObjectGetProperty(this->context(), global, moduleNameRef, &exception);
  if (!JSValueIsNull(this->context(), moduleValueRef) && JSValueIsObject(this->context(), moduleValueRef))
  {
    JSObjectRef moduleRef = JSValueToObject(this->context(), moduleValueRef, &exception);
    JSStringRef methodNameRef = JSStringCreateWithUTF8CString(methodName);
    JSValueRef methodValueRef = JSObjectGetProperty(this->context(), moduleRef, methodNameRef, &exception);
    if (!JSValueIsNull(this->context(), methodValueRef) && JSValueIsObject(this->context(), methodValueRef))
    {
      JSObjectRef methodRef = JSValueToObject(this->context(), methodValueRef, &exception);
      if (JSObjectIsFunction(this->context(), methodRef))
      {
        JSStringRef argsValueRef = args == NULL ? JSStringCreateWithUTF8CString("") : JSStringCreateWithUTF8CString(args);
        JSValueRef callbackArgs[1];
        callbackArgs[0] = JSValueMakeString(this->context(), argsValueRef);
        JSObjectCallAsFunction(this->context(), methodRef, moduleRef, 1, callbackArgs, &exception);
        JSStringRelease(argsValueRef);
      }
    }
    JSStringRelease(methodNameRef);
  }
  JSStringRelease(moduleNameRef);
}

JSCoreEngineContext::~JSCoreEngineContext()
{
  std::cout << "JSCoreEngineContext destroyed" << std::endl;
  JSGlobalContextRelease(_jscContext);
}