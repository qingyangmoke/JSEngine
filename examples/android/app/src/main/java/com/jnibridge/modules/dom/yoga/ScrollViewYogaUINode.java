package com.jnibridge.modules.dom.yoga;

import android.graphics.Color;
import android.util.Log;
import android.view.View;
import android.widget.ScrollView;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;

public class ScrollViewYogaUINode extends ContainerYogaUINode {
    public ScrollViewYogaUINode(int uniqueId, EngineScope scope) {
        super("scroller", uniqueId, scope, false);
        YogaScrollView view = new YogaScrollView(getScope().getActivity(), getYogaNode());
        setNativeView(view);
    }

    public YogaScrollView getScrollView() {
        return (YogaScrollView)getNativeView();
    }

    public void scrollTo(int x, int y) {
        Log.d("JSEngine", "ScrollViewYogaUINode scrollTo y=" + String.valueOf(y));
        getScrollView().scrollTo(x, y);
    }
}
