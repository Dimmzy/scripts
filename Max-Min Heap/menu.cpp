#include "menu.h"

/**
 * Constructs the object. Defaults heapExist to false and creates a new instance of MaxMinHeap (uninitialized)
 */
menu::menu() {
  heapExists = false;
  heap = new MaxMinHeap();
}

/**
 * Runs the main menu loop until the stop flag is set.
 * Gets user input from stdin and passes it to the handleInput function for parsing and behavior.
 */
void menu::runMenu() {
  bool stop = false;
  int input;
  while (!stop) {
    printMenu();
    std::cin >> input;
    stop = handleInput(input);
  }
}

/**
 * Prints the menu in a neat format, depending on the value of the heapExists flag.
 */
void menu::printMenu() {
  if (!this->heapExists) {
    std::cout << "[*]Max-Min Heap Program[*]" << std::endl;
    std::cout << ">> Please enter the action to perform" << std::endl;
    std::cout << "[1] Build Heap" << std::endl;
    std::cout << "[0] Exit" << std::endl;
  } else {
    std::cout << ">> Please enter the action to perform" << std::endl;
    std::cout << "[1] Insert" << std::endl;
    std::cout << "[2] Delete" << std::endl;
    std::cout << "[3] Extract Min" << std::endl;
    std::cout << "[4] Extract Max" << std::endl;
    std::cout << "[5] Print Heap" << std::endl;
    std::cout << "[0] Exit" << std::endl;
  }
}

/**
 * Handles the input passed from the user
 * @param input the integer value the user passed (based on the selection menu)
 * @return a boolean expression to the stop menu flag
 */
bool menu::handleInput(int input) {
  if (!this->heapExists) { // Heap does not exist yet
    if (input == 1) { // Build Heap
      std::string ans;
      std::cout << ">> Would you like to load the array from a file? yes/no" << std::endl;
      std::cin >> ans;
      if (ans == "yes") // Loads the CSV from file
        handleFile();
      else // Loads from stdin
        handleSTDin();
      this->heapExists = true;
      return false; // Continue the menu loop
    } else if (input == 0) { // Send stop flag to menu
      std::cout << "Exiting..." << std::endl;
      return true;
    } else {
      std::cout << "Command not recognized, please enter a valid value (0 or 1)" << std::endl;
      return false;
    }
  } else { // Heap exists, extended menu
    int arg;
    switch (input) {
      /* Performs the function corresponding to the input the user passed */
      case 1: // Insert
        std::cout << ">> Please enter the key to insert:" << std::endl;
        std::cin >> arg;
        this->heap->heapInsert(arg);
        break;
      case 2: // Delete
        std::cout << ">> Please enter the index to delete: (Starting at 0)" << std::endl;
        std::cin >> arg;
        this->heap->heapDelete(arg);
        break;
      case 3: // Extract Min
        this->heap->heapExtractMin();
        break;
      case 4: // Extract Max
        this->heap->heapExtractMax();
        break;
      case 5: // Print Heap
        std::cout << "Printing heap:" << std::endl;
        this->heap->printHeap();
        break;
      case 0: // Exit
        std::cout << "Exiting..." << std::endl;
        return true;
      default: // All the rest
        std::cout << "Command not recognized, please enter a valid value (0-5)" << std::endl;
        break;
    }
    return false; // Keep the menu loop running
  }
}

/**
 * Handles array input from file.
 * Asks user for the file name to load from current directory, if unable to open tries to open input.txt.
 * If that fails as well, we'll ask for manual user input.
 */
void menu::handleFile() {
  std::string fName;
  std::cout << "Please enter a file name to load from CWD, default is input.txt" << std::endl;
  std::cout << "[*] File is a single line of comma separated values representing an array" << std::endl;
  std::cin >> fName;
  std::fstream file;
  file.open(fName,std::ios::in); // Tries to open the user specified file
  if (!file.is_open()) {
    std::cout << "Error reading from file, trying to default to input.txt" << std::endl;
    fName = "input.txt";
    file.open(fName,std::ios::in); // Tries to open input.txt
    if (!file.is_open()) {
      std::cout << "Couldn't open input.txt either, getting input from user" << std::endl;
      handleSTDin(); // Sends user to manual input if all else fails
      return;
    }
  }
  std::string line;
  getline(file,line);
  this->heap->buildHeap(parseCSVLine(line)); // Parses the CSV file and creates a Heap from the output.
  file.close();
  std::cout << "Max-Min Heap has been built!" << std::endl;
}

/**
 * Handles reading user input in a CSV one-line format.
 */
void menu::handleSTDin() {
  std::cout << "Please enter the array in the following CSV format:" << std::endl;
  std::cout << "<element1>,<element2>,...,<elementN>" << std::endl;
  std::string input;
  std::cin >> input;
  this->heap->buildHeap(parseCSVLine(input));
}
