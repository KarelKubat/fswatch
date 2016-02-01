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

 private:
  typedef struct {
    std::string name;
    struct stat statbuf;
  } Entry;
  std::vector<Entry> entry;
  void listdir(char const *dir);
  unsigned sz;
};

#endif // _FSSTATE_H_
