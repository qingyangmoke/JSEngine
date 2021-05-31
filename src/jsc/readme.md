# API

## 支持日志输出
```js
  console
    log
    info
    warn
    error
  console.log('', '');  
```

## 实现invokeModule
```js
   window.__alita__.invokeModule('Navigation', 'to', { name:'xxxx' }, function(error, result) {
        console.log('invokeModule', Array.from(arguments).join(','));
   });
```

##  实现基础类
```js
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
```


