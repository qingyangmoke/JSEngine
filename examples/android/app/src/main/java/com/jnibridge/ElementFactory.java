package com.jnibridge;

import android.util.Log;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.CanvasElement;
import com.jnibridge.modules.dom.Element;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;

public class ElementFactory {
    private EngineScope _scope;

    private HashMap<String, Element> _tempElements = new HashMap<String, Element>();

    public void addElement(Element element) {
        _tempElements.put(String.valueOf(element.uniqueId), element);
    }

    public Element getElement(int uniqueId) {
        return getElement(String.valueOf(uniqueId));
    }

    public Element getElement(String uniqueId) {
        return _tempElements.get(uniqueId);
    }

    public EngineScope getScope() {
        return _scope;
    }

    ElementFactory(EngineScope scope) {
        _scope = scope;
    }

    public void createElement(String args) {
        try {
            Log.d("JSEngine", "createElement: " + args);
            JSONObject json = new JSONObject(args);
            String tagName = json.getString("tagName");
            int uniqueId = json.getInt("uniqueId");
            switch (tagName) {
                case "canvas":
                    Log.d("JSEngine", "createElement: canvas begin=" + String.valueOf(uniqueId));
                    CanvasElement canvas = new CanvasElement(uniqueId, getScope());
                    addElement(canvas);
                    Log.d("JSEngine", "createElement: canvas end=" + String.valueOf(uniqueId));
                    break;
            }
        } catch (JSONException e) {
            e.printStackTrace();
            Log.d("JSEngine", "createElement: " + args);
        }
    }
}
