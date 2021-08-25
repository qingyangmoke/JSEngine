//
//  IUINode.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation

public class IUINode {
    private var _tagName: String;
    private var _uniqueId: Int32;
    private var _scope: JSEngineScope;
    public init(tagName: String, uniqueId: Int32, scope: JSEngineScope) {
        _tagName = tagName
        _uniqueId = uniqueId
        _scope = scope
    }
    
    public func getUniqueId() -> Int32 {
        return _uniqueId;
    }
    
    public func getScope() -> JSEngineScope {
        return _scope
    }

    public func getTagName() -> String {
        return _tagName;
    }
    
    public func getChildNodes() -> [IUINode] {
        return [];
    }

    public func getAttribute(key: String) -> String {
        return ""
    }

    public func setStyle(key: String, value: String) {
        
    }

    public func resetStyle() {
        
    }

    public func setAttribute(key: String, value: String) {
        
    }

    public func removeAttribute(key: String) {
        
    }

    public func appendChild(newChild: IUINode) -> IUINode {
        return newChild
    }

    public func contains(child: IUINode) -> Bool {
        return false
    }

    public func insertBefore(newChild: IUINode, refChild: IUINode?) -> IUINode {
        return newChild
    }

    public func removeChild(child: IUINode) -> IUINode{
        return child
    }

    public func replaceChild(newChild: IUINode, oldChild: IUINode?) -> IUINode {
        return newChild
    }
}
