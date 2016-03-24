#include "fswatch.h"
#include "messager.h"

Messager &Messager::operator<< (char c) {
  if (is_active)
    *os << c;
  return *this;
}
