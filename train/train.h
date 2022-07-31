#ifndef TRAIN_H_
#define TRAIN_H_
//
// train.h
//

#include "ev3api.h"
#include "stdbool.h"

#include "util.h"
#include "timer.h"
#include "horn.h"
#include "drive_unit.h"
#include "signal_reader.h"
#include "emergency_stopper.h"

extern void train_init(void);
extern void train_run(void);

#endif // TRAIN_H_
