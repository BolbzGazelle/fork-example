<?php
declare(ticks=1);
echo "my pid = ".posix_getpid()."\n\n";

$cnt=23;
$id=[];
//pcntl_signal(SIGCHLD,'handlesignal');
pcntl_signal(SIGINT,'interrupt',true);


while(--$cnt>0){
  $pid = pcntl_fork();
  $id[$pid]='runing';
  if($pid===0){
    sleep(rand(10,28));
    exit(0);
  }
#  echo "child is $pid\n";
}
echo "running ".count($id)." childs\n\n";

#pcntl_alarm(2);


 function signal_handler($signal) {
        print "Caught SIGALRM\n";
        pcntl_alarm(1);
    }   

    pcntl_signal(SIGALRM, "signal_handler", true);



while(1){
 $status = 0;
 $pid = pcntl_wait($status);
 echo "$pid exited with status $status\n";
 unset($id[$pid]);
 echo "remain: ".count($id)."\n";
 if($pid===-1){
   echo "no more childs\n";
   exit(0);
 } 
}
function interrupt($sig){
 global $id;
 foreach($id as $pid=>$run){
  echo "sending SIGKILL to $pid ..... \n";
  posix_kill($pid,SIGINT);
 }
 exit(15);
}

function alarmHandler($signo){
  echo "alarm\n"; 
  global $id;
  $cn =8- count($id);
  if($cn<=0) return;
  echo ">>>>>>>>>>>I will add $cn childs\n\n";
  while ($cn--){
    $pid = pcntl_fork();
    if($pid>0){
      $id[$pid] = 'run';
      continue;
    }else{
     sleep(rand(0,10)); exit(0);
   }
  }
  pcntl_alarm(2);
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



##    RUNNING:::::: 34
##    RUNNING:::::: 33
##    RUNNING:::::: 32
##    RUNNING:::::: 31
##    RUNNING:::::: 16
##    RUNNING:::::: 5
##    RUNNING:::::: 4
##    RUNNING:::::: 4
##    

