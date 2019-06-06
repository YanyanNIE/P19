#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

void initTab(bool tab[],int n) {
    for(int i = 3; i < n; i+=2) tab[i] = true;
}

void eratostene(bool tab[],int n) {
    tab[2] = true;
    for(int i = 3; i*i < n + 1; i+=2)
        if(tab[i])
            for(int j = i*i; j < n; j += 2*i) tab[j]=false;
}

void affichePremier(bool tab[],int n) {
    int j = 0;
    printf("nombre premiers de 1 à %d\n", n);
    for (int i = 0; i < n; i++) 
        if (tab[i]) 
            printf("%d ", i);
        printf("\n");   
}

double timeval_diff(struct timeval *begin, struct timeval *end){
    return 
        (double)(end->tv_sec + (double)end->tv_usec/1000000) -
        (double)(begin->tv_sec + (double)begin->tv_usec/1000000);
}


int main(int argc, char const *argv[])
{
    bool *tab;
    int n=atoi(argv[1]);
    struct timeval begin;
    struct timeval end;

    tab=malloc(n*sizeof(int));

    initTab(tab,n);
    gettimeofday(&begin,NULL); 
        eratostene(tab,n);
    gettimeofday(&end,NULL); 

    affichePremier(tab,n);
    double timer = timeval_diff(&begin,&end);
    printf("Time used = %.16g us\n", timer*1000000.0);
    

    free(tab);
    return 0;
}