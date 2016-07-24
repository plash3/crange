#include "twotuple.h"

/**
  Defines tailored objects comparing.
*/

namespace key {

// greatest goes first or if equal then one with lower index precedes
bool CTwoTuple::operator< (const CTwoTuple& rhs) const {
  return (value < rhs.value) || ((value == rhs.value) && (index < rhs.index));
}

std::ostream& operator<< (std::ostream& out, const CTwoTuple& t) {
  return out << "(" << t.value << "," << t.index << ")";
}

} // namespace key
