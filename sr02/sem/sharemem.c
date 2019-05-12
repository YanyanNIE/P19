#include "sharemem.h"

int createshm(void){
    int shmid;
    key_t key; 
    key = 2017;
    shmid = shmget(key, SHMSZ, IPC_CREAT|0666);
    if (shmid < 0){
        perror("sharemem.c/createshm: shmget\n");
        exit(1);
    }
    printf("Creer Shmid = %d\n", shmid);
    return shmid;
}

int* bindshm(int shmid){
    int *shm;
    if((shm=shmat(shmid,NULL,0)) == (int*)-1){
        perror("sharemem.c/bindshm: Echec\n");
        exit(1);
    }
    return shm;
}

void initshm(int *shm){
    *shm = 0;
}

// gcc -c sharemem.c