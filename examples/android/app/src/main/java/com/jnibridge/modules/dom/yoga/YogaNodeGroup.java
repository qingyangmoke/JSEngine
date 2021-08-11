package com.jnibridge.modules.dom.yoga;

import android.content.Context;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;

import com.facebook.yoga.YogaConstants;
import com.facebook.yoga.YogaDirection;
import com.facebook.yoga.YogaEdge;
import com.facebook.yoga.YogaMeasureFunction;
import com.facebook.yoga.YogaMeasureMode;
import com.facebook.yoga.YogaMeasureOutput;
import com.facebook.yoga.YogaNode;
import com.facebook.yoga.YogaNodeFactory;
import com.facebook.yoga.android.VirtualYogaLayout;
import com.facebook.yoga.android.YogaLayout;

public class YogaNodeGroup {
    private ViewGroup _view;
    private YogaNode _yogaNode;

    public YogaNodeGroup(ViewGroup view, YogaNode node, AttributeSet attrs) {
        _view = view;
        if(node == null) {
            _yogaNode = YogaNodeFactory.create();
        } else {
            _yogaNode = node;
        }

        _yogaNode.setData(getViewGroup());
        _yogaNode.setMeasureFunction(new ViewMeasureFunction());

        ViewGroup.LayoutParams layoutParams = null;
        if (attrs != null) {
            layoutParams = new ViewGroup.LayoutParams(view.getContext(), attrs);
        } else {
            layoutParams = generateDefaultLayoutParams();
        }
        applyLayoutParams(layoutParams, getYogaNode(), getViewGroup());
    }

    public YogaNode getYogaNode() {
        return _yogaNode;
    }

    public ViewGroup getViewGroup() {
        return _view;
    }

    public void removeViewAt(int index) {
        removeViewFromYogaTree(getViewGroup().getChildAt(index), false);
    }

    public void removeViewInLayout(View view) {
        removeViewFromYogaTree(view, true);
    }

    public void removeViews(int start, int count) {
        for (int i = start; i < start + count; i++) {
            removeViewFromYogaTree(getViewGroup().getChildAt(i), false);
        }
    }

    public void removeViewsInLayout(int start, int count) {
        for (int i = start; i < start + count; i++) {
            removeViewFromYogaTree(getViewGroup().getChildAt(i), true);
        }
    }

    public void removeAllViews() {
        final int childCount = getViewGroup().getChildCount();
        for (int i = 0; i < childCount; i++) {
            removeViewFromYogaTree(getViewGroup().getChildAt(i), false);
        }
    }

    public void removeAllViewsInLayout() {
        final int childCount = getViewGroup().getChildCount();
        for (int i = 0; i < childCount; i++) {
            removeViewFromYogaTree(getViewGroup().getChildAt(i), true);
        }
    }

    public void removeViewFromYogaTree(View view, boolean inLayout) {
        YogaUINode element = (YogaUINode) view.getTag();
        final YogaNode node = element.getYogaNode();
        if (node == null) {
            return;
        }

        final YogaNode owner = node.getOwner();

        for (int i = 0; i < owner.getChildCount(); i++) {
            if (owner.getChildAt(i).equals(node)) {
                owner.removeChildAt(i);
                break;
            }
        }

        node.setData(null);

        if (inLayout) {
            getYogaNode().calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
        }
    }

    public void onLayout(boolean changed, int l, int t, int r, int b) {
        // Either we are a root of a tree, or this function is called by our owner's onLayout, in which
        // case our r-l and b-t are the size of our node.
        if (!(getViewGroup().getParent() instanceof YogaViewGroup)) {
            Log.d("JSEngine","onLayout1");
            createLayout(
                    View.MeasureSpec.makeMeasureSpec(r - l, View.MeasureSpec.EXACTLY),
                    View.MeasureSpec.makeMeasureSpec(b - t, View.MeasureSpec.EXACTLY));
        }

        applyLayoutRecursive(getYogaNode(), 0, 0);
    }


    protected ViewGroup.LayoutParams generateDefaultLayoutParams() {
        return new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT);
    }


    private void applyLayoutRecursive(YogaNode node, float xOffset, float yOffset) {
        View view = (View) node.getData();

        if (view != null && view != getViewGroup()) {
            if (view.getVisibility() == ViewGroup.GONE) {
                return;
            }
            int left = Math.round(xOffset + node.getLayoutX());
            int top = Math.round(yOffset + node.getLayoutY());
            view.measure(
                    View.MeasureSpec.makeMeasureSpec(
                            Math.round(node.getLayoutWidth()),
                            View.MeasureSpec.EXACTLY),
                    View.MeasureSpec.makeMeasureSpec(
                            Math.round(node.getLayoutHeight()),
                            View.MeasureSpec.EXACTLY));
            view.layout(left, top, left + view.getMeasuredWidth(), top + view.getMeasuredHeight());
        }

        final int childrenCount = node.getChildCount();
        for (int i = 0; i < childrenCount; i++) {
            if (getViewGroup().equals(view)) {
                applyLayoutRecursive(node.getChildAt(i), xOffset, yOffset);
            } else if (view instanceof YogaViewGroup) {
                continue;
            } else {
                applyLayoutRecursive(
                        node.getChildAt(i),
                        xOffset + node.getLayoutX(),
                        yOffset + node.getLayoutY());
            }
        }
    }

    private void createLayout(int widthMeasureSpec, int heightMeasureSpec) {
        final int widthSize = View.MeasureSpec.getSize(widthMeasureSpec);
        final int heightSize = View.MeasureSpec.getSize(heightMeasureSpec);
        final int widthMode = View.MeasureSpec.getMode(widthMeasureSpec);
        final int heightMode = View.MeasureSpec.getMode(heightMeasureSpec);

        if (heightMode == View.MeasureSpec.EXACTLY) {
            getYogaNode().setHeight(heightSize);
        }
        if (widthMode == View.MeasureSpec.EXACTLY) {
            getYogaNode().setWidth(widthSize);
        }
        if (heightMode == View.MeasureSpec.AT_MOST) {
            getYogaNode().setMaxHeight(heightSize);
        }
        if (widthMode == View.MeasureSpec.AT_MOST) {
            getYogaNode().setMaxWidth(widthSize);
        }
        getYogaNode().calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    }

    /**
     * Applies the layout parameters to the YogaNode.  That is, this function is a translator from
     * {@code yoga:X="Y"} to {@code yogaNode.setX(Y);}, with some reasonable defaults.
     *
     * <p>
     * If the SDK version is high enough, and the {@code yoga:direction} is not set on
     * the component, the direction (LTR or RTL) is set according to the locale.
     *
     * <p>
     * The attributes {@code padding_top}, {@code padding_right} etc. default to those of the view's
     * drawable background, if it has one.
     *
     * @param layoutParameters The source set of params
     * @param node The destination node
     */
    protected static void applyLayoutParams(ViewGroup.LayoutParams layoutParameters, YogaNode node, View view) {
        // JELLY_BEAN_MR1 (17) is the first version supporting getLayoutDirection()
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            Configuration configuration = view.getResources().getConfiguration();
            if (configuration.getLayoutDirection() == ViewGroup.LAYOUT_DIRECTION_RTL) {
                node.setDirection(YogaDirection.RTL);
            }
        }

        Drawable background = view.getBackground();
        if (background != null) {
            final Rect backgroundPadding = new Rect();
            if (background.getPadding(backgroundPadding)) {
                node.setPadding(YogaEdge.LEFT, backgroundPadding.left);
                node.setPadding(YogaEdge.TOP, backgroundPadding.top);
                node.setPadding(YogaEdge.RIGHT, backgroundPadding.right);
                node.setPadding(YogaEdge.BOTTOM, backgroundPadding.bottom);
            }
        }

        if (layoutParameters.width >= 0) {
            node.setWidth(layoutParameters.width);
        }

        if (layoutParameters.height >= 0) {
            node.setHeight(layoutParameters.height);
        }
    }

    public void addView(View child, int index, ViewGroup.LayoutParams params) {
        // Internal nodes (which this is now) cannot have measure functions
        getYogaNode().setMeasureFunction(null);
        if(index == -1) {
            index = getViewGroup().getChildCount();
        }

        YogaNode childNode;
        if (child instanceof YogaViewGroup) {
            childNode = ((YogaViewGroup)child).getYogaNode();
        } else {
            YogaUINode element = (YogaUINode)child.getTag();
            if(element.getYogaNode() != null) {
                childNode = element.getYogaNode();
            } else {
                childNode = YogaNodeFactory.create();
                element.setYogaNode(childNode);
            }
            childNode.setData(child);
            childNode.setMeasureFunction(new ViewMeasureFunction());
        }

        final ViewGroup.LayoutParams lp = (ViewGroup.LayoutParams) child.getLayoutParams();
        applyLayoutParams(lp, childNode, child);

        getYogaNode().addChildAt(childNode, index);
    }
 
    public void clearMeasureFunction() {
        getYogaNode().setMeasureFunction(null);
    }

    /**
     * Wrapper around measure function for yoga leaves.
     */
    public static class ViewMeasureFunction implements YogaMeasureFunction {

        /**
         * A function to measure leaves of the Yoga tree.  Yoga needs some way to know how large
         * elements want to be.  This function passes that question directly through to the relevant
         * {@code View}'s measure function.
         *
         * @param node The yoga node to measure
         * @param width The suggested width from the owner
         * @param widthMode The type of suggestion for the width
         * @param height The suggested height from the owner
         * @param heightMode The type of suggestion for the height
         * @return A measurement output ({@code YogaMeasureOutput}) for the node
         */
        public long measure(
                YogaNode node,
                float width,
                YogaMeasureMode widthMode,
                float height,
                YogaMeasureMode heightMode) {
            final View view = (View) node.getData();
            if (view == null || view instanceof YogaViewGroup) {
                return YogaMeasureOutput.make(0, 0);
            }

            final int widthMeasureSpec = View.MeasureSpec.makeMeasureSpec(
                    (int) width,
                    viewMeasureSpecFromYogaMeasureMode(widthMode));
            final int heightMeasureSpec = View.MeasureSpec.makeMeasureSpec(
                    (int) height,
                    viewMeasureSpecFromYogaMeasureMode(heightMode));

            view.measure(widthMeasureSpec, heightMeasureSpec);

            return YogaMeasureOutput.make(view.getMeasuredWidth(), view.getMeasuredHeight());
        }

        private int viewMeasureSpecFromYogaMeasureMode(YogaMeasureMode mode) {
            if (mode == YogaMeasureMode.AT_MOST) {
                return View.MeasureSpec.AT_MOST;
            } else if (mode == YogaMeasureMode.EXACTLY) {
                return View.MeasureSpec.EXACTLY;
            } else {
                return View.MeasureSpec.UNSPECIFIED;
            }
        }
    }
}
