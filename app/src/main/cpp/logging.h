#pragma once

#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "LOG", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "LOG", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "LOG", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "LOG", __VA_ARGS__)

