//
// block_signal.c
//

#include "block_signal.h"

typedef enum _block_signal_state {
    BS_INIT,
    BS_STOP_1,      // 停止表示へ変更中
    BS_STOP_2,      // 停止を現時中
    BS_DEPARTURE_1, // 進行表示へ変更中
    BS_DEPARTURE_2  // 進行を現時中
    TNUM_BLOCK_SIGNAL_STATE
} block_signal_state;

static char state_msg[TNUM_BLOCK_SIGNAL_STATE] = {
    "BS_INIT", "BS_STOP_1", "BS_STOP_2",
    "BS_DEPARTURE_1", "BS_DEPARTURE_2"
};

static block_signal_state bs_state = BS_INIT ;
static bool bs_is_entry = true;

#define ENTRY if(bs_is_entry){bs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){bs_state=(s);bs_is_entry=true;}
#define EXIT }if(bs_is_entry){
#define END }

bool signal_display_is_stop(void) {
    return signal_display_get_current() == SIGNAL_STOP;
}

bool signal_display_is_departure(void) {
    return signal_display_get_current() == SIGNAL_DEPARTURE;
}

void block_signal_init(void) {
  // signal_display_init(); // signal_displayのステートマシンで初期化する
  manual_switch_init();
  train_detector_init();
  horn_confirmation();
  bs_state = BS_INIT;
  bs_is_entry = true;
}

void block_signal_run(void) {
  msg_f((state_msg[bs_state], 1);
  switch( bs_state ) {
  case BS_INIT:
    ENTRY
      block_signal_init();
    DO
    EVTCHK(true,BS_STOP_1);
    EXIT
    END
    break;
  case BS_STOP_1:
    ENTRY
      signal_display_set_stop();
    DO
    EVTCHK(signal_display_is_stop(),BS_STOP_2):
    EXIT
    END
    break;
  case BS_STOP_2:
    ENTRY
    DO
    // マニュアル操作を受け取った場合
    EVTCHK(manual_switch_is_pushed(),BS_DEPARTURE_1);
    // 司令室から進行指示を受け取った場合
    // EVTCHK(司令室からの指示を受け取った(),BS_DEPARTURE_1);
    EXIT
    END
    break;
  case BS_DEPARTURE_1:
    ENTRY
      signal_display_set_departure();
    DO
    EVTCHK(signal_display_is_departure(),BS_DEPARTURE_2):
    END
    break;
  case BS_DEPARTURE_2:
    ENTRY
    DO
    // マニュアル操作を受け取った場合
    EVTCHK(manual_switch_is_pushed(),BS_STOP_1);
    // 列車が通過した場合
    EVTCHK(train_detector_is_detected(),BS_STOP_1);
    // 司令室から進行指示を受け取った場合
    // EVTCHK(司令室からの指示を受け取った(),BS_STOP_1);
    EXIT
    END
    break;
  }
  // 信号表示部のステートマシンの実行
  signal_display_run();
}
