#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

bool FsState::be_silent;

FsState::FsState(std::vector<std::string> dirs, std::vector<std::string> files,
                 bool keepscanning, bool scanallfiles):
    sdirs(dirs), sfiles(files), sz(0)  {
  rescan(keepscanning, scanallfiles);
  be_silent = true;
}
