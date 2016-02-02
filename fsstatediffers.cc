#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

bool FsState::differs(FsState const &other) const {
  if (sz != other.sz) {
    msg << "[fswatch] number of entries has changed from "
        << sz << " to " << other.sz << "\n";
    return true;
  }
  for (unsigned i = 0; i < sz; i++) {
    if (entry[i].name != other.entry[i].name) {
      msg << "[fswatch] " << entry[i].name << " changed into "
          << other.entry[i].name << "\n";
      return true;
    }
    if (entry[i].statbuf.st_size != other.entry[i].statbuf.st_size) {
      msg << "[fswatch] " << entry[i].name << " changed size\n";
      return true;
    }
    if (entry[i].statbuf.st_mtime != other.entry[i].statbuf.st_mtime) {
      msg << "[fswatch] " << entry[i].name
          << " changed modification time\n";
      return true;
    }
  }
  return false;
}
