#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "hash.h"
#include "src/doctest.h"

using namespace lab618;

class TestClass {
 public:
  TestClass() = default;
  TestClass(unsigned int x, int y) : x(x), y(y) {}
  TestClass& operator=(const TestClass& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  ~TestClass() = default;
  unsigned int x = 0;
  int y = 0;
};

int CmpTestClass(const TestClass *first, const TestClass *second) {
  return static_cast<int>(first->x - second->x);
}

unsigned int hashTestClass(const TestClass *x) {
  return x->x;
}

unsigned int hash(const unsigned int *x) {
  return *x;
}

int Cmp(const unsigned int *first, const unsigned int *second) {
  return static_cast<int>(*first - *second);
}

TEST_CASE("Adding elements") {
  CHash hashTable = CHash<unsigned int, hash, Cmp>(100, 100);
  int amount = 1000;
  unsigned int *data = new unsigned int[amount];
  unsigned int *data_check = new unsigned int[amount];
  for (unsigned int i = 0; i < amount; ++i) {
    data[i] = i;
    data_check[i] = i;
    CHECK(hashTable.add(data + i) == true);
  }
  for (unsigned int i = 0; i < amount; ++i) {
    CHECK(hashTable.add(data_check + i) == false);
  }
  delete[] data;
  delete[] data_check;
}

TEST_CASE("Updating elements") {
  CHash hashTable = CHash<unsigned int, hash, Cmp>(100, 100);
  int amount = 1000;
  unsigned int *data = new unsigned int[amount];
  unsigned int *data_check = new unsigned int[amount];
  for (unsigned int i = 0; i < amount; ++i) {
    data[i] = i;
    data_check[i] = i;
    CHECK(hashTable.update(data + i) == false);
  }
  for (unsigned int i = 0; i < amount; ++i) {
    CHECK(hashTable.update(data_check + i) == true);
  }
  delete[] data;
  delete[] data_check;
}

TEST_CASE("Removing elements") {
  CHash hashTable = CHash<unsigned int, hash, Cmp>(100, 100);
  int amount = 1000;
  unsigned int *data = new unsigned int[amount];
  unsigned int *data_check = new unsigned int[amount];
  for (unsigned int i = 0; i < amount; ++i) {
    data[i] = i;
    data_check[i] = i;
    hashTable.add(data + i);
  }
  for (unsigned int i = 0; i < amount / 2; ++i) {
    CHECK(hashTable.remove(data[i]) == true);
  }
  for (unsigned int i = amount / 2; i < amount; ++i) {
    CHECK(hashTable.add(data + i) == false);
  }
  for (unsigned int i = 0; i < amount / 2; ++i) {
    CHECK(hashTable.add(data + i) == true);
  }
  delete[] data;
  delete[] data_check;
}

TEST_CASE("Update and Add with Class with untracked fields") {
  CHash hashTable = CHash<TestClass, hashTestClass, CmpTestClass>(100, 100);
  int amount = 1000;
  int y = 1;
  TestClass *data = new TestClass[amount];
  TestClass *data_check = new TestClass[amount];
  for (unsigned int i = 0; i < amount; ++i) {
    data[i] = TestClass(i, y);
    data_check[i] = TestClass(i, y);
    CHECK(hashTable.add(data + i) == true);
  }
  for (unsigned int i = 0; i < amount; ++i) {
    CHECK(hashTable.add(data_check + i) == false);
  }
  for (unsigned int i = 0; i < amount / 2; ++i) {
    (data + i)->y = -1;
    CHECK(hashTable.update(data + i) == true);
    CHECK(hashTable.find(data[i])->y == -1);
  }
  for (unsigned int i = amount / 2; i < amount; ++i) {
    CHECK(hashTable.find(data[i])->y == 1);
  }
  delete[] data;
  delete[] data_check;
}
