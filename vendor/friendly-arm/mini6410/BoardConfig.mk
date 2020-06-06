# config.mk
#
# Product-specific compile-time definitions.
#

# The generic product target doesn't have any hardware-specific pieces.
TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_CPU_ABI := armeabi

#audio
#HAVE_HTC_AUDIO_DRIVER := true
#BOARD_USES_GENERIC_AUDIO := true
BOARD_USES_ALSA_AUDIO := true
BUILD_WITH_ALSA_UTILS := true

#camera
BOARD_CAMERA_LIBRARIES := libcamera
BOARD_S3CJPEG_LIBRARIES := libs3cjpeg
#USE_CAMERA_STUB := true

#wifi
BOARD_WIFI_LIBRARIES := true
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
WPA_BUILD_SUPPLICANT := true
CONFIG_CTRL_IFACE := y
DRIVER_BUILT_IN := true

#GPS
BOARD_GPS_LIBRARIES :=libgps
