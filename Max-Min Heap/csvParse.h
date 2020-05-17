#ifndef MM14_DS__CSVPARSE_H_
#define MM14_DS__CSVPARSE_H_
#include <vector>
#include <string>
#include <sstream>

 /**
  * Parses a string in CSV format, casting each value into an integer.
  * @param line the line we'll parse
  * @return returns a vector of ints from the parsed line
  */
 inline std::vector<int> parseCSVLine(const std::string& line) {
  std::vector<int> result;
  std::stringstream lineStream(line);
  std::string currentElement;
  while (std::getline(lineStream,currentElement,','))
    result.push_back(std::stoi(currentElement));
  return result;
}

#endif //MM14_DS__CSVPARSE_H_
