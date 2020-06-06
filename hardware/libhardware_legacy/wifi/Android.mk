# Copyright 2006 The Android Open Source Project

ifdef WIFI_DRIVER_MODULE_PATH
LOCAL_CFLAGS += -DWIFI_DRIVER_MODULE_PATH=\"$(WIFI_DRIVER_MODULE_PATH)\"
endif
ifdef WIFI_DRIVER_MODULE_ARG
LOCAL_CFLAGS += -DWIFI_DRIVER_MODULE_ARG=\"$(WIFI_DRIVER_MODULE_ARG)\"
endif
ifdef WIFI_DRIVER_MODULE_NAME
LOCAL_CFLAGS += -DWIFI_DRIVER_MODULE_NAME=\"$(WIFI_DRIVER_MODULE_NAME)\"
endif
ifdef WIFI_FIRMWARE_LOADER
LOCAL_CFLAGS += -DWIFI_FIRMWARE_LOADER=\"$(WIFI_FIRMWARE_LOADER)\"
endif

ifeq ($(BOARD_WIFI_LIBRARIES),true)
#LOCAL_SHARED_LIBRARIES += libwifi
else
LOCAL_SHARED_LIBRARIES += libnetutils
LOCAL_SRC_FILES += wifi/wifi.c
LOCAL_MODULE:= libwifi

ifeq ($(DRIVER_BUILT_IN),true)
LOCAL_CFLAGS += -DBUILT_IN_MODULE
endif

endif
