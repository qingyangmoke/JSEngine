package com.jnibridge.modules.dom;

public class DisplayUnit {
    public float value;
    public String unit;
    public static final String RPX = "rpx";
    public static final String PERCENT = "%";
    public static final String PX = "px";
    public void setPercent(float value) {
        this.value = value;
        unit = DisplayUnit.PERCENT;
    }
    public void setRPX(float value) {
        this.value = value;
        unit = DisplayUnit.RPX;
    }
    public void setPX(float value) {
        this.value = value;
        unit = DisplayUnit.PX;
    }
}
