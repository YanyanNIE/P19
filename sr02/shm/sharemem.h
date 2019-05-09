#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#define SHMSZ 27
#define MAXSIZE 1024
// #define FLAGS O_RDWR | O_APPEND
#define FLAGS O_RDONLY

#define PROT_FLAGS PROT_READ|PROT_WRITE