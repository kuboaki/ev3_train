#include "app.h"
#include "app_train.h"

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("train_slow_stop_cs");
        is_initialized = true;
    }

    train_run();
    ext_tsk();
}
