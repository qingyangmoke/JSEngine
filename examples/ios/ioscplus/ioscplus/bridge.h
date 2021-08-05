//
//  bridge.h
//  ioscplus
//
//  Created by song on 2021/5/19.
//

#ifndef bridge_h
#define bridge_h

#import <Foundation/Foundation.h>
#import "EngineScope.h"

@interface MyBridge : NSObject
+ (void)initBridge;
//+ (EngineScope *)createScope:(int) contextId;
+ (void)createScope:(int) contextId;
+ (void)removeScope:(int) contextId;
+ (int)invokeModuleEvent:(int) contextId widthCallId: (int) callId withErrorCode:(int) errorCode withResult: (NSString *)result;
+ (void)evaluateJavaScript:(int) contextId widthSourceCode: (NSString *) sourceCode widthSourceURL: (NSString *) sourceURL widthStartLine: (int) startLine;
+ (void)invokeJSModule:(int) contextId withModuleName: (NSString *) moduleName widthMethodName: (NSString *) methodName widthArgs: (NSString *) args;
+ (int)engineTest;
@end

#endif /* bridge_h */
