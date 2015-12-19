#!/bin/bash
#until watch -n 0.5 ./lib/png2 /Users/dmitryduev/web/sserv/public /Users/dmitryduev/web/sserv/telemetry; do
#    echo "'png2' crashed with exit code $?. Restarting..." >&2
#    sleep 1
#done
#until while true; do ./lib/png2 /Users/dmitryduev/web/sserv/public /Users/dmitryduev/web/sserv/telemetry; sleep 0.5; done
until while true; do ./lib/png2 /home/roboao/web/sserv/public /home/roboao/Status; sleep 0.5; done
do
   echo "'png2' crashed with exit code $?. Rerunning..." >&2
   sleep 1
done
