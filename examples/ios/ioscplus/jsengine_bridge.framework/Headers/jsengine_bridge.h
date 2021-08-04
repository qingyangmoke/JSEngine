#ifndef BRIDGE_EXPORT_APP_H
#define BRIDGE_EXPORT_APP_H

#include <cstdint>
#include <thread>
#include <iostream>
#include <string>

#include <unordered_map>

// #ifndef __cplusplus
// #define BRIDGE_EXPORT_C extern __attribute__((visibility("default"))) __attribute__((used))
// #define BRIDGE_EXPORT __attribute__((__visibility__("default")))
// #else
// #define BRIDGE_EXPORT_C extern "C" __attribute__((visibility("default"))) __attribute__((used))
// #define BRIDGE_EXPORT __attribute__((__visibility__("default")))
// #endif
#define BRIDGE_EXPORT_C extern "C" __attribute__((visibility("default"))) __attribute__((used))
#define BRIDGE_EXPORT __attribute__((__visibility__("default")))

// 和object-c交互的字符串指针
typedef char *PTR_STR;
//和object-c交互的字符串敞亮指针  注：字符串都用这个类型传递
typedef const char *PTR_C_STR;
// object-c交互的对象执行
typedef void *PTR_OBJECT;

#define OBJECT_INSTANCE(NAME)         \
  static NAME *instance()             \
  {                                   \
    if (singletonInstance == NULL)    \
    {                                 \
      singletonInstance = new NAME(); \
    }                                 \
    return singletonInstance;         \
  }

namespace JSEngineNS
{
  typedef std::function<void(int, const char *)> EngineInvokeModuleCallback;
  typedef std::function<void(int, const char *, const char *)> EngineNativeMethodLog;
  typedef std::function<const char*(int, int, const char *, const char *, const char *)> EngineNativeMethodInvokeModule;

  class BRIDGE_EXPORT EngineNativeMethods
  {
  public:
    OBJECT_INSTANCE(EngineNativeMethods);
    EngineNativeMethodLog logPointer;
    EngineNativeMethodInvokeModule invokeModulePointer;
    void log(int contextId, const std::string tagName, std::string message);
    const char* invokeModule(int contextId, const std::string moduleName, std::string methodName, std::string args, EngineInvokeModuleCallback callback);
    void invokeModuleEvent(int contextId, int callId, int errorCode, const char *result);

  protected:
    static EngineNativeMethods *singletonInstance;
    EngineNativeMethods();
    ~EngineNativeMethods();

  private:
    int _callId = 0;
    std::unordered_map<int, EngineInvokeModuleCallback> _callbackMap = {};
  };

  class BRIDGE_EXPORT EngineContext
  {
  public:
    EngineContext(int contextId);
    virtual ~EngineContext(); // 析构函数要定义成虚函数 否则在释放的时候子类析构函数不会被调用 定义成虚函数后 子类析构函数会被先调用
    int getContextId();
    virtual bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine);

  protected:
    int _contextId;
  };

  class BRIDGE_EXPORT EngineScope
  {
  public:    
    EngineScope(int contextId);
    int getContextId();
    bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine);
    ~EngineScope();

  private:
    EngineContext *_context;
    int _contextId;
  };


  class BRIDGE_EXPORT EnginePlugin
  {
  public:
    std::string name;
    EnginePlugin(const std::string &name);
    virtual ~EnginePlugin();
    virtual void onScopeCreate(EngineScope *scope);
    virtual void onScopeDestroy(EngineScope *scope);
  };

  class BRIDGE_EXPORT Engine
  {
  public:
    std::string version = "v0.0.1";
    OBJECT_INSTANCE(Engine);
    EngineScope *createScope(int contextId);
    EngineScope *getScope(int contextId);
    void removeScope(int contextId);
    void registerPlugin(EnginePlugin *plugin);

  protected:
    static Engine *singletonInstance;
    Engine();
    ~Engine();

  private:
    std::unordered_map<int, EngineScope *> _scopeMap = {};
    std::unordered_map<std::string, EnginePlugin *> _plugins = {};
  };

  class BRIDGE_EXPORT Student
  {
  public:
    std::string name;
    int age;
    Student(const std::string &name, const int age);
    void say();
  };
}

// 和objectc通信的结构体
struct BRIDGE_EXPORT NativeString
{
  PTR_C_STR string;
  int32_t length;
};

BRIDGE_EXPORT_C
int flushBridgeTask();

BRIDGE_EXPORT_C
int testStruct(PTR_OBJECT target);

BRIDGE_EXPORT_C
int printString(PTR_C_STR str); // 测试函数调用2

typedef void (*ResultCallback)(PTR_C_STR result, PTR_OBJECT target); // 定义回调函数

BRIDGE_EXPORT_C
void testCallback(PTR_C_STR str, ResultCallback callback, PTR_OBJECT target); // 测试native回调
#endif
