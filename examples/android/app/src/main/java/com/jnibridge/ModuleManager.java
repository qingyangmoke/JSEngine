package com.jnibridge;

import com.jnibridge.modules.EmptyModule;
import com.jnibridge.modules.ModuleBase;
import com.jnibridge.modules.Navigation;
import com.jnibridge.modules.UIModule;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ModuleManager {
    private EngineScope _scope;
    private Map<String, ModuleBase> _modules = new HashMap<String, ModuleBase>();
    private EmptyModule _emtpyModule;
    public ModuleManager(EngineScope scope) {
        _scope = scope;
        _emtpyModule = new EmptyModule(_scope);
        registerModule(_emtpyModule);
        registerModule(new UIModule(_scope));
        registerModule(new Navigation(_scope));
    }

    public EngineScope getScope() {
        return _scope;
    }

    public void registerModule(ModuleBase module) {
        _modules.put(module.getModuleName(), module);
    }

    public String invokeModule(int callId, String moduleName, String methodName, String args) {
        String result = "";
        if(_modules.containsKey(moduleName)) {
            return _modules.get(moduleName).invokeMethod(callId, methodName, args);
        }

        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("msg","Module (" + moduleName + ") not found");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        _emtpyModule.invokeMethodCallback(callId, 404, jsonObject);
        return "";
    }
}
