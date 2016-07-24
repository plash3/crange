#ifndef TWOTUPLE_H
#define TWOTUPLE_H

#include <iostream>

namespace key {

class CTwoTuple {
    int x, y;;
  public:
    CTwoTuple (int a, int b) : x(a), y(b) {}
    ~CTwoTuple() {}
    bool operator< (const CTwoTuple&) const;
    friend std::ostream& operator<< (std::ostream&, const CTwoTuple&);
};

} // namespace key

#endif /* TWOTUPLE_H */
