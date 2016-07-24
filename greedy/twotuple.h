#ifndef TWOTUPLE_H
#define TWOTUPLE_H

#include <iostream>

namespace key {

class CTwoTuple {
    int value;
  public:
    int index;
    CTwoTuple (int a, int b) : value(a), index(b) {}
    ~CTwoTuple() {}
    int getValue() { return value; }
    bool operator< (const CTwoTuple&) const;
    friend std::ostream& operator<< (std::ostream&, const CTwoTuple&);
};

} // namespace key

#endif /* TWOTUPLE_H */
