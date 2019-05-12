#include "semaph.h"
#include "sharemem.h"


__pid_t pid;
int npere =1, nfils = 1;

void quatre(int *shm){
    int A = *shm;
    usleep(((rand()%(100-20))+20)*1000); 
    A = A+1;
    *shm = A; 
}


int main(int argc, char *argv[])
{   

    int shmid = createshm();
    int *shm = bindshm(shmid);
    initshm(shm);
    srand(time(0));

    init_semaphore();
    val_sem(2,1);

    switch (pid=fork()) {
        case -1:
            perror("excl-mutu-none/fork: Echec\n");
            break;
        case 0:
            while(nfils<=100){ 
                P(2);
                printf("excl-mutu-none/fils: %d\n", nfils);
                quatre(shm);
                V(2);
                usleep(((rand()%(100-20))+20)*1000);
                nfils = nfils+1;
                // printf("excl-mutu-none/fils: E = %d\n", *shm);
            }
            break;
        default:
            while(npere<=100){
                printf("excl-mutu-none/pere: %d\n", npere);
                P(2);
                quatre(shm);
                V(2);
                usleep(((rand()%(100-20))+20)*1000);
                npere = npere+1;
                // printf("excl-mutu-none/pere: E = %d\n", *shm);
            }
            printf("excl-mutu-none/pere: E = %d\n", *shm);
    }

    detruire_semaphore();
    shmdt(shm);
    shmctl(shmid,IPC_RMID,0); 
    return 0;
}

/******
 * 
 * ar rvs libsempv.a sem_pv.o sharemem.o
 * gcc -o excl-mutu-none excl-mutu-none.c -L. libsempv.a
 * ./excl-mutu-none
 * 
 * *********/