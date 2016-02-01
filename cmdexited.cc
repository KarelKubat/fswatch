#include "fswatch.h"
#include "cmd.h"

bool Cmd::exited() const {
  if (isrunning)
    return false;
  return WIFEXITED(status);
}
