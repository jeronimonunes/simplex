#ifndef BASE_HH
#define BASE_HH

#include <map>
#include "Coordinate.hh"
#include <ostream>

class Base
{
private:
  std::map<unsigned int, unsigned int> xtoy;
  std::map<unsigned int, unsigned int> ytox;

public:
  bool containsY(unsigned int y) const;
  void set(unsigned int x, unsigned int y);
  void remove(unsigned int x);
  void yremove(unsigned int y);
  std::map<unsigned int, unsigned int>::const_iterator begin() const;
  std::map<unsigned int, unsigned int>::const_iterator end() const;
  std::map<unsigned int, unsigned int>::const_iterator ybegin() const;
  std::map<unsigned int, unsigned int>::const_iterator yend() const;
  std::map<unsigned int, unsigned int>::const_iterator find(unsigned int x) const;
  std::map<unsigned int, unsigned int>::const_iterator yfind(unsigned int y) const;

};

std::ostream &operator<<(std::ostream &os, const Base &x);

#endif
