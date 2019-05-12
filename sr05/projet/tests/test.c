#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/poll.h>
#include <unistd.h>

#include "sem_pv.h"

void process_input();
void process_output();
pid_t create_process(void (*f)(void));

int main(int argc, char** argv) {
  //Atomic
  init_semaphore();
  val_sem(0, 1);

  create_process(process_output);
  process_input();

  // Waiting for 2 childs
  wait(NULL);
  //wait(NULL);

  detruire_semaphore();

  return 0;
}

pid_t create_process(void (*fct)(void)) {
  pid_t pid = fork();

  switch(pid) {
    case 0: // Process child
      (*fct)();
    case -1: // Erreur
      return -1;

    default: // Process parent
      if(fct != process_output) return 0;
        create_process(process_output);
  }

  return pid;
}

void process_input() {
  fd_set rfds;
  int retval;
  char buf[256];
  struct timeval tv = {0, 0};


  while(1) {

    fgets(buf, 256, stdin);
    P(0);
    fprintf(stderr, "Process input lancé\n");
    fprintf(stderr,"LU: %s\n", buf);

    /*
    fprintf(stderr, "Process input lancé\n");

    struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };
    int ret = poll(&pfd, 1, 0);
   if(ret == 1) {
    	fscanf(stdin, "%s", buf);
    	fprintf(stderr, "LU: %s\n", buf);
   } else if (ret == 0) {
   	fprintf(stderr, "Rien reçu\n");
   }
   */
    /*

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    retval = select(0, &rfds, NULL, NULL, &tv);
    fprintf(stderr, "retval=%d\n", retval);

    gets(buf);
    fprintf(stderr, "LU: %s\n", buf);
    */

    /*
    if(retval == -1) perror("select in process_input\n");
    else if(retval)
    {
      //while(getchar() != '\n');
      fprintf(stderr, "LU: %s\n", buf);
    }
    */

    V(0);
    sleep(1);
  }
}

void process_output() {
  while(1) {
      P(0);
      fprintf(stderr, "Process output lancé\n");

      fprintf(stdout, "*\n\0");
      fflush(stdout);

      V(0);
      sleep(2);
  }
}
