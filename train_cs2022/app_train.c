#include "app_train.h"

typedef enum {
    TR_INIT,
    TR_EXIT,
    TR_WAIT_FOR_DEPARTURE1, // 運転開始待ち1
    TR_WAIT_FOR_DEPARTURE2, // 運転開始待ち2
    TR_FORWARDING,          // 進行中
    TR_STOP,                // 停止中
    TNUM_TRAIN_STATE
} train_state;

// 状態名表示用の文字列配列
static char* state_msg[TNUM_TRAIN_STATE] = {
    "INIT", "EXIT", "W_F_DEP1","W_F_DEP2",
    "FORWARDING", "SLOW_DOWN", "STOP"
};

static train_state tr_state = TR_INIT;
static bool tr_is_entry = true;

void train_init(void) {
    drive_unit_init();
    signal_reader_init();
    operation_switch_init();
    tr_state = TR_INIT;
    tr_is_entry = true;
}

void train_run(void) {
    if( tr_is_entry ) {
        msg_f(state_msg[tr_state], 2);
    }

    switch( tr_state ) {
    case TR_INIT:
        if(tr_is_entry) {
            train_init();
            tr_is_entry = false;
        }
        if(true) {
            tr_state = TR_WAIT_FOR_DEPARTURE1;
            tr_is_entry = true;
        }
        if(tr_is_entry) {
        }
        break;
            if(tr_is_entry) {
      tr_is_entry = false;
      train_init();
      timer_start(300 * 1000);
    }
    // doの処理はない
    if(timer_is_timedout()) {
      tr_state = TRAIN_状態1;
      tr_is_entry = true;
    }
    if(tr_is_entry) {
      timer_stop();
    }
    break;

    case TR_WAIT_FOR_DEPARTURE1:
        ENTRY
            status_indicator_indicate(SI_STAND_BY);
            horn_warning();
        DO
        EVTCHK(operation_switch_is_pushed(),TR_WAIT_FOR_DEPARTURE2)
        EXIT
        END
        break;
    case TR_WAIT_FOR_DEPARTURE2:
        ENTRY
        DO
        EVTCHK((!operation_switch_is_pushed()),TR_FORWARDING)
        EXIT
        END
        break;
    case TR_FORWARDING:
        ENTRY
            status_indicator_indicate(SI_NORMAL_FORWADING);
            horn_confirmation();
            drive_unit_set_power(DRIVE_UNIT_POWER);
            drive_unit_forward();
        DO
        EVTCHK(train_signal_is_slow_down(),TR_SLOW_DOWN)
        EVTCHK(train_signal_is_stop(),TR_STOP)
        EVTCHK(operation_switch_is_pushed(),TR_EXIT)
        EXIT
        END
        break;
    case TR_SLOW_DOWN:
        ENTRY
            status_indicator_indicate(SI_SLOW_FORWARDING);
            drive_unit_set_power(DRIVE_UNIT_SLOW_POWER);
            drive_unit_forward();
            horn_warning();
        DO
        EVTCHK(train_signal_is_stop(),TR_STOP)
        EVTCHK(train_signal_is_departure(),TR_FORWARDING)
        EVTCHK(operation_switch_is_pushed(),TR_EXIT)
        EXIT
        END
        break;
    case TR_STOP:
        ENTRY
            drive_unit_stop();
            status_indicator_indicate(SI_STOPPING);
            horn_arrived();
        DO
        EVTCHK(train_signal_is_departure(),TR_FORWARDING)
        EVTCHK(operation_switch_is_pushed(),TR_EXIT)
        EXIT
        END
        break;
    case TR_EXIT:
        ENTRY
            drive_unit_stop();
            status_indicator_indicate(SI_OPERATION_END);
            horn_warning();
        DO
        EXIT
        END
        break;
    default:
    case TNUM_TRAIN_STATE:
        break;
    }
}
