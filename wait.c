#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define MAXFORKS 20

int *ids;

void handle(){
  //printf ("ALARM\n");

  
  alarm(2);
}

void replace_pid(int pid){

  int count = MAXFORKS;
  int iter = 0;
  //printf("%d ------\n\n",count);
  while(iter < count){
    //printf ("test %d with %d\n",pid, ids[iter]);
    if(ids[iter] == pid){
      int newpid;
      newpid = fork();
      if(newpid == 0){
        //printf("my pid is %d \n",getpid());
        execv("./worker.php",NULL);
        return;
      }
      ids[iter] = newpid;
      return;
    }
    ++iter;
  }
  printf ("PID %d NOT FOUND ----------------- \n",pid);
}

int main(void){
  int cnt = MAXFORKS;
  ids = malloc  (sizeof(int)*MAXFORKS);
  while(--cnt>=0)
  {
      int r = 10 + rand()%10;
    ids[cnt]=fork();
    if(ids[cnt] == 0)
    { 
      //printf("my pid is %d \n",getpid());
      execv("./worker.php",NULL);
      return 0;
    }
   }
  int pc =0 ; //terminated processes

  signal(SIGALRM,handle);
  alarm(4);
  while(1){ 
    int pid;
    int status;
    pid = wait(&status);
    if(pid == -1){
      printf("no childs here, will exit\n");
      exit(0);
    }
    printf("process %d with id=%d and status=%d exited\n",++pc,pid,status);
    replace_pid(pid);
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



