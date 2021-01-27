#include <string>
#include "../common/vgtype.hpp"
#ifndef INCLUDE_CONFIG_DEF_HPP_
#define INCLUDE_CONFIG_DEF_HPP_
namespace vagoo {

#define MILES_TO_KM(x)  ((x)/(0.62137) + 0.005)
#define KM_TO_MILES(x)  ((x)*(0.62137))

enum {
    VAGOO_STANDBY_3S_E =0,
    VAGOO_STANDBY_5S_E,
    VAGOO_STANDBY_10S_E,
    VAGOO_STANDBY_NUM_E
};

enum {
    VAGOO_VIEW_MODE_3D_E=0,
    VAGOO_VIEW_MODE_2D_E,
    VAGOO_VIEW_MODE_NUM_E
};

enum {
    VAGOO_VIEW_NORMAL_DUALF=0,
    VAGOO_VIEW_NORMAL_DUALB,
    VAGOO_VIEW_NORMAL_QUAD,
    VAGOO_VIEW_NORMAL_NUM_E
};

enum {
    VAGOO_SPEEDWAKEUP_10KMH_E=0,
    VAGOO_SPEEDWAKEUP_20KMH_E,
    VAGOO_SPEEDWANKE_30KMH_E
};

enum {
    VAGOO_LANGUAGE_ENGLISH_E=0,
    VAGOO_LANGUAGE_CHINESE_E,
    VAGOO_LANGUAGE_NUM_E
};

struct VAGOO_USER_SETUP_S {
      VG_U32 u32ViewMode;
      VG_U32 u322DNormalView;
      VG_BOOL bAutoStandby;
      VG_U32 u32AutoStandbyIdx;
      VG_BOOL bSpeedWakeup;
      VG_U32 u32SpeedWakeUpIdx;
      VG_BOOL bIconDisplay;
      VG_U32 u32LanguageIdx;

      //时间相关设置
      VG_S32 s32TimeZone;
      VG_BOOL bDayLight;
};


enum {
    ENUM_RECODE_QUALITY_HIGH_E=0,
    ENUM_RECODE_QUALITY_LOW_E,
    ENUM_RECODE_QUALITY_NUM_E
};

enum {
    ENUM_RECODE_DURATION_5MIN_E=0,
    ENUM_RECODE_DURATION_10MIN_E,
    ENUM_RECODE_DURATION_15MIN_E,
    ENUM_RECODE_DURATION_USERDEF_E,
    ENUM_RECODE_DURATION_NUM_E
};

enum {
    ENUM_GSENSOR_SENSITIVITY_LOW_E=0,
    ENUM_GSENSOR_SENSITIVITY_HIGH_E,
    ENUM_GSENSOR_SENSITIVITY_NUM_E
};

struct VAGOO_DVR_CONF_S {
    std::string s8VehicleId;
    VG_U32 u32QualityId;
    VG_BOOL bAutoRecordON;
    VG_U32 u32DurationIdx;
    VG_U32 u32UserDefineDuration;
    VG_BOOL bGsensorEventOn;
    VG_U32 u32GsensorSensitivityId;
    VG_BOOL bGpsEventOn;
    VG_U32 u32SpeedThresh;
};

struct VAGOO_stLoginParams_S{
	VG_BOOL bLogined;
	VG_BOOL bRootLogin;
	std::string loginPassword;
};



typedef VAGOO_USER_SETUP_S (*CONFIG_GET_USERSETUP_CONF)();
typedef VAGOO_DVR_CONF_S (*CONFIG_GET_DVR_CONF)();
typedef VG_S32 (*VAGOO_SET_USER_CONFIG)(const VAGOO_USER_SETUP_S&);
typedef VG_S32 (*VAGOO_SET_DVR_CONF_S)(const VAGOO_DVR_CONF_S&);

typedef VG_S32 (*CONFIG_MOUDLE_CREATE)();
typedef VG_S32 (*CONFIG_MOUDLE_DELETE)();
typedef VG_S32 (*CONFIG_WRITE_TO_XML)();
typedef VG_S32 (*CONFIG_READ_FROM_XML)();
typedef VG_S32 (*CONFIG_EXPORT)(const std::string &);
typedef VG_S32 (*CONFIG_IMPORT)(const std::string &);

typedef VAGOO_stLoginParams_S (*CONFIG_GETLOGINPASSWORDPARAMS)(void);
typedef void (*CONFIG_SETLOGINPASSWORDPARAMS)(VAGOO_stLoginParams_S);

typedef std::string (*_callback_globalXml_getGlobalXmlFileName)(void);

struct VAGOO_CONFIG_OPS_S {
    CONFIG_MOUDLE_CREATE _create;
    CONFIG_MOUDLE_DELETE _delete;
    CONFIG_GET_USERSETUP_CONF _getUserSetup;
    VAGOO_SET_USER_CONFIG _setUserSetup;
    CONFIG_GET_DVR_CONF _getDvrConfig;
    VAGOO_SET_DVR_CONF_S _setDvrConfig;
    CONFIG_WRITE_TO_XML _write;
    CONFIG_READ_FROM_XML _read;
    CONFIG_EXPORT _export;
    CONFIG_IMPORT _import;

    CONFIG_GETLOGINPASSWORDPARAMS _getPwd;
    CONFIG_SETLOGINPASSWORDPARAMS _setPwd;

    _callback_globalXml_getGlobalXmlFileName _getConfigFileFulPathname;
};


}
#endif
