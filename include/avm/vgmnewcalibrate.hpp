/*
 * vgmnewcalibrate.hpp
 *
 *  Created on: May 27, 2020
 *      Author: zdz
 */

#ifndef INCLUDE_SVMNEWCALIBRATE_HPP_
#define INCLUDE_SVMNEWCALIBRATE_HPP_

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "vg_avmcommon.hpp"
#include "vg_avm_calibrate_ops_def.hpp"

namespace vagoo {
namespace vg_avm {
namespace calibrate {
namespace newmethod {

//@brief　获取新模块操作函数集
//@return 舊模块操作函数集
VG_CALIBRATE_BA_OPS_S VG_GetBaCalibrateOpsStruct();

}
}
}
}

#endif /* INCLUDE_SVMNEWCALIBRATE_HPP_ */
