#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

__pid_t pid;

void handler_fils(){
    printf("\n%i\n",rand()%(40-10+1)+10 );
    fflush(stdout);
}

void handler_pere(){
    kill(pid,SIGUSR1);
    alarm(5);
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
      while (1) {
          pause();
      }
      break;
    default:
      sa_pere.sa_handler=&handler_pere;
      sa_pere.sa_flags=0;
      sigemptyset(&sa_pere.sa_mask);
      sigaction(SIGALRM,&sa_pere,0);
      alarm(5);
      while (1) {
          printf("-" );
          fflush(stdout);
          sleep(1);
        }
  }


  return 0;

}
