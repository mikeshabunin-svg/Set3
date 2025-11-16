#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <chrono>
#include <vector>

class SortTester {
 private:
  void merge(std::vector<int>& arr, int left, int mid, int right);
  void insertionSort(std::vector<int>& arr, int left, int right);

 public:
  void mergeSort(std::vector<int>& arr, int left, int right);
  void hybridMergeSort(std::vector<int>& arr, int left, int right,
                       int threshold);

  // Две разные сигнатуры для тестирования
  long long testMergeSort(std::vector<int>& arr);
  long long testHybridMergeSort(std::vector<int>& arr, int threshold);
};

#endif