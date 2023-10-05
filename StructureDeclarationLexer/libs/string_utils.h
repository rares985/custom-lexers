#ifndef __STRING_UTILS_H_
#define __STRING_UTILS_H_ 1

#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>

void squeeze(std::string &s, char delim) {
	s.erase(std::remove(s.begin(),s.end(),delim),s.end());
}

std::string operator+(std::string const &a, int b) {
  std::ostringstream oss;
  oss << a << b;
  return oss.str();
}


#endif