LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

target_hw_init_rc_file := $(TARGET_ROOT_OUT)/init.mini6410.rc
$(target_hw_init_rc_file) : $(LOCAL_PATH)/init.mini6410.rc | $(ACP)
	$(transform-prebuilt-to-target)
ALL_PREBUILT += $(target_hw_init_rc_file)

$(INSTALLED_RAMDISK_TARGET): $(target_init_rc_file) $(target_hw_init_rc_file) 
	
file := $(TARGET_OUT_KEYLAYOUT)/tuttle2.kl
ALL_PREBUILT += $(file)
$(file) : $(LOCAL_PATH)/tuttle2.kl | $(ACP)
	$(transform-prebuilt-to-target)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := tuttle2.kcm
include $(BUILD_KEY_CHAR_MAP)

PRODUCT_COPY_FILES += \
		$(LOCAL_PATH)/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
        $(LOCAL_PATH)/asound.conf:system/etc/asound.conf \
        $(LOCAL_PATH)/vold.conf:system/etc/vold.conf \

