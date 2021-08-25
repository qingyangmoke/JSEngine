//
//  YogaUINode.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation
import UIKit
import YogaKit
import UIColor_Hex_Swift
public class YogaUINode : IUINode {
    private var _view: UIView! = nil
    private var _userStyle: [String:String] = [:]
    public override init(tagName: String, uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: tagName, uniqueId: uniqueId, scope: scope)
    }

    public func getUserStyle(key: String) -> String? {
        return _userStyle[key];
    }
    
    public func setUserStyle(key: String, value: String) {
        _userStyle.updateValue(value, forKey: key)
    }
    
    public func getNativeView() -> UIView {
        return _view;
    }
    
    public func setNativeView(view: UIView) {
        view.yoga.isEnabled = true
        view.yoga.flexDirection = .column
        view.tag = Int(getUniqueId())
        _view = view;
    }
    
    public func getYogaLayout() -> YGLayout {
        return _view.yoga;
    }
    
    public override func getAttribute(key: String) -> String {
        var value = "";
        switch (key) {
            case "width":
                let width = getNativeView().bounds.width
                value = "\(width)"
                break;
            case "height":
                let height = getNativeView().bounds.height
                value = "\(height)"
                break;
            default:
                value = super.getAttribute(key: key)
            break;
        }
        return value
    }
    
    public override func setAttribute(key: String, value: String) {
        switch (key) {
            case "width":
                setStyle(key: key, value: value)
                break;
            case "height":
                setStyle(key: key, value: value)
                break;
            default:
                super.setAttribute(key: key, value: value)
            break;
        }
    }
    
    public override func setStyle(key: String, value: String) {
        setUserStyle(key: key, value: value)
        switch (key) {
            case "backgroundColor":
                getNativeView().backgroundColor = UIColor(value);
                break;
            default:
                YogaStyleHelper.setStyle(node: self, key: key, value: value)
            break;
        }
    }
    
    public override func resetStyle() {
        YogaStyleHelper.resetStyle(node: self, userStyle: _userStyle);
    }
}
