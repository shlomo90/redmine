#ifndef __REDMINE_H__
#define __REDMINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/errno.h>

#include <fcntl.h>
#include <unistd.h>

#include "file.h"

#define MAX_PATH_LENGTH 200
#define REDMINE_DB      ".redmine"
#define ORIGIN_URL      "origin"

#define NUMELEM(var)    (unsigned int)(sizeof(var) / sizeof(var[0]))

int init_main(int argc, char* argv[]);
int open_main(int argc, char* argv[]);


#endif
