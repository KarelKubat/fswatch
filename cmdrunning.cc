#include "fswatch.h"
#include "cmd.h"

bool Cmd::running() const {
  return isrunning;
}
