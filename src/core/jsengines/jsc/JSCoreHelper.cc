#include "JavaScriptCore.h"

#include <iostream>
#include <string>
#include <vector>
#include "JSCoreHelper.h"

using namespace JSEngineNS;

void jsc::throwJSError(JSContextRef ctx, const char *msg, JSValueRef *exception)
{
  JSStringRef _errmsg = JSStringCreateWithUTF8CString(msg);
  const JSValueRef args[] = {JSValueMakeString(ctx, _errmsg), nullptr};
  *exception = JSObjectMakeError(ctx, 1, args, nullptr);
  JSStringRelease(_errmsg);
}

std::string jsc::JSStringToStdString(JSStringRef jsString)
{
  if (jsString == NULL)
  {
    return NULL;
  }
  size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
  std::vector<char> buffer(maxBufferSize);
  JSStringGetUTF8CString(jsString, buffer.data(), maxBufferSize);
  return std::string(buffer.data());
}

std::string jsc::JSValueToStdString(JSContextRef jsContext, JSValueRef val, JSValueRef *exception)
{
  if (val == NULL)
  {
    return NULL;
  }
  JSStringRef jscString = JSValueToStringCopy(jsContext, val, NULL);
  std::string ret = JSStringToStdString(jscString);
  JSStringRelease(jscString);
  return ret;
}