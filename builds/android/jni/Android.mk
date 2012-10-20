LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libponic
LOCAL_CFLAGS    := -Werror -D_DEBUG -g -rdynamic -Ijni/engine/
LOCAL_SRC_FILES := engine/platforms/android/main.cpp \
				   engine/platforms/android/Log.cpp
LOCAL_LDLIBS    := -llog -lGLESv2
APP_ABI         := armeabi armeabi-v7a

include $(BUILD_SHARED_LIBRARY)
