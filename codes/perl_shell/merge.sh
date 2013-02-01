#!/bin/sh
for b in $(seq 9 30)
do
 echo ts.log.$b
 more ts.log.$b >> zj.txt
done