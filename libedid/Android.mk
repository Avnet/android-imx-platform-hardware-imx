# Copyright 2018 NXP.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(findstring imx, $(TARGET_BOARD_PLATFORM)), imx)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := Edid.cpp

LOCAL_C_INCLUDES += $(IMX_PATH)/libdrm-imx \
                    $(IMX_PATH)/libdrm-imx/include/drm

LOCAL_SHARED_LIBRARIES :=   \
    liblog                  \
    libcutils               \
    libutils                \
    libdrm_android

LOCAL_VENDOR_MODULE := true
LOCAL_MODULE := libedid
LOCAL_CFLAGS:= -DLOG_TAG=\"libedid\"

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
endif
