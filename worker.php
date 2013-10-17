#!/usr/bin/env php
<?php
echo posix_getpid()." running \n";
 sleep(rand(1,3));
echo posix_getpid()." exited \n";


