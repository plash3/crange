#ifndef NODE_H
#define NODE_H

#include <iostream>

namespace graph {

class CNode {
    int id;
  public:
    int prev;
    int value;
    bool discovered;
    CNode (int i, int v) : id(i), prev(-1), value(v), discovered(false) {}
    CNode (int i, int p, int v) : id(i), prev(p), value(v), discovered(false) {}
    ~CNode() {}
    auto getId() { return id; }
    bool operator< (const CNode&) const;
    friend std::ostream& operator<< (std::ostream&, const CNode&);
};

} // namespace graph

#endif /* NODE_H */
