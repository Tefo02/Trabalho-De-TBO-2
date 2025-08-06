#pragma once

#include "StringUtils.hpp"
#include <string>
#include <vector>

class ValidatePhone {
private:
  std::vector<std::string> phoneNumbers;

  bool isPhoneNumber(const std::string &potentialPhone) const {
    std::string sanitizedNumber;
    for (char c : potentialPhone) {
      if (StringUtils::isNumeric(c)) {
        sanitizedNumber += c;
      }
    }

    size_t len = sanitizedNumber.length();
    if (len == 10 || len == 11) {
      return true;
    }

    return false;
  }

public:
  ValidatePhone() = default;
  ~ValidatePhone() = default;

  const std::vector<std::string> &getPhoneNumbers() const {
    return phoneNumbers;
  }

  void search(const std::string &dataBase) {
    for (size_t i = 0; i < dataBase.length(); ++i) {
      if (dataBase[i] == '(' || StringUtils::isNumeric(dataBase[i])) {

        size_t start = i;
        size_t end = i;

        while (end < dataBase.length() - 1) {
          char nextChar = dataBase[end + 1];
          if (StringUtils::isNumeric(nextChar) || nextChar == ')' ||
              nextChar == '-' || nextChar == ' ') {
            end++;
          } else {
            break;
          }
        }

        std::string potentialPhone = dataBase.substr(start, end - start + 1);

        if (isPhoneNumber(potentialPhone)) {
          bool exists = false;
          for (const std::string &p : phoneNumbers) {
            if (p == potentialPhone) {
              exists = true;
              break;
            }
          }
          if (!exists) {
            phoneNumbers.push_back(potentialPhone);
          }
          i = end;
        }
      }
    }
  }
};