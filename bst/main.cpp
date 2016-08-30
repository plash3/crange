#include "bst.h"

int main() {
  bst::bst<int> t;
  t.insert (8);
  t.insert (3);
  t.insert (10);
  t.insert (1);
  t.insert (6);
  t.insert (14);
  t.insert (4);
  t.insert (7);
  t.insert (13);
  auto n = t.find (6);
  t.erase(n);
  std::cout << t;

  return 0;
}
