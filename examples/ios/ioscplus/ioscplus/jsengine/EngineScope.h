//
//  EngineScope.h
//  ioscplus
//
//  Created by song on 2021/5/25.
//

#ifndef EngineScope_h
#define EngineScope_h

#import <Foundation/Foundation.h>

@interface EngineScope : NSObject
{
@private
    int _contextId;
    NSMutableDictionary* _modules;
}
- (id)initWithContextId: (int)contextId;
- (int)getContextId;
- (void)evaluateJavaScript: (NSString *) sourceCode widthSourceURL: (NSString *) sourceURL widthStartLine: (int) startLine;
- (void)invokeJSModule: (NSString *) moduleName widthMethodName: (NSString *) methodName widthArgs: (NSString *) args;
- (void)dealloc;
@end

#endif /* EngineScope_h */
