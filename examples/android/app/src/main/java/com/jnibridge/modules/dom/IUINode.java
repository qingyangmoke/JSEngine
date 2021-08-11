package com.jnibridge.modules.dom;

import android.view.View;

import com.jnibridge.EngineScope;

import java.util.ArrayList;

public interface IUINode {
    public EngineScope getScope();

    public int getUniqueId();

    public String getTagName();

    public ArrayList<IUINode> getChildNodes();

    public String getAttribute(String key);

    public void setStyle(String key, String value);

    public void resetStyle();

    public void setAttribute(String key, String value);

    public void removeAttribute(String key);

    public IUINode appendChild(IUINode newChild);

    public boolean contains(IUINode child);

    public IUINode insertBefore(IUINode newChild, IUINode refChild);

    public IUINode removeChild(IUINode child);

    public IUINode replaceChild(IUINode newChild, IUINode oldChild);
}
