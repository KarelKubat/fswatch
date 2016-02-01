#include "fswatch.h"
#include "cmd.h"

int Cmd::exitstatus() const {
  if (! exited())
    return 0;
  return WEXITSTATUS(status);
}
