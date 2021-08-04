package com.jnibridge;

import android.app.Activity;

import com.jnibridge.modules.TimerManager;

import java.sql.Time;
import java.util.HashMap;
import java.util.Map;

public class EngineScope {
    private static int contextIdSeed = 100;
    private static Map<Integer, EngineScope> _scopes = new HashMap<Integer, EngineScope>();

    public static EngineScope createScope(Activity activity) {
        EngineScope scope = new EngineScope(activity);
        _scopes.put(scope.getContextId(), scope);
        return scope;
    }

    public static EngineScope getScope(int contextId) {
        return _scopes.get(contextId);
    }

    public static EngineScope removeScope(int contextId) {
        return _scopes.remove(contextId);
    }

    private int _contextId;
    private ModuleManager _moduleManager;
    private Activity _activity;

    private ElementFactory _elementFactory;
    private TimerManager _timerManager;

    protected EngineScope(Activity activity) {
        _contextId = ++EngineScope.contextIdSeed;
        _activity = activity;
        _moduleManager = new ModuleManager(this);
        JSEngine.createScope(_contextId);
        _elementFactory = new ElementFactory(this);
        _timerManager = new TimerManager(this);
    }

    public ElementFactory getElementFactory() {
        return _elementFactory;
    }

    public int getContextId() {
        return _contextId;
    }

    public Activity getActivity() {
        return _activity;
    }

    public void evaluateJavaScript(String sourceCode, String sourceURL, int startLine) {
        JSEngine.evaluateJavaScript(_contextId, sourceCode, sourceURL , startLine);
    }

    public String invokeModule(int callId, String moduleName, String methodName, String args) {
        return _moduleManager.invokeModule(callId, moduleName, methodName, args);
    }

    public void invokeJSModule(String moduleName, String methodName, String args) {
        JSEngine.invokeJSModule(_contextId, moduleName, methodName , args);
    }
}