#include "fswatch.h"
#include "cmd.h"

bool Cmd::coredumped() const {
  if (!signalled())
    return false;
  return WCOREDUMP(status);
}
