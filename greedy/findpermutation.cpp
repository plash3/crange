#include <iostream>
#include <memory>
#include <queue>
#include "twotuple.h"

/**
  www.hackerrank.com/challenges/largest-permutation
*/

  auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; };
template<typename T>
  using SHPTRT = std::shared_ptr<T>;
template<typename T>
  using PRTYQU = std::priority_queue<SHPTRT<T>, std::vector<SHPTRT<T>>, decltype(derefLess)>;
template<typename T>
  using TARR = std::unique_ptr<SHPTRT<T>[]>;

template<typename T>
void permutate (int k, int n, const TARR<T>& arr, PRTYQU<T>& pq) {
  for (int i = 0; k > 0 && i < n; i++) {
    auto t = pq.top();
    pq.pop();
    if (t->index != i) {
      // adjust index of the current element
      // and swap A[current] and A[top]
      arr[i]->index = t->index;
      arr[t->index] = arr[i];
      arr[i] = t;
      --k;
    }
  }
  return;
}

/*
  Given an array of N integers. At most K swaps can be made.
  Find the largest possible permutation, in numerical order.
*/
int main() {
  int n, k, num;
  std::cin >> n;
  std::cin >> k;

  auto arr = std::make_unique<SHPTRT<key::CTwoTuple>[]>(n);
  PRTYQU<key::CTwoTuple> pq (derefLess);

  for (int i = 0; i < n; i++) {
    std::cin >> num;
    auto spt = std::make_shared<key::CTwoTuple>(num, i);
    arr[i] = spt;
    pq.emplace (spt);
  }
  permutate (k, n, arr, pq);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i]->getValue() << " ";
  }
  std::cout << std::endl;

  return 0;
}
