package com.jnibridge.modules;

import android.graphics.Color;
import android.graphics.Rect;
import android.util.Log;
import com.jnibridge.EngineScope;
import com.jnibridge.modules.dom.CanvasElement;
import com.jnibridge.modules.dom.CanvasRenderingContext2D;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class CanvasModule extends ModuleBase {

  public CanvasModule(EngineScope scope) {
    super("canvas", scope);
  }

  public CanvasElement getCanvas(int uniqueId) {
    return (CanvasElement) getScope().getElementFactory().getElement(uniqueId);
  }

  @EngineMethod(name = "batchCmd")
  public String batchCommand(int callId, String args) {
    try {
      JSONObject json = new JSONObject(args);
      int uniqueId = json.getInt("uniqueId");
      CanvasElement canvas = getCanvas(uniqueId);
      CanvasRenderingContext2D context = canvas.getRenderingContext();
      JSONArray commands = json.getJSONArray("commands");
      Log.d(
        "JSEngine",
        "batchCommand: commands=" +
        commands.join(",") +
        (context.isReady() ? "ready" : "not ready")
      );
      context.batchCommand(commands);
    } catch (JSONException jsonException) {
      jsonException.printStackTrace();
    }
    return "";
  }

  @EngineMethod(name = "measureText")
  public String measureText(int callId, String args) {
    Log.d("JSEngine", "measureText: " + args);
    JSONObject jsonObject = new JSONObject();
    try {
      JSONObject json = new JSONObject(args);
      int uniqueId = json.getInt("uniqueId");
      String text = json.getString("text");
      CanvasElement canvas = getCanvas(uniqueId);
      float width = canvas.getRenderingContext().measureText(text);
      jsonObject.put("width", width);
    } catch (JSONException jsonException) {
      jsonException.printStackTrace();
    }
    return jsonObject.toString();
  }

  @EngineMethod(name = "createContext")
  public String createContext(int callId, String args) {
    Log.d("JSEngine", "createContext: " + args);
    try {
      JSONObject json = new JSONObject(args);
      int uniqueId = json.getInt("uniqueId");
      String type = json.getString("type");
      CanvasElement canvas = getCanvas(uniqueId);
      canvas.createRenderingContext(type);
    } catch (JSONException jsonException) {
      jsonException.printStackTrace();
    }
    return "";
  }
}
