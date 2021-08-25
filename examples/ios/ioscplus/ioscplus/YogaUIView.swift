//
//  YogaUIView.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation
import UIKit
import YogaKit

public class YogaUIView : UIView {
    public override func addSubview(_ view: UIView) {
        super.addSubview(view);
    }

    public override func didAddSubview(_ subview: UIView) {
        super.didAddSubview(subview)
        yoga.applyLayout(preservingOrigin: true)
    }
    
    public override func willRemoveSubview(_ subview: UIView) {
        super.willRemoveSubview(subview);
    }

    public override func insertSubview(_ view: UIView, at index: Int) {
        super.insertSubview(view, at: index)
    }

    public override func insertSubview(_ view: UIView, belowSubview siblingSubview: UIView) {
        super.insertSubview(view, belowSubview: siblingSubview)
    }

    public override func insertSubview(_ view: UIView, aboveSubview siblingSubview: UIView) {
        super.insertSubview(view, aboveSubview: siblingSubview)
    }
    
    public override func removeFromSuperview() {
        super.removeFromSuperview()
        yoga.applyLayout(preservingOrigin: true)
    }
}
