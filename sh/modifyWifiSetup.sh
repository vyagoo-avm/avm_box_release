#!/bin/sh


if [ $# -ne 2 ];then
	echo "please input wifiName and password."
	exit
fi

g_wifiSetupFile=./hostapd.conf
g_newWifiName="ssid=$1"
g_newPassword="wpa_passphrase=$2"
g_oldWifiName=$(sed -n '/^ssid/p' $g_wifiSetupFile)   #^:行首出现
g_oldPassword=$(sed -n '/wpa_passphrase/p' $g_wifiSetupFile)

if [ $g_oldWifiName != $g_newWifiName ];then

	sed -i "/^ssid/c$g_newWifiName" $g_wifiSetupFile
fi

if [ $g_newPassword != $g_oldPassword ];then
	sed -i "/^wpa_passphrase/c$g_newPassword" $g_wifiSetupFile
fi

sync
