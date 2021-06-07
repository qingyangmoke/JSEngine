//
//  bridge.m
//  ioscplus
//
//  Created by song on 2021/5/19.
//

#import <Foundation/Foundation.h>
#include <iostream>
#import "EngineScope.h"

// 一定对mm文件中定义
#import <jsengine_bridge/jsengine_bridge.h>

// 使用MyBridge 暴露C++的对外的接口
@implementation EngineScope

- (id)initWithContextId: (int)contextId {
    if(self = [super init]){
        _contextId = contextId;
        CPlusDemo::Engine::instance()->createScope(contextId);
    }
    return self;
}

- (int)getContextId {
    return _contextId;
}

- (void)evaluateJavaScript: (NSString *) sourceCode widthSourceURL: (NSString *) sourceURL widthStartLine: (int) startLine {
    CPlusDemo::EngineScope* scope = CPlusDemo::Engine::instance()->getScope(_contextId);
    if(scope != NULL) {
        scope->evaluateJavaScript([sourceCode UTF8String], [sourceURL UTF8String], startLine);
    } else {
        printf("【EngineScope】scope 已销毁 _contextId=%d  \n", _contextId);
    }
    scope = NULL;
}

// 对象被销毁
-(void)dealloc {
    printf("【EngineScope】 dealloc _contextId=%d \n", _contextId);
    CPlusDemo::Engine::instance()->removeScope(_contextId);
}
@end

