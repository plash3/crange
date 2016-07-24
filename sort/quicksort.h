#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <vector>

namespace qs {

template<typename T>
auto partition (int lo, int hi, std::vector<T>& arr) {
  // choose a pivot the last element in the array
  auto pivot = arr[hi];
  auto i = lo;
  for (int j = lo; j < hi; j++) {
    if (arr[j] <= pivot) {
      if (j != i) {
        // swap A[i] with A[j]
        auto t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
      }
      ++i;
    }
  }
  // the index to put the pivot in
  arr[hi] = arr[i];
  arr[i] = pivot;
  return i;
}

/**
  partition-exchange sort operates in-place on an array
*/
template<typename T>
void quicksort (int lo, int hi, std::vector<T>& arr) {
  if (lo < hi) {
    auto p = partition (lo, hi, arr);
    if (lo < p-1) {
      quicksort (lo, p-1, arr);
    }
    if (p+1 < hi) {
      quicksort (p+1, hi, arr);
    }
  }

  return;
}

} // namespace qs

#endif /* QUICKSORT_H */
