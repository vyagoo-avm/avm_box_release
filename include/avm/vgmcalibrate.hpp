/*
 * vgmcalibrate.hpp
 *
 *
 * 有关环视标定操作相关的结构体及功能函数
 *
 * 8点式标定法，此版本商未测试
 *
 *  Created on: Dec 17, 2018
 *      Author: zdz
 */

#ifndef VG_SVMCALIBRATE_HPP_
#define VG_SVMCALIBRATE_HPP_
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "vg_avmcommon.hpp"
#include "vg_avm_calibrate_ops_def.hpp"
#ifdef VG_DEBUG
#define VG_CALI_DEBUG 1
#endif

namespace vagoo {
namespace vg_avm {
namespace calibrate {
namespace old {

//@brief　获取舊模块操作函数集
//@return 舊模块操作函数集
VG_CALIBRATE_OLDMETHOD_OPS_S VG_GetOldCalibrateOpsStruct();
}
}//end of namespace vgmcalibrate
}//end of vg_avm
}//endof vagoo

#endif /* VG_SVMCALIBRATE_HPP_ */
