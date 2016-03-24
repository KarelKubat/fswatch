#include "fswatch.h"
#include "messager.h"

Messager &Messager::operator<< (unsigned char c) {
  if (is_active)
    *os << c;
  return *this;
}
