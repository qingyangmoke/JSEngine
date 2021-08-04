package com.jnibridge.modules;

import com.jnibridge.EngineScope;

public class TimerManager {
    EngineScope _scope;

    public TimerManager(EngineScope scope) {
        _scope = scope;
    }

    public EngineScope getScope() {
        return _scope;
    }

    int setInterval(int callId, int interval) {
//        _scope.evaluateJavaScript();
        return -1;
    }

    int setTimeout(int callId, int delay) {
        return -1;
    }

    void clearTimeout(int handle) {

    }

    void clearInterval(int handle) {

    }
}
