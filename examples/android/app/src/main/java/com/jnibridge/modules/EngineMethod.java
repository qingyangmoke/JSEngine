package com.jnibridge.modules;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
@interface EngineMethod {
    public String name();
}
