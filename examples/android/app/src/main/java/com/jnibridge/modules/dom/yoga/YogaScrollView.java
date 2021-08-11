package com.jnibridge.modules.dom.yoga;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ScrollView;

import com.facebook.yoga.YogaNode;
import com.facebook.yoga.android.VirtualYogaLayout;
import com.facebook.yoga.android.YogaLayout;

public class YogaScrollView extends ScrollView {
    private YogaNodeGroup _yogaNodeGroup;
    public YogaScrollView(Context context) {
        this(context, null, 0);
    }

    public YogaScrollView(Context context, YogaNode node) {
        this(context, null, 0, node);
    }

    public YogaScrollView(Context context, AttributeSet attrs) {
        this(context, attrs, 0, null);
    }

    public YogaScrollView(Context context, AttributeSet attrs, int defStyleAttr) {
        this(context, attrs, 0, null);
    }

    public YogaScrollView(Context context, AttributeSet attrs, int defStyleAttr, YogaNode node) {
        super(context, attrs, defStyleAttr);

        _yogaNodeGroup = new YogaNodeGroup(this, node, attrs);
    }


    public YogaNode getYogaNode() {
        return _yogaNodeGroup.getYogaNode();
    }

    @Override
    protected LayoutParams generateDefaultLayoutParams() {
        return new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT);
    }

    @Override
    protected ViewGroup.LayoutParams generateLayoutParams(ViewGroup.LayoutParams p) {
        return new ViewGroup.LayoutParams(p);
    }

    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        _yogaNodeGroup.onLayout(changed,l,t,r,b);
    }


    @Override
    public void removeView(View view) {
        _yogaNodeGroup.removeViewFromYogaTree(view, false);
        super.removeView(view);
    }

    @Override
    public void removeViewAt(int index) {
        _yogaNodeGroup.removeViewAt(index);
        super.removeViewAt(index);
    }

    @Override
    public void removeViewInLayout(View view) {
        _yogaNodeGroup.removeViewFromYogaTree(view, true);
        super.removeViewInLayout(view);
    }

    @Override
    public void removeViews(int start, int count) {
        _yogaNodeGroup.removeViews(start, count);
        super.removeViews(start, count);
    }

    @Override
    public void removeViewsInLayout(int start, int count) {
        _yogaNodeGroup.removeViewsInLayout(start, count);
        super.removeViewsInLayout(start, count);
    }

    @Override
    public void removeAllViews() {
        _yogaNodeGroup.removeAllViews();
        super.removeAllViews();
    }

    @Override
    public void removeAllViewsInLayout() {
        _yogaNodeGroup.removeAllViewsInLayout();
        super.removeAllViewsInLayout();
    }

    /**
     * Adds a child view with the specified layout parameters.
     *
     * In the typical View is added, this constructs a {@code YogaNode} for this child and applies all
     * the {@code yoga:*} attributes.  The Yoga node is added to the Yoga tree and the child is added
     * to this ViewGroup.
     *
     * If the child is a {@link YogaLayout} itself, we do not construct a new Yoga node for that
     * child, but use its root node instead.
     *
     * If the child is a {@link VirtualYogaLayout
    }, we also use its Yoga node, but we also instruct it
     * to transfer all of its children to this {@link YogaLayout} while preserving the Yoga tree (so
     * that the layout of its children is correct).  The {@link VirtualYogaLayout} is then not added
     * to the View hierarchy.
     *
     * <p><strong>Note:</strong> do not invoke this method from
     * {@code #draw(android.graphics.Canvas)}, {@code onDraw(android.graphics.Canvas)},
     * {@code #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
     *
     * @param child the child view to add
     * @param index the position at which to add the child or -1 to add last
     * @param params the layout parameters to set on the child
     */
    @Override
    public void addView(View child, int index, ViewGroup.LayoutParams params) {
        // Internal nodes (which this is now) cannot have measure functions
        _yogaNodeGroup.clearMeasureFunction();
        if(index == -1) {
            index = getChildCount();
        }

        super.addView(child, index, params);

        _yogaNodeGroup.addView(child, index, params);
    }

    /**
     * <p>Adds a child view. If no layout parameters are already set on the child, the
     * default parameters for this ViewGroup are set on the child.</p>
     *
     * <p><strong>Note:</strong> do not invoke this method from
     * {@link #draw(android.graphics.Canvas)}, {@link #onDraw(android.graphics.Canvas)},
     * {@link #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
     *
     * @param child the child view to add
     *
     * @see #generateDefaultLayoutParams()
     */
    public void addView(View child) {
        addView(child, -1);
    }

    /**
     * Adds a child view. If no layout parameters are already set on the child, the
     * default parameters for this ViewGroup are set on the child.
     *
     * <p><strong>Note:</strong> do not invoke this method from
     * {@link #draw(android.graphics.Canvas)}, {@link #onDraw(android.graphics.Canvas)},
     * {@link #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
     *
     * @param child the child view to add
     * @param index the position at which to add the child
     *
     * @see #generateDefaultLayoutParams()
     */
    public void addView(View child, int index) {
        if (child == null) {
            throw new IllegalArgumentException("Cannot add a null child view to a ViewGroup");
        }
        ViewGroup.LayoutParams params = child.getLayoutParams();
        if (params == null) {
            params = generateDefaultLayoutParams();
        }
        addView(child, index, params);
    }

    /**
     * Adds a child view with this ViewGroup's default layout parameters and the
     * specified width and height.
     *
     * <p><strong>Note:</strong> do not invoke this method from
     * {@link #draw(android.graphics.Canvas)}, {@link #onDraw(android.graphics.Canvas)},
     * {@link #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
     *
     * @param child the child view to add
     */
    public void addView(View child, int width, int height) {
        final ViewGroup.LayoutParams params = generateDefaultLayoutParams();
        params.width = width;
        params.height = height;
        addView(child, -1, params);
    }

    /**
     * Adds a child view with the specified layout parameters.
     *
     * <p><strong>Note:</strong> do not invoke this method from
     * {@link #draw(android.graphics.Canvas)}, {@link #onDraw(android.graphics.Canvas)},
     * {@link #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
     *
     * @param child the child view to add
     * @param params the layout parameters to set on the child
     */
    @Override
    public void addView(View child, ViewGroup.LayoutParams params) {
        addView(child, -1, params);
    }
}
