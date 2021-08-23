//
//  NativeModule.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation

public class NativeModule {
    private var _moduleName: String;
    private var _scope: JSEngineScope;
    public init(moduleName: String, scope: JSEngineScope) {
        _moduleName = moduleName;
        _scope = scope;
    }
    
    public func getModuleName() -> String {
        return _moduleName;
    }

    public func getScope() -> JSEngineScope {
        return _scope;
    }
    
    public func invokeMethod(callId: Int32, methodName: String, args: String) -> String {
        // TODO: 子类需实现
        return "";
    }
    
    public func invokeMethodCallBack(callId: Int32, errorCode: Int32, result: String) {
        getScope().invokeModuleEvent(callId: callId, errorCode: errorCode, result: result);
    }
}
