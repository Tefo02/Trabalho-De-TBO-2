#pragma once

#include <fstream>
#include <sstream>
#include <string>

class FileReader {
public:
  static bool readAllText(const std::string &filename, std::string &content) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();

    return true;
  }
};