#include <iostream>
#include <map>
#include <set>
#include <vector>

#ifndef EDGEWEIGHT
#define EDGEWEIGHT 6
#endif

auto Adj (int u, std::vector<int>& arr, std::map<int, std::set<int>>& mp) {
  std::vector<int> adjl;
  auto it = mp.find(u);
  if (it != mp.end()) {
    for (auto nit = it->second.begin(); nit != it->second.end(); nit++) {
      // a node has not been reached yet, and therefore
      // it has no distance from the starting vertex;
      // visited nodes will not be revisited again
      if (arr[*nit] < 0) {
        adjl.emplace_back (*nit);
      }
    }
  }

  return adjl;
}

void BFS (int s, std::vector<int>& arr, std::map<int, std::set<int>>& mp) {
  arr[s] = 0;
  int level = 1;
  std::vector<int> frontier (1, s);
  std::vector<int> next;

  while (!frontier.empty()) {
    // for u in frontier
    for (auto it = frontier.begin(); it != frontier.end(); ++it) {
      auto adjl = Adj (*it, arr, mp);
      // for v in Adj[u]
      for (auto nit = adjl.begin(); nit != adjl.end(); ++nit) {
        arr[*nit] = level * EDGEWEIGHT;
        next.emplace_back (*nit);
      }
    }
    frontier = std::move (next);
    level += 1;
  }

  return;
}

/*
  A key in the map is regarded as a node. A vertex pair (x,y)
  is an edge. Every edge is stored twice - as an outgoing edge
  for one node, and an incoming edge for another. Thus the map
  constitutes adjacency lists for every node in the graph.
 
*/
inline void addedge (int x, int y, std::map<int, std::set<int>>& mp) {
  auto it = mp.find(x);
  if (it != mp.end()) {
    it->second.insert(y);
  } else {
    std::set<int> st;
    st.insert(y);
    mp.emplace (x, st);
  }

  it = mp.find(y);
  if (it != mp.end()) {
    it->second.insert(x);
  } else {
    std::set<int> st;
    st.insert(x);
    mp.emplace (y, st);
  }

}

int main() {
  // Given an undirected graph consisting of N nodes (labelled 1 to N);
  // edges of the graph are assigned weight of 6
  int t, n, m;
  std::cin >> t;

  std::map<int, std::set<int>> mp;
  for (int i = 0; i < t; i++) {
    std::cin >> n;
    std::cin >> m;

    for (int j = 0; j < m; j++) {
      int x, y;
      std::cin >> x;
      std::cin >> y;
      addedge (x-1, y-1, mp);
    }

    // S represents a starting node
    int s;
    std::cin >> s;

    // the distance of each vertex is set to infinity (-1)
    std::vector<int> arr (n, -1);
    BFS (s-1, arr, mp);
    for (auto it = arr.begin(); it != arr.end(); it++) {
      if (*it != 0) {
        std::cout << *it << " ";
      }
    }
    std::cout << std::endl;
    mp.clear();
  }

  return 0;
}
