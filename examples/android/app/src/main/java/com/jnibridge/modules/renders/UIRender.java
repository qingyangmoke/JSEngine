package com.jnibridge.modules.renders;

import com.jnibridge.EngineScope;

import com.jnibridge.modules.dom.IUINode;

import java.util.HashMap;

public abstract class UIRender {
    private EngineScope _scope;
    protected IUINode _rootElement;
    private HashMap<String, IUINode> _tempElements = new HashMap<String, IUINode>();
    public UIRender(EngineScope scope) {
        this._scope = scope;
    }

    public EngineScope getScope() {
        return _scope;
    }

    public IUINode getRootElement() {
        return _rootElement;
    }

    public void addElement(IUINode element) {
        _tempElements.put(String.valueOf(element.getUniqueId()), element);
    }

    public IUINode getElement(int uniqueId) {
        if(uniqueId == 0) {
            return getRootElement();
        }
        return getElement(String.valueOf(uniqueId));
    }

    public IUINode getElement(String uniqueId) {
        return _tempElements.get(uniqueId);
    }

    public abstract void createElement(int uniqueId,String tagName);

    public abstract void insertChild(int uniqueId, int newChildId, int refChildId);

    public abstract void appendChild(int uniqueId, int newChildId);

    public abstract void removeChild(int uniqueId, int newChildId);

    public abstract void replaceChild(int uniqueId, int newChildId, int oldChildId);

    public abstract void setAttribute(int uniqueId,String key,String value);

    public abstract String getAttribute(int uniqueId,String key);

    public abstract void removeAttribute(int uniqueId, String key);

    public abstract void setStyle(int uniqueId, String key, String value);

    public abstract void resetStyle(int uniqueId);

    public abstract void scrollTo(int uniqueId, float x, float y);
}
