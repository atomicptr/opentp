// unistd.h replacement for Windows
// Author: AShelly <http://stackoverflow.com/a/826027>
// modified for OpenTP <https://github.com/Kasoki/opentp> usage
#ifndef _UNISTD_H
#define _UNISTD_H 1

#include <stdlib.h>
#include <io.h>
#include <process.h>

#define srandom srand
#define random rand

#define R_OK 4 
#define W_OK 2
#define F_OK 0

#define access _access
#define ftruncate _chsize

#define ssize_t int

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif /* unistd.h  */