package com.jnibridge.modules.dom.yoga;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.IUINode;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

public class CanvasYogaUINode extends ContainerYogaUINode {
    public static String TAG = "canvas";
    private CanvasRenderingContext2D _renderContext = null;
//    private LinearLayout _view;
    private float _width = 100;
    private float _height = 100;

    public CanvasYogaUINode(int uniqueid, EngineScope scope) {
        super(CanvasYogaUINode.TAG, uniqueid, scope);
        setWidth(_width);
        setHeight(_height);
    }

    public CanvasRenderingContext2D getRenderingContext() {
        return _renderContext;
    }

    public CanvasRenderingContext2D createRenderingContext(String type) {
        if (_renderContext == null) {
            _renderContext = new CanvasRenderingContext2D(this);
            CanvasContextYogaUINode node = new CanvasContextYogaUINode("canvas-context", _uniqueId, getScope(), _renderContext);
            appendChild(node);
        }
        return _renderContext;
    }

    public Context getViewContext() {
        return getScope().getActivity();
    }

    @Override
    public ArrayList<IUINode> getChildNodes() {
        return null;
    }

    @Override
    public String getAttribute(String key) {
        return super.getAttribute(key);
    }

    public void resize() {
    }

    @Override
    public void setAttribute(String key, String value) {
        super.setAttribute(key, value);
        switch (key) {
            case "width":
                _width = Float.parseFloat(value);
                resize();
                break;
            case "height":
                resize();
                break;
            default:
                break;
        }
    }

    @Override
    public void removeAttribute(String key) {
    }

}
