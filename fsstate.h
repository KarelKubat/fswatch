#ifndef _FSSTATE_H_
#define _FSSTATE_H_

#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>

class FsState {
 public:
  FsState(char const *dir);
  unsigned size() const;
  bool differs(FsState const &other) const;
  void rescan();

  // for debugging
  void dump(std::string title) const;

 private:
  typedef struct {
    std::string name;
    struct stat statbuf;
  } Entry;

  std::string sdir;
  std::vector<Entry> entry;
  void listdir(std::string d);
  unsigned sz;
  static bool be_silent;
};

#endif // _FSSTATE_H_
