#include "fswatch.h"
#include "messager.h"

bool Messager::active(bool act) {
  bool ret = is_active;
  is_active = act;
  return ret;
}
