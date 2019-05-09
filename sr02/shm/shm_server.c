# include "sharemem.h"

int createshm(){
    int shmid;
    key_t key; 
    key = 2017;
    shmid = shmget(key, SHMSZ, IPC_CREAT|0666);
    if (shmid < 0){
        perror("Echec shmget");
        exit(1);
    }
    printf("Creer Shmid = %d", shmid);
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
  
  memset(shm,0,sizeof(shm)-1);

  s=shm;
  for (char c='a';c <='z';c++){
    *s++=c;
  }
  *s=NULL;

  while (*shm != '*'){
    sleep(1);
  }

  shmdt(shm);
  shmdt(s);
  shmctl(shmid,IPC_RMID,0);      
  
  return 0;


}
