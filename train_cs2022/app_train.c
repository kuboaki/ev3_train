#include "app_train.h"

typedef enum {
    TR_INIT,
    TR_EXIT,
    TR_WAIT_FOR_DEPARTURE1, // 運転開始待ち1
    TR_WAIT_FOR_DEPARTURE2, // 運転開始待ち2
    TR_FORWARDING,          // 進行中
    TR_STOPPING,            // 停止中
    TNUM_TRAIN_STATE
} train_state;

// 状態名表示用の文字列配列
static char* state_msg[TNUM_TRAIN_STATE] = {
    "INIT", "EXIT", "W_F_DEP1","W_F_DEP2",
    "FORWARDING", "STOPPING"
};

static train_state tr_state = TR_INIT;
static bool tr_is_entry = true;

void train_init(void) {
    init_f("train");
    tr_state = TR_INIT;
    tr_is_entry = true;
    drive_unit_init();
    signal_reader_init();
    operation_switch_init();
}

void train_run(void) {
    if( tr_is_entry ) {
        // 現在の状態が変わったときは状態名を表示する
        msg_f(state_msg[tr_state], 2);
    }

    switch( tr_state ) {
    case TR_INIT:
        if(tr_is_entry) {
            tr_is_entry = false;
            train_init();
            timer_start(300 * 1000);
        }
        if(timer_is_timedout()) {
            tr_state = TR_WAIT_FOR_DEPARTURE1;
            tr_is_entry = true;
        }
        if(tr_is_entry) {
            timer_stop();
        }
        break;
    case TR_WAIT_FOR_DEPARTURE1:
        if(tr_is_entry) {
            tr_is_entry = false;
        }
        if(operation_switch_is_pushed()) {
            tr_state = TR_WAIT_FOR_DEPARTURE2;
            tr_is_entry = true;
        }
        break;
    case TR_WAIT_FOR_DEPARTURE2:
        if(tr_is_entry) {
            tr_is_entry = false;
        }
        if(!operation_switch_is_pushed()) {
            tr_state = TR_FORWARDING;
            tr_is_entry = true;
        }
        break;
    case TR_FORWARDING:
        if(tr_is_entry) {
            tr_is_entry = false;
            drive_unit_forward();
        }
        if(signal_reader_is_stop()) {
            tr_state = TR_STOPPING;
            tr_is_entry = true;
        }
        break;
    case TR_STOPPING:
        if(tr_is_entry) {
            tr_is_entry = false;
            drive_unit_stop();
        }
        if(signal_reader_is_clear()) {
            tr_state = TR_FORWARDING;
            tr_is_entry = true;
        }
        break;
    case TR_EXIT:
        break;
    default:
    case TNUM_TRAIN_STATE:
        break;
    }
}
