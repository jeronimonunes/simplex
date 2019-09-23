#include "Base.hh"

bool Base::containsY(unsigned int y) const
{
  return this->ytox.count(y);
}

void Base::set(unsigned int x, unsigned int y)
{
  this->xtoy[x] = y;
  this->ytox[y] = x;
}

void Base::remove(unsigned int x)
{
  auto xitr = find(x);
  if (xitr != end())
  {
    auto const &[x, y] = *xitr;
    this->ytox.erase(y);
    this->xtoy.erase(x);
  }
}

void Base::yremove(unsigned int y)
{
  auto yitr = yfind(y);
  if (yitr != yend())
  {
    auto const &[y, x] = *yitr;
    this->ytox.erase(y);
    this->xtoy.erase(x);
  }
}

std::map<unsigned int, unsigned int>::const_iterator Base::begin() const
{
  return this->xtoy.begin();
}

std::map<unsigned int, unsigned int>::const_iterator Base::end() const
{
  return this->xtoy.end();
}

std::map<unsigned int, unsigned int>::const_iterator Base::ybegin() const
{
  return this->ytox.begin();
}

std::map<unsigned int, unsigned int>::const_iterator Base::yend() const
{
  return this->ytox.end();
}

std::map<unsigned int, unsigned int>::const_iterator Base::find(unsigned int x) const
{
  return this->xtoy.find(x);
}

std::map<unsigned int, unsigned int>::const_iterator Base::yfind(unsigned int y) const
{
  return this->ytox.find(y);
}

std::ostream &operator<<(std::ostream &os, const Base &v)
{
  auto itr = v.begin();
  if (itr != v.end())
  {
    auto const &[x, y] = *itr;
    os << "(" << x << "," << y << ")";
  }
  for (; itr != v.end(); itr++)
  {
    auto const &[x, y] = *itr;
    os << " (" << x << "," << y << ")";
  }
  return os;
}
