#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define CNT 20

int main(void){
  int cnt = CNT;
  int *ids;
  ids = malloc  (sizeof(int)*CNT);
  while(--cnt>=0)
  {
      int r = 310 + rand()%10;
    ids[cnt]=fork();
    if(ids[cnt] == 0)
    { 
//    printf("is child\n");
      sleep(r);
      printf("I'm exit - %d\n",getpid());
      //printf("rand=%d\n",r);
      return 0;
    }
   }
  int pc =0 ; //terminated processes
  while(1){ 
    int pid;
    int status;
    pid = wait(&status);
    if(pid == -1){
      printf("no childs here");
      exit(0);
    }
    printf("process %d with id=%d and status=%d exited\n",++pc,pid,status);
  }
  return 0;
}


//     
//    max 23:27:59   fork  (master) $ ./wait &
//    [1] 981
//    max 23:28:09   fork  (master) $ ps
//      PID TTY          TIME CMD
//      981 pts/0    00:00:00 wait
//      983 pts/0    00:00:00 wait
//      984 pts/0    00:00:00 wait
//      985 pts/0    00:00:00 wait
//      986 pts/0    00:00:00 wait
//      987 pts/0    00:00:00 wait
//      988 pts/0    00:00:00 wait
//      989 pts/0    00:00:00 wait
//      990 pts/0    00:00:00 wait
//      991 pts/0    00:00:00 wait
//      992 pts/0    00:00:00 wait
//      993 pts/0    00:00:00 wait
//      994 pts/0    00:00:00 wait
//      995 pts/0    00:00:00 wait
//      996 pts/0    00:00:00 wait
//      997 pts/0    00:00:00 wait
//      998 pts/0    00:00:00 wait
//      999 pts/0    00:00:00 wait
//     1000 pts/0    00:00:00 wait
//     1001 pts/0    00:00:00 wait
//     1002 pts/0    00:00:00 wait
//     1013 pts/0    00:00:00 ps
//     5813 pts/0    00:00:05 bash
//    max 23:28:12   fork  (master) $ kill -15 998
//    process 1 with id=998 and status=15 exited
//    max 23:28:20   fork  (master) $ kill -9 994
//    process 2 with id=994 and status=9 exited
//    max 23:28:34   fork  (master) $ kill -1 995
//    process 3 with id=995 and status=1 exited
//    max 23:29:34   fork  (master) $ kill -12 996
//    process 4 with id=996 and status=12 exited
//    max 23:30:04   fork  (master) $ kill -17 997
//    max 23:30:18   fork  (master) $ kill -17 997
//    max 23:30:20   fork  (master) $ ps
//      PID TTY          TIME CMD
//      981 pts/0    00:00:00 wait
//      983 pts/0    00:00:00 wait
//      984 pts/0    00:00:00 wait
//      985 pts/0    00:00:00 wait
//      986 pts/0    00:00:00 wait
//      987 pts/0    00:00:00 wait
//      988 pts/0    00:00:00 wait
//      989 pts/0    00:00:00 wait
//      990 pts/0    00:00:00 wait
//      991 pts/0    00:00:00 wait
//      992 pts/0    00:00:00 wait
//      993 pts/0    00:00:00 wait
//      997 pts/0    00:00:00 wait
//      999 pts/0    00:00:00 wait
//     1000 pts/0    00:00:00 wait
//     1001 pts/0    00:00:00 wait
//     1002 pts/0    00:00:00 wait
//     1294 pts/0    00:00:00 ps
//     5813 pts/0    00:00:05 bash
//    max 23:30:22   fork  (master) $ kill -11 1000
//    process 5 with id=1000 and status=11 exited
//    max 23:30:47   fork  (master) $ 
//    



