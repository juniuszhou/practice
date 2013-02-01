#!/bin/sh
while :; do
echo "snmpwalk -v 2c -c esymac 10.82.111.25:8085 .1"
/usr/bin/snmpwalk -v 2c -c esymac 10.82.111.25:8085 .1
echo "snmpwalk -v 2c -c esymac 10.82.111.24:8085 .1"
/usr/bin/snmpwalk -v 2c -c esymac 10.82.111.24:8085 .1
sleep 300
done

