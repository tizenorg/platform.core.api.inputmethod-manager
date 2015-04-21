/*
 * Copyright (c) 2014-2015 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef __TIZEN_UIX_INPUTMETHOD_MANAGER_H__
#define __TIZEN_UIX_INPUTMETHOD_MANAGER_H__

/**
 * @file inputmethod_manager.h
 * @brief This file contains input method manager APIs for input method editor (IME) list and selector settings.
 */

#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_UIX_INPUTMETHOD_MANAGER_MODULE
 * @{
 */

/**
 * @brief Enumeration for input method manager function error
 *
 * @since_tizen 2.4
 */
typedef enum
{
    IME_MANAGER_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
    IME_MANAGER_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
    IME_MANAGER_ERROR_OPERATION_FAILED = TIZEN_ERROR_IME | 0x0004, /**< Operation failed */
} ime_manager_error_e;

/**
 * @brief Requests to open the installed IME list menu.
 *
 * @details This function provides the installed IME list menu for the IME developers who might want to open it to enable their IME.
 *
 * @since_tizen 2.4
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #IME_MANAGER_ERROR_NONE No error
 * @retval #IME_MANAGER_ERROR_OPERATION_FAILED Operation failed
 *
 * @see ime_manager_show_ime_selector
 */
EXPORT_API int ime_manager_show_ime_list(void);

/**
 * @brief Requests to open the IME selector menu.
 *
 * @details This function provides the IME selector menu for the IME or other application developers who might want to change the default IME.
 *
 * @since_tizen 2.4
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #IME_MANAGER_ERROR_NONE No error
 * @retval #IME_MANAGER_ERROR_OPERATION_FAILED Operation failed
 *
 * @see ime_manager_show_ime_list
 */
EXPORT_API int ime_manager_show_ime_selector(void);

/**
 * @brief Checks if the specific IME is enabled or disabled in the system keyboard setting.
 *
 * @details The IME developers can use this function to check their IME is enabled or not.
 *
 * @since_tizen 2.4
 *
 * @param[in] app_id The application ID of the IME
 * @param[out] enabled The On (enabled) and Off (disabled) state of the IME
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #IME_MANAGER_ERROR_NONE No error
 * @retval #IME_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #IME_MANAGER_ERROR_OPERATION_FAILED Operation failed
 *
 * @see ime_manager_show_ime_list
 */
EXPORT_API int ime_manager_is_ime_enabled(const char *app_id, bool *enabled);

/**
 * @brief Checks which IME is the current activated (selected) IME.
 *
 * @remarks @a app_id must be released using free().
 *
 * @since_tizen 2.4
 *
 * @param[out] app_id The application ID of the active IME
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #IME_MANAGER_ERROR_NONE No error
 * @retval #IME_MANAGER_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #IME_MANAGER_ERROR_OPERATION_FAILED Operation failed
 *
 * @see ime_manager_show_ime_selector
 */
EXPORT_API int ime_manager_get_active_ime(char **app_id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // __TIZEN_UIX_INPUTMETHOD_MANAGER_H__

