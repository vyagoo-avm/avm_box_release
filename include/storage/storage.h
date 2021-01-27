/*
 * vg_storage.h
 *
 *  Created on: Apr 16, 2019
 *      Author: hqh
 */

#ifndef VG_STORAGE_H_
#define VG_STORAGE_H_

#include <string>
#include <pthread.h>
#include <sys/socket.h>
#include "../common/vgtype.hpp"

namespace vagoo {
namespace storage {

#define SDCARD_TOTAL 2
#define STORAGE_TOTAL  2	//sdcard0_id: 0,sdcard1_id: 1,sdcard2_id: 2,sdcard2_id: 3,usb_id1: 4,usb_id1: 5.
#pragma pack(1)

typedef VG_S32 (*CALLBACK_DVR_SETDVRPATH)(const std::string &sdCardPath);

typedef struct{

	VG_U64 u64CycleCoverSize;
	CALLBACK_DVR_SETDVRPATH callback_dvr_setDvrPath;

}VG_stStorageInput_S;

class vg_storage {
public:
	/*
	 * 函数名:vg_storage
	 * 函数功能:vg_storage构造函数
	 * 使用说明:创建VG_stStorageInput_S变量，并对结构体成员赋值，然后创建vg_storage对象即可
	 * 参数:回调函数的函数指针集合
	 * 返回值:无
	 * 注意事项：vg_storage生存期与参数的生存期一致，工程退出时，一起释放资源．
	 */
	vg_storage(const VG_stStorageInput_S &_input);
	/*
	 * 函数名:~vg_storage
	 * 函数功能:vg_storage析构函数，销毁对象，回收资源
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	virtual ~vg_storage();
protected:
	VG_STORAGE_S VG_stStorageInformation_S[STORAGE_TOTAL]; //storage信息数组，0-3为SDCARD，4为USB
public: //for callback function
	/*
	 * 函数名:vg_formatStorage
	 * 函数功能:格式化指定的storage
	 * 参数:storage索引值,sdcard0:0,sdcard1:1,usb:2
	 * 返回值:格式化成功，则返回true，失败返回false
	 * 注意事项：无
	 */
	VG_BOOL vg_formatStorage(VG_S32 s32StorageIndex);
	/*
	 * 函数名:vg_getStorageInformation
	 * 函数功能:获取storage信息
	 * 参数:无
	 * 返回值:storage状态信息
	 * 注意事项：无
	 */
	VG_STORAGE_S *vg_getStorageInformation(void);
	/*
	 * 函数名:vg_getSdcardParentDirectory
	 * 函数功能:获取sdcard挂载父路径
	 * 参数:无
	 * 返回值:sdcard挂载父路径
	 * 注意事项：用于录像管理界面,查询sdcard录像文件
	 */
	std::string vg_getSdcardParentDirectory(void);
	/*
	 * 函数名:vg_getCurrentDvrSdcardId
	 * 函数功能:获取当前录像的sdcard索引值
	 * 参数:无
	 * 返回值:当前录像sdcard索引值
	 * 注意事项：sdcard0:0,sdcard:1,无效：-1
	 */
	VG_S32 vg_getCurrentDvrSdcardId(void);
	/*
	 * 函数名:vg_getCurrentDvrSdcardPath
	 * 函数功能:获取当前录像sdcard路径
	 * 参数:无
	 * 返回值:当前录像sdcard路径
	 * 注意事项：无
	 */
	std::string vg_getCurrentDvrSdcardPath(void);

	VG_BOOL vg_getBIsAllEventDvr(void);

	std::vector<std::string> vg_deleteSeletedLogs(std::vector<std::string> vector_deleteLogs);
	VG_BOOL vg_exportSeletedLogs(std::vector<std::string> vector_exportLogs,const std::string &exportDirectoryPath);
private: //for function
	/*
	 * 函数名:vg_initialzeParameter
	 * 函数功能:初始化回调函数集,全局变量与storage状态
	 * 参数:回调函数的函数指针集合
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_initialzeParameter(const VG_stStorageInput_S& input);
	/*
	 * 函数名:vg_initialzeStorageSlotInformation
	 * 函数功能:初始化storage槽位信息,包括sdcard0-sdcard3,usb
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_initialzeStorageSlotInformation(void);
	/*
	 * 函数名:vg_initialzeAllStorageInformation
	 * 函数功能:初始化storage状态,包括sdcard0-sdcard3,usb
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_initialzeAllStorageInformation(void);
	/*
	 * 函数名:vg_initialzeStorageInformation
	 * 函数功能:初始化指定storage信息
	 * 参数:storage索引值
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_initialzeStorageInformation(VG_S32 u32StorageIndex);
	/*
	 * 函数名:vg_getCycleCoverSize
	 * 函数功能:获取循环覆盖大小,单位ＭB
	 * 参数:无
	 * 返回值:循环覆盖大小
	 * 注意事项：无
	 */
	VG_U64 vg_getCycleCoverSize(void);
	/*
	 * 函数名:vg_createProceessThread
	 * 函数功能:创建线程,用于管理Storage
	 * 参数:无
	 * 返回值:自我修复成功，则返回true，失败返回false
	 * 注意事项：无
	 */
	VG_BOOL vg_createProceessThread(void);
	/*
	 * 函数名:vg_cancelPthread
	 * 函数功能:销毁线程
	 * 参数:线程运行控制变量，线程锁
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_cancelPthread(VG_BOOL *bThreadRun,pthread_mutex_t *mutex);
	/*
	 * 函数名:vg_processPthreadFunction
	 * 函数功能:线程函数,用于监控管理storage
	 * 参数:对象的this指针
	 * 返回值:线程运行状态，一般返回NULL
	 * 注意事项：
	 * 1.有轮询与热插拔两种监控管理机制．
	 * 2.轮询方法比较稳定，但是效率低.
	 * 3.热插拔高效，却当启动前以插入storage的情况，无法监控到storage热插拔事件.
	 * ４．现在使用轮询机制处理storage监控与管理
	 */
	static void *vg_processPthreadFunction(void *pThis);
	/*
	 * 函数名:vg_processFunctionForCycle
	 * 函数功能:轮询法监控管理storage
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_processFunctionForCycle(void);
	/*
	 * 函数名:vg_handleWhenNodeExist
	 * 函数功能:挂着或刷新存在设备节点的信息
	 * 参数:设备节点路径
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_handleWhenNodeExist(std::string deviceNodePath);
	/*
	 * 函数名:vg_handleWhenNodeNonexistent
	 * 函数功能:卸载存在设备节点，刷新节点信息
	 * 参数:设备节点路径
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_handleWhenNodeNonexistent(std::string deviceNodePath);
	/*
	 * 函数名:vg_processSDCardFunctionForCycle
	 * 函数功能:轮询法监控管理storage
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_processStorageFunctionForCycle(void);

	void vg_processMouseFunctionForCycle(void);
	/*
	 * 函数名:vg_cycleCoverAndSetDvrPath
	 * 函数功能:循环覆盖与设置录像路径
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_cycleCoverAndSetDvrPath(void);
	/*
	 * 函数名:vg_isDeviceNodeExistent
	 * 函数功能:判定设备节点是否存在
	 * 参数:设备节点路径(非节点分区路径)(一般为/dev/xxxx)
	 * 返回值:当存在设备节点，则返回true，否则返回false．
	 * 注意事项：无
	 */
	VG_BOOL vg_isDeviceNodeExistent(std::string deviceNodeName);
	/*
	 * 函数名:vg_getStorageIndex
	 * 函数功能:根据设备节点路径，确定槽位号,
	 * 参数:设备节点路径(非节点分区路径)(一般为/dev/xxxx)
	 * 返回值:sd0-sd3:0-3,usb:4
	 * 注意事项：无
	 */
	VG_S32 vg_getStorageIndex(std::string deviceNodeName);
	/*
	 * 函数名:vg_isOkToMount
	 * 函数功能:判定设备节点可否挂载
	 * 参数:设备节点路径(非节点分区路径)(一般为/dev/xxxx)
	 * 返回值:当设备节点可以挂载，则返回true，否则返回false．
	 * 注意事项：无
	 */
	VG_BOOL vg_isOkToMount(std::string deviceNodeName);
	/*
	 * 函数名:vg_mountStorageToTmp
	 * 函数功能:挂载storage到/tmp下,并新storage状态
	 * 参数:设备节点路径(非节点分区路径)(一般为/dev/xxxx)
	 * 		,storage索引值(sdcard0:0,sdcard1:1,usb:2)
	　* 		,挂载路径：sdcard0:/tmp/disk/sd0；　sdcard1:/tmp/disk/sd1；　usb：/tmp/usb
	 * 返回值:当设备节点挂载成功，则返回true，否则返回false．
	 * 注意事项：无
	 */
	VG_BOOL vg_mountStorageToTmp(std::string deviceNodeName,VG_S32 s32StorageIndex,std::string sdcardMountPath);
	/*
	 * 函数名:vg_umountStorage
	 * 函数功能:卸载指定storage(若卸载失败，则共尝试卸载５次)
	 * 参数:挂载路径：sdcard0:/tmp/disk/sd0；　sdcard1:/tmp/disk/sd1；　usb：/tmp/usb
	 * 返回值:当设备节点卸载成功，则返回true，否则返回false．
	 * 注意事项：无
	 */
	VG_BOOL vg_umountStorage(std::string mountPath);
	/*
	 * 函数名:vg_refreshMemorySpace
	 * 函数功能:刷新指定storage状态
	 * 参数:storage索引值,sdcard0:0,sdcard1:1,usb:2
	 * 返回值:无．
	 * 注意事项：无
	 */
	void vg_refreshMemorySpace(VG_S32 s32StorageIndex);
	/*
	 * 函数名:vg_refreshAllSdcardSpace
	 * 函数功能:刷新所有sdcard状态
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_refreshAllSdcardSpace(void);
	/*
	 * 函数名:vg_automaticRepairStorage
	 * 函数功能:storage自我修复
	 * 参数:storage分区路径
	 * 返回值:自我修复成功，则返回true，失败返回false
	 * 注意事项：无
	 */
	VG_BOOL vg_automaticRepairStorage(std::string storagePartitionName);

	VG_S32 vg_remountStorage(const std::string s8StoragePath);
	/*
	 * 函数名:vg_isVailableOfStorageIndex
	 * 函数功能:为了防止storage元素访问越界，判定数组元素是否合法
	 * 参数:storage索引值
	 * 返回值:storage索引值合法，则返回true，否则返回false
	 * 注意事项：无
	 */
	VG_BOOL vg_isVailableOfStorageIndex(VG_S32 u32StorageIndex);
	/*
	 * 函数名:vg_readInformationByFifo
	 * 函数功能:打开管道执行shell命令(开启子进程)
	 * 参数:shell命令,执行结果保存路径，截取信息长度
	 * 返回值:成功返回真实获取的长度，失败返回０；
	 * 注意事项：无
	 */
	VG_S32 vg_readInformationByFifo(std::string shellCmd,VG_S8 *s8Target,VG_S32 s32TargetMaxLength);
	/*
	 * 函数名:vg_buildDeviceNodeName
	 * 函数功能:组建sdcard节点名称
	 * 参数:sdcard索引值
	 * 返回值:sdcard设备节点名称
	 * 注意事项：sdcard0 : /dev/mmcblk0; sdcard1 : /dev/mmcblk1
	 */
	std::string vg_buildDeviceNodeName(VG_S32 s32SdcardIndex);
	/*
	 * 函数名:vg_buildStorageMountPath
	 * 函数功能:组建storage挂载路径
	 * 参数:storage索引值
	 * 返回值:storage挂载路径
	 * 注意事项：sdcard0:/tmp/disk/sd0; sdcard1:/tmp/disk/sd1; usb:/tmp/usb
	 */
	std::string vg_buildStorageMountPath(VG_S32 s32StorageIndex);
	/*
	 * 函数名:vg_createDirectory
	 * 函数功能:判定目录是否存在，若不存在，则创建目录
	 * 参数:目录名称
	 * 返回值:若目录存在或者成功创建目录，返回true，否则返回false
	 * 注意事项：无
	 */
	VG_BOOL vg_createDirectory(std::string directoryPath);
	//for dvr
	/*
	 * 函数名:vg_setCurrentDvrSdcardId
	 * 函数功能:设置当前录像的sdcard索引值
	 * 参数:当前录像sdcard索引值
	 * 返回值:无
	 * 注意事项：sdcard0:0,sdcard:1,无效：-1
	 */
	void vg_setCurrentDvrSdcardId(VG_S32 s32SdcardId);
	/*
	 * 函数名:vg_isOkToRecord
	 * 函数功能:判定指定sdcard是否可以录像
	 * 参数:sdcard索引值
	 * 返回值:可用于录像返回true,否则返回false．
	 * 注意事项：无
	 */
	VG_BOOL vg_isOkToRecord(VG_S32 s32StorageIndex);
	/*
	 * 函数名:vg_getOkToRecordSdcardIndex
	 * 函数功能:获取可录像sdcard索引值
	 * 参数:无
	 * 返回值:可录像sdcard索引值．
	 * 注意事项：无
	 */
	VG_S32 vg_getOkToRecordSdcardIndex(void);

	VG_S32 vg_removeOldAVIFile(VG_S32 s32DeleteTotal);
	/*
	 * 函数名:vg_cycleCover
	 * 函数功能:录像循环覆盖
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_cycleCover(void);
	/*
	 * 函数名:vg_setDvrPath
	 * 函数功能:设置录像路径
	 * 参数:无
	 * 返回值:无
	 * 注意事项：无
	 */
	void vg_setDvrPath(void);
	VG_BOOL vg_bIsRecordDirectory(std::string directoryName);
	VG_BOOL vg_bIsEmptyDirectory(std::string directoryPath);
	VG_VOID vg_checkAndRemoveEmptyDirectory(std::string sdCardMountPath);
	VG_VOID vg_removeAllEmptyDirectory(void);
	VG_BOOL vg_bIsAllEventDvr(void);

	VG_BOOL vg_copyFile(const std::string &targetPath,const std::string &sourcePath);
	VG_BOOL vg_deleteFile(const std::string &filePath);
	VG_BOOL vg_bIsExistLog(void);
	VG_BOOL vg_emptyLogDirectoryAfterFormat(VG_S32 s32StorageIndex);
	std::string vg_createLogDirectory(std::string sdcardMountPath);
	VG_S32 vg_initialzeLogBackUpFile(std::string sdcardMountPath);
	VG_S32 vg_backupLogToSdcard(void);
	VG_S32 vg_emptyFileAfterBackup(void);

private: //for variable
	VG_stStorageInput_S g_stStorageInput_S;	//外部传参，主要是回调函数集
	pthread_t g_processPthreadId;				//storage模块的监控管理线程号
	pthread_mutex_t g_processMutex;				//storage模块监控管理互斥锁
	VG_BOOL g_bProcessPthreadRun;				//storage模块监控管理线程控制变量
	VG_S32 g_s32CurrentDvrSdcardId;				//当前录像sdcard索引值,sdcard0:0,sdcard1:1，无效为－１；
	VG_BOOL g_bIsAllEventDvr;
	std::string g_backUpLogPath;
	std::string storageSlotInformation[STORAGE_TOTAL]; //extend usb.
};
/*
 * 函数名:callback_storage_formatStorage
 * 函数功能:回调函数,格式化指定storage
 * 参数:storage索引值
 * 返回值:格式化成功返回true，否则返回false
 * 注意事项：无
 */
VG_BOOL callback_storage_formatStorage(VG_S32 s32StorageIndex);
/*
 * 函数名:callback_storage_getStorageInformation
 * 函数功能:回调函数,获取storage信息
 * 参数:无
 * 返回值:stoarge信息指针
 * 注意事项：１．返回信息为一个指针，指向一个三元素数组，其中0:sdcard0,1:sdcard1,2:usb.
 * 		   2.请勿修改storage信息内容．若要修改，务必拷贝一份，再做修改
 */
VG_STORAGE_S *callback_storage_getStorageInformation(void);
/*
 * 函数名:callback_storage_getSdcardParentDirectory
 * 函数功能:回调函数,获取sdcard父路径（用于gui视频管理）
 * 参数:无
 * 返回值:sdcard父路径
 * 注意事项：无
 */
std::string callback_storage_getSdcardParentDirectory(void);
/*
 * 函数名:callback_storage_getCurrentDvrIndex
 * 函数功能:回调函数,获取当前录像sdcard索引值
 * 参数:无
 * 返回值:当前录像sdcard索引值(sdcard0:0,sdcard1:1,无效:-1)
 * 注意事项：无
 */
VG_S32 callback_storage_getCurrentDvrIndex(void);
/*
 * 函数名:callback_storage_getDvrRecordpath
 * 函数功能:回调函数,获取当前录像sdcard路径
 * 参数:无
 * 返回值:当前录像sdcard路径
 * 注意事项：为了排序dvr与storage开启时序，给dvr模块创建时获取一次录像路径
 */
std::string callback_storage_getDvrRecordpath(void);

VG_BOOL callback_storage_getBIsAllEventDvr(void);

std::vector<std::string> callback_storage_deleteSeletctedLogs(std::vector<std::string> vector_deleteLogs);
VG_BOOL callback_storage_exportSelectedLogs(std::vector<std::string> vector_exportLogs,const std::string &exportDirectoryPath);

#pragma pack()

}
}
#endif /* VG_STORAGE_H_ */
