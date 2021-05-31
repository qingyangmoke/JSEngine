package com.jnibridge.modules;

import com.jnibridge.EngineScope;

import org.json.JSONException;
import org.json.JSONObject;

public class Navigation extends ModuleBase {
    public Navigation(EngineScope scope) {
        super("Navigation", scope);
    }

    @EngineMethod(name = "to")
    public String to(int callId, String args) {
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("msg", "navigation to");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        invokeMethodCallback(callId, 0, jsonObject);
        return "success";
    }
}
