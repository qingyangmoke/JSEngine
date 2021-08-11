package com.jnibridge.modules.dom.yoga;

import android.view.View;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.yoga.YogaUINode;

public class CanvasContextYogaUINode extends YogaUINode {
    private View _view;
    public CanvasContextYogaUINode(String tagName, int uniqueId, EngineScope scope, View view) {
        super(tagName, uniqueId, scope);
        _view = view;
        _view.setTag(this);
    }

    @Override
    public View getNativeView() {
        return _view;
    }
}
