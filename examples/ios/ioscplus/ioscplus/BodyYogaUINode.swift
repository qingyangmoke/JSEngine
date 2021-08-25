//
//  BodyYogaUINode.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation
import UIKit
import YogaKit
public class BodyYogaUINode : ContainerYogaUINode {
    public init(uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: "body", uniqueId: uniqueId, scope: scope)
        
        let contentView = YogaUIView()
        contentView.backgroundColor = .white
        contentView.configureLayout { (layout) in
          layout.isEnabled = true
          layout.flexDirection = .column
          layout.width = YGValue(UIScreen.main.bounds.size.width)
          layout.height = YGValue(UIScreen.main.bounds.size.height)
          layout.marginTop = 0
          layout.marginBottom = 0
          layout.marginRight = 0
          layout.marginLeft = 0
        }

        setNativeView(view: contentView)
        
        getScope().getViewController().view.addSubview(contentView)
    }
}
