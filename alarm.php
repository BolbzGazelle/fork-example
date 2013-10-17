<?php
    declare(ticks = 1);

    function signal_handler($signal) {
        print "Caught SIGALRM\n";
        pcntl_alarm(1);
    }

    pcntl_signal(SIGALRM, "signal_handler", true);
    pcntl_alarm(1);

while(1){ sleep(2); }
