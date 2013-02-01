ftp -n <<-EOF
open 10.71.30.22
user spcoast .spcoast
bin
put /home/jzhou/9.5/development/src/sseTcl/obj/ssesh  /home/spcoast/ssesh
bye
EOF