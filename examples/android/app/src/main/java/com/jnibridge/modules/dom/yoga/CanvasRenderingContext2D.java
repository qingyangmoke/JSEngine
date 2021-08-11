package com.jnibridge.modules.dom.yoga;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.PointF;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.text.TextPaint;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

import com.facebook.yoga.YogaNode;
import com.jnibridge.EngineScope;
import com.jnibridge.JSEngine;
import com.song.ioscplus.R;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;

public class CanvasRenderingContext2D extends SurfaceView implements SurfaceHolder.Callback, Runnable {
    private static HashMap<String, Typeface> sTypefaceCache = new HashMap<>();
    private static float _sApproximatingOblique = -0.25f;//please check paint api documentation
    private static final String TEXT_ALIGN_LEFT = "left";
    private static final String TEXT_ALIGN_CENTER = "center";
    private static final String TEXT_ALIGN_RIGHT = "right";

    private static final String TEXT_BASELINE_TOP = "top";
    private static final String TEXT_BASELINE_MIDDLE = "middle";
    private static final String TEXT_BASELINE_BOTTOM = "bottom";
    private static final String TEXT_BASELINE_ALPHABETIC = "alphabetic";

    private class FontObject {
        public String name = "Arial";
        public float size = 40.0f;
        public boolean bold = false;
        public boolean italic = false;
        public boolean oblique = false;
        public boolean smallCaps = false;
        public void copy(FontObject target) {
            name = target.name;
            size = target.size;
            bold = target.bold;
            italic = target.italic;
            oblique = target.oblique;
            smallCaps = target.smallCaps;
        }
    }

    private class StyleColor {
        public int r = 0;
        public int g = 0;
        public int b = 0;
        public int a = 255;

        StyleColor() {
        }

        StyleColor(int r, int g, int b, int a) {
            r = r;
            g = g;
            b = b;
            a = a;
        }

        public void copy(StyleColor target) {
            r = target.r;
            g = target.g;
            b = target.b;
            a = target.a;
        }
    }

    private class SaveState {
        public StyleColor fillColor;
        public StyleColor strokeColor;
        public FontObject fontObject;
        public Paint strokePaint;
        public Paint fillPaint;
        public boolean antiAlias;
        public float lineWidth;
        public String lineCap;
        public String lineJoin;
    }

    private SurfaceHolder mSurfaceHolder;
    //绘图的Canvas
    private Canvas mCanvas;
    //子线程标志位
    private boolean mIsDrawing;

    private boolean mAntiAlias = true;
    private Bitmap mBitmap;

    // clear
    private Paint clearPaint;

    // path
    private Path mLinePath;

    // fill
    private Paint fillPaint;
    private StyleColor mFillColor = new StyleColor(0, 0, 0, 255);

    // stroke
    private Paint strokePaint;
    private StyleColor mStrokeColor = new StyleColor(0, 0, 0, 255);

    private float mLineWidth = 0.0f;
    private String mLineCap = "butt";
    private String mLineJoin = "miter";

    // text
    private TextPaint mTextPaint;
    private String mTextAlign = TEXT_ALIGN_LEFT;
    private String mTextBaseline = TEXT_BASELINE_BOTTOM;
    private FontObject mFont;

    private Paint mBitmapPaint;

    private ArrayList<JSONArray> _commandCache = new ArrayList<>();
    private CanvasYogaUINode _canvas;

    private SaveState _saveState;
    public CanvasRenderingContext2D(CanvasYogaUINode canvas) {
        super(canvas.getViewContext());
        _canvas= canvas;

        mIsDrawing = false;

        clearPaint = new Paint();
        clearPaint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.CLEAR));

        fillPaint = new Paint();
        fillPaint.setStyle(Paint.Style.FILL);
        fillPaint.setARGB(mFillColor.a, mFillColor.r, mFillColor.g, mFillColor.b);

        strokePaint = new Paint();
        strokePaint.setARGB(mStrokeColor.a, mStrokeColor.r, mStrokeColor.g, mStrokeColor.b);
        strokePaint.setStyle(Paint.Style.STROKE);
        strokePaint.setAntiAlias(mAntiAlias);

        setLineCap(mLineCap);
        setLineJoin(mLineJoin);

        mLinePath = new Path();

        mBitmapPaint = new Paint();

        mFont = new FontObject();
        initView();
    }

    public YogaNode getYogaNode() {
        return _canvas.getYogaNode();
    }

    public EngineScope getScope() {
        return _canvas.getScope();
    }

    /**
     * 初始化View
     */
    private void initView() {
        mSurfaceHolder = getHolder();
        mSurfaceHolder.addCallback(this);
        setFocusable(true);
        setKeepScreenOn(true);
        setFocusableInTouchMode(true);
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
        mIsDrawing = true;
//        testDraw();
        for (JSONArray object: _commandCache) {
            batchCommand(object);
        }
        _commandCache.clear();
        System.out.println("CanvasRenderingContext2D surfaceCreated");
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        Log.d("JSEngine", "canvas onSizeChanged");
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {
        Log.d("JSEngine", "canvas surfaceChanged");
        _canvas.fireUIEvent("surfaceChanged");
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {
        mIsDrawing = false;
    }

    @Override
    public void run() {
//        while (mIsDrawing) {
//            draw();
//            x += 1;
//            y = (int) (100 * Math.sin(2 * x * Math.PI / 180));
//            //加入新的坐标点
//            mLinePath.lineTo(x, y);
//        }
    }

    public void beginDraw() {
        try {
            //获得canvas对象
            mCanvas = mSurfaceHolder.lockCanvas();
            //绘制背景
            mCanvas.drawColor(Color.TRANSPARENT);
        } catch (Exception e) {

        }
    }

    private void testDraw() {
        beginDraw();

        setLineWidth(4);
        setFillStyle(255, 0, 0, 255);
        setStrokeStyle(0, 255, 0, 255);

        beginPath();
        moveTo(0, 0);
        lineTo(200, 200);
        lineTo(300, 10);
        lineTo(400, 200);
        stroke();

        setStrokeStyle(255, 0, 0, 255);
        setLineWidth(2);

        beginPath();
        moveTo(50, 50);
        lineTo(250, 250);
        lineTo(350, 60);
        lineTo(450, 250);
        stroke();

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.icon);
        int mBitWidth = bitmap.getWidth();
        int mBitHeight = bitmap.getHeight();
        drawImage(bitmap, 0,0, mBitWidth, mBitHeight, 50, 200 , mBitWidth * 2 , mBitHeight * 2);
        endDraw();
    }


    public void endDraw() {
        try {
            if (mCanvas != null) {
                //释放canvas对象并提交画布
                mSurfaceHolder.unlockCanvasAndPost(mCanvas);
            }
        } catch (Exception e) {
        }
    }

    public boolean isReady() {
        return mIsDrawing;
    }

    public void setFillStyle(int r, int g, int b, int a) {
        mFillColor.r = r;
        mFillColor.g = g;
        mFillColor.b = b;
        mFillColor.a = a;
        fillPaint.setARGB(mFillColor.a, mFillColor.r, mFillColor.g, mFillColor.b);
    }

    public void setStrokeStyle(int r, int g, int b, int a) {
        mStrokeColor.r = r;
        mStrokeColor.g = g;
        mStrokeColor.b = b;
        mStrokeColor.a = a;
        strokePaint.setARGB(mStrokeColor.a, mStrokeColor.r, mStrokeColor.g, mStrokeColor.b);
    }

    public void setLineWidth(float lineWidth) {
        JSEngine.log(getScope().getContextId(), "JSEngine", "setLineWidth=" + String.valueOf(lineWidth) + "," + String.valueOf(YogaStyleHelper.rpxRatio));
        mLineWidth = lineWidth;
        strokePaint.setStrokeWidth(mLineWidth);
    }

    public void setLineCap(String lineCap) {
        mLineCap = lineCap;
        switch (mLineCap) {
            case "butt":
                strokePaint.setStrokeCap(Paint.Cap.BUTT);
                break;
            case "round":
                strokePaint.setStrokeCap(Paint.Cap.ROUND);
                break;
            case "square":
                strokePaint.setStrokeCap(Paint.Cap.SQUARE);
                break;
        }
    }

    public void setLineJoin(String lineJoin) {
        mLineJoin = lineJoin;
        switch (mLineJoin) {
            case "bevel":
                strokePaint.setStrokeJoin(Paint.Join.BEVEL);
                break;
            case "round":
                strokePaint.setStrokeJoin(Paint.Join.ROUND);
                break;
            case "miter":
                strokePaint.setStrokeJoin(Paint.Join.MITER);
                break;
        }
    }

    public void setTextAlign(String align) {
        mTextAlign = align;
    }

    public void setTextBaseline(String baseline) {
        mTextBaseline = baseline;
    }

    private void onFontUpdate() {
        mTextPaint = null;
    }

    public void setFontName(String fontName) {
        mFont.name = fontName;
        onFontUpdate();
    }

    public void setFont(String fontName, float fontSize, boolean bold, boolean italic, boolean oblique, boolean smallCaps) {
        mFont.name = fontName;
        mFont.size = fontSize;
        mFont.bold = bold;
        mFont.italic = italic;
        mFont.oblique = oblique;
        mFont.smallCaps = smallCaps;
        onFontUpdate();
    }

    public void setAntiAlias(boolean antiAlias) {
        mAntiAlias = antiAlias;
        strokePaint.setAntiAlias(mAntiAlias);
        onFontUpdate();
    }

    public void save() {
        mCanvas.save();
        // save others config
        if(_saveState == null) {
            _saveState = new SaveState();
            _saveState.fillColor = new StyleColor();
            _saveState.strokeColor = new StyleColor();
            _saveState.fontObject = new FontObject();
        }
        _saveState.fontObject.copy(mFont);
        _saveState.fillColor.copy(mFillColor);
        _saveState.strokeColor.copy(mStrokeColor);
        _saveState.lineCap = mLineCap;
        _saveState.lineJoin = mLineJoin;
        _saveState.lineWidth = mLineWidth;
        _saveState.antiAlias = mAntiAlias;
    }

    public void restore() {
        mCanvas.restore();
        if(_saveState != null) {
            setFont(_saveState.fontObject.name, _saveState.fontObject.size, _saveState.fontObject.bold, _saveState.fontObject.italic, _saveState.fontObject.oblique, _saveState.fontObject.smallCaps);
            setStrokeStyle(_saveState.strokeColor.r,_saveState.strokeColor.g, _saveState.strokeColor.b,_saveState.strokeColor.a);
            setFillStyle(_saveState.fillColor.r,_saveState.fillColor.g, _saveState.fillColor.b,_saveState.fillColor.a);
            setLineCap(_saveState.lineCap);
            setLineWidth(_saveState.lineWidth);
            setLineJoin(_saveState.lineJoin);
            setAntiAlias(_saveState.antiAlias);
        }
    }

    public void scale(float x, float y) {
        mCanvas.scale(x, y);
    }

    public void rotate(float angle) {
        mCanvas.rotate(angle);
    }

    public void translate(float x, float y) {
        mCanvas.translate(x, y);
    }

    public void skew(float skewX, float skewY) {
        this.mCanvas.skew(skewX, skewY);
    }

    public void transform(float a, float b, float c, float d, float dx, float dy) {
        double pivotX = 0;
        double pivotY = 0;

        double skewX = -Math.atan2(-c, d);
        double skewY = Math.atan2(b, a);

        double delta = Math.abs(skewX + skewY);

        double PI_2 = Math.PI * 2;

        double rotation = 0;
        if (delta < 0.00001 || Math.abs(PI_2 - delta) < 0.00001) {
            rotation = skewY;
            skewX = 0;
            skewY = 0;
        }

        // next set scale
        double scaleX = Math.sqrt((a * a) + (b * b));
        double scaleY = Math.sqrt((c * c) + (d * d));

        // next set position
        double x = dx + ((pivotX * a) + (pivotY * c));
        double y = dy + ((pivotX * b) + (pivotY * d));
        this.skew((float) skewX, (float) skewY);
        this.rotate((float) rotation);
        this.scale((float) scaleX, (float) scaleY);
        this.translate((float) x, (float) y);
    }

    public void setTransform(float a, float b, float c, float d, float dx, float dy) {
        Matrix matrix = new Matrix();
        float[] values = new float[9];
        values[0] = a;
        values[1] = c;
        values[2] = dx;
        values[3] = b;
        values[4] = d;
        values[5] = dy;
        values[6] = 0;
        values[7] = 0;
        values[8] = 1;
        matrix.setValues(values);
        mCanvas.setMatrix(matrix);
    }

    public void clearRect(float x, float y, float w, float h) {
        mCanvas.drawRect(x, y, x + w, y + h, clearPaint);
        if (mBitmap != null) {
            int clearSize = (int) (w * h);
            int[] clearColor = new int[clearSize];
            for (int i = 0; i < clearSize; ++i) {
                clearColor[i] = Color.TRANSPARENT;
            }
            mBitmap.setPixels(clearColor, 0, (int) w, (int) x, (int) y, (int) w, (int) h);
        }
    }

    public void rect(float x, float y, float w, float h) {
        beginPath();
        moveTo(x, y);
        lineTo(x, y + h);
        lineTo(x + w, y + h);
        lineTo(x + w, y);
        closePath();
    }

    public void fillRect(float x, float y, float w, float h) {
        mCanvas.drawRect(x, y, x + w, y + h, fillPaint);
    }

    public void strokeRect(float x, float y, float w, float h) {
        JSEngine.log(getScope().getContextId(), "JSEngine", "strokeRect=" + String.valueOf(x) + "," + String.valueOf(y)+ "," + String.valueOf(w)+ "," + String.valueOf(h));
        mCanvas.drawRect(x, y, x + w, y + h, strokePaint);
    }

    public void beginPath() {
        mLinePath.reset();
    }

    public void fill() {
        //绘制路径
        mCanvas.drawPath(mLinePath, fillPaint);
    }

    public void stroke() {
        mCanvas.drawPath(mLinePath, strokePaint);
    }

    public void clip() {
        mCanvas.clipPath(mLinePath);
    }

    public void closePath() {
        mLinePath.close();
    }

    public void moveTo(float x, float y) {
        mLinePath.moveTo(x, y);
    }

    public void lineTo(float x, float y) {
        mLinePath.lineTo(x, y);
    }

    public void quadraticCurveTo(float x1, float y1, float x2, float y2) {
        mLinePath.quadTo(x1, y1, x2, y2);
    }

    public void bezierCurveTo(float x1, float y1, float x2, float y2,
                              float x3, float y3) {
        mLinePath.cubicTo(x1, y1, x2, y2, x3, y3);
    }

    public float measureText(String text) {
        createTextPaintIfNeeded();
        float ret = mTextPaint.measureText(text);
        return ret;
    }

    public void fillText(String text, float x, float y, float maxWidth) {
        createTextPaintIfNeeded();
        mTextPaint.setARGB(mFillColor.a, mFillColor.r, mFillColor.g, mFillColor.b);
        mTextPaint.setStyle(Paint.Style.FILL);
        setTextScaleX(mTextPaint, text, maxWidth);
        PointF pt = convertDrawPoint(new PointF(x, y), text);
        mCanvas.drawText(text, pt.x, pt.y, mTextPaint);
    }

    public void strokeText(String text, float x, float y, float maxWidth) {
        createTextPaintIfNeeded();
        mTextPaint.setARGB(mStrokeColor.a, mStrokeColor.r, mStrokeColor.g, mStrokeColor.b);
        mTextPaint.setStyle(Paint.Style.STROKE);
        mTextPaint.setStrokeWidth(mLineWidth);
        mTextPaint.setAntiAlias(mAntiAlias);
        setTextScaleX(mTextPaint, text, maxWidth);
        PointF pt = convertDrawPoint(new PointF(x, y), text);
        mCanvas.drawText(text, pt.x, pt.y, mTextPaint);
    }

    public void drawImage(Bitmap bitmap, int x, int y, int w, int h) {
        mCanvas.drawBitmap(bitmap, null, new Rect(x, y, x + w, y + h), mBitmapPaint);
    }

    public void drawImage(Bitmap bitmap, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh) {
        mCanvas.drawBitmap(bitmap, new Rect(sx, sy, sx + sw, sy + sh), new Rect(dx, dy, dx + dw, dy + dh), mBitmapPaint);
    }

    public void drawImage(Bitmap bitmap, float x, float y) {
        mCanvas.drawBitmap(bitmap, x, y, mBitmapPaint);
    }

    public void arc(float x, float y, float radius, float startAngle, float endAngle, boolean counterclockwise) {
        float sweepAngle = ((endAngle - startAngle) + 360 % 360);
//        Log.d("JSEngine", "canvas arc: startAngle=" + String.valueOf(startAngle) + ",endAngle=" + String.valueOf(endAngle) + "，sweepAngle=" + String.valueOf(sweepAngle));
        if(counterclockwise) {
            sweepAngle = sweepAngle - 360;
        }
//        Log.d("JSEngine", "canvas arc: startAngle=" + String.valueOf(startAngle) + ",endAngle=" + String.valueOf(endAngle) + "，sweepAngle=" + String.valueOf(sweepAngle));
        mLinePath.addArc(x - radius, y - radius, x + radius, y + radius, startAngle, sweepAngle);
    }

    private void setTextScaleX(TextPaint textPaint, String text, float maxWidth) {
        if (maxWidth < Float.MIN_VALUE) return;
        float measureWidth = this.measureText(text);
        if ((measureWidth - maxWidth) < Float.MIN_VALUE) return;
        float scaleX = maxWidth / measureWidth;
        textPaint.setTextScaleX(scaleX);
    }

    private void createTextPaintIfNeeded() {
        if (mTextPaint == null) {
            mTextPaint = newPaint(mFont, mAntiAlias);
        }
    }

    private static TextPaint newPaint(FontObject font, boolean antiAlias) {
        TextPaint paint = new TextPaint();
        paint.setTextSize(font.size);
        paint.setAntiAlias(antiAlias);
        paint.setSubpixelText(true);

        String key = font.name;
        if (font.bold) {
            key += "-Bold";
            paint.setFakeBoldText(true);
        }
        if (font.italic) {
            key += "-Italic";
        }

        Typeface typeFace;
        if (sTypefaceCache.containsKey(key)) {
            typeFace = sTypefaceCache.get(key);
        } else {
            int style = Typeface.NORMAL;
            if (font.bold && font.italic) {
                style = Typeface.BOLD_ITALIC;
            } else if (font.bold) {
                style = Typeface.BOLD;
            } else if (font.italic) {
                style = Typeface.ITALIC;
            }
            typeFace = Typeface.create(font.name, style);
        }
        paint.setTypeface(typeFace);
        if (font.oblique) {
            paint.setTextSkewX(_sApproximatingOblique);
        }
        return paint;
    }

    private PointF convertDrawPoint(final PointF point, String text) {
        // The parameter 'point' is located at left-bottom position.
        // Need to adjust 'point' according 'text align' & 'text base line'.
        PointF ret = new PointF(point.x, point.y);
        createTextPaintIfNeeded();
        Paint.FontMetrics fm = mTextPaint.getFontMetrics();
        float width = measureText(text);

        if (mTextAlign == TEXT_ALIGN_CENTER) {
            ret.x -= width / 2;
        } else if (mTextAlign == TEXT_ALIGN_RIGHT) {
            ret.x -= width;
        }
        // Canvas.drawText accepts the y parameter as the baseline position, not the most bottom
        if (mTextBaseline == TEXT_BASELINE_TOP) {
            ret.y += -fm.ascent;
        } else if (mTextBaseline == TEXT_BASELINE_MIDDLE) {
            ret.y += (fm.descent - fm.ascent) / 2 - fm.descent;
        } else if (mTextBaseline == TEXT_BASELINE_BOTTOM) {
            ret.y += -fm.descent;
        }
        return ret;
    }

    private static void clearTypefaceCache() {
        sTypefaceCache.clear();
    }

//    private void createBufferIfNeeded() {
//    }
//
//    private void recreateBuffer(float w, float h) {
//        if (mBitmap != null) {
//            mBitmap.recycle();
//        }
//        mBitmap = Bitmap.createBitmap((int)Math.ceil(w), (int)Math.ceil(h), Bitmap.Config.ARGB_8888);
//        mCanvas.setBitmap(mBitmap);
//    }

    public float getDisplayUnit(String cssValue) {
        return YogaStyleHelper.getDisplayUnit(cssValue);
    }

    public float getDisplayUnit(int cssValue) {
        return getDisplayUnit((float) cssValue);
    }

    public float getDisplayUnit(double cssValue) {
        return getDisplayUnit((float) cssValue);
    }

    public float getDisplayUnit(float cssValue) {
        return YogaStyleHelper.getDisplayUnit(cssValue);
    }

    public void batchCommand(JSONArray commands) {
        if(!this.isReady()) {
            _commandCache.add(commands);
            return;
        }
        try {
            beginDraw();
            CanvasRenderingContext2D context = this;
            Log.d("JSEngine", "batchCommand: commands=" + commands.join(",") + (context.isReady() ? "ready" : "not ready"));
            for (int i = 0; i < commands.length(); i++) {
                Log.d("JSEngine", "batchCommand: i=" + String.valueOf(i));
                JSONObject cmdItem = commands.getJSONObject(i);
                String commandSub = cmdItem.getString("command");
                JSONObject commandArgs = cmdItem.has("data") ? cmdItem.getJSONObject("data") : new JSONObject();
                Log.d("JSEngine", "batchCommand: commandSub=" + commandSub + ",commandArgs=" + commandArgs.toString());
                switch (commandSub) {
                    case "save":
                        context.save();
                        break;
                    case "restore":
                        context.restore();
                        break;
                    case "scale":
                        context.scale((float)commandArgs.getDouble("x"), (float) commandArgs.getDouble("y"));
                        break;
                    case "rotate":
                        float rotate = (float) YogaStyleHelper.toDegrees(commandArgs.getDouble("angle"));
                        context.rotate(rotate);
                        break;
                    case "translate":
                        context.translate(getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")));
                        break;
                    case "transform":
                        context.transform(getDisplayUnit(commandArgs.getDouble("a")), getDisplayUnit(commandArgs.getDouble("b")), getDisplayUnit(commandArgs.getDouble("c")),getDisplayUnit(commandArgs.getDouble("d")), getDisplayUnit(commandArgs.getDouble("e")), getDisplayUnit(commandArgs.getDouble("f")));
                        break;
                    case "setTransform":
                        context.setTransform(getDisplayUnit(commandArgs.getDouble("a")), getDisplayUnit(commandArgs.getDouble("b")), getDisplayUnit(commandArgs.getDouble("c")),getDisplayUnit(commandArgs.getDouble("d")), getDisplayUnit(commandArgs.getDouble("e")), getDisplayUnit(commandArgs.getDouble("f")));
                        break;
                    case "rect":
                        context.rect(getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit(commandArgs.getDouble("w")),getDisplayUnit(commandArgs.getDouble("h")));
                        break;
                    case "clearRect":
                        context.clearRect(getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit(commandArgs.getDouble("w")),getDisplayUnit(commandArgs.getDouble("h")));
                        break;
                    case "fillRect":
                        context.fillRect(getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit(commandArgs.getDouble("w")),getDisplayUnit(commandArgs.getDouble("h")));
                        break;
                    case "strokeRect":
                        context.strokeRect(getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit(commandArgs.getDouble("w")),getDisplayUnit(commandArgs.getDouble("h")));
                        break;
                    case "beginPath":
                        context.beginPath();
                        break;
                    case "closePath":
                        context.closePath();
                        break;
                    case "fill":
                        context.fill();
                        break;
                    case "stroke":
                        context.stroke();
                        break;
                    case "clip":
                        context.clip();
                        break;
                    case "moveTo":
                        context.moveTo(getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")));
                        break;
                    case "lineTo":
                        context.lineTo(getDisplayUnit(commandArgs.getDouble("x")),getDisplayUnit(commandArgs.getDouble("y")));
                        break;
                    case "quadraticCurveTo":
                        context.quadraticCurveTo(getDisplayUnit(commandArgs.getDouble("cpx")), getDisplayUnit(commandArgs.getDouble("cpy")), getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")));
                        break;
                    case "bezierCurveTo":
                        context.bezierCurveTo(getDisplayUnit(commandArgs.getDouble("cp1x")), getDisplayUnit(commandArgs.getDouble("cp1y")), getDisplayUnit(commandArgs.getDouble("cp2x")), getDisplayUnit(commandArgs.getDouble("cp2y")), getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")));
                        break;
                    case "fillText":
                        context.fillText(commandArgs.getString("text"), getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit( commandArgs.getDouble("maxWidth")));
                        break;
                    case "strokeText":
                        context.strokeText(commandArgs.getString("text"), getDisplayUnit(commandArgs.getDouble("x")), getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit(commandArgs.getDouble("maxWidth")));
                        break;
                    case "lineDash":
                        commandArgs.getJSONArray("lineDash");
                        break;
                    case "antiAlias":
                        boolean antiAlias = commandArgs.getInt("antiAlias")  == 1;
                        context.setAntiAlias(antiAlias);
                        break;
                    case "lineWidth":
                        float lineWidth = getDisplayUnit(commandArgs.getDouble("value"));
                        context.setLineWidth(lineWidth);
                        break;
                    case "lineCap":
                        context.setLineCap(commandArgs.getString("value"));
                        break;
                    case "lineJoin":
                        context.setLineJoin(commandArgs.getString("value"));
                        break;
                    case "miterLimit":
//                        context.setMiterLimit(commandArgs.getInt("value"));
                        break;
                    case "lineDashOffset":
//                        context.setLineDashOffset(commandArgs.getInt("value"));
                        break;
                    case "fillStyle":
                        context.setFillStyle(commandArgs.getInt("r"),commandArgs.getInt("g"),commandArgs.getInt("b"),commandArgs.getInt("a"));
                        break;
                    case "strokeStyle":
                        context.setStrokeStyle(commandArgs.getInt("r"),commandArgs.getInt("g"),commandArgs.getInt("b"),commandArgs.getInt("a"));
                        break;
                    case "arc":
                        context.arc(getDisplayUnit(commandArgs.getDouble("x")),getDisplayUnit(commandArgs.getDouble("y")), getDisplayUnit(commandArgs.getDouble("radius")),(float)YogaStyleHelper.toDegrees(commandArgs.getDouble("startAngle")), (float) YogaStyleHelper.toDegrees(commandArgs.getDouble("endAngle")), commandArgs.getInt("counterclockwise") == 1);
                        break;
                    case "drawImage":
                        int textureId = commandArgs.getInt("textureId");
                        ImageYogaUINode imageYogaUINode = (ImageYogaUINode)_canvas.getScope().getUIRender().getElement(textureId);
                        if(imageYogaUINode != null) {
                            Bitmap imageSource = imageYogaUINode.getImageSource();
                            if(imageSource != null) {
                                JSONArray drawImageArgs = commandArgs.getJSONArray("params");
                                if (drawImageArgs.length() == 2) {
                                    context.drawImage(imageYogaUINode.getImageSource(), (int)getDisplayUnit(drawImageArgs.getInt(0)),(int)getDisplayUnit(drawImageArgs.getInt(1)), (int)getDisplayUnit(imageYogaUINode.getYogaNode().getWidth().value), (int)getDisplayUnit(imageYogaUINode.getYogaNode().getHeight().value));
                                } else if (drawImageArgs.length() == 4) {
                                    context.drawImage(imageYogaUINode.getImageSource(), (int)getDisplayUnit(drawImageArgs.getInt(0)), (int)getDisplayUnit(drawImageArgs.getInt(1)), (int)getDisplayUnit(drawImageArgs.getInt(2)), (int)getDisplayUnit(drawImageArgs.getInt(3)));
                                } else if (drawImageArgs.length() == 8) {
                                    context.drawImage(imageYogaUINode.getImageSource(), (int)getDisplayUnit(drawImageArgs.getInt(0)), (int)getDisplayUnit(drawImageArgs.getInt(1)), (int)getDisplayUnit(drawImageArgs.getInt(2)), (int)getDisplayUnit(drawImageArgs.getInt(3)), (int)getDisplayUnit(drawImageArgs.getInt(4)), (int)getDisplayUnit(drawImageArgs.getInt(5)), (int)getDisplayUnit(drawImageArgs.getInt(6)), (int)getDisplayUnit(drawImageArgs.getInt(7)));
                                }
                            }
                        }
                        break;
                }
            }
        } catch (JSONException jsonException) {
            jsonException.printStackTrace();
        } finally {
            endDraw();
        }
    }
}
