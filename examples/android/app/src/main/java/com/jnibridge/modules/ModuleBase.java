package com.jnibridge.modules;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;

import org.json.JSONException;
import org.json.JSONObject;

import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;

public class ModuleBase {
    private String _moduleName;
    private EngineScope _scope;
    private Map<String,Method> _methods = new HashMap<String, Method>();
    protected ModuleBase(String moduleName, EngineScope scope) {
        _moduleName = moduleName;
        _scope = scope;
        final Method[] methods = this.getClass().getMethods();
        for(Method method : methods) {
            EngineMethod anno = method.getAnnotation(EngineMethod.class);
            if(anno != null) {
                final String methodName = anno.name().isEmpty() ? method.getName() : anno.name();
                _methods.put(methodName, method);
            }
        }
    }

    public String getModuleName() {
        return _moduleName;
    }
    public EngineScope getScope() {
        return _scope;
    }

    public void invokeMethodCallback(int callId, int errorCode, JSONObject result) {
        JSEngine.invokeModuleEvent(_scope.getContextId(), callId, errorCode, result.toString());
    }

    public String invokeMethod(int callId, String methodName, String args) {
        String result = "";
        if(_methods.containsKey(methodName)) {
            try {
                return (String) _methods.get(methodName).invoke(this, callId, args);
            } catch (Exception e) {
                JSONObject jsonObject = new JSONObject();
                try {
                    jsonObject.put("msg", e.toString());
                } catch (JSONException jsonException) {
                    jsonException.printStackTrace();
                }
                invokeMethodCallback(callId, -1,jsonObject);
                e.printStackTrace();
            }
        }
        return result;
    }
}
