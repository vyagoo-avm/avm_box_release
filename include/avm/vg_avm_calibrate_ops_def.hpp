/*
 * VG_calibrate_ops_def.hpp
 *
 *  Created on: Oct 15, 2020
 *      Author: zdz
 */

#ifndef INCLUDE_VG_CALIBRATE_OPS_DEF_HPP_
#define INCLUDE_VG_CALIBRATE_OPS_DEF_HPP_
#pragma once
#include <vector>
#include <string>
#include "vg_avmcommon.hpp"
namespace vagoo {
namespace vg_avm {
namespace calibrate {

typedef std::vector<VG_IMAGE_S> (*CALLBACK_GETFRAMEVECT)(void);//获取摄像头帧向量回调函数类型
typedef void (*CALLBACK_PUTFRAMEVECT)( std::vector<VG_IMAGE_S>&);//释放摄像头帧向量回调函数类型
struct VG_CALIBRATE_CONF_S {
  CALLBACK_GETFRAMEVECT pCallbackGetFrameVect;
  CALLBACK_PUTFRAMEVECT pCallbaclReleaseFrameVect;
  std::string s8XmlFileFullPathName;
};

typedef VG_VOID (*VG_CALIBRATE_INIT)(const VG_CALIBRATE_CONF_S&);
typedef VG_VOID  (*VG_CALIBRATE_DEINIT)(VG_VOID);


//Old Calibrate Based on Zhangzhengyou calibrate method
typedef VG_BOOL (*VG_CALIBRATE_OLDMETHOD)(const std::vector<VG_CALI_INPUT_S>&,const VG_SIZE_S& ,std::vector<VG_CALI_RESULT_S> &);


//new Calibrate Base on Camera Pose Estimation And Ba
typedef VG_S32 (*VG_CALIBRATE_NEWMETHOD)(const VG_S32&,const VG_S32&);
typedef VG_VOID (*VG_CALIBRATE_DELETE)();
typedef VG_S32 (*VG_CALIBRATE_RECALIBRATE)();
typedef VG_S32 (*VG_CALIBRATE_SAVETOXML)(std::string);
typedef VG_S32 (*VG_CALIBRATE_UPDATERESULT)(VG_IMAGE_S&,VG_RECT_S&);
typedef VG_S32 (*VG_CALIBRATE_SHOWTAGPOINTSANDINTRINSIC)(const VG_S32&,VG_IMAGE_S&);
typedef VG_S32 (*VG_CALIBRATE_TAGPOINTSELECT)(const VG_S32&,const VG_S32&,const VG_POINT2F64_S&,VG_IMAGE_S& );
typedef VG_S32 (*VG_CALIBRATE_GETSRCFRAMESIZE)(const VG_S32&,VG_SIZE_S&);
typedef VG_S32 (*VG_CALIBRATE_GETCURPOINTZOOMOUTIMAGE)(const VG_S32& ,const VG_POINT2S32_S&,VG_IMAGE_S&);
typedef VG_S32 (*VG_CALIBRATE_CAMERAINNER_ADJUST)(const VG_S32&,const VG_F64 &, const VG_F64 &, \
		const VG_F64 &,VG_IMAGE_S&);
typedef VG_S32 (*VG_CALIBRATE_SETVEHICLEADJUST)(const VG_S32&,const VG_S32&,const VG_POINT2S32_S &);
typedef VG_S32 (*VG_CALIBRATE_GETPROCESSSTATE)();
typedef VG_S32 (*VG_CALIBRATE_VEHICLEROTATE)(VG_F32);
typedef VG_S32 (*VG_CALIBRATE_TAGPOINTUPDATE)(const VG_S32&, const std::vector<VG_POINT2F64_S>);
typedef VG_S32 (*VG_CALIBRATE_GETCAMPARAMS)(std::vector<VG_CAMERA_PARAM> &);
typedef VG_S32 (*VG_YUVTOPNG)(const std::string, VG_IMAGE_S &);


//@brief 基與張氏平面標定法的標定操作結構體
struct VG_CALIBRATE_OLDMETHOD_OPS_S {
	//@brief 创建并初始化标定任务模块
	//@param in 标定任务配置结构体
	//@remarks 此函数在主程序调用,用于创建标定任务
	//         此函数需与VG_CalibrateTaskDeInit配对使用
	VG_CALIBRATE_INIT _init;
	//@breif 销毁标定任务
	//@remarks 此函数需与VG_CalibrateTaskInit 配对使用
	VG_CALIBRATE_DEINIT _deinit;
	//@brief 标定并保存标定结果到s8SavedXmlFile
	//@param in  stCaliInVect ，各通道标定输入参数向量
	//       in stVehicleSize,车辆尺寸参数
	//       out stCaliResultVect，各通道摄像头SVM标定结果
	//@return 保存失败，返回VG_FALSE
	VG_CALIBRATE_OLDMETHOD _calibrate;
};

//@brief 基與相機姿態估計與全局BA的標定操作結構體
struct VG_CALIBRATE_BA_OPS_S {
	//@brief 创建并初始化标定任务模块
	//@param in 标定任务配置结构体
	//@remarks 此函数在主程序调用,用于创建标定任务
	//         此函数需与VG_CalibrateTaskDeInit配对使用
	VG_CALIBRATE_INIT _init;
	//@breif 销毁标定任务
	//@remarks 此函数需与VG_CalibrateTaskInit 配对使用
	VG_CALIBRATE_DEINIT _deinit;
	//@brief　创建标定任务,并生成初始标定结果
	//@param　in srcImage　标定摄像头视图
	//       in _s32CaliMethod 标定模式
	//       in _s32CaliVersion 系统版本号
	//@return　标定结果
	//@remarks　如果标定成功，返回０
	//         _s32CaliMethod 可选值　ENUM_CALIBRATE_4CHS_E/ENUM_CALIBRATE_3CH_FRONT_E/ENUM_CALIBRATE_3CH_BACK_E
	//         _s32CaliVersion可选值ENUM_VERSION_A14_E/ENUM_VERSION_A08_HORIZ_E /ENUM_VERSION_A08_VERTICAL_E/ENUM_VERSION_A13_E
	//　　　　　错误码：-5　输入的标定帧数据不符合标定模式需求
	//               -4  存在标定板自动提取失败
	//               -3  内部内存空间申请失败
	//               -2  参数优化失败
	//               -1 标定对象内存申请失败
	VG_CALIBRATE_NEWMETHOD _calibrate;
	//@brief 清空内部标定对象
	//@Remarks 標定結束時調用
	VG_CALIBRATE_DELETE _delete;
	//＠brief　重标定
	//@remarks　当初始标定失败时，通过手动调整内参和手动选点后调用，重标定
	//@return 标定结果，成功返回０
	//@remarks　　　　　错误码：-5　输入的标定帧数据不符合标定模式需求
	//              -4  存在标定板自动提取失败
	//              -3  内部内存空间申请失败
	//              -2  参数优化失败
	//              -1 标定对象 指针为空
	VG_CALIBRATE_RECALIBRATE _recalibrate;
	//@brief 保存到xml
	//@param　in s8XmlFulPath全路径名
	//       in　dirstr　保存文件夹路径
	//@return
	//@remarks 保存数据的同时会清楚标定对象内存
	//         此函数应在整个标定任务结束时调用
	VG_CALIBRATE_SAVETOXML _save;
	//@brief　刷新显示标定结果
	//@param out stImage 标定结果目标视图
	//       out stVehiclePixSize 车模区域大小
	//@return -1 标定对象 指针为空　0成功
	VG_CALIBRATE_UPDATERESULT _update;
	//@brief　/显示内参及提取的标定参考点
	//@param　in s32CamId 摄像头id
	//       out stImage 摄像头图像数据结构
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_SHOWTAGPOINTSANDINTRINSIC _showTagAndIntrinsic;
	//@brief　手动打单个点，同时刷新当前摄像头打点显示
	//@param in s32CamId  摄像头id
	//       in s32PointSel 当前选定点id
	//       in Point　当前点选定坐标
	//       out　stImage　摄像头图像数据结构
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_TAGPOINTSELECT _tagPointSelect;
	//@brief　获取源图尺寸
	//@param in　s32CamId　摄像头ＩD
	//       out stImgSize
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_GETSRCFRAMESIZE _getSrcFrameSize;
	//@brief　获取当前点放大显示区域
	//@param　　in s32CamId  摄像头id
	//        in　Point 当前像素坐标点
	//        out 放大区域图像
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_GETCURPOINTZOOMOUTIMAGE _curPointZoomOut;
	//@brief　摄像头内参调整
	//@param in s32CamId  摄像头id
	//       in f64FxyStep fxy调整阶长
	//       in f64StepU　cu平移阶长
	//       in f64StepV cv平移阶长
	//       out 摄像头图像数据结构
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_CAMERAINNER_ADJUST  _innerAdjust;
	//@brief 车模区域调整
	//@param in s32LenthStep 车长调整量
	//       in　s32WidthStep车宽调整量
	//       in offset 车辆左右上下平移量
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_SETVEHICLEADJUST _vehcileRegionAdjust;
	//@brief 获取自动标定进度
	//@return 当前进度枚举值
	//@remarks 当前进度枚举值  VG_ENUM_LEFTVIEW_POINT_EXTRACT_FINISH_E = 0,
    // VG_ENUM_RIGHTVIEW_POINT_EXTRACT_FINISH_E,
    //VG_ENUM_FRONTVIEW_POINT_EXTRACT_FINISH_E,
    //VG_ENUM_BACKVIEW_POINT_EXTRACT_FINISH_E,
    //VG_ENUM_LEFTVIEW_POINT_EXTRACT_FAILURE_E,
    //VG_ENUM_RIGHTVIEW_POINT_EXTRACT_FAILURE_E,
    //VG_ENUM_FRONTVIEW_POINT_EXTRACT_FAILURE_E,
    //VG_ENUM_BACKVIEW_POINT_EXTRACT_FAILURE_E,
    //VG_ENUM_INNER_CACULATE_FINISH_E,
	//VG_ENUM_AUTOCALIBRATE_BUTT_E,
	VG_CALIBRATE_GETPROCESSSTATE _getState;
	//@brief 调整车模旋转角度
	//@param in angle 角度
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_VEHICLEROTATE _vehiclerotate;
	//@brief　手动打8个点，同时刷新当前摄像头打点显示
	//@param in s32CamId  摄像头id
	//       in Point　当前点选定坐标集合
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_TAGPOINTUPDATE _tagpointsupdate;
	//@brief　获取摄像头参数
	//@param in stCameraParam  摄像头参数集合
	//@return VG_FAILURE/VG_SUCCEED
	VG_CALIBRATE_GETCAMPARAMS _getCamParams;
	//@brief 	tranform yuv to jpeg
	//@param 	s8DestPath saved directory
	//			stImage yuv data
	//@return VG_SUCCEED/VG_FAILURE
	VG_YUVTOPNG _yuvSaveToPng;

};


}
}
}




#endif /* INCLUDE_VG_CALIBRATE_OPS_DEF_HPP_ */
