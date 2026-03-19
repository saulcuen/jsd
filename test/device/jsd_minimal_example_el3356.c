#include "jsd/jsd_pub.h"

// device includes as necessary by application
#include "jsd/jsd_el3356_pub.h"

int main() {
  jsd_t* jsd = jsd_alloc();

  // configure the EL3356 device
  uint16_t slave_id = 3;  // 2nd device on this particular bus

  jsd_slave_config_t my_config = {0};

  snprintf(my_config.name, JSD_NAME_LEN, "my_el3356_device");

  my_config.configuration_active = true;
  my_config.product_code         = JSD_EL3356_PRODUCT_CODE;
  //my_config.el3356.scale_factor  = 6.52965e-1;


  jsd_set_slave_config(jsd, slave_id, my_config);



  // Slave configuration must come before initialization
  if (!jsd_init(jsd, "enp6s0", 1)) {
    ERROR("Could not init jsd");
    return 0;
  }


  // saul
  float nominal_load = 3.0; //
  ecx_SDOwrite(&jsd->ecx_context, 3, 0x8000, 0x24, FALSE, sizeof(float), &nominal_load, EC_TIMEOUTSAFE);

  float sensitivity = 1.879; //
  ecx_SDOwrite(&jsd->ecx_context, 3, 0x8000, 0x23, FALSE, sizeof(float), &sensitivity, EC_TIMEOUTSAFE);


  MSG("tare");
  jsd_el3356_tare(jsd, 3);

  int i = 0;
  for (i = 0; i < 10000; ++i) {  // loop for 5 seconds

    // Process slaves, including PDO exchange
    jsd_read(jsd, EC_TIMEOUTRET);
    jsd_el3356_read(jsd, slave_id);
    jsd_write(jsd);

    // Extract device state to use in application
    //if (0 == i % 500) {  // only print out a few measurements in example

      const jsd_el3356_state_t* state = jsd_el3356_get_state(jsd, slave_id);

      MSG("Value: %d Scaled_value: %lf", state->value, state->scaled_value);

    //}

    // Naive ~1000 hz loop rate
    usleep(10000);
  }

  jsd_free(jsd);

  return 0;
}
