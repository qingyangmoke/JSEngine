package com.jnibridge.modules;

import android.util.Log;

import com.jnibridge.EngineScope;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Iterator;

public class UIModule extends ModuleBase {
    public UIModule(EngineScope scope) {
        super("UI", scope);
    }

    @EngineMethod(name = "createElement")
    public String createElement(int callId, String args) {
        try {
            Log.d("JSEngine", "createElement: " + args);
            JSONObject json = new JSONObject(args);
            String tagName = json.getString("tagName");
            int uniqueId = json.getInt("uniqueId");
            getScope().getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    getScope().getUIRender().createElement(uniqueId, tagName);
                }
            });
        } catch (JSONException e) {
            e.printStackTrace();
            Log.d("JSEngine", "createElement: " + args);
        }
        return "";
    }

    @EngineMethod(name = "setStyle")
    public String setStyle(int callId, String args) {
        Log.d("JSEngine", "setStyle: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            boolean replace = json.has("replace") && json.getInt("replace") == 1;
            if(replace) {
                getScope().getUIRender().resetStyle(uniqueId);
            }
            JSONObject style = json.getJSONObject("style");
            Iterator<String> keys = style.keys();
            while (keys.hasNext()) {
                String key = keys.next();
                String value = style.getString(key);
                getScope().getUIRender().setStyle(uniqueId, key, value);
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "setAttribute")
    public String setAttribute(int callId, String args) {
        Log.d("JSEngine", "setAttribute: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            JSONObject attribute = json.getJSONObject("attribute");
            Iterator<String> keys = attribute.keys();
            while (keys.hasNext()) {
                String key = keys.next();
                String value = attribute.getString(key);
                getScope().getUIRender().setAttribute(uniqueId, key, value);
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "removeAttribute")
    public String removeAttribute(int callId, String args) {
        Log.d("JSEngine", "setAttribute: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            String key = json.getString("key");
            getScope().getUIRender().removeAttribute(uniqueId, key);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "getAttribute")
    public String getAttribute(int callId, String args) {
        Log.d("JSEngine", "getAttribute: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            String key = json.getString("key");
            return getScope().getUIRender().getAttribute(uniqueId, key);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "insertChild")
    public String insertChild(int callId, String args) {
        Log.d("JSEngine", "insertChild: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            JSONObject newChild = json.getJSONObject("newChild");
            int newChildId = newChild.getInt("uniqueId");
            JSONObject refChild = json.getJSONObject("refChild");
            int refChildId = refChild.getInt("uniqueId");
            getScope().getUIRender().insertChild(uniqueId, newChildId, refChildId);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "replaceChild")
    public String replaceChild(int callId, String args) {
        Log.d("JSEngine", "replaceChild: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            JSONObject newChild = json.getJSONObject("newChild");
            int newChildId = newChild.getInt("uniqueId");
            JSONObject oldChild = json.getJSONObject("oldChild");
            int oldChildId = oldChild.getInt("uniqueId");
            getScope().getUIRender().replaceChild(uniqueId, newChildId, oldChildId);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "scrollTo")
    public String scrollTo(int callId, String args) {
        Log.d("JSEngine", "scrollTo: " + args);
        try {
            JSONObject json = new JSONObject(args);
            int uniqueId = json.getInt("uniqueId");
            float x = (float)json.getDouble("x");
            float y = (float)json.getDouble("y");
            getScope().getUIRender().scrollTo(uniqueId, x, y);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }
}
