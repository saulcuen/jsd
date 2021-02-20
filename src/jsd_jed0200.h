#ifndef JSD_JED0200_H
#define JSD_JED0200_H

#ifdef __cplusplus
extern "C" {
#endif

#include "jsd/jsd_jed0200_pub.h"

/**
 * @brief TxPDO struct used to read device data in SOEM IOmap
 *
 * Note: Struct order matters and must be packed.
 */
typedef struct __attribute__((__packed__)) {
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
} jsd_jed0200_txpdo_t;

/**
 * @brief RxPDO struct used to command the device via SOEM IOmap
 *
 * Note: Struct order matters and must be packed.
 */
typedef struct __attribute__((__packed__)) {
  uint32_t cmd;
} jsd_jed0200_rxpdo_t;

/** @brief Initializes jed0200 and registers the PO2SO function
 *
 * @param self pointer JSD context
 * @param slave_id index of device on EtherCAT bus
 * @return true on success, false on failure
 */
bool jsd_jed0200_init(jsd_t* self, uint16_t slave_id);

/**
 * @brief Configuration function called by SOEM upon a PreOp to SafeOp state
 * transition that (re)configures JED device settings
 *
 * @param ecx_context SOEM context pointer
 * @param slave_id index of device on EtherCAT bus
 * @return 1 on success, 0 on failure
 */
int jsd_jed0200_PO2SO_config(ecx_contextt* ecx_context, uint16_t slave_id);

#ifdef __cplusplus
}
#endif

#endif