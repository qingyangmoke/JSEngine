package com.jnibridge;

import org.json.JSONException;

import java.util.HashMap;
import java.util.Map;

public class EngineScope {
    private static int contextIdSeed = 100;
    private static Map<Integer, EngineScope> _scopes = new HashMap<Integer, EngineScope>();

    public static EngineScope createScope() {
        EngineScope scope = new EngineScope();
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

    protected EngineScope() {
        _contextId = ++EngineScope.contextIdSeed;
        _moduleManager = new ModuleManager(this);
        JSEngine.createScope(_contextId);
    }

    public int getContextId() {
        return _contextId;
    }

    public void evaluateJavaScript(String sourceCode, String sourceURL, int startLine) {
        JSEngine.evaluateJavaScript(_contextId, sourceCode, sourceURL , startLine);
    }

    public String invokeModule(int callId, String moduleName, String methodName, String args) {
        return _moduleManager.invokeModule(callId, moduleName, methodName, args);
    }
}