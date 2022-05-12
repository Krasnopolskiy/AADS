#include "application/application.h"

Application *applicationInit() {
    Application *this = malloc(sizeof(Application));
    this->state = stopped;
    return this;
}

void applicationLoop(Application *this) {
    while (this->state == running) {
        int cmd = menuView();
        if (cmd == EXIT_COMMAND)
            this->state = stopped;
        else
            controllers[cmd](this->table);
    }
}

void applicationFree(Application *this) {
    tableFree(this->table);
    free(this);
}

void applicationExecute(Application *this) {
    this->state = running;
    applicationLoop(this);
    applicationFree(this);
}
