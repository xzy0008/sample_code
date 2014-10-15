

#ifndef __VGGGISUTILITY_H__
#define __VGGGISUTILITY_H__
#include <vgGlobal/vgglDefinition.h>

#include <vgGis/vgGisManager.h>
#include <vgGIS3D/vggiDataSource.h>

namespace vgGlobal{

	
	class	VGGL_EXPORT GisUtility
	{
	public:
		GisUtility();
		~GisUtility();

	public:
		static bool renderGisElements();

		/**
			zzy 
			2009/10/21   17:02
			view响应菜单消息调用以下八个接口，不再使用vgGlobal::SystemFacade提供的接口
		*/
		static bool	measureGisPoint();    //查询坐标
		static bool	measureGisLength();   //测量距离
		static bool	measureGisArea();     //测量面积
		static bool	measureGisVolume();   //测量体积
		static bool matchRoad();          //道路匹配--VGMSGBOX2暂时未提取出来 

		static bool measureGisVer_Hor_Slope();//垂直距离测量、水平距离测量、坡度测量

		static bool FaecherAnalysis();//扇面分析

		static bool	updateStateGisPoint();
		static bool	updateStateGisLength();
		static bool	updateStateGisArea();
		static bool updateGisVer_Hor_Slope();

		static bool updateStateGisFaecher();

		static void	reset();
		static void	uninitBeforeOpenGLDestroy();

	public:
		static	bool importShpFile(const string& strFilePath, bool bSpecial = false );

		static	bool readProject( const string& strFilePath );

		static	bool convertShpToEditState();

		//static  bool convertShpToEditState();
		static	bool getSelectFlag();

	private:
		static	bool addShpToUI(vgGIS3D::DataSource* psource);
	private:
		static bool setGisAnalysis(vgGIS3D::EGisState eType);
		static bool	updateGisState(vgGIS3D::EGisState eType);

	};
}//namespace vgGlobal

#endif//__VGGGISUTILITY_H__
