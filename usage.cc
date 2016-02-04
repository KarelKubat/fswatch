#include "fswatch.h"

void usage() {
  std::cerr <<
"\n"
"This is fswatch " VER ", a file system watcher.\n"
"Written by " AUTHOR " " YEARS ", distributed under GPLV3.\n"
"See " URL " for information and sources.\n"
"\n"
"Usage: fswatch [FLAGS] COMMAND [ARGS]\n"
"The current direcotry is watched, and COMMAND [ARGS] is run when changes\n"
"are seen.\n"
"\n"
"Accepted general flags:\n"
"  --                      ends flags, useful when you have -options in ARGS\n"
"  --help, -h:             this help\n"
"  --dir DIR, -d DIR       watches DIR instead of current directory\n"
"  --silent, -s            decreases verbosity\n"
"\n"
"Flags related to file system polling:\n"
"  --dir DIR, -d DIR       watches DIR instead of current directory\n"
"  --interval SEC, -i SEC  poll interval of the filesystem, default 1\n"
"\n"
"Flags for restarting COMMAND:\n"
"  --timeout SEC, -t SEC   restarts CMD when changes are seen but CMD has\n"
"                          been running longer than SEC seconds\n"
"  --killwait SEC, -k SEC  waits SEC secs between delivering signals SIGTERM,\n"
"                          SIGQUIT and SIGKILL to COMMAND, useful to allow\n"
"                          a slow graceful stop, default 1\n"
"\n"
    ;

  exit(1);
}
