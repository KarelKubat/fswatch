#include "fswatch.h"
#include "cmd.h"

void Cmd::hose(unsigned killwait) {
  if (! isrunning)
    return;

  kill(pid, SIGTERM);
  if (reap())
    return;
  sleep(killwait);

  kill(pid, SIGQUIT);
  if (reap())
    return;

  sleep(killwait);
  kill(pid, SIGKILL);
  reap();
}
