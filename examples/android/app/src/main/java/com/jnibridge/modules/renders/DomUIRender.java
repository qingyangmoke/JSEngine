package com.jnibridge.modules.renders;

import android.graphics.Point;
import android.util.Log;
import android.widget.ScrollView;

import com.facebook.soloader.SoLoader;
import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.yoga.BodyYogaUINode;
import com.jnibridge.modules.dom.yoga.CanvasYogaUINode;
import com.jnibridge.modules.dom.yoga.DivYogaUINode;
import com.jnibridge.modules.dom.IUINode;
import com.jnibridge.modules.dom.yoga.ImageYogaUINode;
import com.jnibridge.modules.dom.yoga.InputYogaUINode;
import com.jnibridge.modules.dom.yoga.LabelYogaUINode;
import com.jnibridge.modules.dom.yoga.ScrollViewYogaUINode;
import com.jnibridge.modules.dom.yoga.YogaStyleHelper;

public class DomUIRender extends UIRender {
    public DomUIRender(EngineScope scope) {
        super(scope);
        SoLoader.init(getScope().getActivity(), false);
        onWindowReisze();
    }

    public void onWindowReisze() {
        Point windowPoint = new Point();
        getScope().getActivity().getDisplay().getSize(windowPoint);
        float screenWidth = windowPoint.x;
        YogaStyleHelper.rpxRatio = screenWidth / 750;
    }

    @Override
    public void createElement(int uniqueId, String tagName) {
        switch (tagName) {
            case "body":
                Log.d("JSEngine", "createElement: body begin=" + String.valueOf(uniqueId));
                _rootElement = new BodyYogaUINode(uniqueId, getScope());
                addElement(_rootElement);
                break;
            case "canvas":
                Log.d("JSEngine", "createElement: canvas begin=" + String.valueOf(uniqueId));
                CanvasYogaUINode canvas = new CanvasYogaUINode(uniqueId, getScope());
                addElement(canvas);
                Log.d("JSEngine", "createElement: canvas end=" + String.valueOf(uniqueId));
                break;
            case "text":
            case "label":
                LabelYogaUINode textYogaUINode = new LabelYogaUINode(uniqueId, getScope());
                addElement(textYogaUINode);
                break;
            case "section":
            case "div":
                DivYogaUINode divYogaUINode = new DivYogaUINode(uniqueId, getScope());
                addElement(divYogaUINode);
                break;
            case "img":
                ImageYogaUINode imgYogaUINode = new ImageYogaUINode(uniqueId, getScope());
                addElement(imgYogaUINode);
                break;
            case "input":
                InputYogaUINode inputYogaUINode = new InputYogaUINode(uniqueId, getScope());
                addElement(inputYogaUINode);
                break;
            case "scroller":
                ScrollViewYogaUINode scrollViewYogaUINode = new ScrollViewYogaUINode(uniqueId, getScope());
                addElement(scrollViewYogaUINode);
                break;
            default:
                break;
        }
    }

    @Override
    public void setStyle(int uniqueId, String key, String value) {
        Log.d("JSEngine", "setStyle: key=" + key + "， value=" + value);
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.setStyle(key, value);
        }
    }

    @Override
    public void resetStyle(int uniqueId) {
        Log.d("JSEngine", "resetStyle: uniqueId=" + String.valueOf(uniqueId));
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.resetStyle();
        }
    }


    @Override
    public void setAttribute(int uniqueId, String key, String value) {
        Log.d("JSEngine", "setAttribute: key=" + key + "， value=" + value);
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.setAttribute(key, value);
        }
    }

    @Override
    public String getAttribute(int uniqueId, String key) {
        Log.d("JSEngine", "getAttribute: key=" + key);
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            return ele.getAttribute(key);
        }
        return "";
    }

    @Override
    public void removeAttribute(int uniqueId, String key) {
        Log.d("JSEngine", "setAttribute: key=" + key);
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.removeAttribute(key);
        }
    }

    @Override
    public void insertChild(int uniqueId, int newChildId, int refChildId) {
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.insertBefore(getElement(newChildId), getElement(refChildId));
        }
    }

    @Override
    public void appendChild(int uniqueId, int newChildId) {
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.appendChild(getElement(newChildId));
        }
    }

    @Override
    public void removeChild(int uniqueId, int childId) {
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.removeChild(getElement(childId));
        }
    }

    @Override
    public void replaceChild(int uniqueId, int newChildId, int oldChildId) {
        IUINode ele = getElement(uniqueId);
        if (ele != null) {
            ele.replaceChild(getElement(newChildId), getElement(oldChildId));
        }
    }
    @Override
    public void scrollTo(int uniqueId, float x, float y) {
        IUINode ele = getElement(uniqueId);
        if (ele != null && ele instanceof ScrollViewYogaUINode) {
            ((ScrollViewYogaUINode)ele).scrollTo((int)x, (int)y);
        }
    }
}
