package com.jnibridge.modules.dom.yoga;

import android.app.ActionBar;
import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Point;
import android.os.Build;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import com.facebook.yoga.YogaDisplay;
import com.facebook.yoga.YogaFlexDirection;
import com.jnibridge.EngineScope;
import com.song.ioscplus.R;

public class BodyYogaUINode extends ContainerYogaUINode {
    public BodyYogaUINode(int uniqueid, EngineScope scope) {
        super("body", uniqueid, scope);
        Log.d("JSEngine", "BodyElement: " + String.valueOf(uniqueid));

        getYogaNode().setDisplay(YogaDisplay.FLEX);
        getYogaNode().setFlexDirection(YogaFlexDirection.COLUMN);

        Point windowPoint = new Point();
        getScope().getActivity().getWindowManager().getDefaultDisplay().getSize(windowPoint);

        ActionBar bar = getScope().getActivity().getActionBar();
        int actionBarHeight = bar == null ? 0 : bar.getHeight();
        if(actionBarHeight ==0 ) {
            TypedArray actionbarSizeTypedArray = getScope().getActivity().obtainStyledAttributes(new int[]{android.R.attr.actionBarSize});
            actionBarHeight = (int) actionbarSizeTypedArray.getDimension(0, 0);
        }
        int statusHeight = getStatusBarHeightCompat(getScope().getActivity());
        Log.d("JSEngine", "actionBarHeight=" + String.valueOf(actionBarHeight) + ",statusHeight=" + String.valueOf(statusHeight));
//        int actionBarHeight = 0;
        float screenWidth = windowPoint.x;
        float screenHeight = windowPoint.y - actionBarHeight - statusHeight;
        ViewGroup.LayoutParams vp = new FrameLayout.LayoutParams((int)screenWidth, (int)screenHeight);
        getScope().getActivity().addContentView(getNativeView(), vp);
    }

    public int getStatusBarHeightCompat(Context context) {
        int result = 0;
        int resId = context.getResources().getIdentifier("status_bar_height", "dimen", "android");
        if (resId > 0) {
            result = context.getResources().getDimensionPixelOffset(resId);
        }
        return result;
    }

    @Override
    public void setAttribute(String key, String value) {
        switch (key) {
            case "title":
                getScope().getActivity().setTitle(value);
                break;
            default:
                super.setAttribute(key, value);
                break;
        }
    }
}
