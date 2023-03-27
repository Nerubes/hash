#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "hash.h"
#include "src/doctest.h"

using namespace lab618;

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
