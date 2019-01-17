#!/bin/bash

for x in xargs ./bin/xargs ;do
bash -c 'echo {1..180000} | tr " " \\n | '"$x"' /bin/echo' | wc -l
done
