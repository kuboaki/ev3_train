#include "app.h"
#include "train.h"

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("train");
    is_initialized = true;
    }

    train_run();
    ext_tsk();
}
