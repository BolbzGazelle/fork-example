<?php
declare(ticks=1);
$cnt=323;
$id=[];
pcntl_signal(SIGCHLD,'handlesignal');
pcntl_signal(SIGINT,'interrupt',true);
while(--$cnt>0){
  $pid = pcntl_fork();
  $id[$pid]='runing';
  if($pid===0){
    sleep(rand(4,8));
    exit(0);
  }
#  echo "child is $pid\n";
}

function handlesignal($signo){
 global $id;
    foreach($id as $pid=>$st){
      $stat='a';
      $ret = pcntl_waitpid($pid,$stat,WNOHANG);
      if($ret === -1){
        unset($id[$pid]);
      }
  }
  $prcnt = count($id);
  echo "RUNNING:::::: $prcnt\n";
  if(!$prcnt ) exit(0);  
  #pcntl_signal(SIGCHLD,'handlesignal',true);
}

function interrupt($sig){
 global $id;
 foreach($id as $pid=>$run){
  echo "sending SIGKILL to $pid ..... \n";
  posix_kill($pid,SIGINT);
 }
}

while(1) pcntl_wait($status);



##    RUNNING:::::: 34
##    RUNNING:::::: 33
##    RUNNING:::::: 32
##    RUNNING:::::: 31
##    RUNNING:::::: 16
##    RUNNING:::::: 5
##    RUNNING:::::: 4
##    RUNNING:::::: 4
##    

