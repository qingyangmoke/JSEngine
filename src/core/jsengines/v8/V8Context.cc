#include "v8.h"
#include "V8Context.h"
#include "V8Runtime.h"
#include "V8Console.h"
#include "V8EngineModule.h"
using namespace CPlusDemo;

V8EngineContext::V8EngineContext(int contextId) : EngineContext(contextId)
{
  V8Runtime::instance()->Initialize();
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext init begin");
  v8::Isolate *isolate = V8Runtime::instance()->getIsolate();
  if (isolate == NULL)
  {
    EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext NULL");
  }

  v8::Isolate::Scope isolate_scope(isolate);
  v8::HandleScope handle_scope(isolate);
  auto globalFunctionTemplate = v8::FunctionTemplate::New(isolate);
  globalFunctionTemplate->SetClassName(V8Runtime::instance()->ConvertToV8String(isolate, "JSEngineGlobalObject"));
  auto globalTemplate = v8::ObjectTemplate::New(isolate, globalFunctionTemplate);
  v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, globalTemplate);
  this->m_context = *context;
  this->context.Reset(isolate, context);
  v8::Context::Scope context_scope(context);
  auto global = context->Global();
  const auto readOnlyFlags = static_cast<v8::PropertyAttribute>(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly);
  auto success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "globalThis"), global, readOnlyFlags);
  success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "global"), global, readOnlyFlags);
  success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "window"), global, readOnlyFlags);

  v8::Local<v8::Number> contextIdValue = v8::Number::New(isolate, contextId);
  success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "contextId"), contextIdValue, readOnlyFlags);

  V8Console::initConsole(context);
  V8EngineModule::initModule(context);

  // evaluateJavaScript("console.log('javascript', 'hello world');", "", 0);
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext init end");
  isolate = NULL;
}

bool V8EngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext.evaluateJavaScript");
  v8::Isolate::Scope isolate_scope(V8Runtime::instance()->getIsolate());
  v8::HandleScope handle_scope(V8Runtime::instance()->getIsolate());
  v8::TryCatch tc(V8Runtime::instance()->getIsolate());
  v8::Local<v8::Context> context = getLocalContext();
  v8::Context::Scope context_scope(context);
  std::string strSourceCode(sourceCode);
  v8::Local<v8::String> source = V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), strSourceCode);
  v8::Local<v8::Script> script;
  std::string str(sourceURL);
  v8::ScriptOrigin origin(V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), str));
  v8::Script::Compile(context, source, &origin).ToLocal(&script);
  if (tc.HasCaught())
  {
    EngineNativeMethods::instance()->log(_contextId, "error", "Script contains compilation errors!");
    return false;
  }

  if (!script.IsEmpty())
  {
    script->Run(context);

    if (tc.HasCaught())
    {
      EngineNativeMethods::instance()->log(_contextId, "error", "Error running script ");
    }
  }
  else
  {
    EngineNativeMethods::instance()->log(_contextId, "warn", ">>runScript maybeScript is empty");
  }
  return true;
}

v8::Local<v8::Context> V8EngineContext::getLocalContext()
{
  return this->context.Get(V8Runtime::instance()->getIsolate());
}

V8EngineContext::~V8EngineContext()
{
  this->context.Reset();
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext destroyed");
}