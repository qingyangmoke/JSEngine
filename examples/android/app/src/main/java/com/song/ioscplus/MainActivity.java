package com.song.ioscplus;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
        System.err.println("launch");
        int r1 = JSEngine.initEngine();
        System.err.println("initEngine.result=" + r1);

        EngineScope scope = EngineScope.createScope(this);
        System.err.println("initEngine.scope.getContextId=" + scope.getContextId());

        scope.loadBundle("scroller.js");
    }

    @Override
    protected void onNightModeChanged(int mode) {
        super.onNightModeChanged(mode);
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
//        int actionBarHeight = getActionBar().getHeight();
//        Log.d("JSEngine", "actionBarHeight=" + String.valueOf(actionBarHeight));
        return super.onPrepareOptionsMenu(menu);
    }
}