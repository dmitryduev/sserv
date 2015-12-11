#!/bin/bash
until (python server.py --host 0.0.0.0 -p 8080 --extip 140.252.53.120 -ep 24680); do
    echo "'server.py' crashed with exit code $?. Restarting..." >&2
    sleep 1
done
