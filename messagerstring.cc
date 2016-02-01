#include "fswatch.h"
#include "messager.h"

Messager &Messager::operator<< (std::string s) {
  return operator<<(s.c_str());
}
