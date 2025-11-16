#include "sort_tester.h"

#include <chrono>
#include <vector>

void SortTester::insertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void SortTester::merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> leftArr(n1);
  std::vector<int> rightArr(n2);

  for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
  for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

void SortTester::mergeSort(std::vector<int>& arr, int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

void SortTester::hybridMergeSort(std::vector<int>& arr, int left, int right,
                                 int threshold) {
  if (right - left + 1 <= threshold) {
    insertionSort(arr, left, right);
    return;
  }

  if (left < right) {
    int mid = left + (right - left) / 2;
    hybridMergeSort(arr, left, mid, threshold);
    hybridMergeSort(arr, mid + 1, right, threshold);
    merge(arr, left, mid, right);
  }
}

long long SortTester::testMergeSort(std::vector<int>& arr) {
  std::vector<int> arrCopy = arr;

  auto start = std::chrono::high_resolution_clock::now();
  mergeSort(arrCopy, 0, static_cast<int>(arrCopy.size()) - 1);
  auto elapsed = std::chrono::high_resolution_clock::now() - start;

  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

long long SortTester::testHybridMergeSort(std::vector<int>& arr,
                                          int threshold) {
  std::vector<int> arrCopy = arr;

  auto start = std::chrono::high_resolution_clock::now();
  hybridMergeSort(arrCopy, 0, static_cast<int>(arrCopy.size()) - 1, threshold);
  auto elapsed = std::chrono::high_resolution_clock::now() - start;

  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}