//
// emergency_stopper.c
//

#include "emergency_stopper.h"

static const sensor_port_t emergency_stopper_sensor_port = EV3_PORT_2;
static const sensor_type_t emergency_stopper_sensor_type = TOUCH_SENSOR;

void emergency_stopper_init(void) {
  ev3_sensor_config(emergency_stopper_sensor_port, emergency_stopper_sensor_type);
}

bool emergency_stopper_is_pushed(void) {
  return ev3_touch_sensor_is_pressed(emergency_stopper_sensor_port);
}
