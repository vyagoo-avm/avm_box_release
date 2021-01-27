
#include <string>
#include "../common/vgtype.hpp"
#ifndef INCLUDE_STORAGE_DEF_HPP_
#define INCLUDE_STORAGE_DEF_HPP_

namespace vagoo {
typedef VG_BOOL (*FORMAT_STORAGE)(VG_S32 s32StorageId);
typedef VG_STORAGE_S* (*GET_STORAGE_INFORMATION)(void);
typedef std::string (*GET_SDCARD_PARENTDIR)(void);
typedef VG_S32 (*GET_CURRWRITE_SDCARD_ID)(void);
typedef std::string (*GET_STORAGEPATH_FOR_WRITE)(void);
typedef VG_BOOL (*CHECK_EVENT_BE_RECODE_WRITING)(void);
typedef std::vector<std::string> (*_deleteSeletctedLogs)(std::vector<std::string>);
typedef VG_BOOL (*_exportSelectedLogs)(std::vector<std::string>,const std::string &);


struct VAGOO_STORAGE_OPS_S {
    /*
 * 函数名:callback_storage_formatStorage
 * 函数功能:回调函数,格式化指定storage
 * 参数:storage索引值
 * 返回值:格式化成功返回true，否则返回false
 * 注意事项：无
 */
  FORMAT_STORAGE _format;
  GET_STORAGE_INFORMATION _getInformation;
  GET_SDCARD_PARENTDIR _getSdCardParentDir;
  GET_CURRWRITE_SDCARD_ID _getCurWriteSDId;
  GET_STORAGEPATH_FOR_WRITE _getStoragePathForWrite;
  _deleteSeletctedLogs _deletelog;
  _exportSelectedLogs _exportlog;

};

}

#endif
