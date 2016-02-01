#ifndef _MSG_H_
#define _MSG_H_

#include <iostream>
#include <string>

class Messager {
 public:
  Messager(bool act, bool fat, std::ostream *o);
  Messager &operator<< (char const *s);
  Messager &operator<< (std::string s);
  Messager &operator<< (int i);
  Messager &operator<< (unsigned u);
  bool active(bool act);

 private:
  bool is_active, is_fatal;
  std::ostream *os;
};

#endif // _MSG_H_
