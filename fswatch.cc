#include "fswatch.h"
#include "fsstate.h"
#include "cmd.h"

Messager msg(true, false, &std::cout);
Messager err(true, true, &std::cerr);
Messager warn(true, false, &std::cerr);

static char curdir[] = ".";

int main(int argc, char **argv) {
  // Default flag values
  unsigned interval = 1;	// dirscan interval
  unsigned timeout = 0;		// timeout for external cmd
  unsigned killwait = 1;	// time between sigs when killing cmd
  char *watchdir = curdir;	// watched dir

  // Parse the command line
  struct option opts[] = {
    { "dir",      required_argument, 0, 0 },
    { "help",     no_argument,       0, 0 },
    { "interval", required_argument, 0, 0 },
    { "killwait", required_argument, 0, 0 },
    { "silent",   no_argument,       0, 0 },
    { "timeout",  required_argument, 0, 0 },
  };
  int opt;
  while ( (opt = getopt_long(argc, argv, "d:hi:k:lst:", opts, 0)) > 0 ) {
    switch (opt) {
    case 'd':
      if (! optarg || ! *optarg)
	err << "[fswatch] missing --dir value\n";
      watchdir = optarg;
      break;
    case 'h':
      usage();
      break;
    case 'i':
      if (! optarg || ! *optarg)
	err << "[fswatch] missing --interval value\n";
      if (sscanf(optarg, "%u", &interval) < 1)
	err << "[fswatch] bad --interval " << optarg << ": not a number\n";
      break;
    case 'k':
      if (! optarg || ! *optarg)
	err << "[fswatch] missing --killwait value\n";
      if (sscanf(optarg, "%u", &killwait) < 1)
	err << "[fswatch] bad --killwait " << optarg << ": not a number\n";
      break;
    case 's':
      msg.active(false);
      break;
    case 't':
      if (! optarg || ! *optarg)
	err << "[fswatch] missing --timeout value\n";
      if (sscanf(optarg, "%u", &timeout) < 1)
	err << "[fswatch] bad --timeout " << optarg << ": not a number\n";
      break;
    default:
      usage();
    }
  }
  if (argc - optind < 1)
    usage();
  char **command = argv + optind;

  FsState state(watchdir);

  Cmd *cmd = new Cmd(command);
  bool statechanged = false;
  while (true) {
    if (sleep(interval))
      err << "[fswatch] sleep interrupted\n";

    if (cmd->reap() && cmd->exited())
      msg << "[fswatch] " << command[0] << " exited with status "
	  << cmd->exitstatus() << "\n";

    FsState nextstate(watchdir);
    if (state.differs(nextstate)) {
      statechanged = true;
      state = nextstate;
    }

    if (statechanged) {
      if (! cmd->running()) {
	delete cmd;
	cmd = new Cmd(command);
	statechanged = false;
      } else {
	if (timeout > 0 && cmd->runtime() > timeout) {
	  msg << "[fswatch] " << command[0] << " exceeded timeout " << timeout
	      << " secs, runtime " << cmd->runtime() << ", restarting\n";
	  cmd->hose(killwait);
	  delete cmd;
	  cmd = new Cmd(command);
	  statechanged = false;
	}
      }
    }
  }

  return 0;
}
