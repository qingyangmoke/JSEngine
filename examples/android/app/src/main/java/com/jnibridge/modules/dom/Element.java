package com.jnibridge.modules.dom;

import android.view.View;

import java.util.ArrayList;

public abstract class Element extends Node {
    public String tagName;
    public String id;
    public String className;
    public Element parentNode;
    public Element previousSibling;
    public Element nextSibling;
    public Element ownerDocument;
    Element(String tagName, int nodeType, int uniqueid) {
        super(tagName, nodeType, uniqueid);
        this.tagName = tagName;
    }

    public abstract View getNativeView();

    public abstract ArrayList<Element> getChildNodes();
    public abstract String getAttribute(String key);
    public abstract void setAttribute(String key, String value);
    public abstract void removeAttribute(String key);
}
