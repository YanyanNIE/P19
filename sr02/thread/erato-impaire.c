#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

void showPremier(bool* A,int taille){
    printf("erato-impaire.c/mian::show premier:\n");
    printf("2 ");
    for(int t=1;t<taille;t++){
        if(A[t]==true){
            printf("%d ",2*t+1);
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
        printf("erato-impaire.c/mian: ERROR argument needed!\n");
        exit(-1);
    }

    int n = atoi(argv[1]);

    if(n<=1){
        printf("erato-impaire.c/mian: ERROR argument little than 1!\n");
        exit(-1);
    }

    int taille;
    if (n%2 == 0) taille=(int) n/2;
    else taille = (int) (n/2 + 1);
    printf("erato-impaire.c/mian: taille= %d\n", taille);
    bool A[taille];
    // initialiser tab A
    // printf("erato-impaire.c/mian:initialisation A\n");
    for(int t=0;t<taille;t++){
        A[t] = true;
    }

    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin,NULL); 
    
    for(int i = 3;i <= (int)sqrt(n);i=i+2){  
        int coef=0;
        while(i*i+coef*i<=n){
            int residu = (i*i+coef*i)%2;
            if(residu){
                int index = (int) (i*i+coef*i)/2;
                if(A[index] == true)
                    A[index] = false; 
            }
            coef++;
        }
           
    }
    gettimeofday(&end,NULL); 
    double timer = timeval_diff(&begin,&end);
    printf("Time used = %.16g us\n", timer*1000000.0);

    // showPremier(A,taille);
    return 0;
}

// gcc erato-impaire.c -o erato-impaire -lm