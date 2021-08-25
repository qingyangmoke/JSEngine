//
//  JSTimerModule.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation



public struct CElementArgs: Decodable {
    let uniqueId: Int32;
    let tagName: String?;
}

public class UIModule : NativeModule {
    public init(scope: JSEngineScope) {
        super.init(moduleName: "UI", scope: scope)
    }

    public override func invokeMethod(callId: Int32, methodName: String, args: String) -> String {
        var result = ""
        switch methodName {
            case "createElement":
                createElement(args: args)
                break;
            case "setStyle":
                setStyle(args: args)
                break;
            case "setAttribute":
                setAttribute(args: args)
                break;
            case "removeAttribute":
                removeAttribute(args: args)
                break;
            case "getAttribute":
                result = getAttribute(args: args)
                break;
            case "insertChild":
                insertChild(args: args)
                break;
            case "replaceChild":
                replaceChild(args: args)
                break;
            default:
                break;
        }
        return result;
    }
    
    
    private func createElement(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let createElementArgs = try? JSONDecoder().decode(CElementArgs.self, from: data) {
                getScope().getUIRender().createElement(uniqueId: createElementArgs.uniqueId, tagName: createElementArgs.tagName!)
            }
        }
    }
    
    private func setStyle(args: String) {
        if(!getScope().getUIRender().isReady()) {
            return;
        }
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let setStyleArgs = try? JSONDecoder().decode(SetStyleArgs.self, from: data) {
                if(setStyleArgs.replace == 1) {
                    getScope().getUIRender().resetStyle(uniqueId: setStyleArgs.uniqueId)
                }
                setStyleArgs.style.forEach { (key: String, value: String) in
                    getScope().getUIRender().setStyle(uniqueId: setStyleArgs.uniqueId, key: key, value: value)
                }
            }
        }
    }

    public func setAttribute(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let setAttributeArgs = try? JSONDecoder().decode(SetAttributeArgs.self, from: data) {
                setAttributeArgs.attribute.forEach { (key: String, value: String) in
                    getScope().getUIRender().setAttribute(uniqueId: setAttributeArgs.uniqueId, key: key, value: value)
                }
            }
        }
    }

    public func removeAttribute(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let removeAttributeArgs = try? JSONDecoder().decode(RemoveAttributeArgs.self, from: data) {
                getScope().getUIRender().removeAttribute(uniqueId: removeAttributeArgs.uniqueId, key: removeAttributeArgs.key)
            }
        }
    }

    public func getAttribute(args: String) -> String {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let getAttributeArgs = try? JSONDecoder().decode(GetAttributeArgs.self, from: data) {
                return getScope().getUIRender().getAttribute(uniqueId: getAttributeArgs.uniqueId, key: getAttributeArgs.key)
            }
        }
        return ""
    }

    public func insertChild(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let insertChildArgs = try? JSONDecoder().decode(InsertChildArgs.self, from: data) {
                getScope().getUIRender().insertChild(uniqueId: insertChildArgs.uniqueId, newChildId: insertChildArgs.newChild.uniqueId, refChildId: insertChildArgs.refChild.uniqueId)
            }
        }
    }

    public func replaceChild(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let replaceChildArgs = try? JSONDecoder().decode(ReplaceChildArgs.self, from: data) {
                getScope().getUIRender().replaceChild(uniqueId: replaceChildArgs.uniqueId, newChildId: replaceChildArgs.newChild.uniqueId, oldChildId: replaceChildArgs.oldChild.uniqueId)
            }
        }
    }

    public func scrollTo(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let scrollToArgs = try? JSONDecoder().decode(ScrollToArgs.self, from: data) {
                getScope().getUIRender().scrollTo(uniqueId: scrollToArgs.uniqueId, x: scrollToArgs.x, y: scrollToArgs.y)
            }
        }
    }
}
