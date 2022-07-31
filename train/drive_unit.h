#ifndef DRIVE_UNIT_H_
#define DRIVE_UNIT_H_
//
//  drive_unit.h
//

#include "ev3api.h"

extern void drive_unit_init(void);
extern void drive_unit_set_power(int power);
extern void drive_unit_stop(void);
extern void drive_unit_forward(void);
extern void drive_unit_back(void);

#endif

