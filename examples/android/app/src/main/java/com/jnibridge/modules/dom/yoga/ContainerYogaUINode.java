package com.jnibridge.modules.dom.yoga;

import android.util.Log;
import android.view.View;
import android.view.ViewGroup;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.IUINode;
import com.jnibridge.modules.dom.yoga.YogaUINode;
import com.jnibridge.modules.dom.yoga.YogaViewGroup;

public class ContainerYogaUINode extends YogaUINode {
    public ContainerYogaUINode(String tagName, int uniqueId, EngineScope scope) {
        this(tagName,uniqueId, scope, true);
    }

    public ContainerYogaUINode(String tagName, int uniqueId, EngineScope scope, boolean autoCreatedView) {
        super(tagName, uniqueId, scope);
        if(autoCreatedView) {
            YogaViewGroup view = new YogaViewGroup(getScope().getActivity(), getYogaNode());
            setNativeView(view);
        }
    }

    public ViewGroup getYogaViewGroup() {
        return (ViewGroup)getNativeView();
    }

    @Override
    public IUINode appendChild(IUINode newChild) {
        if(newChild == null) {
            return null;
        }
        YogaUINode child = (YogaUINode) newChild;
        getYogaViewGroup().addView(child.getNativeView());
        return newChild;
    }

    @Override
    public IUINode insertBefore(IUINode newChild, IUINode refChild) {
        if(newChild == null) {
            return null;
        }
        int index = -1;
        if(refChild != null) {
            index = getYogaViewGroup().indexOfChild(((YogaUINode)refChild).getNativeView());
        }
        Log.d("JSEngine", "insertBefore"+String.valueOf(index));
        YogaUINode newElement = (YogaUINode) newChild;
        View view = newElement.getNativeView();
        getYogaViewGroup().addView(view, index);
        return newChild;
    }


    @Override
    public IUINode removeChild(IUINode child) {
        if(child == null) {
            return null;
        }
        YogaUINode newElement = (YogaUINode) child;
        getYogaViewGroup().removeView(newElement.getNativeView());
        return child;
    }

    @Override
    public IUINode replaceChild(IUINode newChild, IUINode oldChild) {
        if(newChild == null) {
            return null;
        }
        int index = -1;
        if(oldChild != null) {
            index = getYogaViewGroup().indexOfChild(((YogaUINode)oldChild).getNativeView());
        }
        YogaUINode newElement = (YogaUINode)newChild;
        YogaUINode oldElement = (YogaUINode)oldChild;
        getYogaViewGroup().addView(newElement.getNativeView(), index);
        getYogaViewGroup().removeView(oldElement.getNativeView());
        return newChild;
    }
}
