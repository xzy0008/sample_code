


#ifndef __VGGMODUTILITY_H__
#define __VGGMODUTILITY_H__


#include <vgGlobal/vgglDefinition.h>
#include <vgMod/vgNodeManager.h>

#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkAbstractEntry.h>


namespace  vgGlobal{

	using namespace vgMod;
	
	/**
		@date     2009/10/21  21:11
		@author   ZhouZY

		@brief    整理了与Mod相关操作的中间层
				  原vgMod::ModUtility中还保留一些接口暂时无法
				  移植过来，以避免底层DLL调用上层DLL

		@see
	*/


	class	VGGL_EXPORT ModUtility
	{
	public:
		ModUtility();
		~ModUtility();

		//对外公共接口
	public:
		static bool importModFile(const String& strFilePath ); 
		
		static bool importVgFile(const String& strFilePath );
		static bool importVgFileDirectly(const String& strFilePath );

		static bool exportVgFile(const String& strFilePath );
		static bool exportVgFileDirectly(const String& strFilePath );

		static bool exportVgImgFile(const String& strFilePath );

		static bool responseLButtonDown(UINT nFlags, CPoint point);
		static bool responseLButtonDblClk(UINT nFlags, CPoint point, CWnd* pwnd );
		static bool responseLButtonUp(UINT nFlags, CPoint point);

		static bool convertSelectedObjectToEffectNode(int nEffectType);
		
		//无参接口用于View类消息响应函数
		static bool importModFile();        //关键帧动画--现为Mod数据

		static bool addModFileToScene(String newModFile, String vgFilePath);	// 增加Mod文件至场景

		static bool convertToWater();        //转换为水面
		static bool convertToGlass();        //转换为玻璃
		static bool convertToMirror();       //转换成镜面
		static bool convertToMetal();        //转换成金属
		static bool convertToBrightFloor();  //转换为光亮物体
		static bool convertToSkybox();       //转换为天空球
		static bool convertToAviTex();       //转换成AVI纹理
		static bool convertToDynTex();       //转换成序列帧纹理
		static bool convertToAutoBuild();    //转换为自动建模
		static bool cloneAutoBuildObj();     //克隆自动建模物体
		static void generateSolidBuild();	 //创建自定义体块
		static bool getGenerateBuildFlag();  //更新标记
		static void generateMarkBuild();     //创建信息标注物体
		static bool getAllLandMarkFlag();       //更新信息标记标志
		static void enableAllLandMark(bool enable);        //开启信息标注显示

		static bool addNodeToUI( CategoryType catType, NodePtrVec* pNodeList, const string& strFilePath );

		static bool getSaveMode();
		static void setSaveMode( bool bMode );

		static bool changeWaterDirection();	 //改变水流方向 Added By FengYK @2010-03-23 14:57

		static bool importModData( const vgKernel::StringVector& strFilePaths );
	private:
		
		static bool importModBegin( const vgKernel::StringVector& strFilePaths );   
		static bool importModEnd( const String& strFilePath );


		static bool addNodeToUI( const string& strFilePath );
		static bool addModNodeToUI( ModItemPtrVec* pNodeList , const string& strFilePath);
		static vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

	};
}//namespace vgGlobal

#endif//__VGGMODUTILITY_H__