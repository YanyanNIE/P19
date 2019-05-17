#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ 5 * sizeof(int)

int createshm(void);
int* bindshm(int);
void initshmE(int*);
void initshmBuffers(int*);