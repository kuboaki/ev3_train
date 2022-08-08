//
//  rotator.c
//

#include "rotator.h""

typedef enum _rotator_state {
    RS_INIT,
    RS_ROTATING_CHECKER_OFF,    // checkerがOFFで回転中
    RS_ROTATING_CHRCKER_ON,     // checkerがONで回転中
    RS_STOP                     // 停止中
} rotator_state;

static rotator_state rs_state = RS_INIT;
static bool rs_is_entry = true;

#define ENTRY if(rs_is_entry){rs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){rs_state=(s);rs_is_entry=true;}
#define EXIT }if(rs_is_entry){
#define END }

#define ROTATOR_POWER 10
int rotator_power = ROTATOR_POWER;

static const motor_port_t motor_port = EV3_PORT_A;
static const motor_type_t motor_type = LARGE_MOTOR;

static const sensor_port_t checker_port = EV3_PORT_2;
static const sensor_type_t checker_type = TOUCH_SENSOR;

static bool rotator_rotate_op = false;

void rotator_init(void) {
    ev3_sensor_config(checker_port, checker_type);
    ev3_motor_config(motor_port, motor_type);
    ev3_led_set_color(LED_ORANGE);
    rotator_rotate_op = false;
}

void rotator_rotate(void) {
    rotator_rotate_op = true;
}

bool rotator_is_rotating(void) {
    return rs_state!=RS_STOP;
}

void rotator_run(void) {
    switch( sd_state ) {
    case SD_INIT:
        ENTRY
            rotator_init();
        DO
        EVTCHK(true, RS_CHECKER_OFF);
        EXIT
        END
        break;
    case RS_ROTATING_CHECKER_OFF:
        ENTRY
            ev3_motor_set_power(rotator_port, rotator_power);
        DO
        EVTCHK(checker_is_pushed(),RS_CHECKER_ON);
        EXIT
        END
        break;
    case RS_ROTATING_CHRCKER_ON:
        ENTRY
            ev3_motor_set_power(rotator_port, rotator_power);
        DO
        EVTCHK((!checker_is_pushed()),RS_STOP);
        EXIT
        END
        break;
    case RS_STOP:
        ENTRY
            ev3_motor_stop(rotator_port, true);
        DO
        EVTCHK(rotator_rotate_op,RS_ROTATING_CHECKER_OFF);
        EXIT
            rotator_rotate_op = false;
        END
        break;
    }
}
