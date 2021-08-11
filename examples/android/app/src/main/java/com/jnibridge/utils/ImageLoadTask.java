package com.jnibridge.utils;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.widget.ImageView;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class ImageLoadTask extends AsyncTask<Void, Void, Bitmap> {
    private String _url;
    private IImageLoadListener _listener;
    public ImageLoadTask(String url, IImageLoadListener listener) {
        _url = url;
        _listener = listener;
    }

    @Override
    protected Bitmap doInBackground(Void... voids) {
        try {
            URL urlConnection = new URL(_url);
            HttpURLConnection connection = (HttpURLConnection) urlConnection
                    .openConnection();
            connection.setDoInput(true);
            connection.connect();
            InputStream input = connection.getInputStream();
            Bitmap myBitmap = BitmapFactory.decodeStream(input);
            _listener.onLoad(myBitmap);
            return myBitmap;
        } catch (Exception e) {
            e.printStackTrace();
            _listener.onError(500, e.getMessage());
        }
        return null;
    }
}
