#ifndef AVM_GUI_DEF_HPP
#define AVM_GUI_DEF_HPP
#include "../common/vgtype.hpp"
#include "../config/config_def.hpp"
#include "../storage/storage_ops_def.hpp"
#include "../avm/vgrender_ops_def.hpp"
#include "../avm/vg_avm_calibrate_ops_def.hpp"
namespace vagoo {
namespace gui {

//for DVR(VPU)
typedef VG_VOID (*CALLBACK_DVR_GETDVRSTATE)(VG_S32*,VG_S32*);
typedef VG_VOID (*CALLBACK_DVR_CLOSEDVR)(VG_VOID);
typedef VG_S32 (*CALLBACK_DVR_OPENDVR)(VG_VOID);

struct VAGOO_GUI_INPUT_S {
    VAGOO_CONFIG_OPS_S config_ops;
    VAGOO_STORAGE_OPS_S storage_ops;
    vg_avm::vgrender::VG_RENDER_OPS_S render_ops;
    vg_avm::calibrate::VG_CALIBRATE_BA_OPS_S calibrate_ops;
    CALLBACK_DVR_GETDVRSTATE _getRecodeState;
    CALLBACK_DVR_CLOSEDVR _closeDvr;
    CALLBACK_DVR_OPENDVR _openDvr;
};


typedef struct{

    VG_U64 u64Position;
    VG_U64 u64TotalSize;
}VG_PlayBackProgress_S;


typedef VG_S32 (*GuiTaskInit)(const VAGOO_GUI_INPUT_S& );
typedef void (*SetPlayBackTotalSize)(VG_U64);
typedef void (*SetPlayBackPosition)(VG_U64);
typedef VG_PlayBackProgress_S (*GetPlayBackprogress)(void);
typedef VG_BOOL (*BOOL_GUI_GETMAINWINDOW)();
typedef void (*GUI_SentQtKey)(const VG_U32 & s32QtKeyCode);

struct VG_GUI_OPS_S {
    GuiTaskInit _init;
    SetPlayBackTotalSize _setPlayBackTotalSize;
    SetPlayBackPosition _setPlayBackPosition;
    GetPlayBackprogress _getPlayBackprogress;
    BOOL_GUI_GETMAINWINDOW _bMainWnd;
    GUI_SentQtKey _sentQtKey;
    
};



}
}
#endif // AVM_GUI_DEF_HPP
