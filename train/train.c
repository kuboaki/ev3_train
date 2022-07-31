//
// train.c
//

#include "train.h"

typedef enum {
  TR_INIT,
  TR_EXIT,
  TR_WAIT_FOR_DEPARTURE,
  TR_FORWARDING,
  TR_STOP,
} train_state;

static train_state tr_state = TR_INIT;
static bool tr_is_entry = true;


#define ENTRY if(tr_is_entry){tr_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){tr_state=(s);tr_is_entry=true;}
#define EXIT }if(tr_is_entry){
#define END }

void train_init(void) {
  drive_unit_init();
  signal_reader_init();
  emergency_stopper_init();
  tr_state = TR_INIT;
  tr_is_entry = true;
  ev3_led_set_color(LED_ORANGE);
}

bool train_signal_is_stop(void) {
  return signal_reader_get_signal() == SIGNAL_STOP;
}

bool train_signal_is_departure(void) {
  return signal_reader_get_signal() == SIGNAL_DEPARTURE;
}

void train_run(void) {
  num_f( tr_state, 2 );
  switch( tr_state ) {
  case TR_INIT:
    ENTRY
    train_init();
    DO
      EVTCHK(true,TR_WAIT_FOR_DEPARTURE);
    EXIT
    END
    break;
  case TR_WAIT_FOR_DEPARTURE:
    ENTRY
      horn_warning();
      timer_start( 3000 * 1000U );
    DO
      EVTCHK(timer_is_timedout(),TR_FORWARDING);
    EXIT
      timer_stop();
    END
    break;
  case TR_FORWARDING:
    ENTRY
      ev3_led_set_color(LED_GREEN);
      horn_confirmation();
    DO
      drive_unit_forward();
      EVTCHK(train_signal_is_stop(),TR_STOP);
      EVTCHK(emergency_stopper_is_pushed(),TR_EXIT);    
    EXIT
      drive_unit_stop();
    END
    break;
  case TR_STOP:
    ENTRY
      ev3_led_set_color(LED_RED);      
      horn_arrived();
    DO
      EVTCHK(train_signal_is_departure(),TR_FORWARDING);
      EVTCHK(emergency_stopper_is_pushed(),TR_EXIT);
    EXIT
      timer_stop();
    END
    break;
  case TR_EXIT:
    ENTRY
      drive_unit_stop();
      ev3_led_set_color(LED_ORANGE);      
      msg_f("exit.", 1);
      horn_warning();
    DO
    EXIT
    END
    break;
  }
}
