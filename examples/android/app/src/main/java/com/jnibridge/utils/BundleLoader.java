package com.jnibridge.utils;

import android.content.res.AssetManager;

import com.jnibridge.EngineScope;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class BundleLoader {
    private EngineScope _scope;
    public BundleLoader(EngineScope scope) {
        _scope = scope;
    }

    public EngineScope getScope() {
        return _scope;
    }

    public boolean loadBundle(String bundleURL) {
        try{
            StringBuilder builder = new StringBuilder();
            AssetManager am = getScope().getActivity().getAssets();
            InputStream is = am.open(bundleURL);
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader br = new BufferedReader(isr);
            String line;
            while (( line = br.readLine()) != null) {
                builder.append(line);
                builder.append("\r\n");
            }
            is.close();
            getScope().evaluateJavaScript(builder.toString(), bundleURL, 0);
            return true;
        }
        catch(Exception e){
            e.printStackTrace();
        }
        return false;
    }
}
