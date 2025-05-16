#ifndef STATUS_INDICATOR_H_
#define STATUS_INDICATOR_H_
//
// status_indicator.h
//

#include "ev3api.h"

// 運転状況表示の種類
typedef enum _status_indicator_t {
    SI_STAND_BY = 0,         // 運転待ち
    SI_NORMAL_FORWADING = 1, // 前進中
    SI_SLOW_FORWARDING = 2,  // 前進中
    SI_STOPPING = 3,         // 停止中
    SI_OPERATION_END = 4,    // 運転終了
    TNUM_STATUS_INDICATOR
} status_indicator_t;

extern void status_indicator_indicate(status_indicator_t sts);

#endif // STATUS_INDICATOR_H_
