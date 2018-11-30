#include "fswatch.h"
#include "fsstate.h"

void FsState::rescan(bool keepscanning, bool scanallfiles) {
  static bool warning_generated;

  entry.clear();
  sz = 0;
  if (! be_silent) {
    msg << "[fswatch] listing top level target(s)";
    for (unsigned i = 0; i < sfiles.size(); i++)
      msg << ' ' << sfiles[i];
    for (unsigned i = 0; i < sdirs.size(); i++)
      msg << ' ' << sdirs[i];
    msg << '\n';
  }

  for (unsigned i = 0; i < sfiles.size(); i++) {
    struct stat statbuf;
    if (stat(sfiles[i].c_str(), &statbuf)) {
      warn << "[fswatch] cannot stat " << sfiles[i] << ": "
           << strerror(errno) << '\n';
      continue;
    }
    if (! (statbuf.st_mode & S_IFREG)) {
      warn << "[fswatch] " << sfiles[i] << " is not a regular file\n";
      continue;
    }
    Entry e = { sfiles[i], statbuf };
    entry.push_back(e);
    sz++;
  }

  for (unsigned i = 0; i < sdirs.size(); i++)
    listdir(sdirs[i], scanallfiles);
  sortentries();

  if (! sz) {
    if (! keepscanning) {
      err << "[fswatch] nothing to watch under" ;
      for (unsigned i = 0; i < sdirs.size(); i++)
        err << ' ' << sdirs[i];
      err << '\n';
    }
    else {
      if (!warning_generated) {
        // Make sure that we print this only once else we keep
        // spamming the screen.
        warning_generated = true;
        msg << "[fswatch] nothing to watch under";
        for (unsigned i = 0; i < sdirs.size(); i++)
          msg << ' ' << sdirs[i];
        msg << " but continuing\n";
      }
    }
  } else {
    // Next time a warning may be shown.
    warning_generated = false;
  }
}
