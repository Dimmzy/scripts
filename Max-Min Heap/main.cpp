#include "menu.h"

/**
 * Runs the main program loop through the menu object
 */
void run() {
  menu* Menu = new menu();
  Menu->runMenu();
}

/**
 * Driver Function
 * @return 0 on successful program termination
 */
int main() {
    run();
    return 0;
}
