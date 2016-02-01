#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

FsState::FsState(char const *dir): sz(0) {
  listdir(dir);
  if (! sz) 
    err << "[fswatch] nothing to watch under " << dir << "\n";
}
