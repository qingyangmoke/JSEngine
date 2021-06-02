#include <iostream>
#include <string>
#include "QuickJSConsole.h"
using namespace CPlusDemo;
using namespace quickjs;

JSValue console_msg(const char *tag, JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  JSValue global = JS_GetGlobalObject(ctx);
  int contextId;
  JS_ToInt32(ctx, &contextId, JS_GetPropertyStr(ctx, global, "contextId"));

  std::string message = "";
  for (size_t i = 0; i < argc; ++i)
  {
    message.append(JS_ToCString(ctx, argv[i]));
    if (i < argc)
    {
      message.append(" ");
    }
  }

  std::cout << message << std::endl;

  EngineNativeMethods::instance()->log(contextId, tag, message);

  return JS_UNDEFINED;
}

JSValue console_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  return console_msg("info", ctx, this_val, argc, argv);
}

JSValue console_warn(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  return console_msg("warn", ctx, this_val, argc, argv);
}
JSValue console_error(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  return console_msg("error", ctx, this_val, argc, argv);
}
JSValue console_debug(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  return console_msg("debug", ctx, this_val, argc, argv);
}
JSValue console_assert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
  return console_msg("assert", ctx, this_val, argc, argv);
}

void QuickJSConsole::initConsole(JSContext *context)
{
  JSValue global = JS_GetGlobalObject(context);
  JSValue console = JS_NewObject(context);

  JS_SetPropertyStr(context, global, "console", console);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "log"),
      JS_DupValue(context, JS_NewCFunction(context, console_log, "log", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "info"),
      JS_DupValue(context, JS_NewCFunction(context, console_log, "info", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "warn"),
      JS_DupValue(context, JS_NewCFunction(context, console_warn, "warn", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "error"),
      JS_DupValue(context, JS_NewCFunction(context, console_error, "error", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "debug"),
      JS_DupValue(context, JS_NewCFunction(context, console_debug, "debug", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);

  JS_DefinePropertyValue(
      context,
      console,
      JS_NewAtom(context, "assert"),
      JS_DupValue(context, JS_NewCFunction(context, console_assert, "assert", 1)),
      JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);
}
