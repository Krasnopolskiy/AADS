#include "lib/controllers/controller.h"

int main() {
    Controller *c = controllerInit();
    controllerRun(c);
    return 0;
}
