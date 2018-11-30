#ifndef _FSSTATE_H_
#define _FSSTATE_H_

#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>

class FsState {
 public:
  FsState(std::vector<std::string> dirs, std::vector<std::string> files,
          bool keepscanning = false, bool scanallfiles = false);
  unsigned size() const;
  bool differs(FsState const &other) const;
  void rescan(bool keepscanning = false, bool scanallfiles = false);

  // for debugging
  void dump(std::string title) const;

  // Entry must be public so that the helper function for sorting sees it,
  // see fsstatesortentries.cc
  typedef struct {
    std::string name;
    struct stat statbuf;
  } Entry;

 private:
  std::vector<std::string> sdirs;
  std::vector<std::string> sfiles;
  std::vector<Entry> entry;
  void listdir(std::string d, bool scanallfiles);
  void sortentries();
  unsigned sz;
  static bool be_silent;
};

#endif // _FSSTATE_H_
