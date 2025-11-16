#include "array_generator.h"

#include <algorithm>
#include <random>

ArrayGenerator::ArrayGenerator(int minVal, int maxVal)
    : minVal(minVal), maxVal(maxVal) {}

std::vector<int> ArrayGenerator::generateRandomArray(int size) {
  std::vector<int> arr(size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(minVal, maxVal);

  for (int i = 0; i < size; ++i) {
    arr[i] = dist(gen);
  }
  return arr;
}

std::vector<int> ArrayGenerator::generateReversedArray(int size) {
  std::vector<int> arr = generateRandomArray(size);
  std::sort(arr.rbegin(), arr.rend());
  return arr;
}

std::vector<int> ArrayGenerator::generateAlmostSortedArray(int size,
                                                           int swapCount) {
  std::vector<int> arr = generateRandomArray(size);
  std::sort(arr.begin(), arr.end());

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> indexDist(0, size - 1);

  for (int i = 0; i < swapCount; ++i) {
    int idx1 = indexDist(gen);
    int idx2 = indexDist(gen);
    std::swap(arr[idx1], arr[idx2]);
  }
  return arr;
}