# include "sharemem.h"

int createshm(){
    int shmid;
    key_t key;
    key = IPC_PRIVATE;
    shmid = shmget(key,SHMSZ, IPC_CREAT | 0666);
    if (shmid < 0){
        perror("shmget");
        exit(1);
    }
    return shmid;
}

int copiefichier(int f1,int f2){
    char buf[MAXSIZE];
    int size=0,tmps ;
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
    if ((fd= open(f,FLAGS)) == -1){
        printf("\nEchec d'overture de ficher: %s", f);
        exit(2);
    }
    return fd;
}

int main(int argc, char *argv[])
{
    if(argc<3) exit(-1);
    int shmid = createshm();
    char *shm, *s;
    if((shm=shmat(shmid,NULL,0)) == (char*)-1){
        perror("shmat");
        exit(1);
    }
    s = shm;

    int fd1,fd2;
    int sizef1, sizef2;

    fd1 = openFicher(argv[1]);
    fd2 = openFicher(argv[2]);

    switch (fork()) {
    case -1:
      perror("Echec de creation.");
      exit(2);
      break;
    case 0:       
      sizef2 = copiefichier(fd2, fileno(stdout));
      *s = sizef2; 
      break;
    default:
      wait(NULL);
      sizef1 = copiefichier(fd1, fileno(stdout));
      printf("Octes lus par pere: %d\n",sizef1);
      printf("Octes lus par fils: %d\n",*s);
      *s += sizef1; 
      printf("Octes total: %d\n",*s);    
    }
    close(fd1);
    close(fd2);
    shmdt(shm);
    shmdt(s);
    shmctl(shmid,IPC_RMID,0); 
    return 0;

}
