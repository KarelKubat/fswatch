#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

bool FsState::be_silent;

FsState::FsState(std::vector<std::string> dirs, bool keepscanning,
                 bool scanallfiles):
    sdirs(dirs), sz(0)  {
  rescan(keepscanning, scanallfiles);
  be_silent = true;
}
