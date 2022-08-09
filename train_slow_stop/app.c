#include "app.h"
#include "train_slow_stop.h"

void cyc0(intptr_t exinf) {
    act_tsk(MAIN_TASK);
}

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("train_slow_stop");
    is_initialized = true;
    }

    train_run();
    ext_tsk();
}
