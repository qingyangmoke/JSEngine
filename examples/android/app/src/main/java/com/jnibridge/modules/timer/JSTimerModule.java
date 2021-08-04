package com.jnibridge.modules.timer;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;
import com.jnibridge.modules.EngineMethod;
import com.jnibridge.modules.ModuleBase;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.Timer;
import java.util.TimerTask;

public class JSTimerModule extends ModuleBase {
    private HashMap<String, JSTimer> _timers;

    public JSTimerModule(EngineScope scope) {
        super("JSMTimer", scope);
        _timers = new HashMap<String, JSTimer>();
    }

    @EngineMethod(name = "setInterval")
    public String setInterval(int callId, String args) {
        try {
            JSONObject jsonArgs = new JSONObject(args);
            int id = jsonArgs.getInt("id");
            int interval = jsonArgs.getInt("interval");
            JSONObject json = new JSONObject();
            json.put("id", id);
            String key = String.valueOf(id);
            if(_timers.containsKey(key)) {
                _timers.get(key).stop();
            }
            JSTimer timer = new JSTimer(id, getScope());
            _timers.put(key, timer);
            timer.setInterval(interval);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "setTimeout")
    public String setTimeout(int callId, String args) {
        try {
            JSONObject jsonArgs = new JSONObject(args);
            int id = jsonArgs.getInt("id");
            int delay = jsonArgs.getInt("delay");
            JSONObject json = new JSONObject();
            json.put("id", id);

            String key = String.valueOf(id);
            if(_timers.containsKey(key)) {
                _timers.get(key).stop();
            }
            JSTimer timer = new JSTimer(id, getScope());
            _timers.put(key, timer);
            timer.setTimeout(delay);
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "clearTimeout")
    public String clearTimeout(int callId, String args) {
        try {
            JSONObject jsonArgs = new JSONObject(args);
            int id = jsonArgs.getInt("id");
            String key = String.valueOf(id);
            if(_timers.containsKey(key)) {
                _timers.get(key).stop();
                _timers.remove(key);
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }

    @EngineMethod(name = "clearInterval")
    public String clearInterval(int callId, String args) {
        try {
            JSONObject jsonArgs = new JSONObject(args);
            int id = jsonArgs.getInt("id");
            String key = String.valueOf(id);
            if(_timers.containsKey(key)) {
                _timers.get(key).stop();
                _timers.remove(key);
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        }
        return "";
    }
}
