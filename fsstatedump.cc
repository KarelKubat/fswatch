#include "fswatch.h"
#include "fsstate.h"

void FsState::dump(std::string title) const {
  std::cout << "State " << title << " has " << sz << " entries\n";
  for (unsigned i = 0; i < sz; i++)
    std::cout << "  entry " << i << ": " << entry[i].name << "\n";
  std::cout << "\n";
}
