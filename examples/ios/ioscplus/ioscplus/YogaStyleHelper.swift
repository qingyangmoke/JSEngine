//
//  YogaStyleHelper.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation
import UIKit
import YogaKit

public class YogaStyleHelper {
    
    public static var rpxRatio: Float = 1;
    
    public static func resize() {
        rpxRatio = Float(UIScreen.main.bounds.size.width / 750);
    }
    
    public static func rpxTopx(rpx: Float) -> Float {
        return rpxRatio * rpx;
    }
    
    public static func getDisplayUnit(cssUnit: String) -> YGValue {
        if(cssUnit == "auto" || cssUnit == "") {
            return YGValue(value: 0, unit: YGUnit.auto);
        }
        
        if(cssUnit.contains("%")) {
           let percent = Float(cssUnit.replacingOccurrences(of: "%", with: "")) ?? 0;
           return YGValue(value: percent, unit: YGUnit.percent);
        }
        
        if(cssUnit.contains("rpx")) {
            let rpx = Float(cssUnit.replacingOccurrences(of: "rpx", with: "")) ?? 0;
            return YGValue(value: rpxTopx(rpx: rpx), unit: YGUnit.point);
        }

        if(cssUnit.contains("px")) {
            let rpx = Float(cssUnit.replacingOccurrences(of: "px", with: "")) ?? 0;
            return YGValue(value: rpx, unit: YGUnit.point);
        }

        let rpx = Float(cssUnit) ?? 0;
        return YGValue(value: rpxTopx(rpx: rpx), unit: YGUnit.point);
    }
    
    public static func parseYogaFlexWrap(value: String) -> YGWrap {
        var wrap = YGWrap.noWrap;
        switch value {
            case "wrap":
                wrap = YGWrap.wrap;
                break;
            case "nowrap":
                wrap = YGWrap.noWrap;
                break
            case "wrap-reverse":
                wrap =  YGWrap.wrapReverse
                break;
            default:
                break
        }
        return wrap;
    }
    
    public static func parseYogaFlexDirection(value: String) -> YGFlexDirection {
        var direction = YGFlexDirection.column;
        switch value {
            case "column":
                direction = YGFlexDirection.column;
                break;
            case "row":
                direction = YGFlexDirection.row;
                break
            case "column-reverse":
                direction =  YGFlexDirection.columnReverse
                break;
            case "row-reverse":
                direction = YGFlexDirection.rowReverse;
                break;
            default:
                break
        }
        return direction;
    }
    
    public static func parseYogaJustify(value: String) -> YGJustify {
        var justify = YGJustify.flexStart;
        switch value {
            case "flex-start":
                justify = YGJustify.flexStart;
                break;
            case "center":
                justify = YGJustify.center;
                break
            case "flex-end":
                justify = YGJustify.flexEnd;
                break;
            case "space-between":
                justify = YGJustify.spaceBetween;
                break;
            case "space-around":
                justify = YGJustify.spaceAround;
                break;
            case "space-evenly":
                justify = YGJustify.spaceEvenly;
                break;
            default:
                break
        }
        return justify;
    }
    
    public static func parseYogaAlign(value: String) -> YGAlign {
        var align = YGAlign.flexStart;
        switch value {
            case "flex-start":
                align = YGAlign.flexStart;
                break;
            case "center":
                align = YGAlign.center;
                break
            case "flex-end":
                align = YGAlign.flexEnd
                break;
            case "space-between":
                align = YGAlign.spaceBetween;
                break;
            case "space-around":
                align = YGAlign.spaceAround
                break;
            case "stretch":
                align = YGAlign.stretch
                break;
            case "baseline":
                align = YGAlign.baseline
                break;
            case "auto":
                align = YGAlign.auto
                break;
            default:
                break
        }
        return align;
    }
    
    
    public static func resetStyle(node: YogaUINode, userStyle: [String: String]) {
        
    }
    
    public static func parseYogaOverflow(cssValue: String) -> YGOverflow {
        var overflow = YGOverflow.visible;
        switch cssValue {
            case "hidden":
                overflow = YGOverflow.hidden
                break
            case "scroll":
                overflow = YGOverflow.scroll
                break;
            default:
                break
        }
        return overflow
    }
    
    public static func setStyle(node: YogaUINode, key: String, value: String) {
        let yoga = node.getYogaLayout();
       switch (key) {
           case "width":
                yoga.width = getDisplayUnit(cssUnit: value)
                break;
           case "height":
                yoga.height = getDisplayUnit(cssUnit: value)
                break;
           case "minWidth":
                yoga.minWidth = getDisplayUnit(cssUnit: value)
               break;
           case "maxWidth":
                yoga.maxWidth = getDisplayUnit(cssUnit: value)
               break;
           case "minHeight":
                yoga.minHeight = getDisplayUnit(cssUnit: value)
               break;
           case "maxHeight":
                yoga.maxHeight = getDisplayUnit(cssUnit: value)
                break;
           case "flex":
                yoga.flex = CGFloat(Float(value) ?? 0);
               break;
           case "display":
                yoga.display = value == "none" ? YGDisplay.none : YGDisplay.flex;
               break;
           case "justifyContent":
                yoga.justifyContent = parseYogaJustify(value: value)
                break;
            case "alignItems":
                yoga.alignItems = parseYogaAlign(value: value)
                break;
           case "alignContent":
                yoga.alignContent = parseYogaAlign(value: value)
                break;
           case "alignSelf":
                yoga.alignSelf = parseYogaAlign(value: value)
               break;
           case "flexBasis":
                yoga.flexBasis = getDisplayUnit(cssUnit: value)
                break;
            case "flexGrow":
                yoga.flexGrow = CGFloat(Float(value) ?? 0);
                break;
           case "flexDirection":
                yoga.flexDirection = parseYogaFlexDirection(value: value)
                break;
           case "flexWrap":
                yoga.flexWrap = parseYogaFlexWrap(value: value)
               break;
           case "flexShrink":
                yoga.flexShrink = CGFloat(Float(value) ?? 0)
                break;
           case "flexFlow":
                let flow = value.split(separator: " ");
                if(flow.count > 0) {
                    yoga.flexDirection = parseYogaFlexDirection(value: String(flow[0]))
                }
                if(flow.count > 1) {
                    yoga.flexWrap = parseYogaFlexWrap(value: String(flow[1]))
               }
               break;
           case "position":
                yoga.position = value == "absolute" ? YGPositionType.absolute : YGPositionType.relative;
               break;
           case "marginLeft":
                yoga.marginLeft = getDisplayUnit(cssUnit: value)
                break;
           case "marginRight":
                yoga.marginRight = getDisplayUnit(cssUnit: value)
                break;
           case "marginTop":
                yoga.marginTop = getDisplayUnit(cssUnit: value)
                break;
           case "marginBottom":
                yoga.marginBottom = getDisplayUnit(cssUnit: value)
                break;
           case "margin":
                let marginAll = value.split(separator: " ");
                if(marginAll.count == 4) {
                    yoga.marginTop = getDisplayUnit(cssUnit: String(marginAll[0]))
                    yoga.marginRight = getDisplayUnit(cssUnit: String(marginAll[1]))
                    yoga.marginBottom = getDisplayUnit(cssUnit: String(marginAll[2]))
                    yoga.marginLeft = getDisplayUnit(cssUnit: String(marginAll[3]))
                } else if(marginAll.count == 3) {
                    yoga.marginTop = getDisplayUnit(cssUnit: String(marginAll[0]))
                    yoga.marginRight = getDisplayUnit(cssUnit: String(marginAll[1]))
                    yoga.marginBottom = getDisplayUnit(cssUnit: String(marginAll[2]))
                    yoga.marginLeft = getDisplayUnit(cssUnit: String(marginAll[2]))
                } else if(marginAll.count == 2) {
                    yoga.marginTop = getDisplayUnit(cssUnit: String(marginAll[0]))
                    yoga.marginRight = getDisplayUnit(cssUnit: String(marginAll[1]))
                    yoga.marginBottom = getDisplayUnit(cssUnit: String(marginAll[0]))
                    yoga.marginLeft = getDisplayUnit(cssUnit: String(marginAll[1]))
                } else if(marginAll.count == 1) {
                    yoga.margin = getDisplayUnit(cssUnit: value)
                }
                break;
           case "paddingLeft":
                yoga.paddingLeft = getDisplayUnit(cssUnit: value)
                break;
           case "paddingRight":
                yoga.paddingRight = getDisplayUnit(cssUnit: value)
                break;
           case "paddingTop":
                yoga.paddingTop = getDisplayUnit(cssUnit: value)
                break;
           case "paddingBottom":
                yoga.paddingBottom = getDisplayUnit(cssUnit: value)
                break;
           case "padding":
                let paddingAll = value.split(separator: " ");
                if(paddingAll.count == 4) {
                    yoga.paddingTop = getDisplayUnit(cssUnit: String(paddingAll[0]))
                    yoga.paddingRight = getDisplayUnit(cssUnit: String(paddingAll[1]))
                    yoga.paddingBottom = getDisplayUnit(cssUnit: String(paddingAll[2]))
                    yoga.paddingLeft = getDisplayUnit(cssUnit: String(paddingAll[3]))
                } else if(paddingAll.count == 3) {
                    yoga.paddingTop = getDisplayUnit(cssUnit: String(paddingAll[0]))
                    yoga.paddingRight = getDisplayUnit(cssUnit: String(paddingAll[1]))
                    yoga.paddingBottom = getDisplayUnit(cssUnit: String(paddingAll[2]))
                    yoga.paddingLeft = getDisplayUnit(cssUnit: String(paddingAll[2]))
                } else if(paddingAll.count == 2) {
                    yoga.paddingTop = getDisplayUnit(cssUnit: String(paddingAll[0]))
                    yoga.paddingRight = getDisplayUnit(cssUnit: String(paddingAll[1]))
                    yoga.paddingBottom = getDisplayUnit(cssUnit: String(paddingAll[0]))
                    yoga.paddingLeft = getDisplayUnit(cssUnit: String(paddingAll[1]))
                } else if(paddingAll.count == 1) {
                    yoga.padding = getDisplayUnit(cssUnit: value)
                }
                break;
           case "aspectRatio":
                yoga.aspectRatio = CGFloat(Float(value) ?? 0)
                break;
           case "overflow":
                node.getNativeView().clipsToBounds = value == "hidden" ? true : false
                yoga.overflow = parseYogaOverflow(cssValue: value)
                break;
           case "opacity":
                node.getNativeView().alpha = CGFloat(Float(value) ?? 1)
                break;
           case "visibility":
                node.getNativeView().alpha = value == "hidden" ? 0 : 1
                break;
           case "backgroundColor":
                node.getNativeView().backgroundColor = UIColor(value);
                break;
           default:
                break
        }
    }
}
