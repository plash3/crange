#include <iostream>
#include <memory>

template<typename T>
auto binarysearch (T v, int lo, int hi, const std::unique_ptr<T[]>& arr) {
  if (hi - lo <= 1) {
    if (arr[lo] == v) {
      return lo;
    } else if (arr[hi] == v) {
      return hi;
    } else {
      return -1;
    }
  }

  int p = (lo + hi) / 2;
  if (arr[p] == v) {
    return p;
  } else if (arr[p] > v) {
    return binarysearch(v, lo, p-1, arr);
  } else {
    return binarysearch(v, p+1, hi, arr);
  }
}

int main() {
  int v, n;
  std::cin >> v;
  std::cin >> n;

  auto arr = std::make_unique<int[]>(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  auto ans = binarysearch (v, 0, n-1, arr);

  std::cout << ans << std::endl;
  return 0;
}
