#include "semaph.h"
#include "sharemem.h"
#include <wait.h>

#define BUFFER_SIZE 5

__pid_t pid;
int n =1, i=0;

void outputTampon(int *tampon){
    for (int i = 0; i < BUFFER_SIZE; i++){
        if(tampon[i]!=0)
            printf("%d ", tampon[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{   
    int shmid = createshm();
    int *tampon = bindshm(shmid);
    srand(time(0));

    init_semaphore();
    val_sem(2,BUFFER_SIZE);
    val_sem(3,0);

    switch (pid=fork()) {
        case -1:
            perror("prod-conso/fork: Echec\n");
            break;
        case 0:
            while(n<10){ 
                P(2);
                // printf("prod-conso/prod:%d\n",n);
                tampon[i] = rand() % 50 + 1;
                printf("produit: %d ---",tampon[i]);
                i = (i+1) % BUFFER_SIZE;
                printf("tampon:");
                outputTampon(tampon);
                V(3);
                n++;
                usleep(((rand()%(100-20))+20)*1000); 
            }
            break;
        default:
            while(n<10){
                usleep(((rand()%(100-20))+20)*1000);
                P(3);
                // printf("prod-conso/conso:%d\n", n);
                printf("consomme: %d ---",tampon[i]);
                tampon[i] = 0;
                i = (i+1) % BUFFER_SIZE;
                printf("tampon:");
                outputTampon(tampon);
                V(2);
                n++;
            }
    }
    wait(NULL);
    detruire_semaphore();
    shmdt(tampon);
    shmctl(shmid,IPC_RMID,0); 
    return 0;
}

/******
 * 
 * ar rvs libsempv.a sem_pv.o sharemem.o
 * gcc -o prod-conso-alea prod-conso-alea.c -L. libsempv.a
 * ./prod-conso-alea
 * 
 * *********/