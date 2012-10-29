# vim: expandtab

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libponic
LOCAL_CFLAGS    := -fno-exceptions -Werror \
                   -D_DEBUG -DANDROID -DPUGIXML_NO_EXCEPTIONS \
                   -g -rdynamic \
                   -Ijni/engine/
LOCAL_SRC_FILES := engine/platforms/android/main.cpp \
                   engine/platforms/android/Log.cpp \
                   engine/platforms/android/Graphics.cpp \
                   engine/thirdparty/pugixml-1.2/pugixml.cpp \
                   engine/platforms/common/ImageManager.cpp \
                   engine/platforms/common/Graphics.cpp \
                   engine/platforms/linux/ImageManager.cpp \
                   engine/thirdparty/tgaload/tgaload.c \
                   engine/System.cpp \
                   engine/misc/Utils.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
