#!/bin/sh
version="20191018-heqh"

func_umount()
{
	if [ $# -ne 1 ];then
		echo "Please input device node path."
		return
	fi
	
	local l_deviceNodePath=$1
	
	while true
	do
		local l_mountPath=$(df -h | grep $l_deviceNodePath | awk '{print $6}')
		if [ "$l_mountPath" = "" ];then	
			return
		else 
			umount $l_mountPath
		fi
	done

}
  
func_format()
{
	if [ $# -ne 1 ];then
		echo "Please input device node path."
		exit
	fi
	
	local l_deviceNodePath=$1
	local l_devicePartitionPath=${l_deviceNodePath}p1
	func_umount $l_deviceNodePath
	
	fdisk $l_deviceNodePath <<EOF
  	d
 	1
  	d
  	2
  	d
  	3
  	d
  	4
  	n
  	p
  	1


t
b
w
EOF
	sleep 2
	mkfs.vfat $l_devicePartitionPath
}

if [ $# -ne 1 ];then
	echo "Please input device node path."
	exit
fi

g_deviceNodePath=$1
#if endwith 1,delete it
g_deviceNodePath=${g_deviceNodePath%1*}

if [ ! -e "$g_deviceNodePath" ];then
	echo "$g_deviceNodePath is nonexistent."
	exit
fi

func_format $g_deviceNodePath


#end file
