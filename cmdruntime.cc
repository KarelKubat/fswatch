#include "fswatch.h"
#include "cmd.h"

unsigned Cmd::runtime() const {
  return (unsigned) (time(0) - starttime);
}
