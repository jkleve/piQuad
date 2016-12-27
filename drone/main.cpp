#include <unistd.h>
#include "manager.h"
#include "pi_types.h"



int main() {
    Manager manager;

    manager.initialize();

    manager.run();

    return 0;
}
