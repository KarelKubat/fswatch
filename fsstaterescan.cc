#include "fswatch.h"
#include "fsstate.h"

void FsState::rescan() {
  entry.clear();
  sz = 0;
  listdir(sdir);
  if (! sz)
    err << "[fswatch] nothing to watch under " << sdir << "\n";
}
