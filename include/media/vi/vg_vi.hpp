/*
 * vg_vi.hpp
 *
 *  Created on: Jul 1, 2019
 *      Author: zdz
 */

#ifndef INCLUDE_VG_VI_HPP_
#define INCLUDE_VG_VI_HPP_
#pragma once

#include <vector>
#include"../../common/vgtype.hpp"//POD数据自定义及SV公共数据结构
namespace  vagoo {
namespace  media {
namespace  vi {
//remarks 使用范例如下
//              CHECK(VG_VI_TaskCreate());
//              while(bRun) {
//                ...
//               std::vector<VG_IMAGE_S> stImgVect=VG_VIGetFrame();
//               ...
//               VG_VIReleaseFrame(stImgVect);
//               }
//              VG_VI_TaskDelete();
//@brief 创建视频采集任务
//@remarks 只能在主函数调用,需与VG_VI_TaskDelete成对出现
//@return VG_SUCESSED/VG_FAILURED
 VG_S32 VG_VI_TaskCreate(VG_VOID);
 //@brief 关闭视频采集任务
 //@return VG_SUCESSED/VG_FAILURED
 VG_S32 VG_VI_TaskDelete(VG_VOID);
 //@brief 获取帧图像
 std::vector<VG_IMAGE_S> VG_VIGetFrame(VG_VOID);
 //@brief 释放帧图像
 //@remarks 需与VG_VIGetFrame配对使用
 VG_VOID VG_VIReleaseFrame(std::vector<VG_IMAGE_S>& stImage);
//@breif 获取用于录像的帧图像数据
//@param in s32CameraChs 摄像头通道号
//       out pstImage
//@return VG_FAILURE/VG_SUCCEED
 VG_S32 VG_VIGetRecodeFrame(const VG_S32 s32CameraChs, VG_IMAGE_S *pstImage);

}
}
}


#endif /* INCLUDE_VG_VI_HPP_ */
