#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ 27

int createshm(void);
int* bindshm(int);
void initshm(int*);