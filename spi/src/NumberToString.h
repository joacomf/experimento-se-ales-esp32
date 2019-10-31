#ifndef NumberToString_h
#define NumberToString_h

#include <sstream>

template <class T>
inline std::string numberToString(const T &t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

#endif