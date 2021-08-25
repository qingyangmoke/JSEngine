//
//  JSEngineScope.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation

public class UIRender {
    private var _scope: JSEngineScope
    private var _rootElement: IUINode! = nil;
    private var _tempElements: [Int32:IUINode] = [:]
    private var _isReady: Bool = false;
    public init(scope: JSEngineScope) {
        _scope = scope
    }

    public func getScope() -> JSEngineScope{
        return _scope;
    }

    public func getRootElement() -> IUINode {
        return _rootElement
    }
    
    public func setRootElement(node: IUINode) {
        _rootElement = node;
        _isReady = true;
    }
    
    public func isReady() -> Bool {
        return _isReady;
    }

    public func addElement(element: IUINode) {
        _tempElements.updateValue(element, forKey: element.getUniqueId())
    }

    public func getElement(uniqueId: Int32) -> IUINode? {
        if(uniqueId == 0) {
            return getRootElement();
        }
        return _tempElements[uniqueId]
    }

    public func createElement(uniqueId: Int32, tagName: String) {}

    public func insertChild(uniqueId: Int32, newChildId: Int32, refChildId: Int32) {}

    public func appendChild(uniqueId: Int32, newChildId: Int32) {}

    public func removeChild(uniqueId: Int32, newChildId: Int32) {}

    public func replaceChild(uniqueId: Int32, newChildId: Int32, oldChildId: Int32) {}

    public func setAttribute(uniqueId: Int32, key: String, value: String) {}

    public func getAttribute(uniqueId: Int32, key: String) -> String { return "" }

    public func removeAttribute(uniqueId: Int32, key: String) {}

    public func setStyle(uniqueId: Int32, key: String, value: String) {}

    public func resetStyle(uniqueId: Int32) {}

    public func scrollTo(uniqueId: Int32, x: Float, y: Float) {}
}
