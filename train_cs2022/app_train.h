#ifndef APP_TRAIN_H_
#define APP_TRAIN_H_

#include "ev3api.h"
#include "stdbool.h"

#include "util.h"
#include "unit_timer.h"
#include "unit_horn.h"
#include "unit_drive_unit.h"
#include "unit_signal_reader.h"
#include "unit_operation_switch.h"
/* #include "unit_status_indicator.h" */

extern void train_init(void);
extern void train_run(void);

#endif // APP_TRAIN_H_
