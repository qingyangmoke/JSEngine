package com.jnibridge.modules.dom.yoga;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ScrollView;

import com.facebook.yoga.YogaConstants;
import com.facebook.yoga.YogaDisplay;
import com.facebook.yoga.YogaFlexDirection;
import com.facebook.yoga.YogaNode;
import com.facebook.yoga.YogaNodeFactory;
import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.IUINode;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

public abstract class YogaUINode implements IUINode {
    protected YogaNode _yogaNode;
    protected String _tagName;
    protected int _uniqueId;
    protected EngineScope _scope;
    protected View _view;
    public YogaUINode(String tagName, int uniqueId, EngineScope scope) {
        this(tagName, uniqueId, scope, YogaNodeFactory.create());
    }

    public YogaUINode(String tagName, int uniqueId, EngineScope scope, YogaNode node) {
        _tagName = tagName;
        _uniqueId = uniqueId;
        _scope = scope;
        _yogaNode = node == null ? YogaNodeFactory.create() : node;
        getYogaNode().setDisplay(YogaDisplay.FLEX);
        getYogaNode().setFlexDirection(YogaFlexDirection.COLUMN);
    }

    public void setWidth(float width) {
        _yogaNode.setWidth(width);
    }

    public void setHeight(float height) {
        _yogaNode.setHeight(height);
    }

    public void setBackgroundColor(int color) {
        getNativeView().setBackgroundColor(color);
    }

    public YogaNode getYogaNode() {
        return _yogaNode;
    }

    public void setYogaNode(YogaNode node) {
        _yogaNode = node;
    }

    public View getNativeView() {
        return _view;
    }

    protected void setNativeView(View view) {
        _view = view;
        _view.setTag(this);
        getYogaNode().setData(_view);
        getNativeView().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("JSEngine","click tagName=" + getTagName());
                fireUIEvent("click");
            }
        });
        getNativeView().setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        fireUIEvent("touchstart");
                    case MotionEvent.ACTION_MOVE:
                        fireUIEvent("touchmove");
                    case MotionEvent.ACTION_UP:
                        fireUIEvent("touchend");
                    case MotionEvent.ACTION_CANCEL:
                        fireUIEvent("touchcancel");
                    case MotionEvent.ACTION_OUTSIDE:
                        fireUIEvent("touchoutside");
                }
                return false;
            }
        });
    }

    public void calculateLayout() {
        getYogaNode().calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    }

    @Override
    public EngineScope getScope() {
        return _scope;
    }

    @Override
    public int getUniqueId() {
        return _uniqueId;
    }

    @Override
    public String getTagName() {
        return _tagName;
    }

    @Override
    public ArrayList<IUINode> getChildNodes() {
        return null;
    }

    @Override
    public String getAttribute(String key) {
        String value = "";
        switch (key) {
            case "width":
                calculateLayout();
                value = String.valueOf(YogaStyleHelper.toDisplayUnit(getYogaNode().getLayoutWidth()));
                break;
            case "height":
                calculateLayout();
                value = String.valueOf(YogaStyleHelper.toDisplayUnit(getYogaNode().getLayoutHeight()));
                break;
        }
        Log.d("JSEngine", "getAttribute key=" + key + ", value=" + value);
        return value;
    }

    @Override
    public void setAttribute(String key, String value) {
        switch (key) {
            case "width":
            case "height":
                this.setStyle(key, value);
                break;
        }
    }

    @Override
    public void setStyle(String key, String value) {
        YogaStyleHelper.setStyle(getYogaNode(), key, value);
    }

    @Override
    public void resetStyle() {
        YogaStyleHelper.resetStyle(getYogaNode());
    }

    @Override
    public void removeAttribute(String key) {

    }

    @Override
    public IUINode appendChild(IUINode newChild) {
        return null;
    }

    @Override
    public boolean contains(IUINode child) {
        return false;
    }

    @Override
    public IUINode insertBefore(IUINode newChild, IUINode refChild) {
        return null;
    }

    @Override
    public IUINode removeChild(IUINode child) {
        return null;
    }

    @Override
    public IUINode replaceChild(IUINode newChild, IUINode oldChild) {
        return null;
    }

    public void fireUIEvent(String eventType) {
        fireUIEvent(eventType, null);
    }

    public void fireUIEvent(String eventType, JSONObject obj) {
        JSONObject json = new JSONObject();
        try {
            json.put("uniqueId", _uniqueId);
            json.put("type", eventType);
            if(obj != null) {
                json.put("data", obj);
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        getScope().invokeJSModule("JSMUIEvent", "onNativeEvent", json.toString());
    }
}
