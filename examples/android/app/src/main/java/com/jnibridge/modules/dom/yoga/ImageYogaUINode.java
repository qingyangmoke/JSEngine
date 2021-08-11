package com.jnibridge.modules.dom.yoga;

import android.graphics.Bitmap;
import android.widget.ImageView;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.yoga.YogaUINode;
import com.jnibridge.utils.IImageLoadListener;
import com.jnibridge.utils.ImageLoadTask;

public class ImageYogaUINode extends YogaUINode implements IImageLoadListener {
    private Bitmap _imageSource = null;
    public ImageYogaUINode(int uniqueId, EngineScope scope) {
        super("img", uniqueId, scope);
        ImageView view = new ImageView(getScope().getActivity());
        setNativeView(view);
    }

    public ImageView getImageView() {
        return (ImageView)getNativeView();
    }

    public Bitmap getImageSource() {
        return _imageSource;
    }

    @Override
    public void setAttribute(String key, String value) {
        switch (key) {
            case "src":
                new ImageLoadTask(value, this).execute();
                break;
            default:
                super.setAttribute(key, value);
                break;
        }
    }

    @Override
    public void onLoad(Bitmap bitmap) {
        _imageSource = bitmap;
        getScope().getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                getImageView().setImageBitmap(bitmap);
                fireUIEvent("load");
            }
        });
    }

    @Override
    public void onError(int errorCode, String msg) {
        fireUIEvent("error");
    }
}
