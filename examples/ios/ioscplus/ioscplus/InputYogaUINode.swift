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
public class InputYogaUINode: YogaUINode {

    public init(uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: "input", uniqueId: uniqueId , scope: scope)
        let inputView = UITextField();
        setNativeView(view: inputView)
    }
    
    public func getInputView() -> UITextField {
        return getNativeView() as! UITextField
    }
    
    public func setText(text: String) {
        getInputView().text = text
    }
    
    public func setPlaceholder(placeholder: String) {
        getInputView().placeholder = placeholder
    }
    
    public func setColor(color: String) {
        getInputView().textColor = UIColor(color);
    }
    
    public func setTextAlign(textAlign: String) {
        switch (textAlign) {
            case "left":
                getInputView().textAlignment = NSTextAlignment.left
                break;
            case "right":
                getInputView().textAlignment = NSTextAlignment.right
                break;
            case "center":
                getInputView().textAlignment = NSTextAlignment.center
                break;
            default:
                break;
        }
    }
    
    public func setContentType(contentType: String) {
        getInputView().isSecureTextEntry = false
        getInputView().yoga.display = YGDisplay.flex;
        switch contentType {
            case "tel":
                getInputView().textContentType = UITextContentType.telephoneNumber
                break;
            case "password":
                getInputView().isSecureTextEntry = true
                break;
            case "text":
                getInputView().textContentType = nil
                break;
            case "number":
                getInputView().textContentType = UITextContentType.telephoneNumber
                break;
            case "hidden":
                getInputView().yoga.display = YGDisplay.none;
                break;
            default:
                break
        }
    }
    
    public override func setAttribute(key: String, value: String) {
        switch (key) {
            case "text":
                setText(text: value)
                break;
            case "value":
                setText(text: value)
                break;
            case "placeholder":
                setPlaceholder(placeholder: value)
                break;
            case "type":
                setContentType(contentType: value)
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
                setColor(color: value)
                break;
            case "textAlign":
                setTextAlign(textAlign: value)
                break;
            case "fontSize":
                getInputView().font?.withSize(CGFloat(YogaStyleHelper.rpxTopx(rpx: Float(value) ?? 0)))
                break;
            case "placeholderColor":
                getInputView().attributedPlaceholder = NSAttributedString(string: getUserStyle(key: key) ?? "", attributes: [NSAttributedString.Key.foregroundColor: UIColor(value)])
                break;
            case "verticalAlign":
                 // todo: //
                break;
            default:
                break;
        }
    }
}
