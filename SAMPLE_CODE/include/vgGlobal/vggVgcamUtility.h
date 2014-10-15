

#ifndef __VGGCAMUTILITY_H__
#define __VGGCAMUTILITY_H__

#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>

namespace  vgGlobal{

	/**
		@date     2009/10/21  20:45
		@author   zzy

		@brief    整理了与Cam相关操作的中间层

		@see
	*/

	class	VGGL_EXPORT CamUtility
	{
	public:
		CamUtility();
		~CamUtility();

	public:
		static  bool importVcrFile();              //导入漫游动画
		//static  bool exportVcrFile();            //导出漫游动画

		static  bool exportBmp();                  //导出Bmp静态图
		static  bool exportAvi();                  //导出Avi视频文件

		static	bool createViewCam();              //创建相机
		static	bool switchViewCam();              //切换相机

		static  bool switchToTopView();            // 切换到顶视图
		static  bool switchToPerspectiveView();    // 切换到透视图

		static  bool switchToAxonoViewNorthWest(); //切换到西北轴测图
		static  bool switchToAxonoViewSouthWest(); //切换到西南轴测图
		static  bool switchToAxonoViewNorthEast(); //切换到东北轴测图
		static  bool switchToAxonoViewSouthEast(); //切换到东南轴测图

		static	bool positionViewCamToRenderer();  //切换至物体

		static	bool beginRecordVcr();             //开始记录Vcr漫游动画
		static  bool endRecordVcr();               //结束录制Vcr漫游动画

		static	bool runVcr();
		static	bool continueRunVcr();
		static	bool stopRunVcr();

		static  bool accelerateVcrSpeed();          //加快漫游动画播放速度
		static  bool decelerateVcrSpeed();          //减慢漫游动画播放速度

		static  bool setVcrCameraHeight();          //设置动画高度位移--SetTimer暂时未提取     

		static  bool onOrOffCollicition();          //开/关碰撞检测
		static  bool updateOnOrOffCollication();

		//以下两项已被替换，将被抛弃
		/*static	bool importVCRAnimation( const String& file_name);	
		static	bool exportVCRAnimation( const String& file_name);*/

		//带参的对外接口
		static  bool importVcrAni( const String& strFilePath );  
		static  bool exportVcrAni( const String& strFilePath );

		static  bool setCenterOfScreen( const uint& centerx , 
			const uint& centery );

		static  bool setAviRecordCnt(int cnt);

		static  bool setChannelNum(int par);

	private:
		static  bool importVcrBegin( const vgKernel::StringVector& strFilePaths );   
		static  bool importVcrAni( const vgKernel::StringVector& strFilePaths );
		static  bool importVcrEnd( const String& strFilePath );

	};

}//namespace vgGlobal

#endif//__VGGCAMUTILITY_H__