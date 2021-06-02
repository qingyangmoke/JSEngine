#include "JavaScriptCore.h"
#include <iostream>
#include <string>
#include "JSCoreConsole.h"
#include "JSCoreHelper.h"
#include "JSCoreContext.h"
#include "include/my_bridge.h"
using namespace CPlusDemo;
using namespace jsc;

JSValueRef jsc_console_msg(std::string type, JSContextRef ctx, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  JSCoreEngineContext *context = JSCoreEngineContext::getContext(ctx);

  JSValueRef undefined = JSValueMakeUndefined(ctx);
  std::string message = "";
  std::cout << "contextId=" << context->getContextId() << " console." << type << " ";
  for (size_t i = 0; i < argumentCount; ++i)
  {
    message.append(jsc::JSValueToStdString(ctx, arguments[i], exception));
    if (i < argumentCount)
    {
      message.append(" ");
    }
  }

  std::cout << message << std::endl;

  EngineNativeMethods::instance()->log(context->getContextId(), type, message);

  return undefined;
}

JSValueRef jsc_console_log(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  return jsc_console_msg("info", ctx, argumentCount, arguments, exception);
}
JSValueRef jsc_console_info(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  return jsc_console_msg("info", ctx, argumentCount, arguments, exception);
}
JSValueRef jsc_console_warn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  return jsc_console_msg("warn", ctx, argumentCount, arguments, exception);
}
JSValueRef jsc_console_error(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  return jsc_console_msg("error", ctx, argumentCount, arguments, exception);
}
JSValueRef jsc_console_debug(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  return jsc_console_msg("debug", ctx, argumentCount, arguments, exception);
}
JSValueRef jsc_console_assert(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef *arguments, JSValueRef *exception)
{
  return jsc_console_msg("assert", ctx, argumentCount, arguments, exception);
}

void JSCoreConsole::initConsole(JSGlobalContextRef jscContext, JSObjectRef global)
{
  JSClassDefinition console_def = kJSClassDefinitionEmpty;
  JSStaticFunction console_funcs[] = {
      {"log", jsc_console_log, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {"info", jsc_console_info, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {"warn", jsc_console_warn, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {"error", jsc_console_error, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {"debug", jsc_console_debug, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {"assert", jsc_console_assert, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly},
      {} // null termination
  };
  console_def.staticFunctions = console_funcs;
  JSClassRef console_class = JSClassCreate(&console_def);

  JSStringRef consoleName = JSStringCreateWithUTF8CString("console");
  JSObjectRef console_obj = JSObjectMake(jscContext, console_class, NULL);
  JSObjectSetProperty(jscContext, global, consoleName, console_obj, kJSPropertyAttributeNone, NULL);

  JSStringRelease(consoleName);
}
