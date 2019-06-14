#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lck;
int ia=0, ja=0;

void *prod1 (void *arg) {
  printf("thread-mutex/producteur1: start\n");
  pthread_mutex_lock(&lck);
  ia++; 
  ja++ ; 
  printf("thread-mutex/producteur1:ia=%d, ja=%d\n",ia, ja);
  sleep(2);
  pthread_mutex_unlock(&lck);

}

void *prod2 (void *arg) { 
  printf("thread-mutex/producteur2: start\n");
  pthread_mutex_lock(&lck);
  ia++; 
  sleep(1); 
  ja++ ;
  printf("thread-mutex/producteur2:ia=%d, ja=%d\n",ia, ja);
  pthread_mutex_unlock(&lck);
  
}

void *cnsmr (void *arg) { 
  printf("thread-mutex/consommateur: start\n");
  sleep(1);
  pthread_mutex_lock(&lck);
  printf("thread-mutex/consommateur:ia=%d, ja=%d\n",ia, ja);
  pthread_mutex_unlock(&lck);
}

void main () {
  printf("********thread-mutex/main********\n");
  pthread_t pth1, pth2, cth; 
  void *rval;
  int pthr1,pthr2,pthr3; 

  pthread_mutex_init(&lck, 0);
  pthr1=pthread_create(&pth1,0,prod1,0); 
  pthr2=pthread_create(&pth2,0,prod2,0); 
  pthr3=pthread_create(&cth,0,cnsmr,0);
  sleep(10);
}
  
// gcc -pthread thread-mutex.c -o thread-mutex