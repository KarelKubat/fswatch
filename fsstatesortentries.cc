#include "fswatch.h"
#include "fsstate.h"

bool compareEntries(FsState::Entry a, FsState::Entry b) {
  return a.name < b.name;
}

void FsState::sortentries() {
  std::sort(entry.begin(), entry.end(), compareEntries);
}
