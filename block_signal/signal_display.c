//
//  signal_display.c
//

#include "signal_display.h"

typedef enum _signal_display_state {
  SD_INIT,
  SD_STOP_OR_DEP,       /* 信号現示中 */
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

static const sensor_port_t rotate_checker_sensor_port = EV3_PORT_2;
static const sensor_type_t rotate_checker_sensor_type = TOUCH_SENSOR;

#define SIGNAL_DISPLAY_ROTATE_POWER 10
int signal_display_power = SIGNAL_DISPLAY_ROTATE_POWER;

static const motor_port_t signal_display_motor_port = EV3_PORT_A;
static const motor_type_t signal_display_motor_type = LARGE_MOTOR;

signal_type_t signal_display_current_signal = SIGNAL_STOP;
signal_type_t signal_display_signal_saved = SIGNAL_NONE;

// モーターの回転位置を初期化し、そこで手動でパレットを動かして合わせる
void signal_display_init(void) {
  ev3_sensor_config(rotate_checker_sensor_port, rotate_checker_sensor_type);
  ev3_motor_config(signal_display_motor_port, signal_display_motor_type);
  ev3_motor_reset_counts(signal_display_motor_port);
  signal_display_current_signal = SIGNAL_STOP;
  ev3_led_set_color(LED_ORANGE);
}

signal_type_t signal_display_get_current(void) {
  return signal_display_current_signal;
}

bool signal_display_is_changed(void) {
  return signal_display_current_signal
           != signal_display_signal_saved; 
}

void signal_display_set_stop(void) {
  signal_display_current_signal = SIGNAL_STOP;
  signal_display_signal_saved = SIGNAL_NONE;
  ev3_led_set_color(LED_RED);
}

void signal_display_set_departure(void) {
  signal_display_current_signal = SIGNAL_DEPARTURE;
  signal_display_signal_saved = SIGNAL_NONE; 
  ev3_led_set_color(LED_GREEN);      
}

bool signal_display_rotating(void) {
  return ev3_touch_sensor_is_pressed(
    rotate_checker_sensor_port);
}

bool signal_display_rotated(void) {
  return !ev3_touch_sensor_is_pressed(
    rotate_checker_sensor_port);
}

static char buf[50] = {0};

void signal_display_run(void) {
  const int duration = 100U * 1000U;
  sprintf(buf, "s:%d,c:%d,o:%d,t:%d",
          sd_state,
          signal_display_current_signal,
          signal_display_signal_saved,
          ev3_touch_sensor_is_pressed(
            rotate_checker_sensor_port)
          );
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


