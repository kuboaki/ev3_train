#include "app.h"
#include "app_train.h"

void main_task(intptr_t unused) {
    train_run();
    ext_tsk();
}
