# vim: expandtab

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libponic
LOCAL_CFLAGS    := -Werror -D_DEBUG -DANDROID -DPUGIXML_NO_EXCEPTIONS \
                   -g -rdynamic \
                   -Ijni/engine/
LOCAL_SRC_FILES := engine/platforms/android/main.cpp \
                   engine/platforms/android/Log.cpp \
                   engine/thirdparty/pugixml-1.2/pugixml.cpp \
                   engine/platforms/common/ImageManager.cpp \
                   engine/System.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
