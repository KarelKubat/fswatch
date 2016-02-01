#include "fswatch.h"
#include "messager.h"

Messager &Messager::operator<< (char const *s) {
  if (is_active)
    *os << s;
  if (is_fatal && strchr(s, '\n'))
      exit(1);
  return *this;
}
