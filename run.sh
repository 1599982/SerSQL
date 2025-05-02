clear

PROGRAM="server"
MYSQL_PATH="mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit"

export LD_LIBRARY_PATH=$MYSQL_PATH/lib64

./$PROGRAM $1 $2 $3 $4
