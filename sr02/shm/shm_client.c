# include "sharemem.h"

int createshm(){
    int shmid;
    key_t key; 
    key = 2017;
    shmid = shmget(key, SHMSZ, IPC_CREAT|0666);
    if (shmid < 0){
        perror("shmget");
        exit(1);
    }
    printf("Creer Shmid = %d\n", shmid);
    return shmid;
}

int main(int argc, char *argv[])
{   

  int shmid = createshm();
  char *shm,*s;
  if((shm=shmat(shmid,NULL,0)) == (char*)-1){
    perror("Echec shmat");
    exit(1);
  }

  for (s=shm; *s != NULL;s++){
    putchar(*s);
  }
  putchar('\n');

  *shm = '*';


  return 0;
}
