#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>

struct Entity {
  int age;
  std::string email;

  Entity(int a, std::string_view e) : age{a}, email{e} {}
  Entity() : age{0}, email{""} {}
};

class Hashmap {
private:
  int m_size{10};
  std::vector<std::list<std::pair<std::string, Entity>>> m_table;

public:
  Hashmap() : m_table(m_size) {}
  Hashmap(int capacity) : m_size{capacity}, m_table(m_size) {}

  int hash(std::string_view key, int size) const {
    int sum{0};
    for (char c : key) {
      sum += c;
    }
    return sum % size;
  }

  bool contains(std::string_view key) const {
    int index = hash(key, m_size);
    for (const auto &pair : m_table[index]) {
      if (pair.first == key) {
        return true;
      }
    }
    return false;
  }

  void insert(std::string_view key, const Entity &value) {
    int index{hash(key, m_size)};
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
    int index{hash(key, m_size)};
    auto &bucket{m_table[index]};

    for (auto i{bucket.begin()}; i != bucket.end(); ++i) {
      if (i->first == key) {
        bucket.erase(i);
        return;
      }
    }
    std::cout << "Didn't erase anything. No matching key.\n";
  }

  const Entity *get(std::string_view key) const {
    int index{hash(key, m_size)};
    auto &bucket{m_table[index]};
    for (auto i{bucket.begin()}; i != bucket.end(); ++i) {
      if (i->first == key) {
        return &i->second;
      }
    }
    return nullptr;
  }

  Entity *get(std::string_view key) {
    int index{hash(key, m_size)};
    auto &bucket{m_table[index]};
    for (auto i{bucket.begin()}; i != bucket.end(); ++i) {
      if (i->first == key) {
        return &i->second;
      }
    }
    return nullptr;
  }

  int size() const {
    int c{0};
    for (const auto &i : m_table) {
      c += i.size();
    }
    return c;
  }

  int capacity() const { return m_size; }

  bool isEmpty() const { return size() == 0; }

  Entity &operator[](std::string_view key) {
    if (!contains(key)) {
      insert(key, Entity{});
    }
    return *get(key);
  }

  double load_factor() const {
    return capacity() > 0
               ? static_cast<double>(size()) / static_cast<double>(capacity())
               : 0.00;
  }

  void rehash(int newCapacity) {
    std::vector<std::list<std::pair<std::string, Entity>>> temp(newCapacity);
    for (auto &bucket : m_table) {
      for (auto &pair : bucket) {
        int newIndex{hash(pair.first, newCapacity)};
        temp[newIndex].emplace_back(pair);
      }
    }
    m_table = temp;
    m_size = newCapacity;
  }
};

int main() { return 0; }
