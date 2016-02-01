#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

static bool gen_warnings = true;

void FsState::listdir(char const *dir) {
  DIR *d = opendir(dir);
  if (! d) {
    if (gen_warnings)
      warn << "[fswatch] cannot read " << dir << ": "
           << strerror(errno) << "\n";
    return;
  }

  struct dirent *direntry;
  while ( (direntry = readdir(d)) ) {
    // Skip . and ..
    if (!strcmp(direntry->d_name, ".") || !strcmp(direntry->d_name, ".."))
      continue;
    // Build up full path & stat it
    std::string fname = dir;
    fname += "/";
    fname += direntry->d_name;
    struct stat statbuf;
    if (stat(fname.c_str(), &statbuf)) {
      if (gen_warnings)
        warn << "[fswatch] cannot stat " << fname << ": "
             << strerror(errno) << "\n";
      continue;
    }

    // Recurse into subdirs, store true files
    if (statbuf.st_mode & S_IFDIR)
      listdir(fname.c_str());
    else if (statbuf.st_mode & S_IFREG) {
      Entry e = { fname, statbuf };
      entry.push_back(e);
      sz++;
    }
  }
  closedir(d);
}
