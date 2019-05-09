#include "sharemem.h"

int main(int argc, char *argv[]) {
    int fd;
    struct stat etatfic;
    long taillefic;
    int taille;
    int tmp;
    
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

    for(int i = 0; i<taille/2;i++){
        tmp = projetcion[i];
        projetcion[i] = projetcion[taille-i-1];
        projetcion[taille-i-1] = tmp;
    }

    munmap((void*)projetcion,taillefic);
    return 0;
} 