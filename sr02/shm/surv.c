# include "sharemem.h"

int copiefichier(int f1,int f2){
    char buf[MAXSIZE];
    int size=0, tmps;
    lseek(f1,0,SEEK_SET);
    while(1){
        if ((tmps= read(f1,buf,MAXSIZE)) >0){
            size += tmps;
            write(f2,buf,tmps);  
        } else break;

    }
    
    return size;
}

int openFicher(char *f){
    int fd;
    if ((fd= open(f,FLAGS, 0666)) == -1){
        printf("\nEchec d'overture de ficher: %s", f);
        exit(2);
    }
    return fd;
}

int main(int argc, char *argv[])
{   
    if(argc<3) exit(-1);
    int fd1,fd2;
    int sizef1, sizef2;

    fd1 = openFicher(argv[1]);
    fd2 = openFicher(argv[2]);

    switch (fork()) {
    case -1:
      perror("Echec de creation.");
      exit(3);
      break;
    case 0:       
      sizef2 = copiefichier(fd2, fileno(stdout));
      printf("fils: Octes lus: %d\n",sizef2); 
      break;
    default:
      sizef1 = copiefichier(fd1, fileno(stdout));
      printf("pere: Octes lus: %d\n",sizef1);
      
    }
    close(fd1);
    close(fd2);
    return 0;


}
