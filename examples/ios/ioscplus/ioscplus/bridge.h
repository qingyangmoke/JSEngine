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
+ (int)flushBridgeTask;
+ (EngineScope *)createScope:(int) contextId;
+ (int)engineTest;
+ (int)printCPlusString:(NSString *) str;
+ (int)testStruct:(NSString *) str widthLength: (int) length;
+ (void)testCallback:(NSString *) str widthCallBack: (void(*)(const char* result, void* target)) resultCallback withTarget: (void*) target;
@end

#endif /* bridge_h */
