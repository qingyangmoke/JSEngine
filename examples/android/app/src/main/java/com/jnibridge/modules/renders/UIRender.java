package com.jnibridge.modules.renders;

import com.jnibridge.EngineScope;
import com.jnibridge.modules.EngineMethod;
import com.jnibridge.modules.UIModule;

import org.json.JSONException;
import org.json.JSONObject;

public class UIRender {
    private UIModule _uiModule;
    public UIRender(UIModule uimodule) {
      this._uiModule = uimodule;
    }

    public void responseToJS(int callId, JSONObject jsonObject) {
      this._uiModule.invokeMethodCallback(callId, 0,jsonObject);
    }

    @EngineMethod(name = "refresh")
    public String refresh(int callId, String args) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("args", args);
            jsonObject.put("callId", callId);
            jsonObject.put("method", "UI.refresh");
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        this.responseToJS(callId, jsonObject);
        return "";
    }

    @EngineMethod(name = "createElement")
    public String createElement(int callId, String args) {
        return "";
    }
}
