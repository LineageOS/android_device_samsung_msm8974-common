LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS

include $(CLEAR_VARS)
LOCAL_MODULE            := init.recovery.qcom.rc
LOCAL_MODULE_TAGS       := optional eng
LOCAL_MODULE_CLASS      := ETC
LOCAL_SRC_FILES         := init.recovery.qcom.rc
LOCAL_MODULE_PATH       := $(TARGET_RECOVERY_ROOT_OUT)
include $(BUILD_PREBUILT)
