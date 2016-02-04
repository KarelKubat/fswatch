#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

bool FsState::be_silent;

FsState::FsState(char const *dir): sdir(dir), sz(0)  {
  rescan();
  be_silent = true;
}
