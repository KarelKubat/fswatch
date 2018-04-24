#include "fswatch.h"
#include "fsstate.h"
#include "cmd.h"

Messager msg(true, false, &std::cout);
Messager err(true, true, &std::cerr);
Messager warn(true, false, &std::cerr);

static Cmd *cmd;			// command to run, for interrupts

static void dieded(int sig) {		// signal catcher
  msg << "[fswatch] caught interrupt\n";
  if (cmd && cmd->running())
    cmd->hose(1);
  exit(1);
}

int main(int argc, char **argv) {
  // Default flag values. Note - not synced with usage.cc,
  // apply text changes when modifying this.
  unsigned interval = 1;	 	// dirscan interval
  unsigned timeout = 30;	 	// timeout for external cmd
  unsigned killwait = 1;	        // time between sigs when killing cmd
  unsigned restartwait = 2;             // FS settle time before restarting cmd
  bool keepscanning = false;            // keep scanning even when empty dir
  bool allfiles = false;		// also scan #file etc
  std::vector<std::string> watchdirs;   // dirs to watch

  // Parse the command line
  struct option opts[] = {
    { "allfiles",     no_argument,       0, 'a' },
    { "dir",          required_argument, 0, 'd' },
    { "help",         no_argument,       0, 'h' },
    { "interval",     required_argument, 0, 'i' },
    { "keepscanning", no_argument,       0, 'K' },
    { "killwait",     required_argument, 0, 'k' },
    { "restartwait",  required_argument, 0, 'r' },
    { "silent",       no_argument,       0, 's' },
    { "timeout",      required_argument, 0, 't' },
  };
  int opt;
  while ( (opt = getopt_long(argc, argv, "d:hi:Kk:r:st:", opts, 0)) > 0 ) {
    switch (opt) {
      case 'a':
        allfiles = true;
        break;
      case 'd':
        if (! optarg || ! *optarg)
          err << "[fswatch] missing --dir value\n";
        watchdirs.push_back(optarg);
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
      case 'K':
        keepscanning = true;
        break;
      case 'k':
        if (! optarg || ! *optarg)
          err << "[fswatch] missing --killwait value\n";
        if (sscanf(optarg, "%u", &killwait) < 1)
          err << "[fswatch] bad --killwait " << optarg << ": not a number\n";
        break;
      case 'r':
        if (! optarg || ! *optarg)
          err << "[fswatch] missing --restartwait value\n";
        if (sscanf(optarg, "%u", &restartwait) < 1)
          err << "[fswatch] bad --restartwait " << optarg << ": not a number\n";
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

  // Watch cwd if no --dirs were seen.
  if (!watchdirs.size())
    watchdirs.push_back(".");

  FsState state(watchdirs, keepscanning, allfiles);
  // state.dump("initial");

  signal(SIGINT, dieded);
  signal(SIGQUIT, dieded);
  signal(SIGTERM, dieded);

  // Create new command to run.
  cmd = new Cmd(command);
  bool statechanged = false;
  while (true) {
    if (sleep(interval))
      err << "[fswatch] sleep interrupted\n";

    if (cmd->reap() && cmd->exited()) {
      msg << "[fswatch] " << command[0] << " exited with status "
	  << cmd->exitstatus() << "\n";
      state.rescan(keepscanning);
      // state.dump("rescanned after cmd");
      statechanged = false;
    } else {
      FsState nextstate(watchdirs, keepscanning, allfiles);
      // nextstate.dump("next state");
      if (state.differs(nextstate)) {
        statechanged = true;
        state = nextstate;
      }
    }

    if (statechanged) {
      if (! cmd->running()) {
	delete cmd;
        if (restartwait)
          sleep(restartwait);
	cmd = new Cmd(command);
	statechanged = false;
      } else {
	if (timeout > 0 && cmd->runtime() > timeout) {
          msg << "[fswatch] change detected and " << command[0]
              << " running already for " << cmd->runtime()
              << " secs, restarting\n";
	  cmd->hose(killwait);
	  delete cmd;
          if (restartwait)
            sleep(restartwait);
          cmd = new Cmd(command);
	  statechanged = false;
	}
      }
    }
  }

  return 0;
}
