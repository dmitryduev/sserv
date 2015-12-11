#!/bin/bash
until (python status.py --host 140.252.53.120 -p 24680); do
    echo "'status.py' crashed with exit code $?. Restarting..." >&2
    sleep 1
done
