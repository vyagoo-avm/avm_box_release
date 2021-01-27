/*
 * vgrender_ops_def.hpp
 *
 *  Created on: Sep 24, 2020
 *      Author: zdz
 */

#ifndef INCLUDE_SVRENDER_OPS_DEF_HPP_
#define INCLUDE_SVRENDER_OPS_DEF_HPP_
#include "vg_avmcommon.hpp"
#include <vector>
namespace vagoo {
namespace vg_avm {
namespace vgrender {

typedef std::string (*CALLBACK_GETVEHICLEDAE)(void);//获取车模文件全路径名称回调函数类型
typedef VG_BOWL_GRID_PARAM_S (*CALLBACK_GETBOWLGRID)();//获取碗面网格参数
typedef std::vector<VG_IMAGE_S> (*CALLBACK_GETFRAMEVECT)(void);//获取摄像头帧向量回调函数类型
typedef void (*CALLBACK_PUTFRAMEVECT)( std::vector<VG_IMAGE_S>&);//释放摄像头帧向量回调函数类型
typedef VG_BOOL (*CALLBACK_GET_RENDER2D_FLAG)(VG_VOID);//回调，是否为2D显示模式
typedef VG_S32 (*CALLBACK_GET_RENDER2D_NORMALVIEW)(VG_VOID);//回调,获取2D显示模式下的默认显示模式
typedef VG_VOID (*CALLBACK_SOCKETCAN_GET_BACKTRACKMSG)(VG_BOOL &, VG_F32 &); //鍥炶皟,鑾峰彇鏉ヨ嚜socketcan鐨勮溅杈嗚浆鍚戝崐寰勭瓑淇℃伅


//开启Render任务需要的回调函数
struct VG_RENDER_CONFIG_S {
  CALLBACK_GETVEHICLEDAE pCallGetVehicleDae;
  CALLBACK_GETBOWLGRID  pCallGetBowlGridParam;
  CALLBACK_GETFRAMEVECT pCallGetFrameS;
  CALLBACK_PUTFRAMEVECT pCallPutFrameS;
  CALLBACK_GET_RENDER2D_FLAG pCallGet2DModeFlag;
  CALLBACK_GET_RENDER2D_NORMALVIEW pCallBackGet2DNormalView;
  VG_S8* s8XmlFileName; //标定结果xml文件路径
  VG_F32 f32VehicleTranslucency;//车模半透明度0.5-1.0
  VG_S8* s8KeyBoardDevName; //键盘设备全路径名称
  VG_S8* s8MouseDevName; //鼠标设备全路径名称
  VG_S8* s7GpioKeyBoardDevName;//gpio键盘设备全路径名
  CALLBACK_SOCKETCAN_GET_BACKTRACKMSG pCallGetBackTrackLineMsg;
};

//@brief 虚拟视点参数
struct VG_RENDER_VIRTULVIEW_PARAM_S {
  VG_POINT3F32_S stCamPosition;
  VG_POINT2F32_S stCamRotate;
};

typedef VG_BOOL (*VG_RENDER_OPEN)(const VG_RENDER_CONFIG_S&,const VG_S32&);
typedef VG_VOID (*VG_RENDER_CLOSE)(VG_VOID);
typedef VG_BOOL (*VG_RENDER_UPDATEMESH)(const VG_BOOL bIsUpdateVehicle);
typedef VG_BOOL (*VG_RENDER_TRANSFORM)(const VG_S32& ,const VG_RENDER_VIRTULVIEW_PARAM_S&);
typedef VG_BOOL (*VG_RENDER_TRAANSFORMTOCALLBACK)(const VG_S32&);
typedef VG_BOOL (*VG_RENDER_GETVIEWPARAMS)(VG_RENDER_VIRTULVIEW_PARAM_S* );
typedef VG_VOID (*VG_RENDER_CLASSVIEW)(const VG_S32&);
typedef VG_S32  (*VG_RENDER_EXPORT2STORAGE)(const std::string &);
typedef VG_S32  (*VG_RENDER_EXPORT2WEB)(const std::string &);
typedef VG_S32  (*VG_RENDER_IMPORT)(const std::string &);
typedef VG_S32  (*VG_RENDER_GETFBFRAME)(const VG_S32,VG_IMAGE_S*);
typedef VG_S32  (*VG_RENDER_AUTOSTANDBY_BLOCK)(const VG_BOOL&);
typedef VG_S32  (*VG_RENDER_GETBIRDVIEW_PARAMS)(VG_RENDER_BIRDVIEW_ADJUST_S*);
typedef VG_S32  (*VG_RENDER_SETBIRDVIEW_PARAMS)(const VG_RENDER_BIRDVIEW_ADJUST_S&);
typedef VG_S32  (*VG_RENDER_GET3DVIEW_PARAMS)(VG_RENDER_3DView_Adjust*,VG_BOOL);
typedef VG_S32  (*VG_RENDER_SET3DVIEW_PARAMS)(const VG_RENDER_3DView_Adjust &Params,VG_BOOL bBackWardMOde);
typedef VG_S32  (*VG_RENDER_SAVEVIEW_PARAMS)();

typedef VG_S32  (*VG_RENDER_SETVEHICLETRANCY)(const VG_F32 );
typedef VG_S32  (*VG_RENDER_GETVEHICLETRANCY)(VG_F32*);
typedef VG_VOID (*VG_RENDER_DISPLAYMODE_SET)(const VG_S32);

typedef VG_S32 (*VG_RENDER_SETOUTRIGGER_DISPLAY)(const VG_BOOL);
typedef VG_S32 (*VG_RENDER_SETDYNAMICTRACE_DISPLAY)(const VG_BOOL );

typedef VG_S32 (*VG_RENDER_GETOUTRIGGER_PARAMS)(VG_OutTTRIGL_S* pParams,const VG_S32 s32Chn);
typedef VG_S32 (*VG_RENDER_SETOUTRIGGER_PARAMS)(const VG_OutTTRIGL_S &Params,const VG_S32 s32Chn);
typedef VG_SIZE_S (*VG_RENDER_GETVEHICLESIZE)(VG_VOID);

typedef VG_BOOL (*_UpdateGridParams)(const VG_BOWL_GRID_PARAM_S& );
typedef VG_BOOL (*_UpdateWhenVehileDaeChanged)();

struct VG_RENDER_OPS_S {
	//@brief 开启全景映射任务
	//@param in stCallBack 回调函数结构体
	//@return VG_FALSE/VG_BOOL
	//@remarks 函数内部检查回调函数是否已注册，同时创建映射线程
	//         RenderTaskOpen 需与RenderTaskClose成对出现
	//         RenderTaskOpen只能在主线程中调用
	VG_RENDER_OPEN _open;
	//@brief 关闭全景映射任务
	//@remarks 销毁映射线程，并去注册回调函数
	//         只能在主线程中调用
	VG_RENDER_CLOSE _close;
	//@brief 当变更摄像头mesh时，刷新用于绘制的摄像头网格或车模网格
	//@return VG_FALSE/VG_TRUE
	//@remaks 可在每次标定成功时或更换车模时调用，用于显示结果
	VG_RENDER_UPDATEMESH _update;
	//@brief Render视点变换
	//@param in S32DisplayMode显示模式
	//       in stVirtualParam虚拟视点参数
	//@return 任务未创建，返回VG_FALSE;
	//@remarks   可在其他线程中作为回调函数调用，变更当前的3D显示视角或显示模式
	//           S32DisplayMode 可选值为VG_ENUM_VIEW_3D、VG_ENUM_VIEW_DUAL_LEFT-VG_ENUM_VIEW_DUAL_BACK\VG_ENUM_VIEW_QUAD
	//           VG_ENUM_VIEW_3D显示模式几种视角推荐参数值
	//           左转 stCamRotate = {2.09,-0.75} stCamPosition采用默认值{0,0.1,-3.45}
	//           右转 stCamRot={1.05,-0.75} stCamPosition采用默认值{0,0.1，-3.45}
	//           常态显示 stCamRot采用默认值，即{1.75，,0.75} stCamPosition采用默认值
	VG_RENDER_TRANSFORM _transform;
	//@brief Render视点变换
	//@param in S32DisplayMode显示模式
	//@return 任务未创建，返回VG_FALSE;
	//@remarks   可在其他线程中作为回调函数调用，变更当前的3D显示视角或显示模式
	//           S32DisplayMode 可选值为VG_ENUM_VIEW_3D、VG_ENUM_VIEW_DUAL_LEFT-VG_ENUM_VIEW_DUAL_BACK\VG_ENUM_VIEW_QUAD
	VG_RENDER_TRAANSFORMTOCALLBACK _transform2Callback;
	//@brief 获取当前的虚拟视点参数
	//@param out pstVirtualParam 虚拟视点参数
	//@return 任务未创建，返回VG_FALSE;
	VG_RENDER_GETVIEWPARAMS _getVirView;
	//@brief 经典视角
	//@param in s32ClassicalView 经典视角模式
	//@remarks s32ClassicalView可选值为VG_ENUM_CLASSIC_3DVIEW_TLEFT->VG_ENUM_CLASSIC_3DVIEW_SCAN
	VG_RENDER_CLASSVIEW _classview;
	//@breif 保存当前各摄像头视图到存储设备
	//@param in s8StoragePath 存储设备路径
	//@return VG_FAILURED/VG_SUCESSED
	VG_RENDER_EXPORT2STORAGE _export2storage;
	//@breif 保存当前各摄像头视图到webapp目录
	//@param in s8StoragePath 存储路径
	//@return VG_FAILURED/VG_SUCESSED
	VG_RENDER_EXPORT2WEB _export2web;
	//@breif 从存储设备导入拼接结果到vg_avm
	//@param in s8CCaliResultXmlFileFulPathName 待导入xml文件全路径名
	//@return VG_FAILURED/VG_SUCESSED
	//@remarks 导入文件不完整或参数超出范围时,返回VG_FAILURED
	VG_RENDER_IMPORT _import;
	//@brief 阻滯待機
	VG_RENDER_AUTOSTANDBY_BLOCK _autoStandbyBlock;

	//@brief 获取当前的环视图调整参数
	//@param out pParams 环视图调整参数指针
	//@return VG_FAILURE/VG_SUCCEED
	VG_RENDER_GETBIRDVIEW_PARAMS _getBirdViewParam;
	//@brief 调整环视图调整参数
	//@param in Params 环视图调整参数
	//@return VG_SUCCEED
	//@remarks  此函数会实时刷新结果
	VG_RENDER_SETBIRDVIEW_PARAMS _setBirdViewParam;
	//@brief 获取当前的3D视图调整参数
	VG_RENDER_GET3DVIEW_PARAMS _get3DViewParam;
	//@brief 调整环视图调整参数
	//@param in Params 3D视图调整参数
	//@return VG_SUCCEED
	//@remarks  此函数会实时刷新结果
	VG_RENDER_SET3DVIEW_PARAMS _set3DViewParam;
	//@brief　保存经过调整的视图参数
	VG_RENDER_SAVEVIEW_PARAMS _saveViewParams;
	//@brief 设定３Ｄ车模透明度
	VG_RENDER_SETVEHICLETRANCY _setVehicleTrancy;
	//@brief　获取３Ｄ车模透明读
	VG_RENDER_GETVEHICLETRANCY _getVehicleTrancy;
	//@brief 显示模式的切换（2D/3D）
	//@param in s32DisplayMode 显示模式
	//@remarks s32DisplayMode可选值为
	//enum {
	//	VG_ENUM_VIEW_LEFT=0,
	//	VG_ENUM_VIEW_RIGHT=1,
	//	VG_ENUM_VIEW_FRONT=2,
	//	VG_ENUM_VIEW_BACK=3
	//};
	VG_RENDER_DISPLAYMODE_SET _setDisplayMode;
	//@brief　设定Ｏutrriger显示标志位
	VG_RENDER_SETOUTRIGGER_DISPLAY _setOutRiggerDisplayFlag;
	//@brief　设定动态倒车轨迹显示标志位
	VG_RENDER_SETDYNAMICTRACE_DISPLAY _setDynamicTraceDisplayFlag;
	//@brief 获取当前的outrigger参数
	//@param out pParams Outrigger参数指针
	//@return VG_FAILURE/VG_SUCCEED
	VG_RENDER_GETOUTRIGGER_PARAMS _getOutriggerParam;
	//@brief 调整Outrigger参数
	//@param in Params Outrigger参数
	//@return VG_SUCCEED
	//@remarks  此函数会实时刷新结果
	VG_RENDER_SETOUTRIGGER_PARAMS _setOutriggerParam;
	//@brief　获取车辆尺寸
	VG_RENDER_GETVEHICLESIZE _getVehicleSize;
	//@brief 動態刷新網面參數
	//@param in VG_BOWL_GRID_PARAM_S  Params 碗面網格參數
	_UpdateGridParams _updateGridParam;
	//@brief dae文件改變時動態刷新車模
	_UpdateWhenVehileDaeChanged _updateVehicleDae;
};


}
}
}
#endif /* INCLUDE_SVRENDER_OPS_DEF_HPP_ */
