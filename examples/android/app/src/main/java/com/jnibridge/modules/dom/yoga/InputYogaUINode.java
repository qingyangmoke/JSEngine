package com.jnibridge.modules.dom.yoga;

import android.graphics.Color;
import android.text.InputType;
import android.view.KeyEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.jnibridge.EngineScope;

public class InputYogaUINode extends YogaUINode {
    public InputYogaUINode(int uniqueId, EngineScope scope) {
        super("input", uniqueId, scope);
        EditText view = new EditText(getScope().getActivity());
        view.setInputType(InputType.TYPE_CLASS_TEXT);
        view.setBackground(null);
        setNativeView(view);
    }

    public EditText getEditText() {
        return (EditText)getNativeView();
    }

    @Override
    public void setAttribute(String key, String value) {
        switch (key) {
            case "text":
            case "value":
                getEditText().setText(value);
                break;
            case "readonly":
            case "disabled":
                getEditText().setEnabled(value != "1");
                break;
            case "type":
                getEditText().setVisibility(View.VISIBLE);
                switch (value) {
                    case "tel":
                        getEditText().setInputType(InputType.TYPE_CLASS_PHONE);
                        break;
                    case "password":
                        getEditText().setInputType(InputType.TYPE_TEXT_VARIATION_PASSWORD);
                        break;
                    case "text":
                        getEditText().setInputType(InputType.TYPE_CLASS_TEXT);
                        break;
                    case "number":
                        getEditText().setInputType(InputType.TYPE_CLASS_NUMBER);
                        break;
                    case "hidden":
                        getEditText().setVisibility(View.INVISIBLE);
                        break;
                }
                break;
            case "placeholder":
                getEditText().setHint(value);
                break;
            case "color":
                getEditText().setTextColor(Color.parseColor(value));
                break;
            case "font-size":
                getEditText().setTextSize(YogaStyleHelper.getDisplayUnit(value));
                break;
            default:
                super.setAttribute(key, value);
                break;
        }
    }

    @Override
    public void setStyle(String key, String value) {
        switch (key) {
            case "placeholder-color":
                getEditText().setHintTextColor(Color.parseColor(value));
                break;
            default:
                super.setStyle(key, value);
                break;
        }
    }
}
