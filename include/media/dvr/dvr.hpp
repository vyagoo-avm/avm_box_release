/*
 * vg_dvr.hpp
 *
 *  Created on: Sep 17, 2019
 *      Author: zdz
 */

#ifndef INCLUDE_VG_DVR_HPP_
#define INCLUDE_VG_DVR_HPP_
#pragma once

#include "glog/logging.h"

#include "../../common/vgtype.hpp"
#include "../../common/vg_media_com.hpp"
namespace vagoo {
namespace media {
namespace dvr {

//config
typedef VG_BOOL (*CALLBACK_GET_VENCQUALITY)(void);
typedef VG_BOOL (*CALLBACK_GET_AUTORECODE_FLAG)(void);
typedef VG_S64 (*CALLBACK_GET_FILELENTH)(void);//获取设定的文件时长
//SRC
typedef VG_S32 (*CALLBACK_VI_GET_FRAME)(const VG_S32, VG_IMAGE_S*); //获取摄像头帧图像数据
typedef VG_VOID (*CALLBACK_VI_RELEASE_FRAME)(const VG_S32, const VG_S32); //获取摄像头帧图像数据

typedef VG_SIZE_S (*CALLBACK_GETSRCFRAMESIZE)();//获取摄像头帧图像尺寸
typedef VG_S32(*CALLBACK_GETSRC_FRAME_RATE)(VG_U8* pFrameRate);
typedef VG_U8 (*CALLBACK_GET_CAMERA_LOST)(const VG_S32);
//@remarks s2DataType 可选值为VG_ENUM_DATA_STREAM_GPS/VG_ENUM_DATA_STREAM_GSENSOR
typedef VG_S32 (*CALLBACK_GET_DATASTREAMS)(const VG_S32& s2DataType,VG_DATA_STREAM_S* pstDataStream);
//storage
typedef std::string (*CALLBACK_GET_STORAGE_PATH)(void);
typedef VG_S32 (*CALLBACK_STORAGE_HANDLEDVRFAILED)(std::string s8MountPath);


//Main Stream
typedef VG_S32 (*CALLBACK_PUTSTREAMUFFER)(const VG_VOID *pStream, const VG_MEDIA_STREAM_S*);
typedef VG_S32 (*CALLBACK_GET_MAINSTREAM)(VG_U8 *, VG_MEDIA_STREAM_S*);					//从media buffer中获取主码流数据
typedef VG_S32 (*CALLBACK_SET_MEDIABUFFER_READBACK)(const VG_U32);
typedef VG_S32 (*CALLBACK_SET_MEDIABUFFER_READIFRAME)();

//Rtsp Stream
typedef VG_S32 (*CALLBACK_PUT_RTSP_STREAMUFFER)(const VG_VOID *pStream, const VG_MEDIA_STREAM_S*);



typedef void (*CALLBACK_UPDATE_MFileDuration)(VG_U64 MFileDuration);
typedef void (*CALLBACK_UPDATE_PTS)(VG_U64 pts);
typedef VG_S32 (*CALLBACK_DATAFLOW_SWITCH_PLAYBACKMODE)(VG_BOOL);
//dataflow切換回訪模式
typedef void (*CALLBACK_DATAFLOW_PLAYBACKMODE)(const VG_BOOL bPlayBackMode);


struct VG_DVR_CONF_S {
	//config
	CALLBACK_GET_VENCQUALITY _getVencQuality;//获取录像文件质量
	CALLBACK_GET_FILELENTH _getFileLenth;//获取录像文件时长
	CALLBACK_GET_AUTORECODE_FLAG _getAutoRecodeFlag;//获取是否开启自动录像标志位

	//src
	CALLBACK_VI_GET_FRAME _getSrcFrame;
	CALLBACK_VI_RELEASE_FRAME _releaseSrcFrame;
	CALLBACK_GETSRCFRAMESIZE _getSrcFrameSize;
	CALLBACK_GETSRC_FRAME_RATE _getSrcFrameRate;
	CALLBACK_GET_CAMERA_LOST _getCamLost;
	CALLBACK_GET_DATASTREAMS _getDataStream;

	//storage
	CALLBACK_STORAGE_HANDLEDVRFAILED callback_storage_handleDvrFailed;
	CALLBACK_GET_STORAGE_PATH _getStoragePath;//获取存储设备路径

	//stream
	CALLBACK_PUTSTREAMUFFER _putStreamBuffer;//推送帧到mediabuffer
	CALLBACK_GET_MAINSTREAM _getStreamBuffer;//从mediabuffer获取帧
	CALLBACK_SET_MEDIABUFFER_READBACK _setMediaBufferReadBack;//设置mediabuffer 读取回退，用于事件录像
	CALLBACK_SET_MEDIABUFFER_READIFRAME _setMediaBufferReadIFrame;//设置mediabuffer 读取I帧

	CALLBACK_PUT_RTSP_STREAMUFFER _putRtspStreamBuffer;

	//playback
	CALLBACK_UPDATE_MFileDuration _updateGuiFileDuration;//刷新当前回放文件时长
	CALLBACK_UPDATE_PTS _updateGuiPts;//刷新当前回放文件时间戳
	CALLBACK_DATAFLOW_SWITCH_PLAYBACKMODE _dataflowModeSwitch;//Dataflow模块进入或退出回放模式
	CALLBACK_DATAFLOW_PLAYBACKMODE _playbackModeWitch;
};
//@brief 初始化vg_dvr模块
//@param in stConfig vg_dvr模块配置参数
//@return  VG_FAILURE/VG_SUCCEED
//@remarks 需与VG_Dvr_DeInit配对使用
VG_S32 VG_Dvr_Init(const VG_DVR_CONF_S &stConfig);
//@brief Deinit vg_dvr模块
//@return VG_SUCCEED
//@remarks 需与VG_Dvr_Init配对使用
VG_S32 VG_Dvr_DeInit();
//@brief 开启录像
//@return VG_FAILURE/VG_SUCCEED
VG_S32 VG_Dvr_Open(void);
//@brief 关闭录像
//@return VG_SUCCEED
VG_VOID VG_Dvr_Close(void);


//@brief 开启视频输出回写
//@return VG_FAILURE/VG_SUCCEED
VG_S32 VG_WBC_Open(void);
//@brief 关闭视频输出回写
//@return NULL
VG_VOID VG_WBC_Close(void);

//@brief 设置录像文件的存储路径
//@param in s8StoragePath 存储设备路径
//@return VG_FAILURE/VG_SUCCEED
//@remarks vg_vpu模块未Init时,返回错误
VG_S32 VG_Dvr_SetStoragePath(const std::string &s8StoragePath);
//@brief 获取VG_vpu模块当前录像存储设备路径
//@return 录像存储设备路径
std::string VG_GetDvrStorgePath(void);
//@brief 生成事件录像
//@return NULL
//@remarks 为避免短时间内，多次事件触发，产生大量碎片文件
//         30s内多次事件触发，不会生成新的事件录像文件
//         当前事件录像结束时间以30s内最后次事件触发时间为基准，往后延20s关闭，
//当时长超过3min钟时，强制关闭当前事件录像文件
VG_VOID VG_GenEventRecode(VG_S32 s32EventType);
//@brief 获取VPU模块录像状态以及录像类型
//@param out s32RecodeFlag state VG_TRUE/VG_FALSE
//       out s32RecodeType type： -1 :normal  0:PANIC 1:GFORCE 2:Speed
//@return NULL
VG_VOID VG_Dvr_GetRecodeState(VG_S32* s32RecodeFlag,VG_S32* s32RecodeType);


//@brief 等待所有录像文件关闭
VG_VOID VG_WaitAllRecodeFileClosedForPowerOff();

//@brief 回放同一时间一组文件
//@param in s8FileName文件列表
//@return VG_FAILURE/VG_SUCCEED
VG_S32 VG_PlayAviFiles(std::vector<std::string> s8FileName);
//@brief 关闭视频回放
///@return VG_SUCCEED
VG_S32 VG_PlayBackStop(void);
//@brief 暂停回放
VG_VOID VG_PlayPause(void);

//@brief 获取当前回放帧图像数据
//@return 各通道帧图像数据向量
std::vector<VG_IMAGE_S> VG_VIGetCurPlaybackFrame(VG_VOID);


VG_VOID* VG_s32WbcGetJpegData(const VG_S32 s32Chn, VG_S32* framesize);
VG_VOID* VG_s32WbcGetRtspData(const VG_S32 s32Chn, VG_S32* framesize);

//@brief 视频编码码流拷贝
VG_S32 s32Encode_Vstream_CopyTo(void* pDest,void* pSrc);
//@brief 当前帧是否为I帧
VG_U8  u832Encode_Vstream_isKeyFlag(void* pSrc);
//@brief 获取当前帧时间戳，单位为us
VG_U64 s64Encode_Vstream_GetPts(void* pSrc);
//@brief 获取当前编码后视频帧Size
VG_U32 u32Encode_Vstream_GetSize(void* pSrc);

}
}
}





#endif /* INCLUDE_VG_DVR_HPP_ */
