#include "fswatch.h"
#include "cmd.h"

bool Cmd::signalled() const {
  if (isrunning)
    return false;
  return WIFSIGNALED(status);
}
