#include "unit_status_indicator.h"

void status_indicator_indicate(status_indicator_t sts) {
    ledcolor_t led = LED_OFF;
    switch(sts) {
        break;
    case SI_NORMAL_FORWADING:      // 前進中
        led = LED_GREEN;
        break;
    case SI_SLOW_FORWARDING:       // 前進中
        led = LED_ORANGE;
        break;
    case SI_STOPPING:              // 停止中
        led = LED_RED;
        break;
    case SI_STAND_BY:              // 運転待ち
    case SI_OPERATION_END:         // 運転終了
    default:
        led = LED_OFF;
    }
    ev3_led_set_color(led);
}
