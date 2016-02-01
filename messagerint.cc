#include "fswatch.h"
#include "messager.h"

Messager &Messager::operator<< (int i) {
  if (is_active)
    *os << i;
  return *this;
}
