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
}
- (id)initWithContextId: (int)contextId;
- (int)getContextId;
- (void)evaluateJavaScript: (NSString *) sourceCode widthSourceURL: (NSString *) sourceURL widthStartLine: (int) startLine;
- (void)dealloc;
@end

#endif /* EngineScope_h */
