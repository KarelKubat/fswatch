#include "fswatch.h"
#include "cmd.h"

Cmd::Cmd(char **args): pid(0), status(0), isrunning(true), starttime(0) {
  int p = fork();
  if (p > 0) {
    // Parent branch
    pid = p;
    msg << "[fswatch] starting " << args[0] << " as pid " << pid << "\n";
    starttime = time(0);
  } else if (p == 0) {
    // Child branch
    execvp(args[0], args);
    err << "[fswatch] failed to run " << args[0] << ": "
	<< strerror(errno) << "\n";
  } else {
    err << "[fswatch] cannot fork: " << strerror(errno) << "\n";
  }
}
