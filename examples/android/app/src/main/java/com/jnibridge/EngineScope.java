package com.jnibridge;

import android.app.Activity;
import android.content.res.AssetManager;

import com.jnibridge.modules.renders.DomUIRender;
import com.jnibridge.modules.renders.UIRender;
import com.jnibridge.utils.BundleLoader;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.sql.Time;
import java.util.HashMap;
import java.util.Map;

public class EngineScope {
    private static int contextIdSeed = 1000; // 前1000预留
    private static Map<Integer, EngineScope> _scopes = new HashMap<Integer, EngineScope>();
    public static EngineScope createScope(Activity activity) {
        EngineScope scope = new EngineScope(activity);
        _scopes.put(scope.getContextId(), scope);
        scope.intJSScope();
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
    private UIRender _uiRender;
    private boolean _jsScopeInited = false;
    private BundleLoader _bundleLoader;
    protected EngineScope(Activity activity) {
        _contextId = ++EngineScope.contextIdSeed;
        _activity = activity;
        _moduleManager = new ModuleManager(this);
        _uiRender = new DomUIRender(this);
        _bundleLoader = new BundleLoader(this);
    }

    protected void intJSScope() {
        if(!_jsScopeInited) {
            _jsScopeInited = true;
            JSEngine.createScope(_contextId);
        }
    }

    public UIRender getUIRender() {
        return _uiRender;
    }

    public int getContextId() {
        return _contextId;
    }

    public Activity getActivity() {
        return _activity;
    }

    public BundleLoader getBundleLoader() {
        return _bundleLoader;
    }

    public void evaluateJavaScript(String sourceCode, String sourceURL, int startLine) {
        JSEngine.evaluateJavaScript(_contextId, sourceCode, sourceURL , startLine);
    }

    public void invokeJSModule(String moduleName, String methodName, String args) {
        JSEngine.invokeJSModule(_contextId, moduleName, methodName , args);
    }

    public String invokeModule(int callId, String moduleName, String methodName, String args) {
        return _moduleManager.invokeModule(callId, moduleName, methodName, args);
    }

    public boolean loadBundle(String bundleURL) {
        return getBundleLoader().loadBundle(bundleURL);
    }
}