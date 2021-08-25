//
//  ContainerYogaUINode.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation

public class ContainerYogaUINode: YogaUINode {
    public override init(tagName: String, uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: tagName, uniqueId: uniqueId, scope: scope)
    }
    public override func appendChild(newChild: IUINode) -> IUINode {
        let child: YogaUINode = newChild as! YogaUINode
        self.getNativeView().addSubview(child.getNativeView())
        return newChild
    }
    
    public override func insertBefore(newChild: IUINode, refChild: IUINode?) -> IUINode {
        let newChildYoga: YogaUINode = newChild as! YogaUINode
        if(refChild != nil) {
            let refChildYoga: YogaUINode = refChild as! YogaUINode
            getNativeView().insertSubview(newChildYoga.getNativeView(), belowSubview: refChildYoga.getNativeView())
        } else {
            getNativeView().addSubview(newChildYoga.getNativeView());
        }
        return newChild
    }
    
    public override func removeChild(child: IUINode) -> IUINode {
        let childYoga: YogaUINode = child as! YogaUINode
        childYoga.getNativeView().removeFromSuperview();
        return child
    }
    
    public override func replaceChild(newChild: IUINode, oldChild: IUINode?) -> IUINode {
        let newChildYoga: YogaUINode = newChild as! YogaUINode
        if(oldChild != nil) {
            let oldChildYoga: YogaUINode = oldChild as! YogaUINode
            getNativeView().insertSubview(newChildYoga.getNativeView(), belowSubview: oldChildYoga.getNativeView())
            oldChildYoga.getNativeView().removeFromSuperview()
        } else {
            getNativeView().addSubview(newChildYoga.getNativeView());
        }
        return newChild
    }
}
