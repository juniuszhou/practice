#import os
fd=open("input.txt","r")
hour = 0
minute = 0

fix = ""
line = fd.readline()
while line:
    fix = "Sun Oct 02 "
    
    if hour < 10:
        fix += "0"
    fix += str(hour)
    fix += ":"

    if minute < 10:
        fix += "0"
    fix += str(minute)
    minute += 5
    fix += ":00"
    
    if minute > 59:
        minute = 0
        hour += 1
    fix += "CST 2011,sms,\""    
    line = line.replace('\r','')
    line = line.replace('\n','')
    fix += line
    fix += "\",sms,false,0,true,Daily,Days: SunMonTueWedThuFriSat"
    print (fix)
    line = fd.readline()
fd.close()
