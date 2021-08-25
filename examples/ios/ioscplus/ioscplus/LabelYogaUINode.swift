//
//  LabelYogaUINode.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//
import Foundation
import UIKit
import YogaKit
import UIColor_Hex_Swift
public class LabelYogaUINode: YogaUINode {
    public init(uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: "label", uniqueId: uniqueId , scope: scope)
        let label = UILabel()
        setNativeView(view: label)
    }
    
    public func getLabelView() -> UILabel {
        return getNativeView() as! UILabel
    }
    
    public func setText(text: String) {
        getLabelView().text = text
    }
    
    public override func setAttribute(key: String, value: String) {
        switch (key) {
            case "text":
                setText(text: value);
                break;
            default:
                super.setAttribute(key: key, value: value)
                break;
        }
    }

    public override func setStyle(key: String, value: String) {
        super.setStyle(key: key, value: value)
        switch (key) {
            case "color":
                getLabelView().textColor = UIColor(value)
                break;
            case "textAlign":
                switch (value) {
                    case "left":
                        getLabelView().textAlignment = NSTextAlignment.left;
                        break;
                    case "right":
                        getLabelView().textAlignment = NSTextAlignment.right;
                        break;
                    case "center":
                        getLabelView().textAlignment = NSTextAlignment.center;
                        break;
                    default:
                        break;
                }
                break;
            case "verticalAlign":
                 // todo: //
                break;
            default:
                break;
        }
    }
}
