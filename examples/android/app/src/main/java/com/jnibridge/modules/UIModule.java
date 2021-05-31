package com.jnibridge.modules;

import com.jnibridge.EngineScope;

import org.json.JSONException;
import org.json.JSONObject;

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
        invokeMethodCallback(callId, 0,jsonObject);
        return "";
    }

    @EngineMethod(name = "createElement")
    public String createElement(int callId, String args) {
        return "";
    }
}
