#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <unistd.h>

int main() {
  pid_t pid1,pid2,pid3;
  struct sched_param parA, parB, parC;
  
  parA.sched_priority = 10;
  parB.sched_priority = 30;
  parC.sched_priority = 20;
  
  struct timespec startA, endA;
  
  clock_gettime(CLOCK_REALTIME, &startA);
  pid1 = fork();
  
  if (pid1== 0) {
    printf("Child process is running1\n");
    sched_setscheduler(getpid(),SCHED_OTHER,&parA);
    execl("/bin/bash","sh","compile_kernel1.sh",NULL);
    exit(0);
  } 
    
  else {
    printf("Parent process is running1\n");
    struct timespec startB, endB;
    clock_gettime(CLOCK_REALTIME, &startB);
    pid2 = fork();
    if (pid2== 0) {
      printf("Child process is running2\n");
      sched_setscheduler(getpid(),SCHED_RR,&parB);
      execl("/bin/bash","sh","compile_kernel2.sh",NULL);
      exit(0);
    } 
    else {
      printf("Parent process is running2\n");
      struct timespec startC, endC;
      clock_gettime(CLOCK_REALTIME, &startC);
      pid3 = fork();
      if (pid3 == 0) {
        printf("Child process is running3\n");
        sched_setscheduler(getpid(),SCHED_FIFO,&parC);
        execl("/bin/bash","sh","compile_kernel3.sh",NULL);
        exit(0);
      } 
      else {
        printf("Parent process is running4\n");
        for(int i=0;i<3;i++) {
            pid_t lastpid;
            lastpid=waitpid(0,NULL,0);
            if(lastpid==pid1) {
                printf("Child process 1 is finished\n");
                clock_gettime(CLOCK_REALTIME, &endA);
                double timeA = (endA.tv_sec - startA.tv_sec) * 1000000000 + (endA.tv_nsec - startA.tv_nsec);
                printf("Time taken by Process A is %lf\n", (timeA/(long long int)pow(10,9)));
            }
            else if(lastpid==pid2) {
                printf("Child process 2 is finished\n");
                clock_gettime(CLOCK_REALTIME, &endB);
                double timeB = (endB.tv_sec - startB.tv_sec) * 1000000000 + (endB.tv_nsec - startB.tv_nsec);
                printf("Time taken by Process B is %lf\n", (timeB/(long long int)pow(10,9)));
            }
            else if(lastpid==pid3) {
                printf("Child process 3 is finished\n");
                clock_gettime(CLOCK_REALTIME, &endC);
                double timeC = (endC.tv_sec - startC.tv_sec) * 1000000000 + (endC.tv_nsec - startC.tv_nsec);
                printf("Time taken by Process C is %lf\n", (timeC/(long long int)pow(10,9)));
            }
        }
      }
    }
  }
  return 0;
}
