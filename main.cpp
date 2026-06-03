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
  int m_size{10};
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
};

int main() { return 0; }
