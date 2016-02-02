#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

FsState::FsState(char const *dir): sdir(dir), sz(0) {
  rescan();
}
