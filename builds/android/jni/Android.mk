LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libponic
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := engine/platforms/android/main.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
