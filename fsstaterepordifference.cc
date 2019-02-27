#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

#define MAX_TO_SHOW 5

void FsState::report_difference(FsState const &other) const {
  unsigned int this_index = 0, that_index = 0;

  // Sudden (dis)|(re)appearance? Report as oneliner.
  if (!sz) {
    msg << "[fswatch] all files have disappeared\n";
    return;
  }
  if (!other.sz) {
    msg << "[fswatch] files have appeared\n";
    return;
  }

  unsigned nshown = 0;
  while (this_index < sz && that_index < other.sz) {
    /* printf debugging is the best debugging      
      msg << "[this] " << entry[this_index].name << '\n';
      msg << "[that] " << other.entry[that_index].name << '\n';
    */
    
    // Same files? Compare next.
    if (entry[this_index].name == other.entry[that_index].name) {
      ++this_index;
      ++that_index;
      continue;
    }

    // Appeared?
    if (sz > other.sz) {
      msg << "[fswatch] " << entry[this_index].name << " has (re)appeared\n";
      ++this_index;
      continue;
    }

    // Disappeared
    msg << "[fswatch] " << entry[this_index].name << " has disappeared\n";
    ++that_index;

    // Limit output
    if (++nshown >= MAX_TO_SHOW) {
      msg << "[fswatch] more differences are not shown\n";
      return;
    }
  }

  // Must be at the end
  if (this_index < sz)
    msg << "[fswatch] " << entry[sz].name << " has appeared\n";
  else
    msg << "[fswatch] " << entry[other.sz].name << " has appeared\n";
}
