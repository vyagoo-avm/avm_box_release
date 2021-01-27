/*
 * vg_avmcommon.hpp
 *
 *  Created on: Dec 18, 2018
 *      Author: zdz
 */

#ifndef VG_SVMAVM_VG_AVMCOMMON_HPP_
#define VG_SVMAVM_VG_AVMCOMMON_HPP_
#include "../common/vgtype.hpp"
namespace vagoo {
namespace vg_avm {

 enum { //标定方式枚举
     VG_ENUM_CALIMETHOD_UCHESSBORD=0,//棋盘格式标定
     VG_ENUM_CALIMETHOD_U8POINTS,//8点式标定
     VG_ENUM_CALIMETHOD_BUTT,
   };

 enum {//标定结果枚举
   VG_ENUM_CALI_NOIMAGE,
   VG_ENUM_CALI_NOCHESSBOARD,//当前通道未提取到棋盘格，只限于棋盘格标定方式
   VG_ENUM_CALI_CALCFAILED,//当前通道参数计算错误，即计算的参数超出许可的参数范围
   VG_ENUM_CALI_FAILED,//标定失败，未提取到至少2块棋盘格，只限于棋盘格标定方式
   VG_ENUM_CALI_SUCCEED,//标定成功
   VG_ENUM_CALI_BUTT,
 };

 //有关摄像头参数的结构体，摄像头参数由相机内参矩阵(3x3)、鱼眼畸变参数(1x4)、相机旋转向量(1x3)、相机平移向量(1x3)组成；
     //其中，相机内参矩阵与鱼眼畸变参数为内参；相机旋转向量、相机平移向量为外餐；
     //摄像头内参矩阵为3x3的矩阵{fx,0.0,u0,0.0,fy,v0,0.0,0.0,1.0}表征的是相机坐标（xc,yc）于图像像素坐标(u,v)之间的变换关系，变换关系如下：
     //u =fx*xc+u0
     //v=fy*yc+vo
     //鱼眼畸变参数为1x4的矩阵，畸变模型为：r=sita*(1+k1*sita^2+k2*sita^4+k3*sita^6+k4*sita^8)；
     //相机外参表征的是世界坐标与相机坐标之间的转换关系，摄像头外参由旋转向量与平移向量构成；
     struct VG_CAMERA_PARAMS_S {
          VG_F64 af64CameraK[9];//摄像头内参矩阵
          VG_F64 af64CameraDistort[4];//鱼眼畸变参数
          VG_F64 af64CameraRotateVect[3];//相机旋转向量
          VG_F64 af64CameraTranslateVect[3];//相机平移向量
          VG_SIZE_S stImageSize;//摄像头图像尺寸，比如1920,1080 或1280,720
     };
     //有关棋盘格式标定方式标定模板；
     //所谓棋盘格式标定，是指在车前后左右铺设标定布进行标定的方式；
     //每块标定布由一块中央区域棋盘格+两块边缘区域棋盘格组成，其中，边缘两块棋盘格具有同样的规格；
     //棋盘格规格的定义：水平方向黑白格交叉点数×垂直方向黑白格交叉点数；
     //前后通道棋盘格居中铺设；
     //左右通道棋盘格要铺设在同一水平线上，但铺设位置，随摄像头安装位置而有所不同，以保证左右标定布在左右视图上均匀分布为宜；
     struct VG_CALI_UCHESSBOARD_PATERN_S {
         VG_S32 s32ChessPosition;//左右棋盘格铺设位置，即左右棋盘格中心点到后视棋盘格的垂直距离
         VG_SIZE_S stChessBoardCenter;//中央区域棋盘格规格
         VG_SIZE_S stChessBoardEdge;//边缘区域棋盘格规格
         VG_S32 s32GridSize;//棋盘格单块黑白格的宽度
     };
     //有关8点式标定方式标定模板
     //所谓8点式标定，是指在车辆左前、右前、左后、右后各铺设一块正方型的黑白格标定布，在标定时通过手动选点的方式，每个通道各选取8个顶点进行标定；
     //8个顶点从视图中左上方的第一个顶点开始，按顺时针方向选取；
     struct VG_CALI_U8P_PATERN_S {
         VG_S32 s3U8PaternBoardSize;//正方形黑白格标定布的长
         VG_POINT2F32_S stf32ImagePoints[8];//选取的8个顶点的像素坐标
     };

     //摄像头纹理网格参数
     struct VG_BOWL_GRID_PARAM_S {      /* Parameters of grid */
         VG_F32 f32GroundRadiusScal;//车模矩形对角线一半的f32GroundRadiusScal倍长度为碗面地面区域半径
         VG_S32 s32Angles;     /*  碗面1+2象限角度个数，比如以1°为阶梯，则s32GridAngles为180*/
         VG_S32 s32NopZ;         /* Number of points in z axis */
         VG_F32 f32StepX;      /* Step in x axis which is used to define grid points in z axis.                         * Step in z axis: step_z[i] = (i * step_x)^2, i = 1, 2, ... - number of point */
         VG_F32 f32OverLayAngle;
     };

     //标定操作有关摄像头通道，图像及标定模板输入的结构体
       struct VG_CALI_INPUT_S {
    	 VG_IMAGE_S stImage;
         VG_S32 s32CameraChannl; //摄像头通道
         //标定方式，可选：VG_ENUM_CALIMETHOD_UCHESSBORD
         //             VG_ENUM_CALIMETHOD_U8POINTS
         VG_S32 s32CaliMethod;
         union {
           VG_CALI_UCHESSBOARD_PATERN_S stChessboard;//棋盘格标定模板
           VG_CALI_U8P_PATERN_S stU8Point;//8点式标定模板
         }stCaliPatern;
       };

       //标定结果结构体
       struct VG_CALI_RESULT_S {
         //标定结果，可选值为:VG_ENUM_CALI_NOIMAGE，
         //                VG_ENUM_CALI_NOCHESSBOARD，
         //                VG_ENUM_CALI_CALCFAILED，
         //                VG_ENUM_CALI_FAILED，
         //                VG_ENUM_CALI_SUCCEED
         VG_S32 s32Result;
         ////摄像头通道号,可选: VG_ENUM_CAMERA_LEFT =0,
         //                 VG_ENUM_CAMERA_RIGHT,
         //                 VG_ENUM_CAMERA_FRONT,
         //                 VG_ENUM_CAMERA_BACK,
         VG_S32 s32CameraChannl;
         //后续参数只有在标定结果为VG_ENUM_CALI_SUCCEED时才赋值
         VG_CAMERA_PARAMS_S stCameraParam;
         VG_S32 s32CaliMethod;//标定方式，可选值为 VG_ENUM_CALIMETHOD_UCHESSBORD或VG_ENUM_CALIMETHOD_U8POINTS或VG_ENUM_CALIMETHOD_BUTT
         union {
           VG_CALI_UCHESSBOARD_PATERN_S stChessboard;//棋盘格标定模板
           VG_CALI_U8P_PATERN_S stU8Point;//8点式标定模板
         }stCaliPatern;
       };
       //环视观察视点结构体
       struct VG_VIEW_CAMERA_S {
    	   VG_POINT3F32_S stCameraPos;//观察摄像头位置
    	   VG_POINT2F32_S stCameraRotate;//观察摄像头旋转参数
       };

       //消防车应用outriger
       struct VG_OutTTRIGL_S {
       	VG_F32 stPixY;
       	VG_S32 s32Lenth;
       	VG_S32 s32Width;
       	VG_S32 bDisplay;
       };

       struct VG_RENDER_OUTTRIGER_S {
       	VG_OutTTRIGL_S astConf[4];
       };

       //倒车轨迹线
       struct VG_BACKWARD_TRACE_S {
       	VG_S32 s32Wheelbase;// 前后轮之间距离,即车辆轴距
       	VG_S32 s32ReaLWheelOffset;//后轮到车尾的距离
       };


       struct VG_CAL_RESULT_INFOR_S {
           VG_S32 s32ResultIdx;
           VG_S32 s32Chn;
       };

       //摄像头打点坐标与内参圆
       typedef struct VG_CAMERA_PARAM {
       	VG_S32 s32CameraId;
       	VG_POINT2S32_S stPoint[8];
       	VG_F32 s32Circle_r;
       	VG_POINT2S32_S stCircle_center;
       }VG_CAMERA_PARAM;

       //@brief 虚拟视点参数
       struct VG_RENDER_VIRTULVIEW_PARAM_S{
         VG_POINT3F32_S stCamPosition;
         VG_POINT2F32_S stCamRotate;
       };

       //@brief 俯视图调整参数
       //  -          -
       //    -      -
       //     ------
       //     ------
       //     ------
       //     ------
       //    -      -
       //  -          -
       struct VG_RENDER_BIRDVIEW_ADJUST_S {
    	   VG_F32 f32OverLay[4]; //四交叠区域交叠角
    	   VG_S32 s32DisplayRegion[4];//前后左右四个方向的显示距离
       };

       struct VG_RENDER_3DView_Adjust {
          VG_F32 f32CameraPosZ;
          VG_F32 f32CameraRotateY;
       };

       enum {
       	ENUM_CALIBRATE_4CHS_E=0,
       	ENUM_CALIBRATE_3CH_FRONT_E,
       	ENUM_CALIBRATE_3CH_BACK_E,
       };

       enum {
       	ENUM_VERSION_A14_E=0,
       	ENUM_VERSION_A08_HORIZ_E,
       	ENUM_VERSION_A08_VERTICAL_E,
       	ENUM_VERSION_A13_E
       };

       //auto calibrate
       enum {
           CALI_ERR_SRCIMAGE_ERR_E=-5,//确失标定输入图像
           CALI_ERR_TAGPOINT_LOST_E,//-4 提取标定板坐标点失败
           CALI_ERR_ALLOC_ERR_E,//-3　　内部内存空间申请失败
           CALI_ERR_OPTMIZE_ERR_E,//-2　//优化出错
       };

       enum {
           VG_ENUM_LEFTVIEW_POINT_EXTRACT_FINISH_E = 0,
           VG_ENUM_RIGHTVIEW_POINT_EXTRACT_FINISH_E,
           VG_ENUM_FRONTVIEW_POINT_EXTRACT_FINISH_E,
           VG_ENUM_BACKVIEW_POINT_EXTRACT_FINISH_E,
           VG_ENUM_LEFTVIEW_POINT_EXTRACT_FAILURE_E,
           VG_ENUM_RIGHTVIEW_POINT_EXTRACT_FAILURE_E,
           VG_ENUM_FRONTVIEW_POINT_EXTRACT_FAILURE_E,
           VG_ENUM_BACKVIEW_POINT_EXTRACT_FAILURE_E,
           VG_ENUM_INNER_CACULATE_FINISH_E,
       	VG_ENUM_AUTOCALIBRATE_BUTT_E,
       };

}
}


#endif /* SRC_COMMON_VG_AVMCOMMON_HPP_ */
