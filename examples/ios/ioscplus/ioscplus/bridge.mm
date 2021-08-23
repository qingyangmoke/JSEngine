//
//  bridge.m
//  ioscplus
//
//  Created by song on 2021/5/19.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <iostream>
#import "bridge.h"
#import "EngineScope.h"
// oc 中调用swift 要引入此文件 {Product Module Name}-Swift.h
#import "ioscplus-Swift.h"
// 一定对mm文件中定义
#import <jsengine_bridge/jsengine_bridge.h>

// 使用MyBridge 暴露C++的对外的接口
@implementation MyBridge

+ (void)initBridge {
    if(!JSEngineNS::EngineNativeMethods::instance()->invokeModulePointer) {
        JSEngineNS::EngineNativeMethods::instance()->invokeModulePointer = ^const char *(int contextId, int callId, const char *moduleName, const char *methodName, const char *args) {
            NSString *result = [OCSwiftEngineProxy invokeModuleWithContextId:contextId callId: callId moduleName:[NSString stringWithUTF8String:moduleName] methodName:[NSString stringWithUTF8String: methodName] args: [NSString stringWithUTF8String: args]];
            return [result UTF8String];
        };
    }
    if(!JSEngineNS::EngineNativeMethods::instance()->logPointer) {
        JSEngineNS::EngineNativeMethods::instance()->logPointer = ^const char *(int contextId, const char *tagName, const char *message) {
            // 需要在这里实现module对应的处理类
            printf("【Console】contextId=%d, tagName=%s, message=%s \n",  contextId, tagName, message);
            return "success";
        };
    }
}

+ (int)invokeModuleEvent
:(int) contextId widthCallId: (int) callId withErrorCode:(int) errorCode withResult: (NSString *)result {
    JSEngineNS::EngineNativeMethods::instance()->invokeModuleEvent(contextId, callId, errorCode, [result UTF8String]);
    return 0;
}

//+ (EngineScope *)createScope:(int) contextId {
//    EngineScope *scope = [[EngineScope alloc] initWithContextId:contextId];
//    return scope;
//}

+ (void)createScope:(int) contextId {
    JSEngineNS::Engine::instance()->createScope(contextId);
}
+ (void)evaluateJavaScript:(int) contextId widthSourceCode: (NSString *) sourceCode widthSourceURL: (NSString *) sourceURL widthStartLine: (int) startLine {
    JSEngineNS::EngineScope* scope = JSEngineNS::Engine::instance()->getScope(contextId);
    if(scope != NULL) {
        scope->evaluateJavaScript([sourceCode UTF8String], [sourceURL UTF8String], startLine);
    } else {
        printf("【EngineScope】scope 已销毁 _contextId=%d  \n", contextId);
    }
    scope = NULL;
}

+ (void)invokeJSModule:(int) contextId withModuleName: (NSString *) moduleName widthMethodName: (NSString *) methodName widthArgs: (NSString *) args {
    JSEngineNS::EngineScope* scope = JSEngineNS::Engine::instance()->getScope(contextId);
    if(scope != NULL) {
        scope->invokeJSModule([moduleName UTF8String], [methodName UTF8String], [args UTF8String]);
    } else {
        printf("【EngineScope】scope 已销毁 _contextId=%d  \n", contextId);
    }
    scope = NULL;
}

+ (void)removeScope:(int) contextId {
    JSEngineNS::Engine::instance()->removeScope(contextId);
}

+ (int)engineTest {
    int contextId = 1;
    // 获取全局对象
    JSEngineNS::Engine* engine = JSEngineNS::Engine::instance();
    // 创建jsscope
    JSEngineNS::EngineScope* scope = engine->createScope(contextId);
    printf("contextId=%d \n\t", scope->getContextId());
    
    scope->evaluateJavaScript([@"var a = 1; window.delayCall(function(){ console.log('callback', 'args1', 'args2'); }, 2000);" UTF8String], [@"" UTF8String], 0);
    
    scope->evaluateJavaScript([@"a++; console.warn(a);;" UTF8String], [@"" UTF8String], 0);
    
    scope->evaluateJavaScript([@"window.__alita__.invokeModule('Navigation', 'to', {name:'xxxx'}, function() { console.log('invokeModule'); });" UTF8String], [@"" UTF8String], 0);
    
    scope = NULL; // 不用的时候把指针设置为空
    
    JSEngineNS::EngineScope* scope2 = engine->getScope(contextId);
    printf("contextId=%d \n\t", scope2->getContextId());
    scope2 = NULL; // 不用的时候把指针设置为空
    
    // 释放scope
    engine->removeScope(contextId);
    
    // 已经释放 则获取不到了
    JSEngineNS::EngineScope* scope3 = engine->getScope(contextId);
    printf("contextId=%d \n\t", scope3 == NULL ? -1 : scope3->getContextId());
    
    // C++ string 转成NSString使用
    NSString *version = [NSString stringWithUTF8String:engine->version.c_str()];
    printf("version=%s \n\t", [version UTF8String]);
    return 1;
}

@end

