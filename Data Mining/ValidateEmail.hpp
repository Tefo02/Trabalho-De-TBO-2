#pragma once

#include "StringUtils.hpp"
#include <string>
#include <vector>

class ValidateEmail {
private:
  std::vector<std::string> emails;

  bool isBeforeChar(char c) const {
    return StringUtils::isAlphanumeric(c) || c == '.' || c == '_' || c == '-';
  }
  bool isAfterChar(char c) const {
    return StringUtils::isAlphanumeric(c) || c == '.' || c == '-';
  }

  bool isEmail(const std::string &dataBase) const {
    size_t atPos = StringUtils::findChar(dataBase, '@');

    if (atPos == std::string::npos || atPos == 0 ||
        atPos == dataBase.length() - 1)
      return false;

    std::string beforePart = dataBase.substr(0, atPos);
    std::string afterPart = dataBase.substr(atPos + 1);

    if (beforePart.length() > 64 || afterPart.length() > 255)
      return false;
    if (beforePart.front() == '.' || beforePart.back() == '.')
      return false;

    for (size_t i = 0; i < beforePart.length(); ++i) {
      if (i > 0 && beforePart[i] == '.' && beforePart[i - 1] == '.')
        return false;
      if (!isBeforeChar(beforePart[i]))
        return false;
    }

    size_t dotPos = StringUtils::findChar(afterPart, '.');
    if (dotPos == std::string::npos || dotPos == 0 || afterPart.back() == '.')
      return false;

    for (size_t i = 0; i < afterPart.length(); ++i) {
      if (i > 0 && afterPart[i] == '.' && afterPart[i - 1] == '.')
        return false;
      if (!isAfterChar(afterPart[i]))
        return false;
    }
    return true;
  }

public:
  ValidateEmail() = default;
  ~ValidateEmail() = default;

  const std::vector<std::string> &getEmails() const { return emails; }

  void search(const std::string &dataBase) {

    for (size_t i = 0;
         (i = StringUtils::findChar(dataBase, '@', i)) != std::string::npos;
         ++i) {

      size_t start = StringUtils::findLastOf(dataBase, " \t\n\r", i);
      start = (start == std::string::npos) ? 0 : start + 1;

      size_t end = StringUtils::findFirstOf(dataBase, " \t\n\r", i);
      if (end == std::string::npos) {
        end = dataBase.length();
      }

      std::string possibleEmail = dataBase.substr(start, end - start);

      while (!possibleEmail.empty() &&
             (possibleEmail.back() == '.' || possibleEmail.back() == ',')) {
        possibleEmail.pop_back(); // remove o último caractere.
      }

      if (isEmail(possibleEmail)) {
        bool existingEmail = false;
        for (const std::string &emailExistente : emails) {
          if (emailExistente == possibleEmail) {
            existingEmail = true;
            break;
          }
        }
        if (!existingEmail) {
          emails.push_back(possibleEmail);
        }
      }
    }
  }
};