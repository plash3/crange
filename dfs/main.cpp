#include <memory>
#include "dfs.h"
#include "node.h"

/**
  www.hackerrank.com/challenges/cat-the-tree
*/

inline void addedge (const int& x, const int& y, graph::MAP& mp) {
  auto it = mp.find(x);
  if (it != mp.end()) {
    it->second.emplace(y);
  } else {
    std::set<int> st;
    st.emplace(y);
    mp.emplace(x, st);
  }

  it = mp.find(y);
  if (it != mp.end()) {
    it->second.emplace(x);
  } else {
    std::set<int> st;
    st.emplace(x);
    mp.emplace(y, st);
  }
  return;
}

int main() {
  int n, mean, tot = 0;
  std::cin >> n;

  auto arr = std::make_unique<graph::SHPT<graph::CNode>[]>(n);
  for (int i = 0; i < n; i++) {
    int num;
    std::cin >> num;
    tot += num;
    arr[i] = std::make_shared<graph::CNode>(i, num);
  }
  mean = tot / 2;

  graph::MAP mp;
  for (int i = 0; i < n-1; i++) {
    int x, y;
    std::cin >> x;
    std::cin >> y;
    addedge (x-1, y-1, mp);
  }

  std::set<int> st;
  graph::dfs (0, st, mp, arr);
  auto it = st.lower_bound (mean);
  auto h = *it;
  auto l = *(--it);
  auto res = h;
  if (mean - l < h - mean) {
    res = l;
  }
  res = tot - 2*res;
  if (res < 0) res = -res;
  std::cout << res << std::endl;

  return 0;
}
