#include <iostream>
#include <memory>

template<typename T>
auto siftup (int i, std::unique_ptr<T[]>& arrp) {
  auto v = arrp[i];
  for ( ; i > 0; i--) {
    if (arrp[i-1] <= v) {
      break;
    }
    arrp[i] = arrp[i-1];
  }
  arrp[i] = v;
  return i;
}

template<typename T>
auto insertionsort (int ln, std::unique_ptr<T[]>& arrp) {
  int count = 0;
  // an array with just the first element is already "sorted"
  // since there is nothing to its left that is smaller.
  for (int i=1; i < ln; i++) {
    // number of shifts done equals the differense in indexes
    count += i - siftup (i, arrp);
  }

  return count;
}

int main() {
  int n;
  std::cin >> n;

  auto arrp = std::make_unique<int[]>(n);
  for (int i=0; i < n; i++) {
    std::cin >> arrp[i];
  }
  auto cnt = insertionsort(n, arrp);

  std::cout << cnt << std::endl;
  for (int i=0; i < n; i++) {
    if (i > 0) std::cout << " ";
    std::cout << arrp[i];
  }
  std::cout << std::endl;
  return 0;
}
