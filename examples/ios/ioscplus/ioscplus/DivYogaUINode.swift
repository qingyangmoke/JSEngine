import Foundation
import UIKit
import YogaKit
public class DivYogaUINode : ContainerYogaUINode {
    public init(uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: "div", uniqueId: uniqueId, scope: scope)
        
        let contentView = YogaUIView()
        setNativeView(view: contentView)
    }
}
