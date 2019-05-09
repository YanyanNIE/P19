#include "sharemem.h"

int main(int argc, char *argv[]) {
    int fd;
    struct stat etatfic;
    long taillefic;
    int taille;
    
    int *projetcion;
    int stdi=0; 

    // ouvrir fichier
    fd=open("titi.dat",O_RDWR,0666);
    stat("titi.dat",&etatfic);
    taillefic = etatfic.st_size;
    taille = taillefic/sizeof(int);

    // projeter 
    projetcion = (int*) mmap(NULL,taillefic,PROT_FLAGS, MAP_SHARED,fd,0);
    if(projetcion==(int*)MAP_FAILED){
        perror("Echec mmap\n");
        exit(-1);
    }
    close(fd);

    while (stdi != 99){
        printf("\nEntrez un nombre(99 pour sortir):");
        scanf("%d",&stdi);
        projetcion[(stdi+taille)%taille] += 1;
        
    }

    munmap((void*)projetcion,taillefic);
    return 0;
} 