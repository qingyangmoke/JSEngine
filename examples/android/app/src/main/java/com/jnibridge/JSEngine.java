package com.jnibridge;
import org.json.JSONException;

import java.util.logging.*;
public class JSEngine {
    public static Logger _logger = Logger.getLogger("JSEngine");
    static {
        try {
//            System.loadLibrary("c++_shared");
//            System.loadLibrary("jsc");
            System.loadLibrary("jsengine_bridge");
            System.loadLibrary("MyBridgeJNI");
        }catch (Exception e) {
            System.err.println("UnsatisfiedLinkError:" + e.toString());
        }
    }
    public static native int initEngine();
    public static native int createScope(int contextId);
    public static native int evaluateJavaScript(int contextId, String sourceCode, String sourceURL, int startLine);
    public static native int invokeModuleEvent(int contextId, int callId, int errorCode, String result);
    public static native int invokeJSModule(int contextId, String moduleName, String methodName, String args);

    public static String invokeModule(int contextId, int callId, String moduleName, String methodName, String args) {
        log(contextId, "info", "[android] contextId="+ contextId +", callId=" + callId + ", moduleName=" + moduleName+", methodName=" + methodName + ", args=" + args);
        EngineScope scope = EngineScope.getScope(contextId);
        if(scope != null) {
            return scope.invokeModule(callId, moduleName, methodName, args);
        } else {
            log(contextId, "error", "[android] scope not init contextId="+ contextId +", callId=" + callId + ", moduleName=" + moduleName+", methodName=" + methodName + ", args=" + args);
            invokeModuleEvent(contextId, callId, 0, "{\"moduleName\": \"" + moduleName + "\", \"methodName\": \"" + methodName + "\"}");
        }
        return "";
    }

    public static void log(int contextId, String tagName, String message) {
        switch (tagName.toLowerCase()) {
            case "warn":
                _logger.warning("contextId="+ contextId +  " ," + message);
                break;
            default:
                _logger.info(message);
                break;
        }
    }

}