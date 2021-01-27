
#ifndef _VG_COMMUNITY_DEF_
#define _VG_COMMUNITY_DEF_
#include"../common/vgtype.hpp"//POD数据自定义及SV公共数据结构
#include "../avm/vgrender_ops_def.hpp"
#include "../gui/avm_gui_def.hpp"
namespace vagoo {
namespace communication {

typedef VG_BOOL (*VG_SENT_GUIKeyCode)(const VG_S32& s32QtCode);
typedef VG_BOOL (*BOOL_GUI_GETMAINWINDOW)();


struct VG_IRDEV_CONFIG_S {
    vg_avm::vgrender::VG_RENDER_OPS_S renderops;
    vagoo::gui::VG_GUI_OPS_S guiops;
    VG_SENT_GUIKeyCode _sentQtKey;
};

typedef VG_S32 (*s32Openirdev)(const VG_IRDEV_CONFIG_S& configs);
typedef VG_VOID (*CloseIrDev)();

struct VG_IRDEV_OPS {
    s32Openirdev _open;
    CloseIrDev _close;

};

struct GPS_DATA_S {
	VG_S32             s32Mode; // 1 GPS_WEAK  2 GPS_STRONGER 3 VG_ENUM_GPS_STRONG_E
    VG_S32             s32SatellitesUsed;
    VG_S32             s32SatellitesVisible;

    VG_F64          f64latitude;        //latitude
    VG_F64          f64Lontitude;
    VG_F64          f64Altitude;
    VG_F64          f64GroundSpeed;      //speed over ground
    VG_F64          f64GroundCourse;     //course over ground
    VG_F64          f64Time;
    VG_F64          f64Epx;
    VG_F64          f64Epy;
    VG_F64          f64Epv;
    VG_F64          f64Pdop;
    VG_F64          f64Hdop;
    VG_F64          f64Vdop;
};

struct GPS_DEV_DATA_S {
		GPS_DATA_S stGpsData;
		VG_BOOL bDisconnected;
};


}
}

#endif