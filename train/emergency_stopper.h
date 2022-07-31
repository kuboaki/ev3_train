#ifndef EMERGENCY_STOPPER_H_
#define EMERGENCY_STOPPER_H_
//
// emergency_stopper.h
//

#include "ev3api.h"
#include "stdbool.h"

extern void emergency_stopper_init(void);
extern bool emergency_stopper_is_pushed(void);

#endif // EMERGENCY_STOPPER_H_
