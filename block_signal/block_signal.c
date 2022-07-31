//
// block_signal.c
//

#include "block_signal.h"

typedef enum _block_signal_state {
  BS_INIT,
  BS_STOP,
  BS_DEPARTURE
} block_signal_state;

static block_signal_state bs_state = BS_INIT ;
static bool bs_is_entry = true;

#define ENTRY if(bs_is_entry){bs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){bs_state=(s);bs_is_entry=true;}
#define EXIT }if(bs_is_entry){
#define END }

void block_signal_init(void) {
  // signal_display_init();
  manual_switch_init();
  train_detector_init();
  bs_state = BS_INIT;
  bs_is_entry = true;
}

void block_signal_run(void) {
  num_f( bs_state, 1 );
  switch( bs_state ) {
  case BS_INIT:
    ENTRY
      msg_f("state: INIT", 2);
      block_signal_init();
      horn_confirmation(); // 手動設定を促すため
    DO
      // 最初は、手動で停止にセットして、手動スイッチを押す
      EVTCHK(manual_switch_is_pushed(),BS_DEPARTURE); 
    EXIT
    END
    break;
  case BS_DEPARTURE:
    ENTRY
      signal_display_set_departure();
      msg_f("state: DEPARTURE", 2);
    DO
    // マニュアル操作を受け取った場合
    EVTCHK(manual_switch_is_pushed(),BS_STOP);
    // 列車が通過した場合
    EVTCHK(train_detector_is_detected(),BS_STOP);
    EXIT
    END
    break;
  case BS_STOP:
    ENTRY
      // horn_warning();
      signal_display_set_stop();
      msg_f("state: STOP", 2);
    DO
    // マニュアル操作を受け取った場合
    EVTCHK(manual_switch_is_pushed(),BS_DEPARTURE); 
    // 司令室から進行指示を受け取った場合
    // EVTCHK(司令室からの指示を受け取った(),BS_DEPARTURE); 
    EXIT
    END
    break;
  }
  // 信号表示部のステートマシンの実行
  signal_display_run();
}
