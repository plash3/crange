#include <iostream>
#include <memory>
#include <set>
#include <map>
#include <vector>

/**
  www.hackerrank.com/challenges/rust-murderer
*/

using SET = std::set<int>;
using MAP = std::map<int, std::set<int>>;
using ARR = std::unique_ptr<int[]>;

auto Adj (const int& u, SET& st, const MAP& mp) {
  // std::vector<int> adjl;
  SET adjl;
  auto it = mp.find(u);
  if (it != mp.end()) {
    for (auto its = it->second.begin(); its != it->second.end(); ++its) {
      auto nit = st.find (*its);
      if (nit != st.end()) {
        st.erase (nit);
        adjl.emplace (*nit);
      }
    }
  }
  adjl.swap (st);
  return adjl;
}

void BFS (const int& s, const int& n, ARR& arr, const MAP& mp) {
  SET st;
  for (int i = 0; i < n; i++) {
    st.emplace(i);
  }
  st.erase(s);

  arr[s] = 0;
  int level = 1;
  std::vector<int> frontier (1, s);
  std::vector<int> next;

  while (!frontier.empty()) {
    // for u in frontier
    for (auto it = frontier.begin(); it != frontier.end(); ++it) {
      auto adjl = Adj (*it, st, mp);
      // for v in Adj[u]
      for (auto nit = adjl.begin(); nit != adjl.end(); ++nit) {
        arr[*nit] = level;
        next.emplace_back (*nit);
      }
    }
    frontier = std::move (next);
    ++level;
  }

  return;
}

inline void addedge (const int& x, const int& y, MAP& mp) {
  auto it = mp.find(x);
  if (it != mp.end()) {
    it->second.emplace(y);
  } else {
    SET st;
    st.emplace(y);
    mp.emplace (x, st);
  }

  it = mp.find(y);
  if (it != mp.end()) {
    it->second.emplace(x);
  } else {
    SET st;
    st.emplace(x);
    mp.emplace (y, st);
  }
}

int main() {
  int t, n, m;
  std::cin >> t;

  MAP mp;
  for (int j = 0; j < t; j++) {
    std::cin >> n;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
      int x, y;
      std::cin >> x;
      std::cin >> y;
      addedge (x-1, y-1, mp);
    }
  
    int s;
    std::cin >> s;
    auto arr = std::make_unique<int[]>(n);
    BFS (s-1, n, arr, mp);
    for (int i = 0; i < n; i++) {
      if (i != s-1) {
        std::cout << arr[i] << " ";
      }
    }
    mp.clear();
    std::cout << std::endl;
  }

  return 0;
}
