#include <iostream>
#include <map>

/**
  Modified Fibonacci numbers
    F(n) = F(n-1)^2 + F(n-2)
*/
template<typename T>
auto fibonacci (const int& n, const T& f1, const T& f2, std::map<int, T>& cache) {
  T ans;

  // if n in cache then return it
  auto it = cache.find(n);
  if (it != cache.end()) {
    return it->second;
  }

  if (n == 1) {
    ans = f1;
  } else if (n == 2) {
    ans = f2;
  } else if (n > 2) {
    auto fn_2 = fibonacci (n-2, f1, f2, cache);
    auto fn_1 = fibonacci (n-1, f1, f2, cache);
    ans = fn_1*fn_1 + fn_2;
  }
  cache.emplace (n, ans);

  return ans;
}

int main() {
  int n;
  using UNSGNL = unsigned long long;
  UNSGNL f1, f2;
  std::cin >> f1;
  std::cin >> f2;
  std::cin >> n;

  std::map<int, UNSGNL> cache;
  auto ans = fibonacci (n, f1, f2, cache);

  std::cout << ans << std::endl;
  return 0;
}
