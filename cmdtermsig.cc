#include "fswatch.h"
#include "cmd.h"

int Cmd::termsig() const {
  if (!signalled())
    return 0;
  return  WTERMSIG(status);
}
