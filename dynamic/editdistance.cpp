#include <memory>
#include <map>
#include "twotuple.h"

using MAP = std::map<key::CTwoTuple, int>;

auto recurse (const int& m, const int& n, const std::string& s,
              const std::string& t, MAP& cache) {
  int ans;

  auto key = std::make_unique<key::CTwoTuple>(m, n);
  auto it = cache.find(*key);
  // if (m,n) in cache then return it
  if (it != cache.end()) {
    return it->second;
  }

  if (m == 0) {
    ans = n;
  } else if (n == 0) {
    ans = m;
  } else if (s[m-1] == t[n-1]) {
    ans = recurse (m-1, n-1, s, t, cache);
  } else {
    auto tn1 = recurse (m-1, n, s, t, cache);
    auto tn2 = recurse (m, n-1, s, t, cache);
    auto tn3 = recurse (m-1, n-1, s, t, cache);
    ans = 1 + std::min (std::min (tn1, tn2), tn3);
  }
  cache.emplace(*key, ans);

  std::cout << *key << "=>" << ans << std::endl;
  return ans;
}

auto editdistance (const int& m, const int& n,
     const std::string& s, const std::string& t) {
  MAP cache;
  auto ans = recurse (m, n, s, t, cache);

  return ans;
}

int main() {
  int tc;
  std::cin >> tc;

  for (int i=0; i < tc; i++) {
    std::string s, t;
    std::cin >> s;
    std::cin >> t;
    auto m = s.size();
    auto n = t.size();
    auto ans = editdistance (m, n, s, t);
    std::cout << ans << std::endl;
  }
  return 0;
}
