# JSEngine
> JSEngine，构建一个js运行时的抽象层，让JS具备调用IOS、安卓、Flutter、C++能力，底层可以无缝对接支持v8,javascriptCore,quickjs等，抹平底部框架细节，无缝切换，对调用方透明。

**仅供初学者学习使用，初衷是让前端能够轻松的进入跨端领域的入门学习**

## 环境要求
- cmake >= 3.11-3.18
- c++17

## pod install
``` js
cd examples/ios/ioscplus
pod install
```

## 生成make文件
```shell
  # dom polyfil
  npm run build:bridge:polyfill
  # 模拟器可用库 Debug使用
  npm run build:bridge:ios:simulator
  # 无模拟器链接库 真机使用
  npm run build:bridge:ios
  # release
  npm run build:bridge:ios:release
  # 编译v8版本
  npm run build:bridge:android:v8
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
 