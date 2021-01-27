/*
 * vgrender.hpp
 *
 *  Created on: Jan 11, 2019
 *      Author: zdz
 */

#ifndef VG_SVRENDER_HPP_
#define VG_SVRENDER_HPP_
#pragma once
#include <pthread.h>
#include <string>
#include <vector>

#include"vgrender_ops_def.hpp"
namespace vagoo {
namespace vg_avm {
namespace vgrender {
VG_RENDER_OPS_S VG_RenderGetOpsStruct();
}
}
}
#endif /* VG_SVRENDER_HPP_ */