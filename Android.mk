LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_C_INCLUDES += \
       $(LOCAL_PATH)/include/ \

LOCAL_STATIC_LIBRARIES := libc \


LOCAL_MODULE_NAME = libpw_encrypt
LOCAL_MODULE    := $(LOCAL_MODULE_NAME)
#LOCAL_FORCE_STATIC_EXECUTABLE := true

LOCAL_SRC_FILES := pw_encrypt.c \
	pw_encrypt_sha.c \
	utils.c \
	hash_md5_sha.c

LOCAL_CFLAGS += -Wno-int-conversion -Wno-implicit-function-declaration

#include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)
include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)


LOCAL_C_INCLUDES += \
       $(LOCAL_PATH)/include/ \

LOCAL_STATIC_LIBRARIES := libpw_encrypt

LOCAL_SHARED_LIBRARIES += \
        libcutils \
        libutils \

         
LOCAL_LDLIBS :=  -llog

LOCAL_MODULE_NAME = mycrypt
LOCAL_MODULE    := $(LOCAL_MODULE_NAME)
LOCAL_FORCE_STATIC_EXECUTABLE := true

LOCAL_SRC_FILES := mycrypt.c
#LOCAL_CFLAGS += -Wall

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)
#include $(BUILD_STATIC_LIBRARY)
