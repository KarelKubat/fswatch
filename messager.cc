#include "fswatch.h"
#include "messager.h"

Messager::Messager (bool act, bool fat, std::ostream *o):
  is_active(act), is_fatal(fat), os(o) {
}
