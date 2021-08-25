//
//  JSEngineScope.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation

public class YogaUIRender : UIRender {
    public override init(scope: JSEngineScope) {
        super.init(scope: scope)
        resize();
    }

    public func resize() {
        YogaStyleHelper.resize()
    }
    
    public override func createElement(uniqueId: Int32, tagName: String) {
        switch (tagName) {
            case "body":
                NSLog("JSEngine createElement: body begin=" + String(uniqueId));
                let body = BodyYogaUINode(uniqueId: uniqueId, scope: getScope())
                addElement(element: body)
                setRootElement(node: body)
                break;
//            case "canvas":
//                Log.d("JSEngine", "createElement: canvas begin=" + String.valueOf(uniqueId));
//                CanvasYogaUINode canvas = new CanvasYogaUINode(uniqueId, getScope());
//                addElement(canvas);
//                Log.d("JSEngine", "createElement: canvas end=" + String.valueOf(uniqueId));
//                break;
            case "text":
                let textYogaUINode = LabelYogaUINode(uniqueId: uniqueId, scope: getScope())
                addElement(element: textYogaUINode)
                break;
            case "label":
                let textYogaUINode = LabelYogaUINode(uniqueId: uniqueId, scope: getScope())
                addElement(element: textYogaUINode)
                break;
            case "div":
                let divYogaUINode = DivYogaUINode(uniqueId: uniqueId, scope: getScope())
                addElement(element: divYogaUINode)
                break;
            case "img":
                let imgYogaUINode = ImageYogaUINode(uniqueId: uniqueId, scope: getScope())
                addElement(element: imgYogaUINode)
                break;
//            case "input":
//                InputYogaUINode inputYogaUINode = new InputYogaUINode(uniqueId, getScope());
//                addElement(inputYogaUINode);
//                break;
//            case "scroller":
//                ScrollViewYogaUINode scrollViewYogaUINode = new ScrollViewYogaUINode(uniqueId, getScope());
//                addElement(scrollViewYogaUINode);
//                break;
            default:
                break;
        }
    }

    public override func insertChild(uniqueId: Int32, newChildId: Int32, refChildId: Int32) {
        if let elem = getElement(uniqueId: uniqueId) {
            if let newChild = getElement(uniqueId: newChildId) {
                elem.insertBefore(newChild: newChild, refChild: getElement(uniqueId: refChildId))
            }
        }
    }

    public override func appendChild(uniqueId: Int32, newChildId: Int32) {
        if let elem = getElement(uniqueId: uniqueId) {
            if let newChild = getElement(uniqueId: newChildId) {
                elem.appendChild(newChild: newChild)
            }
        }
    }

    public override func removeChild(uniqueId: Int32, newChildId: Int32) {
        if let elem = getElement(uniqueId: uniqueId) {
            if let newChild = getElement(uniqueId: newChildId) {
                elem.removeChild(child: newChild)
            }
        }
    }

    public override func replaceChild(uniqueId: Int32, newChildId: Int32, oldChildId: Int32) {
        if let elem = getElement(uniqueId: uniqueId) {
            if let newChild = getElement(uniqueId: newChildId) {
                elem.replaceChild(newChild: newChild, oldChild: getElement(uniqueId: oldChildId))
            }
        }
    }

    public override func setAttribute(uniqueId: Int32, key: String, value: String) {
        if let ele = getElement(uniqueId: uniqueId) {
           return ele.setAttribute(key: key, value: value)
        }
    }

    public override func getAttribute(uniqueId: Int32, key: String) -> String {
        if let ele = getElement(uniqueId: uniqueId) {
           return ele.getAttribute(key: key)
        }
        return ""
    }

    public override func removeAttribute(uniqueId: Int32, key: String) {
        if let ele = getElement(uniqueId: uniqueId) {
            ele.removeAttribute(key: key)
        }
    }

    public override func setStyle(uniqueId: Int32, key: String, value: String) {
        if let elem = getElement(uniqueId: uniqueId) {
            elem.setStyle(key: key, value: value)
        }
    }

    public override func resetStyle(uniqueId: Int32) {
        if let ele = getElement(uniqueId: uniqueId) {
            ele.resetStyle()
        }
    }

    public override func scrollTo(uniqueId: Int32, x: Float, y: Float) {
//        if let elem = getElement(uniqueId: uniqueId) {
//            elem.scroll
//        }
    }
}
