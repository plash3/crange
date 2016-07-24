#include <iostream>
#include <string>
#include <vector>
#include <set>

/**
  www.hackerrank.com/challenges/maximum-subarray-sum
*/

template<typename T>
auto maxmodulo (T mod, int n, std::vector<T>& arr) {
  // apply Modulo operation and construct a prefix array -
  //   prefix[n] = (a[1] + a[2] + ... + a[n]) % M
  T curr = 0;
  for (int i = 0; i < n; i++) {
    curr = (arr[i] % mod + curr) % mod;
    arr[i] = curr;
  }

  T ret = 0;
  std::set<T> prefix_set;
  for (int i = 0; i < n; i++) {
    auto it = prefix_set.upper_bound (arr[i]);
    if (it != prefix_set.end()) {
      ret = std::max (ret, (arr[i] - *it + mod) % mod);
    } else {
      ret = std::max (ret, arr[i]);
    }
    prefix_set.insert (arr[i]);
  }

  return ret;
}

int main() {
  int t, n;
  std::cin >> t;

  std::vector<unsigned long long> arr;
  for (int i=0; i < t; i++) {
    unsigned long long mod;
    std::cin >> n;
    std::string istr;
    getline (std::cin, istr);
    mod = std::stoull(istr);
    for (int j=0; j < n; j++) {
      int num;
      std::cin >> num;
      arr.push_back(num);
    }
    auto res = maxmodulo (mod, n, arr);
    arr.clear();
    std::cout << res << std::endl;
  }
  return 0;
}
