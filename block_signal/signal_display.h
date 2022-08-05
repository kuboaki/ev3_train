#ifndef SIGNAL_DISPLAY_H_
#define SIGNAL_DISPLAY_H_
//
//  signal_display.h
//

#include "ev3api.h"
#include "stdbool.h"
#include "rotator.h""
#include "util.h"

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

extern void signal_display_init(void);
extern void signal_display_run(void);
extern void signal_display_set_departure(void);
extern void signal_display_set_stop(void);
extern signal_type_t signal_display_get_current(void);

#endif
