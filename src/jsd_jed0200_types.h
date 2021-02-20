#ifndef JSD_JED0200_TYPES_H
#define JSD_JED0200_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "jsd/jsd_common_device_types.h"

#define JSD_JED0200_PRODUCT_CODE (uint32_t)0x00009252

/**
 * @brief configuration struct for JED0200 device initialization
 */
typedef struct {
  uint32_t initial_cmd;  ///< Initial cmd value
} jsd_jed0200_config_t;

/**
 * @brief state data for JED module
 */
typedef struct {
  uint32_t status;
  uint32_t ticks;
  uint32_t voltage_hv;
  uint32_t voltage_lv;
  uint32_t voltage_12v;
  uint32_t temp_ambient;
  uint32_t temp_actuator;
  uint32_t humidity;
  uint32_t pressure;
  uint32_t brake_current;
  uint32_t brake_cc_val;
  uint32_t cmd;
} jsd_jed0200_state_t;

#ifdef __cplusplus
}
#endif

#endif
