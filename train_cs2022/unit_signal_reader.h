#ifndef UNIT_SIGNAL_READER_H_
#define UNIT_SIGNAL_READER_H_
#include "ev3api.h"
#include "stdbool.h"

// 信号の種類
// 当座は進行と停止だけ
typedef enum _signal_type_t {
  SIGNAL_NONE = 0,     // 未定
  SIGNAL_STOP = 1,     // 停止
  SIGNAL_DEPARTURE = 2,// 進行
  SIGNAL_REDUCE = 3,   // 減速
  SIGNAL_CAUTION = 4,  // 注意
  SIGNAL_ALERT = 5,    // 警戒
  TNUM_SIGNAL
} signal_type_t;

extern void signal_reader_init(void);
extern signal_type_t signal_reader_get_signal(void);
extern bool signal_reader_is_clear(void);
extern bool signal_reader_is_stop(void);

#endif // UNIT_SIGNAL_READER_H_
