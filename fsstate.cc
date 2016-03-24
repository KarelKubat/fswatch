#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

bool FsState::be_silent;

FsState::FsState(std::vector<std::string> dirs, bool keepscanning):
    sdirs(dirs), sz(0)  {
  rescan(keepscanning);
  be_silent = true;
}
