#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>

struct Entity {
  int age;
  std::string email;

  Entity(int a, std::string_view e) : age{a}, email{e} {}
};

class Hashmap {
private:
  const int m_size{10};
  std::vector<std::list<std::pair<std::string, Entity>>> m_table;

public:
  Hashmap() : m_table(m_size) {}

  int hash(std::string_view key) const {
    int sum{0};
    for (char c : key) {
      sum += c;
    }
    return sum % m_size;
  }

  bool contains(std::string_view key) const {
    int index = hash(key);
    for (auto &pair : m_table[index]) {
      if (pair.first == key) {
        return true;
      }
    }
    return false;
  }

  void insert(std::string_view key, const Entity &value) {
    int index{hash(key)};
    auto &bucket{m_table[index]};
    for (auto &pair : bucket) {
      if (pair.first == key) {
        std::cout
            << "Key already exists. Replacing old value with new value.\n";
        pair.second = value;
        return;
      }
    }
    bucket.emplace_back(key, value);
  }

  void remove(std::string_view key) {
    int index{hash(key)};
    auto &bucket{m_table[index]};

    for (auto i{bucket.begin()}; i != bucket.end(); ++i) {
      if (i->first == key) {
        bucket.erase(i);
        return;
      }
    }
    std::cout << "Didn't erase anything. No matching key.\n";
  }
};

int main() { return 0; }
