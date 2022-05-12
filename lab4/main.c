#include "lib-balanced/views/view.h"
#include "lib-balanced/controllers/controller.h"
//#include "lib-balanced/models/node.h"

int main() {
    Controller *c = controllerInit();
    controllerRun(c);
//    Node *root = nodeInit(5, 5);
//    for (int i = 10; i < 20; i++)
//        root = nodeInsert(root, i, i);
    return 0;
}
