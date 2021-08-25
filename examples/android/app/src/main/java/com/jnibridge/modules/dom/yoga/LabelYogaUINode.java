package com.jnibridge.modules.dom.yoga;

import android.graphics.Color;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.TextView;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.yoga.YogaUINode;

public class LabelYogaUINode extends YogaUINode {
    public LabelYogaUINode(int uniqueId, EngineScope scope) {
        super("label", uniqueId, scope);
        View view = new TextView(getScope().getActivity());
        setNativeView(view);
    }

    public TextView getTextView() {
        return (TextView)getNativeView();
    }

    public void setText(String text) {
        getTextView().setText(text);
    }

    @Override
    public void setAttribute(String key, String value) {
        switch (key) {
            case "text":
                setText(value);
                break;
            default:
                super.setAttribute(key, value);
                break;
        }
    }

    @Override
    public void setStyle(String key, String value) {
        switch (key) {
            case "color":
                getTextView().setTextColor(Color.parseColor(value));
                break;
            case "textAlign":
                switch (value) {
                    case  "left":
                        getTextView().setTextAlignment(View.TEXT_ALIGNMENT_TEXT_START);
                        break;
                    case  "right":
                        getTextView().setTextAlignment(View.TEXT_ALIGNMENT_TEXT_END);
                        break;
                    case  "center":
                        getTextView().setTextAlignment(View.TEXT_ALIGNMENT_CENTER);
                        break;
                }
                break;
            case "verticalAlign":
                switch (value) {
                    case "middle":
                        getTextView().setGravity(Gravity.CENTER_VERTICAL);
                        break;
                    case "top":
                        getTextView().setGravity(Gravity.TOP);
                        break;
                    case "bottom":
                        getTextView().setGravity(Gravity.BOTTOM);
                        break;
                }
                break;
            default:
                super.setStyle(key, value);
                break;
        }
    }
}
