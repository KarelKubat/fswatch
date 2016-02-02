#include "fswatch.h"
#include "fsstate.h"
#include "messager.h"

static bool gen_warnings = true;
static std::unordered_map<std::string, bool> filewarning;

void FsState::listdir(std::string sdir) {
  DIR *d = opendir(sdir.c_str());
  if (! d) {
    if (gen_warnings)
      warn << "[fswatch] cannot read " << sdir << ": "
           << strerror(errno) << "\n";
    return;
  }

  struct dirent *direntry;
  while ( (direntry = readdir(d)) ) {
    // Skip . and ..
    if (!strcmp(direntry->d_name, ".") || !strcmp(direntry->d_name, ".."))
      continue;
    // Build up full path & stat it
    std::string fname = sdir;
    fname += "/";
    fname += direntry->d_name;
    struct stat statbuf;
    if (stat(fname.c_str(), &statbuf)) {
      if (gen_warnings)
        if (! filewarning[fname]) {
          filewarning[fname] = true;
          warn << "[fswatch] cannot stat " << fname << ": "
               << strerror(errno) << "\n";
        }
      continue;
    }

    // Recurse into subdirs, store true files
    if (statbuf.st_mode & S_IFDIR)
      listdir(fname);
    else if (statbuf.st_mode & S_IFREG) {
      Entry e = { fname, statbuf };
      entry.push_back(e);
      sz++;
    }
  }
  closedir(d);
}
