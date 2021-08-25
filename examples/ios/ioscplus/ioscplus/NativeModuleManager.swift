//
//  NativeModuleManager.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation

public class NativeModuleManager {
    private var dict: [String:NativeModule] = [:];
    private var _scope: JSEngineScope;
    public init(scope: JSEngineScope) {
        _scope = scope;
        registerModule(module: JSTimerModule(scope: scope))
        registerModule(module: UIModule(scope: scope))
    }
    
    public func getScope() -> JSEngineScope {
        return _scope;
    }
    
    public func registerModule(module: NativeModule) {
        dict.updateValue(module, forKey: module.getModuleName());
    }
    
    public func invokeNativeModule(callId: Int32, moduleName: String, methodName: String, args: String) -> String {
        if let module = dict[moduleName] {
            return module.invokeMethod(callId: callId, methodName: methodName, args: args);
        } else {
            let result = String(format: "{\"moduleName\": \"%@\", \"methodName\": \"%@\",\"msg\": \"method not found\"}", moduleName, methodName);
            getScope().invokeModuleEvent(callId: callId, errorCode: 404, result: result);
        }
        return "";
    }
}
