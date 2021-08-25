//
//  JSEngineScope.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation
import UIKit
public class JSEngineScope {
    private var _contextId: Int32;
    private var _moduleManager: NativeModuleManager! = nil;
    private var _uiRender: UIRender! = nil;
    private var _view: UIViewController! = nil;
    private var _jsScopeInited: Bool = false;
    public init(contextId: Int32, view: UIViewController) {
        _contextId = contextId
        _view = view
        _moduleManager = NativeModuleManager(scope: self)
        _uiRender = YogaUIRender(scope: self)
    }
    
    public func intJSScope() {
        if(!_jsScopeInited) {
            _jsScopeInited = true;
            MyBridge.createScope(_contextId)
        }
    }
    
    
    public func getUIRender() -> UIRender {
        return _uiRender;
    }
    
    public func getContextId() -> Int32 {
        return _contextId;
    }
    
    public func getViewController() -> UIViewController {
        return _view;
    }

    public func evaluateJavaScript(sourceCode: String, sourceURL: String, startLine: Int32) {
        MyBridge.evaluateJavaScript(_contextId, widthSourceCode: sourceCode, widthSourceURL: sourceURL, widthStartLine: startLine);
    }
    
    public func invokeJSModule(moduleName: String, methodName: String, args: String) {
        MyBridge.invokeJSModule(_contextId, withModuleName: moduleName, widthMethodName: methodName, widthArgs: args);
    }
    
    public func invokeModuleEvent(callId: Int32, errorCode: Int32, result: String) {
        MyBridge.invokeModuleEvent(_contextId, widthCallId: callId, withErrorCode: errorCode, withResult: result);
    }
    
    public func invokeNativeModule(callId: Int32, moduleName: String, methodName: String, args: String) -> String {
        let result = String(format: "{\"moduleName\": \"%@\", \"methodName\": \"%@\",\"from\": \"swift\"}", moduleName, methodName);
        invokeModuleEvent(callId: callId, errorCode: 0, result: result);
        return _moduleManager.invokeNativeModule(callId: callId, moduleName: moduleName, methodName: methodName, args: args);
    }
    
    deinit {
        MyBridge.removeScope(_contextId);
    }
}
