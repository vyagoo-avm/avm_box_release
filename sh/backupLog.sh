#!/bin/sh

if [ $# -ne 1 ];then
	echo "please input filePath for backup logs."
	exit
fi

g_backupPath=$1

for filePath in `find /root/log -type f -size +0 | grep WARNING_log_`
do
	information=$(cat $filePath)
	if [ "$information" != "" ];then
		echo "$information" >> $g_backupPath
	fi
done
