#ifndef MM14_DS__MENU_H_
#define MM14_DS__MENU_H_
#include <iostream>
#include <fstream>
#include "MaxMinHeap.h"
#include "csvParse.h"

class menu {
 public:
  menu(); // Constructor, defaults heapExists to false.
  void runMenu(); // Runs the menu object
 private:
  bool heapExists; // Flag that denotes whether we've created a heap already or not.
  MaxMinHeap* heap; // Pointer to the Heap structure.
  void printMenu(); // Prints the menu and selections.
  bool handleInput(int input); // Handles input based on the passed value.
  void handleFile(); // Handles reading an array from a file.
  void handleSTDin(); // Handles reading an array from stdin.
};

#endif //MM14_DS__MENU_H_
