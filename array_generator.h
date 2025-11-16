#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>

class ArrayGenerator {
 private:
  int minVal;
  int maxVal;

 public:
  ArrayGenerator(int minVal = 0, int maxVal = 6000);
  std::vector<int> generateRandomArray(int size);
  std::vector<int> generateReversedArray(int size);
  std::vector<int> generateAlmostSortedArray(int size, int swapCount = 10);
};

#endif