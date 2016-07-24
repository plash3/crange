#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <vector>
#include <set>
#include <map>

namespace graph {

//auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; };
template<typename T>
  using SHPT = std::shared_ptr<T>;
template<typename T>
  using ARRT = std::unique_ptr<SHPT<T>[]>;
  using MAP = std::map<int, std::set<int>>;

template<typename T>
auto Adj (const int& u, const MAP& mp, const ARRT<T>& arr) {
  std::vector<int> adjl;
  auto it = mp.find(u);
  if (it != mp.end()) {
    for (auto its = it->second.begin(); its != it->second.end(); ++its) {
      if (!arr[*its]->discovered) {
        adjl.emplace_back (*its);
      }
    }
  }

  return adjl;
}

template<typename T>
int dfs (const int& s, std::set<int>& st, const MAP& mp, const ARRT<T>& arr) {
  auto val = arr[s]->value;
  arr[s]->discovered = true;
  auto adjl = Adj (s, mp, arr);
  for (auto it = adjl.begin(); it != adjl.end(); ++it) {
    // next line is not a part of the algorithm
    arr[*it]->prev = s;
    val += dfs (*it, st, mp, arr);
  }

  st.insert (val);
  return val;
}

} // namespace graph

#endif /* DFS_H */
