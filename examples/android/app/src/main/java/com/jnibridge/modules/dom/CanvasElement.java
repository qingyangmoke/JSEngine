package com.jnibridge.modules.dom;

import android.app.Activity;
import android.content.Context;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.jnibridge.EngineScope;

import java.util.ArrayList;

public class CanvasElement extends Element {
    public static String TAG = "canvas";
    private CanvasRenderingContext2D _renderContext = null;
    private EngineScope _scope;
    private LinearLayout _view;
    private int _width = 100;
    private int _height = 100;

    public CanvasElement(int uniqueid, EngineScope scope) {
        super(CanvasElement.TAG, 0, uniqueid);
        _scope = scope;
        LinearLayout view = new LinearLayout(this.getViewContext());
        view.setOrientation(LinearLayout.HORIZONTAL);
        android.widget.FrameLayout.LayoutParams params = new android.widget.FrameLayout.LayoutParams(this._width, this._height);
        ((Activity) this.getViewContext()).addContentView(view, params);
        _view = view;
    }

    public CanvasRenderingContext2D getRenderingContext() {
        return _renderContext;
    }

    public CanvasRenderingContext2D createRenderingContext(String type) {
        if (_renderContext == null) {
            _renderContext = new CanvasRenderingContext2D(this);
            ViewGroup.LayoutParams vlp = new ViewGroup.LayoutParams(
                    ViewGroup.LayoutParams.WRAP_CONTENT,
                    ViewGroup.LayoutParams.WRAP_CONTENT);
            _renderContext.setLayoutParams(vlp);
            _view.addView(_renderContext);
        }
        return _renderContext;
    }

    public Context getViewContext() {
        return this._scope.getActivity();
    }


    @Override
    public View getNativeView() {
        return this._view;
    }

    @Override
    public ArrayList<Element> getChildNodes() {
        return null;
    }

    @Override
    public String getAttribute(String key) {
        return null;
    }

    public void resize() {
        ViewGroup.LayoutParams params = this._view.getLayoutParams();
        params.width = this._width;
        params.height = this._height;
        this._view.setLayoutParams(params);
    }

    @Override
    public void setAttribute(String key, String value) {
        switch (key) {
            case "width":
                this._width = Integer.parseInt(value);
                this.resize();
                break;
            case "height":
                this._height = Integer.parseInt(value);
                this.resize();
                break;
        }
    }

    @Override
    public void removeAttribute(String key) {
    }
}
