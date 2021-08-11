package com.jnibridge.modules.dom.yoga;

import android.graphics.Color;
import android.graphics.Point;
import android.view.View;

import com.facebook.yoga.YogaAlign;
import com.facebook.yoga.YogaDisplay;
import com.facebook.yoga.YogaEdge;
import com.facebook.yoga.YogaFlexDirection;
import com.facebook.yoga.YogaJustify;
import com.facebook.yoga.YogaNode;
import com.facebook.yoga.YogaPositionType;
import com.facebook.yoga.YogaWrap;
import com.jnibridge.modules.dom.DisplayUnit;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class YogaStyleHelper {
    public static ArrayList<String> yogaJustifyMap = new ArrayList<String>(Arrays.asList("flex-start", "center", "flex-end","space-between","space-around", "space-evenly"));
    public static ArrayList<String> yogaAlignMap = new ArrayList<String>(Arrays.asList("auto", "flex-start", "center", "flex-end","stretch","baseline","space-between","space-around"));
    public static ArrayList<String> yogaPositionTypeMap = new ArrayList<String>(Arrays.asList("static", "relative", "absolute"));

    // rpx转px的转换率 windowWidth / 750
    public static float rpxRatio = 1;

    public static YogaJustify parseYogaJustify(String cssValue) {
        int result = yogaJustifyMap.indexOf(cssValue);
        if(result == -1) {
            result = 0;
        }
        return YogaJustify.fromInt(result);
    }

    public static String parseYogaJustify(YogaJustify yogaJustify) {
        return yogaJustifyMap.get(yogaJustify.intValue());
    }

    public static YogaAlign parseYogaAlign(String cssValue) {
        int result = yogaAlignMap.indexOf(cssValue);
        if(result == -1) {
            result = 0;
        }
        return YogaAlign.fromInt(result);
    }

    public static String parseYogaAlign(YogaAlign yogaAlign) {
        return yogaAlignMap.get(yogaAlign.intValue());
    }

    public static String parseYogaPositionType(YogaPositionType yogaPositionType) {
        return yogaPositionTypeMap.get(yogaPositionType.intValue());
    }

    public static YogaPositionType parseYogaPositionType(String cssValue) {
        int result = yogaPositionTypeMap.indexOf(cssValue);
        if(result == -1) {
            result = 0;
        }
        return YogaPositionType.fromInt(result);
    }

    public static DisplayUnit parseDisplayUnit(YogaNode yogaNode, String cssUnit) {
        DisplayUnit unit = new DisplayUnit();
        int index = cssUnit.indexOf("%");
        if(index != -1) {
            float value = Float.parseFloat(cssUnit.substring(0, index));
            unit.setPercent(value);
        }
        index = cssUnit.indexOf("rpx");
        if(index != -1) {
            float value = Float.parseFloat(cssUnit.substring(0, index));
            unit.setRPX(value);
        }
//        index = cssUnit.indexOf("rem");
//        if(index != -1) {
//            float value = Float.parseFloat(cssUnit.substring(0, index));
//            unit.setRPX(value);
//        }
        index = cssUnit.indexOf("px");
        if(index != -1) {
            float value = Float.parseFloat(cssUnit.substring(0, index));
            unit.setPX(value);
        }
        return unit;
    }

    public static boolean isPureNumber(String value) {
        Pattern p = Pattern.compile("[0-9]*");
        Matcher m = p.matcher(value);
        return m.matches();
    }


    public static float toDisplayUnit(double nativeUnit) {
        return toDisplayUnit((float)nativeUnit);
    }

    public static float toDisplayUnit(float nativeUnit) {
        return nativeUnit / rpxRatio;
    }

    public static float getDisplayUnit(double cssUnit) {
        return getDisplayUnit((float)cssUnit);
    }

    public static float getDisplayUnit(int cssUnit) {
        return getDisplayUnit((float)cssUnit);
    }

    public static float getDisplayUnit(float cssUnit) {
        return rpxRatio * cssUnit;
    }

    /**
     * 度数转成弧度
     * @param degrees - 度数
     * @return 弧度
     */
    public static double toRadian(double degrees) {
        return degrees * Math.PI / 180;
    }

    /**
     * 弧度转度数
     * @param radian - 弧度
     * @return 弧度
     */
    public static double toDegrees(double radian) {
        return radian * 180 / Math.PI;
    }

    public static float getDisplayUnit(String cssUnit) {
        if(isPureNumber(cssUnit)) {
            return getDisplayUnit(Float.parseFloat(cssUnit));
        }

        int index = cssUnit.indexOf("rpx");
        if(index != -1) {
            float rpx = Float.parseFloat(cssUnit.substring(0, index));
            return getDisplayUnit(rpx);
        }

        index = cssUnit.indexOf("px");
        if(index != -1) {
            return Float.parseFloat(cssUnit.substring(0, index));
        }

        return Float.parseFloat(cssUnit);
    }


    public static float getPercentUnit(String cssUnit) {
        int percentIndex = cssUnit.indexOf("%");
        if(percentIndex != -1) {
            return Float.parseFloat(cssUnit.substring(0,percentIndex));
        }
        return -1;
    }

    public static void setMargin(YogaNode yogaNode, YogaEdge yogaEdge, String value) {
        if(value == "auto" || value == "") {
            yogaNode.setMarginAuto(yogaEdge);
            return;
        }
        float percentUnit = getPercentUnit(value);
        if(percentUnit != -1) {
            yogaNode.setMarginPercent(yogaEdge, percentUnit);
        } else {
            yogaNode.setMargin(yogaEdge, getDisplayUnit(value));
        }
    }

    public static void setPadding(YogaNode yogaNode, YogaEdge yogaEdge, String value) {
        if(value == "auto" ||  value == "") {
            yogaNode.setPadding(yogaEdge, 0);
            return;
        }
        float percentUnit = getPercentUnit(value);
        if(percentUnit != -1) {
            yogaNode.setPaddingPercent(yogaEdge, percentUnit);
        } else {
            yogaNode.setPadding(yogaEdge, getDisplayUnit(value));
        }
    }

    public static void setFlexShrink(YogaNode yogaNode, String cssValue) {
        if(cssValue == "initial") {
            yogaNode.setFlexShrink(0);
        } else {
            yogaNode.setFlexShrink(getDisplayUnit(cssValue));
        }
    }

    public static void setFlexWrap(YogaNode yogaNode, String cssValue) {
        if(cssValue == "wrap") {
            yogaNode.setWrap(YogaWrap.WRAP);
        } else if(cssValue == "nowrap") {
            yogaNode.setWrap(YogaWrap.NO_WRAP);
        } else if(cssValue == "initial") {
            yogaNode.setWrap(YogaWrap.NO_WRAP);
        }
    }

    public static void setFlexDirection(YogaNode yogaNode, String cssValue) {
        if(cssValue == "row") {
            yogaNode.setFlexDirection(YogaFlexDirection.ROW);
        } else if(cssValue == "column") {
            yogaNode.setFlexDirection(YogaFlexDirection.COLUMN);
        }
    }

    public static void setWidth(YogaNode yogaNode, String cssValue) {
        if(cssValue == "auto" || cssValue == "") {
            yogaNode.setWidthAuto();
        } else {
            float percentUnit = getPercentUnit(cssValue);
            if(percentUnit != -1) {
                yogaNode.setWidthPercent(percentUnit);
            } else {
                yogaNode.setWidth(getDisplayUnit(cssValue));
            }
        }
    }

    public static void setHeight(YogaNode yogaNode, String cssValue) {
        if(cssValue == "auto" || cssValue == "") {
            yogaNode.setHeightAuto();
        } else {
            float percentUnit = getPercentUnit(cssValue);
            if(percentUnit != -1) {
                yogaNode.setHeightPercent(percentUnit);
            } else {
                yogaNode.setHeight(getDisplayUnit(cssValue));
            }
        }
    }

    public static void setMinWidth(YogaNode yogaNode, String cssValue) {
        float percentUnit = getPercentUnit(cssValue);
        if(percentUnit != -1) {
            yogaNode.setMinWidthPercent(percentUnit);
        } else {
            yogaNode.setMinWidth(getDisplayUnit(cssValue));
        }
    }

    public static void setMaxWidth(YogaNode yogaNode, String cssValue) {
        float percentUnit = getPercentUnit(cssValue);
        if(percentUnit != -1) {
            yogaNode.setMaxWidthPercent(percentUnit);
        } else {
            yogaNode.setMaxWidth(getDisplayUnit(cssValue));
        }
    }
    public static void resetStyle(YogaNode yogaNode) {
        yogaNode.reset();
        View view = (View)yogaNode.getData();
        if(view != null) {
            view.setBackgroundColor(Color.TRANSPARENT);
        }
    }

    public static void setStyle(YogaNode yogaNode, String key, String value) {
        float percentUnit;
        switch (key) {
            case "width":
                setWidth(yogaNode, value);
                break;
            case "height":
                setHeight(yogaNode, value);
                break;
            case "min-width":
                setMinWidth(yogaNode, value);
                break;
            case "max-width":
                setMaxWidth(yogaNode, value);
                break;
            case "min-height":
                percentUnit = getPercentUnit(value);
                if(percentUnit != -1) {
                    yogaNode.setMinHeightPercent(percentUnit);
                } else {
                    yogaNode.setMinHeight(getDisplayUnit(value));
                }
                break;
            case "max-height":
                percentUnit = getPercentUnit(value);
                if(percentUnit != -1) {
                    yogaNode.setMaxHeightPercent(percentUnit);
                } else {
                    yogaNode.setMaxHeight(getDisplayUnit(value));
                }
                break;
            case "flex":
                yogaNode.setFlex(Float.parseFloat(value));
                break;
            case "display":
                yogaNode.setDisplay(value == "none" ? YogaDisplay.NONE : YogaDisplay.FLEX);
                break;
            case "justify-content":
                yogaNode.setJustifyContent(YogaStyleHelper.parseYogaJustify(value));
                break;
            case "align-items":
                yogaNode.setAlignItems(YogaStyleHelper.parseYogaAlign(value));
                break;
            case "align-self":
                yogaNode.setAlignSelf(YogaStyleHelper.parseYogaAlign(value));
                break;
            case "flex-basis":
                if(value == "auto") {
                    yogaNode.setFlexBasisAuto();
                } else if(value == "initial") {
                    yogaNode.setFlexBasisAuto();
                } else if(value == "inherit") {
                    // TODO: //
                } else {
                    yogaNode.setFlexBasis(getDisplayUnit(value));
                }
                break;
            case "flex-grow":
                if(value == "auto" || value == "initial") {
                    yogaNode.setFlexGrow(0);
                } else if(value == "inherit") {
                    // TODO:
                } else {
                    yogaNode.setFlexGrow(getDisplayUnit(value));
                }
                break;
            case "flex-direction":
                setFlexDirection(yogaNode, value);
                break;
            case "flex-wrap":
                setFlexWrap(yogaNode, value);
                break;
            case "flex-shrink":
                setFlexShrink(yogaNode, value);
                break;
            case "flex-flow":
                String [] flow = value.split(" ");
                if(flow.length > 0) {
                    setFlexDirection(yogaNode, flow[0]);
                }
                if(flow.length > 1) {
                    setFlexWrap(yogaNode, flow[1]);
                }
                break;
            case "position":
                yogaNode.setPositionType(YogaStyleHelper.parseYogaPositionType(value));
                break;
            case "margin-left":
                setMargin(yogaNode, YogaEdge.LEFT, value);
                break;
            case "margin-right":
                setMargin(yogaNode, YogaEdge.RIGHT, value);
                break;
            case "margin-top":
                setMargin(yogaNode, YogaEdge.TOP, value);
                break;
            case "margin-bottom":
                setMargin(yogaNode, YogaEdge.BOTTOM, value);
                break;
            case "margin":
                String [] marginAll = value.split(" ");
                // 参考Chrome的规则
                if(marginAll.length == 4) {
                    setMargin(yogaNode,YogaEdge.TOP, marginAll[1]);
                    setMargin(yogaNode,YogaEdge.RIGHT, marginAll[2]);
                    setMargin(yogaNode,YogaEdge.BOTTOM, marginAll[3]);
                    setMargin(yogaNode,YogaEdge.LEFT, marginAll[4]);
                } else if(marginAll.length == 3) {
                    setMargin(yogaNode,YogaEdge.TOP, marginAll[0]);
                    setMargin(yogaNode,YogaEdge.RIGHT, marginAll[1]);
                    setMargin(yogaNode,YogaEdge.BOTTOM, marginAll[2]);
                    setMargin(yogaNode,YogaEdge.LEFT, marginAll[2]);
                } else if(marginAll.length == 2) {
                    setMargin(yogaNode,YogaEdge.TOP, marginAll[0]);
                    setMargin(yogaNode,YogaEdge.RIGHT, marginAll[1]);
                    setMargin(yogaNode,YogaEdge.BOTTOM, marginAll[1]);
                    setMargin(yogaNode,YogaEdge.LEFT, marginAll[0]);
                } else if(marginAll.length == 1) {
                    setMargin(yogaNode,YogaEdge.TOP, marginAll[0]);
                    setMargin(yogaNode,YogaEdge.RIGHT, marginAll[0]);
                    setMargin(yogaNode,YogaEdge.BOTTOM, marginAll[0]);
                    setMargin(yogaNode,YogaEdge.LEFT, marginAll[0]);
                }
                break;
            case "padding-left":
                setPadding(yogaNode, YogaEdge.LEFT, value);
                break;
            case "padding-right":
                setPadding(yogaNode,YogaEdge.RIGHT, value);
                break;
            case "padding-top":
                setPadding(yogaNode,YogaEdge.TOP, value);
                break;
            case "padding-bottom":
                setPadding(yogaNode,YogaEdge.BOTTOM, value);
                break;
            case "padding":
                String [] paddingAll = value.split(" ");
                // 参考Chrome的规则
                if(paddingAll.length == 4) {
                    setPadding(yogaNode, YogaEdge.TOP, paddingAll[1]);
                    setPadding(yogaNode, YogaEdge.RIGHT, paddingAll[2]);
                    setPadding(yogaNode, YogaEdge.BOTTOM, paddingAll[3]);
                    setPadding(yogaNode, YogaEdge.LEFT, paddingAll[4]);
                } else if(paddingAll.length == 3) {
                    setPadding(yogaNode, YogaEdge.TOP, paddingAll[0]);
                    setPadding(yogaNode, YogaEdge.RIGHT, paddingAll[1]);
                    setPadding(yogaNode, YogaEdge.BOTTOM, paddingAll[2]);
                    setPadding(yogaNode, YogaEdge.LEFT, paddingAll[2]);
                } else if(paddingAll.length == 2) {
                    setPadding(yogaNode, YogaEdge.TOP, paddingAll[0]);
                    setPadding(yogaNode, YogaEdge.RIGHT, paddingAll[1]);
                    setPadding(yogaNode, YogaEdge.BOTTOM, paddingAll[1]);
                    setPadding(yogaNode, YogaEdge.LEFT, paddingAll[0]);
                } else if(paddingAll.length == 1) {
                    setPadding(yogaNode, YogaEdge.TOP, paddingAll[0]);
                    setPadding(yogaNode, YogaEdge.RIGHT, paddingAll[0]);
                    setPadding(yogaNode, YogaEdge.BOTTOM, paddingAll[0]);
                    setPadding(yogaNode, YogaEdge.LEFT, paddingAll[0]);
                }
                break;
            case "background-color":
            case "backgroundColor":
                View view = (View)yogaNode.getData();
                if(view != null) {
                    view.setBackgroundColor(Color.parseColor(value));
                }
                break;
        }
    }
}
