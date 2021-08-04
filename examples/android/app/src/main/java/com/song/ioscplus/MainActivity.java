package com.song.ioscplus;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.res.AssetManager;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.ViewGroup;
import android.widget.TextView;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;
import com.jnibridge.modules.dom.CanvasElement;
import com.jnibridge.modules.dom.CanvasRenderingContext2D;

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
        System.err.println("initEngine.result=" + r1);
//        SurfaceView surfaceView = new SurfaceView(this);
//        android.widget.FrameLayout.LayoutParams params = new android.widget.FrameLayout.LayoutParams(200, 200);
//        this.addContentView(surfaceView, params);
////        view.setLayoutParams(params);
//        // 从SurfaceView的surfaceHolder里锁定获取Canvas
//        Paint mPaint  = new Paint();
//        mPaint.setColor(Color.BLACK);
//        mPaint.setStyle(Paint.Style.STROKE);
//        mPaint.setAntiAlias(true);
//        mPaint.setStrokeWidth(5);
//        SurfaceHolder surfaceHolder = surfaceView.getHolder();
//        //获取Canvas
//        Canvas c = surfaceHolder.lockCanvas();
//        c.drawLine(0,50,200,50, mPaint);
//        // ...（进行Canvas操作）
//        // Canvas操作结束之后解锁并执行Canvas
//        surfaceHolder.unlockCanvasAndPost(c);

        EngineScope scope = EngineScope.createScope(this);
        System.err.println("initEngine.scope.getContextId=" + scope.getContextId());
        String bundleCode = loadBundle("main.js");
        scope.evaluateJavaScript(bundleCode, "main.js", 0);

//        JSEngine.invokeJSModule(scope.getContextId(), "JSTimers", "sayHi" ,"hello1");
//
//        JSEngine.invokeJSModule(scope.getContextId(), "JSTimers", "sayHi" ,"hello2");
////        String sourceCode = "window.nativeFlushQueueImmediate('nativeFlushQueueImmediate');window.nativeFlushQueueImmediate('nativeFlushQueueImmediate'); ";
//        scope.evaluateJavaScript(sourceCode, "main.js", 0);

//        CanvasElement canvas = new CanvasElement(1, scope);
//        canvas.createRenderingContext("2d");
//        canvas.setAttribute("width", "1080");
//        canvas.setAttribute("height", "600");
//        this.findViewById(R.id.action_text).setAlpha(0.5f);
    }
}