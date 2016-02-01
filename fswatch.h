#ifndef _FSWATCH_H_
#define _FSWATCH_H_

#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <iostream>
#include <string>
#include <unordered_map>

#include "messager.h"
extern Messager msg;
extern Messager err;
extern Messager warn;

extern void usage();

#endif // _FSWATCH_H_
