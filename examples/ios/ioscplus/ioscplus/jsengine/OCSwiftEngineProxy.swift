//
//  JSModule.swift
//  ioscplus
//
//  Created by song on 2021/8/4.
//

import Foundation
import UIKit
// 以表示文件中成员可以被OC调用
@objcMembers
public class OCSwiftEngineProxy : NSObject {
    static var contextIdSeed: Int32 = 0;
    static var _scopes: [Int32:JSEngineScope] = [:];
    
    public static func createScope(view: UIViewController) -> (JSEngineScope)  {
        contextIdSeed += 1;
        let scope = JSEngineScope(contextId: contextIdSeed, view: view);
        _scopes.updateValue(scope, forKey: scope.getContextId());
        scope.intJSScope()
        return scope;
    }
    
    public static func getScope(contextId: Int32) -> JSEngineScope? {
        return _scopes[contextId];
    }
    
    
    public static func removeScope(contextId: Int32) {
        _scopes.removeValue(forKey: contextId);
    }
    
    public static func invokeModule(contextId: Int32, callId: Int32, moduleName: NSString, methodName: NSString, args: NSString) -> String {
        NSLog("【OCSwiftEngineProxy】moduleName=%@, methodName=%@, args=%@ contextId=%d\n",  moduleName, methodName, args, contextId);
        return getScope(contextId: contextId)?.invokeNativeModule(callId: callId, moduleName: moduleName as String, methodName: methodName  as String, args: args  as String) ?? "";
    }
}
