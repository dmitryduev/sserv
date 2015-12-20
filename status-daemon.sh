#!/bin/bash
until (python status.py --host 192.168.1.10 -p 8080); do
    echo "'status.py' crashed with exit code $?. Restarting..." >&2
    sleep 1
done
