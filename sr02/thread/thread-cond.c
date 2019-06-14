#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFFER_SIZE 4

int buffer[BUFFER_SIZE];

int readpos=0, writepos=0, count=0; 
pthread_cond_t notempty;
pthread_cond_t notfull; 
pthread_mutex_t lck;

void showBuffer(){
    printf("thread-cond/showBuffer:");
    for(int i=0; i<BUFFER_SIZE; i++)
        printf("%d ", buffer[i]);
    printf("\n");
}
void produce() { 
    sleep(1); 
    buffer[writepos]+=1;
    printf("++produce buffer[%d]=%d\n",writepos, buffer[writepos]);
    showBuffer();
} 

void consume () { 
    sleep(2);
    printf("--consume buffer[%d]=%d\n",readpos,buffer[readpos]);
    buffer[readpos]-=1;
    showBuffer();
 } 

void *prod (void *data) { 
    printf("thread-cond/producteur: Start\n");
    while (true){
        produce(); 
        count ++; 
        pthread_mutex_lock(&lck);
        while(count == BUFFER_SIZE) { // si plein
            printf("thread-cond/producteur: producer bloqué\n");
            pthread_cond_wait(&notfull, &lck); 
        }
        writepos++;
        if (writepos>= BUFFER_SIZE) 
            writepos=0; 
        pthread_cond_signal(&notempty); 
        pthread_mutex_unlock (&lck);
    } 
}

void *cnsmr (void *data) {
    printf("thread-cond/consommateur: Start\n"); 
    while (true){
        pthread_mutex_lock(&lck); 
        while(count == 0)
            pthread_cond_wait(&notempty, &lck);
        if (readpos == BUFFER_SIZE) 
            readpos=0; 
        if (count == BUFFER_SIZE-1) {
            printf("thread-cond/consommateur:Buffer nou full\n");
            pthread_cond_signal(&notfull);
        }
        pthread_mutex_unlock (&lck); 
        consume();
        count --; 
        readpos++;
    }
}


int main(){ 
    printf("********thread-cond/main********\n");
    pthread_t pth, cth;
    void * retval ; 
    pthread_cond_init(&notempty, 0); 
    pthread_cond_init(&notfull, 0); 
    pthread_mutex_init(&lck, 0); 
    readpos=0; 
    writepos=0; 
    count=0; 
    pthread_create(&pth, 0, prod, 0); 
    pthread_create(&cth, 0, cnsmr, 0);
    sleep(10);
}

// gcc -pthread thread-cond.c -o thread-cond