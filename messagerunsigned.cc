#include "fswatch.h"
#include "messager.h"

Messager &Messager::operator<< (unsigned u) {
  if (is_active)
    *os << u;
  return *this;
}
