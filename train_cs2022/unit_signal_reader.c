#include "unit_signal_reader.h"

static const sensor_port_t signal_reader_sensor_port = EV3_PORT_1;
static const sensor_type_t signal_reader_sensor_type = COLOR_SENSOR;

void signal_reader_init(void) {
  ev3_sensor_config(signal_reader_sensor_port, signal_reader_sensor_type);
  dly_tsk(1000U * 1000U);
}

bool signal_reader_is_clear(void) {
    return signal_reader_get_signal() == SIGNAL_DEPARTURE;
}

bool signal_reader_is_stop(void) {
    return signal_reader_get_signal() != SIGNAL_DEPARTURE;
}

signal_type_t signal_reader_get_signal(void) {
    colorid_t color = COLOR_NONE;
    signal_type_t signal = SIGNAL_NONE;
    color = ev3_color_sensor_get_color(signal_reader_sensor_port);
    switch(color) {
    case COLOR_RED:
        signal = SIGNAL_STOP;
        break;
    case COLOR_GREEN:
        signal = SIGNAL_DEPARTURE;
        break;
    case COLOR_YELLOW:
        signal = SIGNAL_REDUCE;
        break;
    default:
        color = COLOR_NONE;
        signal = SIGNAL_NONE;
    }
    return signal;
}
