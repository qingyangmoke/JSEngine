LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := jsengine_bridge
LOCAL_SRC_FILES :=  ./libs/$(TARGET_ARCH_ABI)/libjsengine_bridge.so
LOCAL_EXPORT_C_INCLUDES := jni
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_SHARED_LIBRARIES := jsengine_bridge
LOCAL_MODULE := MyBridgeJNI
LOCAL_SRC_FILES := MyBridge.cpp
include $(BUILD_SHARED_LIBRARY)

# TARGET_CPU_API := armeabi
APP_ABI := arm64-v8a armeabi-v7a x86_64