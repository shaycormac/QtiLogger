LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        zxlogger.cpp \
        configdata.cpp \
		kmsg.cpp \
		logcat.cpp \
		modem.cpp \
		net.cpp \
		dynamic.cpp \
		logcatcore.cpp \
		bugreport.cpp \
		qsee.cpp \
		tz.cpp \

# 模块的名称， 后期就可以通过 mmm zxlogger来单编
LOCAL_MODULE:= zxlogger
# 无论是在user，eng版本，都可以编译
LOCAL_MODULE_TAGS := optional
# 将被rc执行的脚本，是在vendor/下的脚本
LOCAL_INIT_RC := zxlogger.rc
# 表明这个必须在vendor 即高通供应商下面的目录中
LOCAL_PROPRIETARY_MODULE := true
# 依赖的静态库
LOCAL_STATIC_LIBRARIES += libcutils
# 依赖的动态库
LOCAL_SHARED_LIBRARIES := \
			liblog\
			libutils
# 最终输出一个可以执行的二进制文件
include $(BUILD_EXECUTABLE) 

include $(CLEAR_VARS)
LOCAL_MODULE := modemmask
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := modemmask.cfg
# 这个表示中转 临时文件生成的地方
LOCAL_MODULE_CLASS := ETC
# 后缀
LOCAL_MODULE_SUFFIX := .cfg
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := dynamic
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := dynamic.cfg
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_SUFFIX := .cfg
include $(BUILD_PREBUILT)

# 这个模块目的是拷贝蓝牙和boot启动的日志
include $(CLEAR_VARS)
LOCAL_MODULE := logcp
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := logcp.sh
LOCAL_MODULE_CLASS := ETC
# 这个位置表示最终安装位置，在out/product/类型/vendor/bin中
LOCAL_MODULE_PATH := $(PRODUCT_OUT)/vendor/bin
LOCAL_MODULE_SUFFIX := .sh
# 安装完后要对这个文件进行权限处理，方便后面可以执行
LOCAL_POST_INSTALL_CMD := \
        chmod 6755 $(LOCAL_MODULE_PATH)/$(LOCAL_SRC_FILES)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := modem
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := modem.sh
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(PRODUCT_OUT)/vendor/bin
LOCAL_MODULE_SUFFIX := .sh
LOCAL_POST_INSTALL_CMD := \
        chmod 6755 $(LOCAL_MODULE_PATH)/$(LOCAL_SRC_FILES)
include $(BUILD_PREBUILT)

# 自定义的tcp,为啥要自定义的？
include $(CLEAR_VARS)
LOCAL_MODULE := mytcpdump
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := mytcpdump
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(PRODUCT_OUT)/vendor/bin
LOCAL_POST_INSTALL_CMD := \
        chmod 6755 $(LOCAL_MODULE_PATH)/$(LOCAL_SRC_FILES)
include $(BUILD_PREBUILT)

