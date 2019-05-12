#include "semaph.h"

int main(int argc, char *argv[]){
    init_semaphore();
    val_sem(2,1);
    P(2);
    sleep(10);
    V(2);
    detruire_semaphore();
    printf("seml/main: fin");
    return 0;
}

// ar rcs libsempv.a sem_pv.o 
// gcc -o seml seml.c -L. libsempv.a
// ./seml &
// ipcs -s