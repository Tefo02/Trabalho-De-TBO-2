#pragma once
#include <string>
#include <type_traits>
#include <vector>

template <typename Key, typename Value> class HashTable {
public:
  HashTable(size_t size = 16) : table(size) {}

  void insert(const Key &key, const Value &value) {
    size_t index = hashKey(key) % table.size();
    table[index].emplace_back(key, value);
  }

  bool find(const Key &key, Value &value) const {
    size_t index = hashKey(key) % table.size();
    for (const auto &pair : table[index]) {
      if (pair.first == key) {
        value = pair.second;
        return true;
      }
    }
    return false;
  }

  void remove(const Key &key) {
    size_t index = hashKey(key) % table.size();
    auto &bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (it->first == key) {
        bucket.erase(it);
        return;
      }
    }
  }

  size_t size() const {
    size_t count = 0;
    for (const auto &bucket : table)
      count += bucket.size();
    return count;
  }

  bool empty() const {
    for (const auto &bucket : table)
      if (!bucket.empty())
        return false;
    return true;
  }

  void clear() {
    for (auto &bucket : table)
      bucket.clear();
  }

  std::vector<std::pair<Key, Value>> getAll() const {
    std::vector<std::pair<Key, Value>> allPairs;
    for (const auto &bucket : table)
      for (const auto &pair : bucket)
        allPairs.push_back(pair);
    return allPairs;
  }

  Value &operator[](const Key &key) {
    size_t index = hashKey(key) % table.size();
    auto &bucket = table[index];
    for (auto &pair : bucket) {
      if (pair.first == key) {
        return pair.second;
      }
    }

    bucket.emplace_back(key, Value{});
    return bucket.back().second;
  }

private:
  std::vector<std::vector<std::pair<Key, Value>>> table;

  size_t hashKey(const Key &key) const {
    if constexpr (std::is_same_v<Key, std::string>) {
      size_t hashValue = 0;
      const int prime = 131;
      for (char c : key) {
        hashValue = hashValue * prime + static_cast<unsigned char>(c);
      }
      return hashValue;
    } else if constexpr (std::is_same_v<Key, int>) {
      return static_cast<size_t>(key);
    } else if constexpr (std::is_same_v<Key, double>) {
      return static_cast<size_t>(key * 1000);
    } else if constexpr (std::is_same_v<Key, char>) {
      return static_cast<size_t>(key);
    } else if constexpr (std::is_same_v<Key, bool>) {
      return key ? 1 : 0;
    } else {
      static_assert(sizeof(Key) == 0,
                    "hashKey() not implemented for this type");
    }
  }
};
