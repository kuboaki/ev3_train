#ifndef UNIT_DRIVE_UNIT_H_
#define UNIT_DRIVE_UNIT_H_

#include "ev3api.h"

#define DRIVE_UNIT_POWER 40
#define DRIVE_UNIT_SLOW_POWER 20

extern void drive_unit_init(void);
extern void drive_unit_forward(void);
extern void drive_unit_stop(void);

// extern void drive_unit_set_power(int power);
// extern void drive_unit_back(void);

#endif // UNIT_DRIVE_UNIT_H_
