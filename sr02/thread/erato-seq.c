#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

void showPremier(bool* A,int n){
    printf("erato-seq.c/mian::test:\n");
    for(int i=2;i<n+1;i++){
        if(A[i]==true){
            printf("%d ",i);
        }
    }
    printf("\n");
}

double timeval_diff(struct timeval *begin, struct timeval *end){
    return 
        (double)(end->tv_sec + (double)end->tv_usec/1000000) -
        (double)(begin->tv_sec + (double)begin->tv_usec/1000000);
}

int main(int argc, char* argv[]){
    
    if (argc != 2){
        printf("erato-seq.c/mian: ERROR argument needed!");
        exit(-1);
    }

    int n = atoi(argv[1]);

    if(n<=1){
        printf("erato-seq.c/mian: ERROR argument little than 1!");
        exit(-1);
    }

    bool A[n];
    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin,NULL);
    // initialiser tab A
    for(int i=2;i<n+1;i++){
        A[i] = true;
    }

    for(int i = 2;i <= (int)sqrt(n);i++){
        if (A[i]==true){
            int ii=i*i;
            int coef=0;
            while(ii+coef*i<=n){
                A[ii+coef*i] = false;
                coef++;
            }
        }
    }
    gettimeofday(&end,NULL); 
    // unsigned long timer = 1000000L * (end.tv_sec - begin.tv_sec) + end.tv_usec - begin.tv_usec;
    double timer = timeval_diff(&begin,&end);
    printf("Time used = %.16g us\n", timer*1000000.0);

    // showPremier(A,n);
    return 0;
}

// gcc erato-seq.c -o erato-seq -lm