#include "fswatch.h"
#include "cmd.h"

bool Cmd::reap() {
  int mystatus;
  pid_t p = waitpid(pid, &mystatus, WNOHANG);

  if (p <= 0)
    return false;

  status = mystatus;
  isrunning = false;
  return true;
}
