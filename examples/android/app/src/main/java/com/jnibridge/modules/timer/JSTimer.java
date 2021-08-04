package com.jnibridge.modules.timer;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.TimeUnit;

public class JSTimer {
    private int _id = 0;
    private EngineScope _scope;
    private Timer _timer = null;
    private String _callbackArgs = "";

    public JSTimer(int id, EngineScope scope) {
        _id = id;
        _scope = scope;
        JSONObject json = new JSONObject();
        try {
            json.put("id", _id);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        _callbackArgs = json.toString();
    }

    public void setTimeout(int delay) {
        JSEngine.log(_scope.getContextId(), "info", "setTimeout delay=" + String.valueOf(delay));
        if (_timer != null) {
            this.stop();
        }
        if (delay == 0) {
            JSEngine.invokeJSModule(_scope.getContextId(), "JSMTimer", "timerCallback", _callbackArgs);
            return;
        }
        _timer = new Timer();
        _timer.schedule(new TimerTask() {
            @Override
            public void run() {
                if (_timer != null) {
                    _scope.getActivity().runOnUiThread(new Runnable() {
                        public void run() {
                            JSEngine.invokeJSModule(_scope.getContextId(), "JSMTimer", "timerCallback", _callbackArgs);
                        }
                    });
                    stop();
                }
            }
        }, delay);
    }

    public void setInterval(int interval) {
        if (_timer != null) {
            this.stop();
        }
        _timer = new Timer();
        _timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                _scope.getActivity().runOnUiThread(new Runnable() {
                    public void run() {
                        if (_timer != null) {
                            JSEngine.invokeJSModule(_scope.getContextId(), "JSMTimer", "timerCallback", _callbackArgs);
                        }
                    }
                });
            }
        }, interval, interval);
    }

    public void stop() {
        if (_timer != null) {
            _timer.cancel();
            _timer = null;
        }
    }

    public int getId() {
        return _id;
    }
}
