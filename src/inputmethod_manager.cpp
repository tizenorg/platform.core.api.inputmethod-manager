/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isf_control.h"
#include <dlog.h>
#include <unistd.h>
#include <privilege_checker_private.h>
#include <inputmethod_manager.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "INPUTMETHOD_MANAGER"

ime_manager_error_e _check_privilege()
{
    char uid[16];
    ime_manager_error_e ret = IME_MANAGER_ERROR_NONE;

    if (inputmethod_cynara_initialize() == false) {
        LOGE("inputmethod_cynara_initialize () == false");
        return IME_MANAGER_ERROR_PERMISSION_DENIED;
    }

    snprintf(uid, 16, "%d", getuid());
    if (check_privilege(uid, IME_MANAGER_PRIVILEGE) == false) {
        LOGE("check_privilege(uid, IME_MANAGER_PRIVILEGE) == false");
        LOGE("uid : %s.", uid);
        ret = IME_MANAGER_ERROR_PERMISSION_DENIED;
    }

    inputmethod_cynara_finish();

    return ret;
}

int ime_manager_show_ime_list(void)
{
    ime_manager_error_e retVal = IME_MANAGER_ERROR_NONE;

    retVal = _check_privilege();
    if (retVal != IME_MANAGER_ERROR_NONE) {
        LOGE("_check_privilege returned %d.", retVal);
        return retVal;
    }

    int ret = isf_control_show_ime_list();
    if (ret == 0) {
        return IME_MANAGER_ERROR_NONE;
    }
    else {
        LOGW("IME_MANAGER_ERROR_OPERATION_FAILED");
        return IME_MANAGER_ERROR_OPERATION_FAILED;
    }
}

int ime_manager_show_ime_selector(void)
{
    ime_manager_error_e retVal = IME_MANAGER_ERROR_NONE;

    retVal = _check_privilege();
    if (retVal != IME_MANAGER_ERROR_NONE) {
        LOGE("_check_privilege returned %d.", retVal);
        return retVal;
    }

    int ret = isf_control_show_ime_selector();
    if (ret == 0) {
        return IME_MANAGER_ERROR_NONE;
    }
    else {
        LOGW("IME_MANAGER_ERROR_OPERATION_FAILED");
        return IME_MANAGER_ERROR_OPERATION_FAILED;
    }
}

int ime_manager_is_ime_enabled(const char *app_id, bool *enabled)
{
    ime_manager_error_e retVal = IME_MANAGER_ERROR_NONE;

    retVal = _check_privilege();
    if (retVal != IME_MANAGER_ERROR_NONE) {
        LOGE("_check_privilege returned %d.", retVal);
        return retVal;
    }

    if (!app_id || !enabled) {
        LOGW("IME_MANAGER_ERROR_INVALID_PARAMETER");
        return IME_MANAGER_ERROR_INVALID_PARAMETER;
    }

    int ret = isf_control_is_ime_enabled(app_id, enabled);
    if (ret < 0) {
        LOGW("IME_MANAGER_ERROR_OPERATION_FAILED");
        return IME_MANAGER_ERROR_OPERATION_FAILED;
    }

    return IME_MANAGER_ERROR_NONE;
}

int ime_manager_get_active_ime(char **app_id)
{
    ime_manager_error_e retVal = IME_MANAGER_ERROR_NONE;

    retVal = _check_privilege();
    if (retVal != IME_MANAGER_ERROR_NONE) {
        LOGE("_check_privilege returned %d.", retVal);
        return retVal;
    }

    if (!app_id) {
        LOGW("IME_MANAGER_ERROR_INVALID_PARAMETER");
        return IME_MANAGER_ERROR_INVALID_PARAMETER;
    }

    int ret = isf_control_get_active_ime(app_id);
    if (ret < 0) {
        LOGW("IME_MANAGER_ERROR_OPERATION_FAILED");
        return IME_MANAGER_ERROR_OPERATION_FAILED;
    }

    return IME_MANAGER_ERROR_NONE;
}

int ime_manager_get_enabled_ime_count(void)
{
    ime_manager_error_e retVal = IME_MANAGER_ERROR_NONE;
    ime_info_s *ime_info = NULL;
    int i, enable_ime_count = 0, total_ime_count;

    retVal = _check_privilege();
    if (retVal != IME_MANAGER_ERROR_NONE) {
        set_last_result(IME_MANAGER_ERROR_PERMISSION_DENIED);
        LOGE("_check_privilege returned %d.", retVal);
        return enable_ime_count;
    }

    total_ime_count = isf_control_get_all_ime_info(&ime_info);
    if (ime_info) {
        for (i = 0; i < total_ime_count; i++) {
            if (ime_info[i].is_enabled)
                enable_ime_count++;
        }
        free(ime_info);
    }

    if (enable_ime_count == 0)
        set_last_result(IME_MANAGER_ERROR_OPERATION_FAILED);
    else
        set_last_result(IME_MANAGER_ERROR_NONE);

    return enable_ime_count;
}
