#!/bin/sh

checkFilePathIsExist() {

	if [ $# -ne 1 ];then
		echo "Input-Variable is not equal one on checkFilePathIsExist."
		return 1
	fi
	
	local l_filePath=$1
	if [ -e $l_filePath ];then
		return 0
	fi
	return 1
}

deleteFile() {

	if [ $# -ne 1 ];then
		echo "None will be deleted."
		return 1
	fi 
	
	local l_filePath=$1
	chmod 777 $l_filePath
	rm -r $l_filePath
	return 0
}

createDirectory() {

	if [ $# -ne 1 ];then
		echo "Input-Variable is not equal one on createDirectory."
		return 1
	fi

	local l_directoryPath=$1
	mkdir -p $l_directoryPath
	chmod 777 $l_directoryPath
	return 0
}


getMD5Code() {

	local l_md5Code=$(cat $1 | awk '{print $4}')
	echo $l_md5Code
}

md5Encode() {

	if [ $# -ne 1 ];then
		return 
	fi

	if [ -z $1 ];then 
		return
	fi

	local l_filePath=$1

	checkFilePathIsExist $l_filePath
	local l_returnValue=$?
	if [ $l_returnValue -ne 0 ];then
		return 
	fi
	local l_md5Code=$(md5sum $l_filePath | awk '{print $1}')
	echo $l_md5Code
}

checkByMd5Code() {

	if [ $# -ne 2 ];then
		echo "Input-Value is not equal two on checkByMd5Code."
		return 1
	fi 

	echo "$1 and $2 on checkByMd5Code."
	if [ "$1" == "$2" ];then

		return 0
	fi
	return 1
}

getSlotInformation() {

	local l_tempInformation=$(cat $1 | awk '{print $1}')
	local l_slotInformation=$(expr substr "$l_tempInformation" 1 57)
	echo $l_slotInformation
}

getSdcardDeviceNode() {

	if [ $# -ne 1 ];then
		echo ""
		return
	fi

	local l_time=1
	local l_slotInformation=$1
	while [ $l_time -le 15 ]
	do
  		sleep 0.2
			for i in 'a' 'b' 'c' 'd' 'e'
			do 
				local l_tempInformation=$(readlink /sys/block/sd${i})
				local l_result=$(expr substr "$l_tempInformation" 1 57)
				if [ "$l_result" == "$l_slotInformation" ]; then
					echo "/dev/sd${i}1"
					return
				fi
			done
  		l_time=$(( $l_time + 1 ))
	done
	echo ""
	return 
}

getPackagePath() {

	local l_packageName=$(cat $1 | awk '{print $2}')
	echo $l_packageName
}

getUpdateTime() {

	local l_updateTime=$(cat $1 | awk '{print $3}')
	echo $l_updateTime
}

handleUpdateTime() {
	
	if [ $# -ne 1 ];then
		echo "The indexFile is nonexistent."
		return 1
	fi

	local l_indexFile=$1
	local l_slotInformation=$(cat $l_indexFile | awk '{print $1}')
	local l_packageName=$(getPackagePath $l_indexFile)
	local l_updateTime=$(getUpdateTime $l_indexFile)
	if [ $l_updateTime -ge 5 ];then
		deleteFile $l_indexFile
		return
	fi	
	l_updateTime=$(( $l_updateTime + 1 ))
	local l_tempUpdateInformation="$l_slotInformation  $l_packageName   $l_updateTime"
	echo  $l_tempUpdateInformation > $l_indexFile
	return 0
}

checkDeviceNode() {

	if [ -z $1 ];then
		echo "DevicePath is empty on checkDeviceNode."
		return 1
	fi

	local l_devicePath=$1

	local l_time=1
	while [ $l_time -le 15 ]
	do
		echo $l_time
  		sleep 0.2
  		if [ -e $l_devicePath ];then
			return 0
		fi
  		l_time=$(( $l_time + 1 ))
	done
	return 1
}

getMountPath() {

	if [ -z $1 ];then
		echo ""
		return 1
	fi
	
	local l_devicePath=$1
	local l_deviceName=$(expr substr "$l_devicePath" 6 4)  #for example,from /dev/sdb1 to sdb1,the result is sdb1.
	local l_mountPath=/tmp/disk/$l_deviceName
	if [ ! -d $l_mountPath ];then
		createDirectory $l_mountPath
		local l_returnValue=$?
		if [ $l_returnValue -eq 0 ];then
			
			echo $l_mountPath
			return 0
		fi
	else
		echo $l_mountPath
		return 0
	fi
	return 1
}

mountFunction() {

	if [ $# -ne 2 ];then
		echo "MountFunction-Variable is not equal two."
		return 1
	fi

	if [ -z $1 ] || [ -z $2 ];then
		echo "MountPath or DevicePath is empty."
		return 1
	fi

	
	local l_devicePath=$1
	local l_mountPath=$2
	echo "mount $l_devicePath to $l_mountPath"
	mount -t vfat $l_devicePath $l_mountPath
	return 0
}

umountFunction() {

	if [ -z $1 ];then
		echo "Input-Value is empty on umountFunction."
		return 1
	fi

	local l_umountPath=$1
	checkFilePathIsExist $l_umountPath
	local l_returnValue=$? 
	if [ $l_returnValue -ne 0 ];then
		echo "$l_umountPath is nonexistent."
		return 1
	fi

	umount $l_umountPath
	deleteFile $l_umountPath
	return 0
}

upgrade() {

	if [ $# -ne 1 ];then
		"Input-Value is not equal one on upgrade-function."
		return 1;
	fi
	
	if [ -z $1 ];then
			
		echo "Input-Value is empty on upgrade."
		return 1
	fi

	local l_packagePath=$1
	chmod 777 $l_packagePath
	tar -xvf $l_packagePath -C /
	sync
	echo "It has finished to upgrade."
	return 0
}

runAPPFunction() {

	cd /root/user_ko
	./load.sh
	cd /root
	./repair.sh &
	source /etc/profile
	./avs360 &
}



if [ $# -ne 1 ]; then

	echo "please input filePath"
	exit
fi


g_filePath=$1

#checkFilePathIsExist $g_filePath
#returnValue=$?
#if [ $returnValue -ne 0 ];then
#	echo "IndexFile is nonexistent."
#	exit
#fi

slotInformation=$(getSlotInformation $g_filePath)
echo "slotInformation : $slotInformation" 

packageName=$(getPackagePath $g_filePath) 
echo "PackageName : $packageName"
 
deviceNodePath=$(getSdcardDeviceNode $slotInformation)
echo "DevicePath : $deviceNodePath" 

mountPath=$(getMountPath $deviceNodePath)
echo "MountPath : $mountPath" 
if [ -z $mountPath ];then

	echo "It was failed to create directory for mounting."
	handleUpdateTime $g_filePath
	reboot
fi 

mountFunction $deviceNodePath $mountPath
returnValue=$?
if [ $returnValue -ne 0 ];then
	echo "It was failed to mount from $deviceNodePath to $mountPath."
	handleUpdateTime $g_filePath
	reboot
fi

packagePath=$mountPath/$packageName
checkFilePathIsExist $packagePath
returnValue=$?
if [ $returnValue -ne 0 ];then
	echo "$packagePath is nonexistent."
	deleteFile $g_filePath
	umountFunction $mountPath
	reboot
fi

#md5CodeOnIndexFile=$(getMD5Code $g_filePath)
#if [ -n $md5CodeOnIndexFile ];then
#	fileMd5Code=$(md5Encode $packagePath)
#	if [ -z $fileMd5Code ];then
#		echo "It was failed to md5Encode $g_filePath."
#		umountFunction $mountPath
#		exit;
#	fi
#	checkByMd5Code $md5CodeOnIndexFile $fileMd5Code
#	returnValue=$?
#	if [ $returnValue -ne 0 ];then
#		echo "Md5Check error."
#		deleteFile $g_filePath
#		deleteFile $packagePath
#		umountFunction $mountPath
#		exit
#	fi
#fi

upgrade $packagePath
returnValue=$?
if [ $returnValue -eq 0 ];then
	deleteFile $g_filePath
	deleteFile $packagePath
	umountFunction $mountPath
	runAPPFunction
fi

