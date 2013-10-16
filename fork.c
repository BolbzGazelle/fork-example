#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define CNT 2000

void handler(int signo){
  static int count =0;
  count ++;
  printf("call number %d\n",count);
 
}

int main(void){
  signal (SIGCHLD,handler);
  int cnt = CNT;
  int *ids;
  ids = malloc  (sizeof(int)*CNT);
  while(--cnt>0)
  {
      int r = 2 + rand()%10;
    ids[cnt]=fork();
    if(ids[cnt] == 0)
    { 
//    printf("is child\n");
      sleep(r);
      //printf("rand=%d\n",r);
      return 0;
    }
   }
  while(1){ sleep(1); }
  return 0;
}

