#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>
#include <math.h>

void *CountA(void *arg){
    struct timespec startA, endA;
    clock_gettime(CLOCK_REALTIME, &startA);
    nice(0);
    long long int result=pow(2,32);
    long long int count=0;
    for(long long int i=1;i<result;i++){
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &endA);
    double timeA = (endA.tv_sec - startA.tv_sec) * 1000000000 + (endA.tv_nsec - startA.tv_nsec);
    printf("Time taken by thread A is: %lf\n", (timeA/(long long int)pow(10,9)));
    return NULL;
}

void *CountB(void *arg){
    struct timespec startB, endB;
    clock_gettime(CLOCK_REALTIME, &startB);
    long long int result=pow(2,32);
    long long int count=0;
    for(long long int i=1;i<result;i++){
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &endB);
    double timeB = (endB.tv_sec - startB.tv_sec) * 1000000000 + (endB.tv_nsec - startB.tv_nsec);
    printf("Time taken by thread B is: %lf\n", (timeB/(long long int)pow(10,9)));
    return NULL;
}

void *CountC(void *arg){
    struct timespec startC, endC;
    clock_gettime(CLOCK_REALTIME, &startC);
    long long int result=pow(2,32);
    long long int count=0;
    for(long long int i=1;i<result;i++){
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &endC);
    double timeC = (endC.tv_sec - startC.tv_sec) * 1000000000 + (endC.tv_nsec - startC.tv_nsec);
    printf("Time taken by thread C is: %lf\n", (timeC/(long long int)pow(10,9)));
    return NULL;
}

int main(){
    pthread_t thrA, thrB, thrC;
    pthread_create(&thrA, NULL, &CountA, NULL);
    pthread_create(&thrB, NULL, &CountB, NULL);
    pthread_create(&thrC, NULL, &CountC, NULL);
    struct sched_param parA, parB, parC;
    parB.sched_priority = 1;
    parC.sched_priority = 1;
    pthread_setschedparam(thrA, SCHED_OTHER, &parA);
    pthread_setschedparam(thrB, SCHED_RR, &parB);
    pthread_setschedparam(thrC, SCHED_FIFO, &parC);
    pthread_join(thrA, NULL);
    pthread_join(thrB, NULL);
    pthread_join(thrC, NULL);
    return 0;
}
