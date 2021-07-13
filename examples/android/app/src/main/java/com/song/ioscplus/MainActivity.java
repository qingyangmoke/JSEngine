package com.song.ioscplus;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {
    private String loadBundle(String bundleURL) {
        String jscontent = "";
        try{
            AssetManager am = this.getAssets();
            InputStream is = am.open(bundleURL);
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader br = new BufferedReader(isr);

            String line;
            while (( line = br.readLine()) != null) {
                jscontent += line;
            }
            is.close();
        }
        catch(Exception e){}
        return jscontent;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.err.println("launch");
        int r1 = JSEngine.initEngine();
        System.err.println("initEngine.result="+r1);
        EngineScope scope = EngineScope.createScope();
        System.err.println("initEngine.scope.getContextId=" + scope.getContextId());
        String bundleCode = loadBundle("main.js");
        scope.evaluateJavaScript(bundleCode, "main.js", 0);
//        String sourceCode = "window.nativeFlushQueueImmediate('nativeFlushQueueImmediate');window.nativeFlushQueueImmediate('nativeFlushQueueImmediate'); ";
//        scope.evaluateJavaScript(sourceCode, "main.js", 0);
    }
}