//
//  bridge.m
//  ioscplus
//
//  Created by song on 2021/5/19.
//

#import <Foundation/Foundation.h>
#include <iostream>
#import "bridge.h"
#import "EngineScope.h"

// 一定对mm文件中定义
#import <jsengine_bridge/jsengine_bridge.h>

// 使用MyBridge 暴露C++的对外的接口
@implementation MyBridge

+ (void)initBridge {
    if(!CPlusDemo::EngineNativeMethods::instance()->invokeModulePointer) {
        CPlusDemo::EngineNativeMethods::instance()->invokeModulePointer = ^const char *(int contextId, int callId, const char *moduleName, const char *methodName, const char *args) {
            // 需要在这里实现module对应的处理类
            printf("【MyBridge】moduleName=%s,methodName=%s, args=%s \n",  moduleName, methodName, args);
            NSString *str = [[NSString alloc] initWithFormat: @"{\"moduleName\": \"%@\", \"methodName\": \"%@\"}", [NSString stringWithUTF8String: moduleName], [NSString stringWithUTF8String: methodName]];
            // 处理完毕通过事件回调给值
            CPlusDemo::EngineNativeMethods::instance()->invokeModuleEvent(contextId, callId, 0, [str UTF8String]);
            return "success";
        };
    }
    if(!CPlusDemo::EngineNativeMethods::instance()->logPointer) {
        CPlusDemo::EngineNativeMethods::instance()->logPointer = ^const char *(int contextId, const char *tagName, const char *message) {
            // 需要在这里实现module对应的处理类
            printf("【Console】contextId=%d, tagName=%s, message=%s \n",  contextId, tagName, message);
            return "success";
        };
    }
}

+ (EngineScope *)createScope:(int) contextId {
    EngineScope *scope = [[EngineScope alloc] initWithContextId:contextId];
    return scope;
}

+ (int)flushBridgeTask {
    return flushBridgeTask();
}

// 测试传递字符串
+ (int)printCPlusString:(NSString *) str {
    CPlusDemo::Student *student = new CPlusDemo::Student([@"hello" UTF8String], 10);
    student->say();
    delete student;
    return printString([str UTF8String]);
}

// 测试传递结构体
+ (int)testStruct:(NSString *) str widthLength: (int) length {
    NativeString *ns = new NativeString();
    ns->string = [str UTF8String];
    ns->length = length;
    return testStruct(ns);
}

// 测试传递回调函数+target指针
+ (void)testCallback: (NSString *) str widthCallBack: (void(*)(const char* result, void* target)) resultCallback withTarget: (void*) target {
    testCallback([str UTF8String], resultCallback, target);
}

+ (int)engineTest {
    int contextId = 1;
    // 获取全局对象
    CPlusDemo::Engine* engine = CPlusDemo::Engine::instance();
    // 创建jsscope
    CPlusDemo::EngineScope* scope = engine->createScope(contextId);
    printf("contextId=%d \n\t", scope->getContextId());
    
    scope->evaluateJavaScript([@"var a = 1; window.delayCall(function(){ console.log('callback', 'args1', 'args2'); }, 2000);" UTF8String], [@"" UTF8String], 0);
    
    scope->evaluateJavaScript([@"a++; console.warn(a);;" UTF8String], [@"" UTF8String], 0);
    
    scope->evaluateJavaScript([@"window.__alita__.invokeModule('Navigation', 'to', {name:'xxxx'}, function() { console.log('invokeModule'); });" UTF8String], [@"" UTF8String], 0);
    
    scope = NULL; // 不用的时候把指针设置为空
    
    CPlusDemo::EngineScope* scope2 = engine->getScope(contextId);
    printf("contextId=%d \n\t", scope2->getContextId());
    scope2 = NULL; // 不用的时候把指针设置为空
    
    // 释放scope
    engine->removeScope(contextId);
    
    // 已经释放 则获取不到了
    CPlusDemo::EngineScope* scope3 = engine->getScope(contextId);
    printf("contextId=%d \n\t", scope3 == NULL ? -1 : scope3->getContextId());
    
    // C++ string 转成NSString使用
    NSString *version = [NSString stringWithUTF8String:engine->version.c_str()];
    printf("version=%s \n\t", [version UTF8String]);
    return 1;
}

@end

