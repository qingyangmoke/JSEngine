#include "JavaScriptCore.h"
#include <iostream>
#include <string>
#include <vector>
#include "include/jsengine_bridge.h"
#include "JSCoreContext.h"
#include "JSCoreHelper.h"
#include "JSCoreConsole.h"
#include "JSCoreModule.h"

using namespace JSEngineNS;
using namespace JSEngineNS::jsc;

JSCoreEngineContext::JSCoreEngineContext(int contextId) : EngineContext(contextId)
{
  JSStaticFunction globalFunctions[] = {
      {nullptr} // null termination
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
  if (exc == NULL)
  {
    return true;
  }
  JSObjectRef error = JSValueToObject(this->context(), exc, nullptr);
  JSStringRef messageKey = JSStringCreateWithUTF8CString("message");
  JSStringRef stackKey = JSStringCreateWithUTF8CString("stack");
  JSValueRef messageRef = JSObjectGetProperty(this->context(), error, messageKey, nullptr);
  JSValueRef stackRef = JSObjectGetProperty(this->context(), error, stackKey, nullptr);
  JSStringRef messageStr = JSValueToStringCopy(this->context(), messageRef, nullptr);
  JSStringRef stackStr = JSValueToStringCopy(this->context(), stackRef, nullptr);
  std::string &&message = JSStringToStdString(messageStr);
  std::string &&stack = JSStringToStdString(stackStr);
  // handler(getContextId(), (message + '\n' + stack).c_str());
  EngineNativeMethods::instance()->log(getContextId(), "error", (message + '\n' + stack).c_str());
  JSStringRelease(messageKey);
  JSStringRelease(stackKey);
  JSStringRelease(messageStr);
  JSStringRelease(stackStr);
  return false;
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
  handleException(exception);
}

JSCoreEngineContext::~JSCoreEngineContext()
{
  std::cout << "JSCoreEngineContext destroyed" << std::endl;
  JSGlobalContextRelease(_jscContext);
}