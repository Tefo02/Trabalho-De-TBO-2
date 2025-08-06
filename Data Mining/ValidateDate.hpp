#pragma once

#include "StringUtils.hpp"
#include <string>
#include <vector>

class ValidateDate {
private:
  std::vector<std::string> dates;

  bool isDate(const std::string &potentialDate) const {
    if (potentialDate.length() != 10)
      return false;

    if (potentialDate[2] != '/' || potentialDate[5] != '/')
      return false;

    try {
      int day = std::stoi(potentialDate.substr(0, 2));
      int month = std::stoi(potentialDate.substr(3, 2));
      int year = std::stoi(potentialDate.substr(6, 4));

      if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
      }

      if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
      }

      if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap && day > 29) {
          return false;
        }
        if (!isLeap && day > 28) {
          return false;
        }
      }
      return true;
    } catch (...) {
      return false;
    }
  }

public:
  ValidateDate() = default;
  ~ValidateDate() = default;

  const std::vector<std::string> &getDates() const { return dates; }

  void search(const std::string &dataBase) {
    for (size_t i = 0;
         (i = StringUtils::findChar(dataBase, '/', i)) != std::string::npos;
         ++i) {
      if (i >= 2 && i <= dataBase.length() - 8) {
        size_t start = i - 2;
        size_t end = i + 7;
        std::string potentialDate = dataBase.substr(start, 10);

        if (isDate(potentialDate)) {
          bool exists = false;
          for (const std::string &d : dates) {
            if (d == potentialDate) {
              exists = true;
              break;
            }
          }
          if (!exists) {
            dates.push_back(potentialDate);
          }
          i = end;
        }
      }
    }
  }
};