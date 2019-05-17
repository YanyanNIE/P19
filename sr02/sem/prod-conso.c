#include "semaph.h"
#include "sharemem.h"
#include <wait.h>

#define BUFFER_SIZE 5

int main(int argc, char *argv[])
{   
    int shmid = createshm();
    int *tampon = bindshm(shmid);
    srand(time(0));

    init_semaphore();
    val_sem(2,BUFFER_SIZE);
    val_sem(3,0);

    int i = 0 ;
    switch (fork()) {
        case -1:
            perror("prod-conso/fork: Echec\n");
            break;
        case 0:
           for(i;i<10;i++){ 
                P(2);
                tampon[i%BUFFER_SIZE] = i + 1;
                printf("produit: %d \n",tampon[i%BUFFER_SIZE]);
                V(3);
                usleep(((rand()%(100-20))+20)*1000); 
            }
            break;
        default:
            for(i;i<10;i++){
                usleep(((rand()%(100-20))+20)*1000);
                P(3);
                printf("consomme: %d \n",tampon[i%BUFFER_SIZE]);
                V(2);
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
 * gcc -o prod-conso prod-conso.c -L. libsempv.a
 * ./prod-conso
 * 
 * *********/