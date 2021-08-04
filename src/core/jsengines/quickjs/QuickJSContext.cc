#include "QuickJSContext.h"
#include "QuickJSConsole.h"
#include "QuickJSModule.h"
using namespace JSEngineNS;
using namespace JSEngineNS::quickjs;

JSRuntime *QuickJSEngineContext::_runtime = NULL;

QuickJSEngineContext::QuickJSEngineContext(int contextId) : EngineContext(contextId)
{
  EngineNativeMethods::instance()->log(_contextId, "info", "QuickJSEngineContext init");
  if (QuickJSEngineContext::_runtime == NULL)
  {
    QuickJSEngineContext::_runtime = JS_NewRuntime();
  }

  _context = JS_NewContext(QuickJSEngineContext::_runtime);

  if (_context == NULL)
  {
    EngineNativeMethods::instance()->log(_contextId, "error", "QuickJSEngineContext._context is NULL");
  }

  JSValue global = JS_GetGlobalObject(_context);
  JS_SetPropertyStr(_context, global, "globalThis", global);
  JS_SetPropertyStr(_context, global, "window", global);
  JS_SetPropertyStr(_context, global, "contextId", JS_NewInt32(_context, contextId));

  QuickJSModule::initModule(_context);
  QuickJSConsole::initConsole(_context);
}

bool QuickJSEngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  EngineNativeMethods::instance()->log(_contextId, "info", "QuickJSEngineContext.evaluateJavaScript begin");
  JS_Eval(_context, sourceCode, strlen(sourceCode), sourceURL, JS_EVAL_TYPE_GLOBAL);
  EngineNativeMethods::instance()->log(_contextId, "info", "QuickJSEngineContext.evaluateJavaScript end");
  return false;
}

void QuickJSEngineContext::invokeJSModule(const char *moduleName, const char *methodName, const char *args)
{
  EngineNativeMethods::instance()->log(_contextId, "warn", "quickjs >>invokeJSModule");

  if (moduleName == NULL || methodName == NULL)
  {
    return;
  }
  JSValue global = JS_GetGlobalObject(_context);

  JSValue moduleValueRef = JS_GetPropertyStr(_context, global, moduleName);
  if (!JS_IsException(moduleValueRef) && JS_IsObject(moduleValueRef))
  {
    JSValue methodValueRef = JS_GetPropertyStr(_context, moduleValueRef, methodName);
    if (!JS_IsException(methodValueRef) && JS_IsFunction(_context, methodValueRef))
    {
      JSValue callbackArgs[1];
      callbackArgs[0] = args == NULL ? JS_NewString(_context, "") : JS_NewString(_context, args);
      JS_Call(_context, methodValueRef, moduleValueRef, 2, callbackArgs);
    }
  }
}

QuickJSEngineContext::~QuickJSEngineContext()
{
  JS_FreeContext(_context);
  // JS_FreeRuntime(_runtime);
  _context = NULL;
  // QuickJSEngineContext::_runtime = NULL;
  EngineNativeMethods::instance()->log(_contextId, "info", "QuickJSEngineContext destroyed");
}