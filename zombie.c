#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>


int main(void){
  if(fork()>0){
    sleep(12000);
  }else{
    exit(3);
  }

  return 0;
}

