#ifndef _FSSTATE_H_
#define _FSSTATE_H_

#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>

class FsState {
 public:
  FsState(std::vector<std::string> dirs, bool keepscanning = false,
          bool scanallfiles = false);
  unsigned size() const;
  bool differs(FsState const &other) const;
  void rescan(bool keepscanning = false, bool scanallfiles = false);

  // for debugging
  void dump(std::string title) const;

 private:
  typedef struct {
    std::string name;
    struct stat statbuf;
  } Entry;

  std::vector<std::string> sdirs;
  std::vector<Entry> entry;
  void listdir(std::string d, bool scanallfiles);
  unsigned sz;
  static bool be_silent;
};

#endif // _FSSTATE_H_
