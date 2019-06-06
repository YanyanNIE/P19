#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

#define NUM_TH 7

/* struct utilise pour passer les auguments vers thread routine */
struct th_plage {
    int num_id;
    int start;
    int end;
};


bool *A;

/* declarer des fonctions*/
void showPremier(bool* A,int n);
void* thRoutine(void* th_arg);
double timeval_diff(struct timeval *begin, struct timeval *end);

/* MAIN */
int main(int argc, char* argv[]){
     if (argc != 2){
        printf("erato-seq.c/mian: ERROR argument needed!\n");
        exit(-1);
    }

    int n = atoi(argv[1]);
    if(n<=1){
        printf("erato-seq.c/mian: ERROR argument little than 1!\n");
        exit(-1);
    }

    /* Variables */
    pthread_t *th_id;
    struct th_plage *th_arg;
    th_id = (pthread_t *)malloc(sizeof(pthread_t)*NUM_TH);
    th_arg = (struct th_plage *)malloc(sizeof(struct th_plage)*NUM_TH);

    int div_result = (int) n/NUM_TH;
    int div_residu = n % NUM_TH;

    struct timeval begin;
    struct timeval end;
    
    /* Initialiser tab A */
    A = (bool *)malloc(sizeof(bool)*n);
    for(int i=2;i<n+1;i++){
        A[i] = true;
    }

    int k = 1;
    gettimeofday(&begin,NULL);
    for(int i=0;i < NUM_TH;i++){
        th_arg[i].num_id = i;
        th_arg[i].start = k;
        if (i < div_residu)
            k = k + div_result + 1;
        else
            k = k + div_result;
        th_arg[i].end = k-1;
        pthread_create(&th_id[i],NULL,thRoutine,(void*) &th_arg[i]);
        pthread_join(th_id[i], NULL);
    }

    gettimeofday(&end,NULL); 

    // unsigned long timer = 1000000L * (end.tv_sec - begin.tv_sec) + end.tv_usec - begin.tv_usec;
    double timer = timeval_diff(&begin,&end);
    printf("Time used = %.16g us\n", timer*1000000.0);
    // showPremier(A,n);
    
    free(A);
    free(th_id);
    free(th_arg);

   
    return 0;
}

double timeval_diff(struct timeval *begin, struct timeval *end){
    return 
        (double)(end->tv_sec + (double)end->tv_usec/1000000) -
        (double)(begin->tv_sec + (double)begin->tv_usec/1000000);
}

void showPremier(bool* A,int n){
    printf("All premier within %d:\n", n);
    for(int i=2;i<n+1;i++){
        // printf("A[%d]=%d--", i,A[i]);
        if(A[i]==true){
            printf("%d ",i);
        }
    }
    printf("\n");
}

void* thRoutine(void* th_arg){
    pthread_t th_id = pthread_self();
    struct th_plage * arg;
    arg = (struct th_plage *) th_arg;
    int id = arg->num_id;
    int start = arg->start;
    int end = arg->end;

    printf("Thread %d : with ID %ld travaille sur %d et %d.\n",id,th_id,start, end);
    int k = 2;
    while (k*k <= end){
        int i;
        int temp;
        if(k*k < start){
            if(start%k == 0) temp = start;
            else temp = start+(k-start%k);
            for (i= temp; i <= end; i += k){
                A[i] = false;
            }
               
        }
        else 
            for(i = k*k; i <= end; i += k){
                A[i] = false;  
            }

                
        k++;
    }
    pthread_exit(NULL);

}

// gcc -pthread erato-ll.c -o erato-ll
