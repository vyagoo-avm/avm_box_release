/*
 * vg_media_buf.hpp
 *
 *  Created on: Mar 22, 2019
 *      Author: zdz
 */

#ifndef INCLUDE_VG_MEDIA_BUF_HPP_
#define INCLUDE_VG_MEDIA_BUF_HPP_

#pragma once
#include "../../../common/vgtype.hpp"
#include "../../../common/vg_media_com.hpp"
//#include "../../../common/vgtype.hpp"
//#include "../../../common/vg_media_com.hpp"
namespace vagoo {
namespace media {
namespace dvr {
namespace mediabuf {
#define VIDEO_STREAM_TYPE_CNT  3
#define VIDEO_STREAM_TYPE_MAIN  0
#define VIDEO_STREAM_TYPE_WBC   1
#define VIDEO_STREAM_TYPE_WBC_JPG   2


typedef VG_S32 (*CALLBACK_ASTREAMCOPYTO)(void* pDest,void* pSrc);
typedef VG_U64 (*CALLBACK_ASTREAMGETPTS)(void* pSrc);
typedef VG_U32 (*CALLBACK_ASTREAMGETSIZE)(void* pSrc);

typedef VG_S32 (*CALLBACK_VSTREAMCOPYTO)(void* pDest,void* pSrc);
typedef VG_U8 (*CALLBACK_VSTREAMISKEYFLAG)(void* pSrc);
typedef VG_U64 (*CALLBACK_VSTREAMGETPTS)(void* pSrc);
typedef VG_U32 (*CALLBACK_VSTREAMGETSIZE)(void* pSrc);

struct VG_MEDIABUF_CALLBACK_S {
	CALLBACK_ASTREAMCOPYTO _AStreamCopyto;
	CALLBACK_ASTREAMGETPTS _AStreamGetPts;
	CALLBACK_ASTREAMGETSIZE _AStreamGetSize;

	CALLBACK_VSTREAMCOPYTO _VStreamCopyto;
	CALLBACK_VSTREAMISKEYFLAG _VStreamIsKey;
	CALLBACK_VSTREAMGETPTS _VStreamGetPts;
	CALLBACK_VSTREAMGETSIZE _VStreamGetSize;
};

//@brief 设置mediabuffer 读取I帧
//@return VG_FAILURE/VG_SUCCEED
VG_S32 MEDIA_BUFFER_SetReaderIframe(void);
//@brief 设置mediabuffer 读取回退，用于事件录像
//@param u32Offset second
//@return VG_FAILURE/VG_SUCCEED
VG_S32 MEDIA_BUFFER_SetReaderBack(const VG_U32 u32Offset);
//@brief 获取主媒体缓存包
//@param in pu8Addr 缓存包存储地址，需调用前申请足够空间,有内存泄露风险
//       out pPacketInfo 媒体包信息
//@return VG_FAILURE/VG_SUCCEED
VG_S32 MEDIA_BUFFER_GetMainStream(VG_U8 *pu8Addr, VG_MEDIA_STREAM_S* pPacketInfo);
//@brief 推送媒体包到媒体缓存
//@param in pStream 媒体包
//       in pStreamInfor  媒体包信息
//@return VG_FAILURE/VG_SUCCEED
//@remarks
//       pStream  could been VG_DATA_STREAM_S VENC_STREAM_S AUDIO_STREAM_S
VG_S32 MEDIA_BUFFER_PutMainStream(const VG_VOID *pStream,const VG_MEDIA_STREAM_S *pStreamInfor);
//@brief 推送JPEG媒体包到媒体缓存
//@param in pStream VENC_STREAM_S
//       in pStreamInfor  媒体包信息
//@return VG_FAILURE/VG_SUCCEED
VG_S32 MEDIA_BUFFER_PutJpegStream(const VG_VOID *pStream,const VG_MEDIA_STREAM_S *pStreamInfor);
VG_S32 MEDIA_BUFFER_GetJpgStream(VG_U8 *pu8Addr, VG_MEDIA_STREAM_S* pPacketInfo);
VG_S32 MEDIA_BUFFER_SetJpegReaderBack(const VG_U32 u32Offset);
VG_S32 MEDIA_BUFFER_SetJpegReaderIframe(void);

VG_S32 MEDIA_BUFFER_PutRtspStream(const VG_VOID *pStream,const VG_MEDIA_STREAM_S *pStreamInfor);
VG_S32 MEDIA_BUFFER_GetRtspStream(VG_U8 *pu8Addr, VG_MEDIA_STREAM_S* pPacketInfo);
VG_S32 MEDIA_BUFFER_SetRtspReaderBack(const VG_U32 u32Offset);
VG_S32 MEDIA_BUFFER_SetRtspReaderIframe(void);

//@Remarks Used with MEDIA_BUFFER_DeInit
//VG_S32 MEDIA_BUFFER_Init(void);
VG_S32 MEDIA_BUFFER_Init(const VG_MEDIABUF_CALLBACK_S& stCallbacks);
VG_VOID MEDIA_BUFFER_DeInit(void);

}
}
}
}



#endif /* INCLUDE_VG_MEDIA_BUF_HPP_ */
