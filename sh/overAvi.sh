#!/bin/sh

if [ $# -lt 1 ]; then
	
	echo "please input DelectAviTotal."
	exit 
fi

g_deleteAviTotal=$1
g_tempFilePath=./aviSavePath.txt
g_tempFileName=./aviSaveName.txt

deleteFile() {

	if [ $# -ne 1 ];then
		echo "please input filePath to delete."
		return 1
	fi
	
	local l_filePath=$1
	if [ -e $l_filePath ];then
		chmod 777 $l_filePath
		rm -r $l_filePath
		sync
	fi
	return 0
}

getAllAviPathToFile() {

	if [ $# -ne 1 ];then
		echo "please input filePath to save AviPath."
		return 1
	fi
	
	local l_filePath=$1
	find /tmp/disk/ -type f | grep avi | grep Normal > $l_filePath		
	return 0
}

getAllAviNameToFile() {

	if [ $# -ne 3 ];then
		echo "please input two filePath and deleteAviTotal."
		echo "aviSavePath and aviSaveName."
		return 1
	fi
	
	local l_filePath=$1
	local l_fileName=$2
	local l_deleteAviTotal=$3
	cut -f6 -d"/" $l_filePath | sort | head -n $l_deleteAviTotal > $l_fileName
	return 0
}

deleteOlderAvi() {

	if [ $# -ne 2 ];then
		echo "please input deleteAviTotal and fileName while save aviFileName."
		return 1
	fi
	
	local l_aviTotal=$1
	local l_fileName=$2
	while [ ${l_aviTotal} -gt 0 ]
	do
		local l_tempFileName=$(sed -n ${l_aviTotal}P $l_fileName)
		local l_filePath=$(find /tmp/disk -name $l_tempFileName)
		rm -r $l_filePath
		#sync
		l_aviTotal=$((l_aviTotal - 1))
	done
	return 0
}

getAllAviPathToFile $g_tempFilePath
getAllAviNameToFile $g_tempFilePath $g_tempFileName $g_deleteAviTotal
deleteFile $g_tempFilePath
deleteOlderAvi $g_deleteAviTotal $g_tempFileName
deleteFile $g_tempFileName





