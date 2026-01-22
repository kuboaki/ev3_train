#ifndef UNIT_TIMER_H_
#define UNIT_TIMER_H_

// User Timer

#include "ev3api.h"
#include "stdbool.h"

extern void timer_start(int delay_ms);
extern void timer_stop(void);
extern int timer_is_started(void);
extern int timer_is_timedout(void);

#endif  // UNIT_TIMER_H_
