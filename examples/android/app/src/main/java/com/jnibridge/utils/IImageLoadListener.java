package com.jnibridge.utils;

import android.graphics.Bitmap;

public interface IImageLoadListener {
    public void onLoad(Bitmap bitmap);
    public void onError(int errorCode, String msg);
}
