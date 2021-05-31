# cplus-study
c++ study demo

## 环境要求
- cmake >= 3.11-3.18
- c++17

## 生成make文件
```js
  // 模拟器可用库 Debug使用
  npm run build:bridge:ios:simulator
  // 无模拟器链接库 真机使用
  npm run build:bridge:ios
  // release
  npm run build:bridge:ios:release
```
## 配置Xcode
> 禁用Bitcode
```js
   Build Settings -> Build Options
   -> Enable Bitcode : No
```

> 添加和C++交互的头文件
```js
   Build Settings -> Swift Compiler - General 
   -> Objective-C Briding Header : ioscplus/ioscplus-Bridging-Header.h
```

> 解决模拟器启动报错
```js
   Build Settings -> Build Active Architecture Only 
   -> Debug : Yes
```

> 解决真机启动找不到签名错误
```js
  Build Phases -> Embed Frameworks 勾选 Copy Sign On Copy
```

> 编译排除无效代码
```js
  Build Settings -> Excluded Architectures 
    -> Any iOS Simulator SDK : arm64, arm64e, armv7
    -> Any iOS SDK: x86_64, i386
```

# 资料
 * [vscode C++插件](https://code.visualstudio.com/docs/languages/cpp)
 * 
 