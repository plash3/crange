#include "quicksort.h"

/*
  Given a word w, rearrange the letters of w to construct
  another word s in such a way that s is lexicographically
  greater than w. In case of multiple possible answers,
  find the lexicographically smallest one among them.
*/
auto find_lesser (int n, std::vector<char>& arr) {
  for (int i = n - 1; i > 0; i--) {
    if (arr[i-1] < arr[i]) {
      // place for swapping
      qs::quicksort (i, n - 1, arr);
      for (int j = i; j < n; j++) {
        if (arr[i-1] < arr[j]) {
          auto t = arr[i-1];
          arr[i-1] = arr[j];
          arr[j] = t;
          return i;
        }
      }
    }
  }

  return -1;
}

int main() {
  int t;
  std::cin >> t;

  std::vector<char> arr;
  for (int i = 0; i < t; i++) {
    std::string str;
    std::cin >> str;
    auto n = str.size();
    for (int j = 0; j < n; j++) {
      arr.push_back(str[j]);
    }
    auto p = find_lesser (n, arr);
    if (p > 0) {
      for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it;
      }
      std::cout << std::endl;
    } else {
      std::cout << "no answer" << std::endl;
    }
    arr.clear();
  }

  return 0;
}
