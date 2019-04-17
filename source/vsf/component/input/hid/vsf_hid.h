/*****************************************************************************
 *   Copyright(C)2009-2019 by VSF Team                                       *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#ifndef __VSF_HID_H__
#define __VSF_HID_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/

#define HID_USAGE_PAGE_GENERIC      0x01
#define HID_USAGE_PAGE_KEYBOARD     0x07
#define HID_USAGE_PAGE_BUTTON       0x09

// HID_USAGE_PAGE_GENERIC (Generic Desktop Page)
#define HID_USAGE_ID_X              0x30
#define HID_USAGE_ID_Y              0x31
#define HID_USAGE_ID_Z              0x32
#define HID_USAGE_ID_Rx             0x33
#define HID_USAGE_ID_Ry             0x34
#define HID_USAGE_ID_Rz             0x35
#define HID_USAGE_ID_Slider         0x36
#define HID_USAGE_ID_Dial           0x37
#define HID_USAGE_ID_Wheel          0x38
#define HID_USAGE_ID_Hat            0x39

#define HID_USAGE_ID_GENERIC_MIN    HID_USAGE_ID_X
#define HID_USAGE_ID_GENERIC_MAX    HID_USAGE_ID_Hat

#define HID_USAGE_ID_KEYBOARD_MIN   0
#define HID_USAGE_ID_KEYBOARD_BITS  224
#define HID_USAGE_ID_KEYBOARD_MAX   255

#define HID_USAGE_ID_BUTTON_MIN     1
#define HID_USAGE_ID_BUTTON_MAX     32

#define HID_GENERIC_DESKTOP_UNDEFINEED              0
#define HID_GENERIC_DESKTOP_POINTER                 1
#define HID_GENERIC_DESKTOP_MOUSE                   2
#define HID_GENERIC_DESKTOP_JOYSTICK                4
#define HID_GENERIC_DESKTOP_GAMEPAD                 5
#define HID_GENERIC_DESKTOP_KEYBOARD                6
#define HID_GENERIC_DESKTOP_KEYPAD                  7
#define HID_GENERIC_DESKTOP_MULTIAXIS_CONTROLLER    8

/*============================ MACROFIED FUNCTIONS ===========================*/

#define HID_USAGE_IS_CONST(usage)   ((usage)->data_flag & 1)
#define HID_USAGE_IS_DATA(usage)    !HID_USAGE_IS_CONST(usage)
#define HID_USAGE_IS_VAR(usage)     ((usage)->data_flag & 2)
#define HID_USAGE_IS_ARRAY(usage)   !HID_USAGE_IS_VAR(usate)
#define HID_USAGE_IS_REL(usage)     ((usage)->data_flag & 4)
#define HID_USAGE_IS_ABS(usage)     !HID_USAGE_IS_REL(usage)

/*============================ TYPES =========================================*/

struct vsf_hid_usage_t {
    implement_ex(vsf_slist_node_t, usage_node)

    uint16_t usage_page;
    uint8_t usage_min;
    uint8_t usage_max;
    int32_t logical_min;
    int32_t logical_max;
    int32_t bit_offset;
    int32_t bit_length;
    int32_t report_size;
    int32_t report_count;
    uint32_t data_flag;
};
typedef struct vsf_hid_usage_t vsf_hid_usage_t;

struct vsf_hid_event_t {
    uint16_t usage_page;
    uint16_t usage_id;
    int32_t pre_value;
    int32_t cur_value;
    vsf_hid_usage_t *usage;
};
typedef struct vsf_hid_event_t vsf_hid_event_t;

struct vsf_hid_report_t {
    implement_ex(vsf_slist_node_t, report_node)

    uint8_t type;
    int16_t id;
    uint16_t bitlen;
    uint16_t generic_usage;

    uint8_t *value;
    vsf_slist_t usage_list;
};
typedef struct vsf_hid_report_t vsf_hid_report_t;

struct vsf_hid_dev_t {
    vsf_slist_t report_list;
    bool report_has_id;
};
typedef struct vsf_hid_dev_t vsf_hid_dev_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ PROTOTYPES ====================================*/

extern vsf_err_t vsf_hid_parse_report(vsf_hid_dev_t *dev, uint8_t *buf, uint_fast32_t len);
extern void vsf_hid_process_input(vsf_hid_dev_t *dev, uint8_t *buf, uint_fast32_t len);
extern uint_fast32_t vsf_hid_get_max_input_size(vsf_hid_dev_t *dev);
extern void vsf_hid_free_dev(vsf_hid_dev_t *dev);

#endif      // __VSF_HID_H__