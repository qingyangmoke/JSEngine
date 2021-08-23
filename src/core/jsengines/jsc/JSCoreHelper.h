#pragma once
#include "JavaScriptCore.h"

#if __has_builtin(__builtin_expect) || defined(__GNUC__)
#define JSC_LIKELY(EXPR) __builtin_expect((bool)(EXPR), true)
#define JSC_UNLIKELY(EXPR) __builtin_expect((bool)(EXPR), false)
#else
#define JSC_LIKELY(EXPR) (EXPR)
#define JSC_UNLIKELY(EXPR) (EXPR)
#endif

#include <iostream>
#include <string>
#include <vector>

#define HANDLE_JSC_EXCEPTION(ctx_, exc, handler)                                   \
  {                                                                                \
    JSObjectRef error = JSValueToObject(ctx_, exc, nullptr);                       \
    JSStringRef messageKey = JSStringCreateWithUTF8CString("message");             \
    JSStringRef stackKey = JSStringCreateWithUTF8CString("stack");                 \
    JSValueRef messageRef = JSObjectGetProperty(ctx_, error, messageKey, nullptr); \
    JSValueRef stackRef = JSObjectGetProperty(ctx_, error, stackKey, nullptr);     \
    JSStringRef messageStr = JSValueToStringCopy(ctx_, messageRef, nullptr);       \
    JSStringRef stackStr = JSValueToStringCopy(ctx_, stackRef, nullptr);           \
    std::string &&message = JSStringToStdString(messageStr);                       \
    std::string &&stack = JSStringToStdString(stackStr);                           \
    handler(getContextId(), (message + '\n' + stack).c_str());                     \
    JSStringRelease(messageKey);                                                   \
    JSStringRelease(stackKey);                                                     \
    JSStringRelease(messageStr);                                                   \
    JSStringRelease(stackStr);                                                     \
  }

namespace JSEngineNS::jsc
{
  void throwJSError(JSContextRef ctx, const char *msg, JSValueRef *exception);

  std::string JSStringToStdString(JSStringRef jsString);

  std::string JSValueToStdString(JSContextRef jsContext, JSValueRef val, JSValueRef *exception);

  std::string JSPropertyGetString(JSContextRef jsContext, JSObjectRef val, const char *key);

  double JSPropertyGetNumber(JSContextRef jsContext, JSObjectRef val, const char *key);
}