#include "QuickJSContext.h"
#include "QuickJSConsole.h"
#include "QuickJSModule.h"
using namespace CPlusDemo;
using namespace CPlusDemo::quickjs;

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

QuickJSEngineContext::~QuickJSEngineContext()
{
  JS_FreeContext(_context);
  // JS_FreeRuntime(_runtime);
  _context = NULL;
  // QuickJSEngineContext::_runtime = NULL;
  EngineNativeMethods::instance()->log(_contextId, "info", "QuickJSEngineContext destroyed");
}