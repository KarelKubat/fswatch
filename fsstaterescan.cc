#include "fswatch.h"
#include "fsstate.h"

void FsState::rescan() {
  entry.clear();
  sz = 0;
  if (! be_silent)
    msg << "[fswatch] listing top level target " << sdir << "\n";
  listdir(sdir);
  if (! sz)
    err << "[fswatch] nothing to watch under " << sdir << "\n";
}
