#include "app.h"
#include "train.h"

void cyc0(intptr_t exinf) {
    act_tsk(MAIN_TASK);
}

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("train");
    is_initialized = true;
    }

    train_run();
    ext_tsk();
}
