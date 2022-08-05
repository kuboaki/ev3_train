//
//  signal_display.c
//

#include "signal_display.h"

typedef enum _signal_display_state {
    SD_INIT,
    SD_STOP,              /* 停止現示中 */
    SD_ROTATE1,           /* 回転1回目 */
    SD_WAIT_FOR_REL1,     /* 回転1回目完了待ち */
    SD_ROTATE2,           /* 回転2回目 */
    SD_WAIT_FOR_REL2,     /* 回転2回目完了待ち */
} signal_display_state;

static signal_display_state sd_state = SD_INIT ;
static bool sd_is_entry = true;

#define ENTRY if(sd_is_entry){sd_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){sd_state=(s);sd_is_entry=true;}
#define EXIT }if(sd_is_entry){
#define END }

#define SIGNAL_DISPLAY_ROTATE_POWER 10
int signal_display_power = SIGNAL_DISPLAY_ROTATE_POWER;


static const sensor_port_t reader_sensor_port = EV3_PORT_3;
static const sensor_type_t reader_sensor_type = COLOR_SENSOR;

// モーターの回転位置と信号の表示を初期化する
void signal_display_init(void) {
    ev3_sensor_config(checker_sensor_port, checker_sensor_type);
    ev3_sensor_config(reader_sensor_port, reader_sensor_type);
    ev3_motor_config(signal_display_motor_port, signal_display_motor_type);
    ev3_led_set_color(LED_ORANGE);
}

signal_type_t signal_display_get_current(void) {
    return ev3_color_sensor_get_color(checker_sensor_port);
}

void signal_display_set_stop(void) {
}

void signal_display_set_departure(void) {
}

bool signal_display_rotating(void) {
    return ev3_touch_sensor_is_pressed(checker_sensor_port);
}

bool signal_display_rotated(void) {
    return !ev3_touch_sensor_is_pressed(
        rotate_checker_sensor_port);
}

static char buf[50] = {0};

void signal_display_run(void) {
    sprintf(buf, "disp: s:%d, c:%d", sd_state,
            ev3_color_sensor_get_color(reader_sensor_port));
    msg_f(buf, 5);
    switch( sd_state ) {
    case SD_INIT:
        ENTRY
            signal_display_init();
        DO
        EVTCHK(true, SD_STOP_OR_DEP);
        EXIT
        END
        break;
    case SD_STOP_OR_DEP:    /* 信号現示中 */
        ENTRY
        DO
        EVTCHK(signal_display_is_changed(),SD_ROTATE1);
        EXIT
            END
            break;
    case SD_ROTATE1:           /* 回転1回目 */
        ENTRY
            ev3_motor_set_power(signal_display_motor_port,
                                signal_display_power);
        DO
        EVTCHK(signal_display_rotating(),SD_WAIT_FOR_REL1);
        EXIT
        END
        break;
    case SD_WAIT_FOR_REL1:     /* 回転1回目完了待ち */
        ENTRY
        DO
            EVTCHK(signal_display_rotated(),SD_ROTATE2);
        EXIT
        END
        break;
    case SD_ROTATE2:           /* 回転2回目 */
        ENTRY
        DO
        EVTCHK(signal_display_rotating(),SD_WAIT_FOR_REL2);
        EXIT
        END
        break;
    case SD_WAIT_FOR_REL2:     /* 回転2回目完了待ち */
        ENTRY
        DO
        EVTCHK(signal_display_rotated(),SD_STOP_OR_DEP);
        EXIT
            // dly_tsk(duration);
            ev3_motor_stop(signal_display_motor_port,true);
        END
        break;
    }
    signal_display_signal_saved = signal_display_current_signal;
}

/***
#define SIGNAL_DISPLAY_ROTATE_DEGREE 700
int signal_display_rotate_degree
    = SIGNAL_DISPLAY_ROTATE_DEGREE;
***/

/***
void signal_display_set_departure(void) {
  ev3_motor_rotate(
    signal_display_motor_port,
    signal_display_rotate_degree,
    signal_display_power, false);

  signal_display_current_signal = SIGNAL_DEPARTURE;
  msg_f("signal: DEPARTURE", 3);
}

void signal_display_set_stop(void) {
  ev3_motor_rotate(
    signal_display_motor_port,
    signal_display_rotate_degree,
    signal_display_power, false);
  signal_display_current_signal = SIGNAL_STOP;
  msg_f("signal: STOP", 3);
}
***/
