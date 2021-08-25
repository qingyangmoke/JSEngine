//
//  ImageYogaUINode.swift
//  ioscplus
//
//  Created by song on 2021/8/25.
//
import Foundation
import UIKit
import YogaKit
public class ImageYogaUINode: YogaUINode {
    public init(uniqueId: Int32, scope: JSEngineScope) {
        super.init(tagName: "img", uniqueId: uniqueId, scope: scope)
        let imageView = UIImageView()
        setNativeView(view: imageView)
        imageView.yoga.aspectRatio = 1;
    }

    public func getImageView() -> UIImageView {
        return getNativeView() as! UIImageView
    }

    public func setImageSource(url: String) {
        ImageHelper.loadImageUsingCache(withUrl: url, completion: { (image: UIImage?) in
            if image != nil {
                DispatchQueue.main.async {
                    self.getImageView().image = image
                }
            }
        })
    }

    public override func setAttribute(key: String, value: String) {
        switch (key) {
            case "src":
                setImageSource(url: value)
                break;
            default:
                super.setAttribute(key: key, value: value)
                break;
        }
    }

    public override func setStyle(key: String, value: String) {
        super.setStyle(key: key, value: value)
        switch (key) {
            case "verticalAlign":
                 // todo: //
                break;
            default:
                break;
        }
    }
}
