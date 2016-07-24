#include "twotuple.h"

namespace key {

/**
  Defines tailored objects comparing.
*/
bool CTwoTuple::operator< (const CTwoTuple& rhs) const {
  return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y));
}

std::ostream& operator<< (std::ostream& out, const CTwoTuple& t) {
  return out << "(" << t.x << "," << t.y << ")";
}

} // namespace key
