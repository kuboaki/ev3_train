#include "unit_operation_switch.h"

static const sensor_port_t operation_switch_sensor_port = EV3_PORT_2;
static const sensor_type_t operation_switch_sensor_type = TOUCH_SENSOR;

void operation_switch_init(void) {
    ev3_sensor_config(operation_switch_sensor_port, operation_switch_sensor_type);
}

bool operation_switch_is_pushed(void) {
    return ev3_touch_sensor_is_pressed(operation_switch_sensor_port);
}
