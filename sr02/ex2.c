#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

__pid_t pid;
int posa='a',posA='A';
int lena=1,lenA=1;

void handler_fils(){
    int i=0;
    for (i;i<lena; i++){
      if(posa+i<='z'){
        printf("%c",posa+i);
        fflush(stdout);
      }
    }
    lena++;
    posa+=i; 
    kill(getppid(),SIGUSR1); 
}

void handler_pere(){    
    int i=0;
    for (i;i<lenA; i++){
      if(posA+i<='Z'){
        printf("%c",posA+i);
        fflush(stdout);
      }
    }
    lenA++;
    posA+=i;
    kill(pid,SIGUSR1);
}

int main(){
  srand(time(NULL));
  struct sigaction sa_fils,sa_pere;
  switch (pid=fork()) {
    case -1:
      perror("Echec de creation.");
      exit(2);
      break;
    case 0:
      sa_fils.sa_handler=&handler_fils;
      sa_fils.sa_flags=0;
      sigemptyset(&sa_fils.sa_mask);
      sigaction(SIGUSR1,&sa_fils,0);
      while (lena<8) {
          pause();
      }
      break;
    default:
      sa_pere.sa_handler=&handler_pere;
      sa_pere.sa_flags=0;
      sigemptyset(&sa_pere.sa_mask);
      sigaction(SIGUSR1,&sa_pere,0);
      sleep(1);
      kill(pid,SIGUSR1); 
      while (lenA<8) {
          pause();
        }
  }
  return 0;

}
