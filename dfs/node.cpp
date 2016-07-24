#include "node.h"

namespace graph {

bool CNode::operator< (const CNode& rhs) const {
  return id < rhs.id;
}

std::ostream& operator<< (std::ostream& out, const CNode& t) {
  return out << "(" << t.id << "->" << t.prev << "," << t.value << ")";
}

} // namespace graph
