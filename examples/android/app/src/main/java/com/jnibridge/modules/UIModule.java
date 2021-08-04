package com.jnibridge.modules;

import android.graphics.Canvas;
import android.util.Log;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.CanvasElement;
import com.jnibridge.modules.dom.CanvasRenderingContext2D;
import com.jnibridge.modules.dom.Element;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Iterator;
import java.util.Timer;
import java.util.TimerTask;

public class UIModule extends ModuleBase {
    public UIModule(EngineScope scope) {
        super("UI", scope);
    }

    @EngineMethod(name = "refresh")
    public String refreshUI(int callId, String args) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("args", args);
            jsonObject.put("callId", callId);
            jsonObject.put("method", "UI.refresh");
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        invokeMethodCallback(callId, 0, jsonObject);

        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask(){
            @Override
            public void run(){
                timer.cancel();
                Log.i("tag", "A Kiss every 5 seconds");
            }
        },0,5000);
        return "";
    }

    @EngineMethod(name = "createElement")
    public String createElement(int callId, String args) {
        getScope().getElementFactory().createElement(args);
        return "";
    }

    @EngineMethod(name = "setAttribute")
    public String setAttribute(int callId, String args) {
        Log.d("JSEngine", "setAttribute: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            Element ele = getScope().getElementFactory().getElement(uniqueId);
            if (ele != null) {
                JSONObject attribute = json.getJSONObject("attribute");
                Iterator<String> keys = attribute.keys();
                while (keys.hasNext()) {
                    String key = keys.next();
                    String value = attribute.getString(key);
                    Log.d("JSEngine", "setAttribute: " + key + "=" + value);
                    ele.setAttribute(key, value);
                }
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }
}
