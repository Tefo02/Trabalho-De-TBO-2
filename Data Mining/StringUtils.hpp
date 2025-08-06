#pragma once

#include <string>

class StringUtils {
public:
  static size_t findChar(const std::string &text, char target,
                         size_t startPos = 0) {
    for (size_t i = startPos; i < text.length(); ++i) {
      if (text[i] == target) {
        return i;
      }
    }
    return std::string::npos;
  }

  static size_t findFirstOf(const std::string &text, const std::string &charSet,
                            size_t startPos = 0) {
    for (size_t i = startPos; i < text.length(); ++i) {
      for (size_t j = 0; j < charSet.length(); ++j) {
        if (text[i] == charSet[j]) {
          return i;
        }
      }
    }
    return std::string::npos;
  }

  static size_t findLastOf(const std::string &text, const std::string &charSet,
                           size_t pos) {
    size_t startPos = (pos >= text.length()) ? text.length() - 1 : pos;
    for (long long i = startPos; i >= 0; --i) {
      for (size_t j = 0; j < charSet.length(); ++j) {
        if (text[i] == charSet[j]) {
          return i;
        }
      }
    }
    return std::string::npos;
  }

  static bool isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
  }

  static bool isNumeric(char c) { return c >= '0' && c <= '9'; }
};