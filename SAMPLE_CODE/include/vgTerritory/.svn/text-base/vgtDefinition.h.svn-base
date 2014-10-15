


#ifndef __VGTDEFINITION_H__
#define __VGTDEFINITION_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkVec2.h>

#define VGT_DESC  "vgTerritoryDLL"

#ifdef VGT_DLL
#	ifdef VGT_NONCLIENT_BUILD_DLL
#		define  VGT_EXPORT __declspec( dllexport )
#	else
#		define  VGT_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGT_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGT_DLL_NAME VGT_DESC##"_Debug.dll"
#		define  VGT_LIB_NAME VGT_DESC##"_Debug.lib"
#	else
#		define  VGT_DLL_NAME VGT_DESC##"_Release.dll"
#		define  VGT_LIB_NAME VGT_DESC##"_Release.lib"
#	endif


namespace vgTerritory {
	struct StructVtrHeader;
}



#ifdef __cplusplus
extern "C" {
#endif



	typedef bool (*pfnTerrainManager_getElevationByPosition)( 
		const vgKernel::Vec3& pos , float& out_elevation , 
		const bool& use_accurate );

	extern VGT_EXPORT  bool TerrainManager_getElevationByPosition( 
		const vgKernel::Vec3& pos , float& out_elevation , 
		const bool& use_accurate );



	typedef bool (*pfnTerrainManager_saveData)( 
		 const String& absolute_path );

	extern VGT_EXPORT  bool TerrainManager_saveData( 
		const String& absolute_path );


	typedef bool (*pfnTerrainManager_hasTerrainData)();
	extern VGT_EXPORT  bool TerrainManager_hasTerrainData();

	typedef bool (*pfnTerrainManager_initAfterOpenGLSetup)();
	extern VGT_EXPORT  bool TerrainManager_initAfterOpenGLSetup();

	typedef bool (*pfnTerrainManager_uninitBeforeOpenGLDestroy)();
	extern VGT_EXPORT  bool TerrainManager_uninitBeforeOpenGLDestroy();

	typedef bool (*pfnTerrainManager_dropTerrianData)();
	extern VGT_EXPORT  bool TerrainManager_dropTerrianData();

	typedef void (*pfnTerrainManager_render)();
	extern VGT_EXPORT  void TerrainManager_render();

	typedef bool (*pfnTerrainManager_openVtrFile)(const String& abs_vtr_filename);
	extern VGT_EXPORT  bool TerrainManager_openVtrFile(const String& abs_vtr_filename);

	typedef void (*pfnTerrainManager_setRenderFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setRenderFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getRenderFlag)();
	extern VGT_EXPORT  bool TerrainManager_getRenderFlag();


	typedef void (*pfnTerrainManager_setCollisionDetectedFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCollisionDetectedFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getCollisionDetectedFlag)();
	extern VGT_EXPORT  bool TerrainManager_getCollisionDetectedFlag();


	typedef void (*pfnTerrainManager_setCutSurfaceAnalysisFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCutSurfaceAnalysisFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getCutSurfaceAnalysisFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getCutSurfaceAnalysisFlag() ;


	typedef void (*pfnTerrainManager_setCutSurfaceAnalysisFlag2)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCutSurfaceAnalysisFlag2(const bool& enable);

	typedef bool (*pfnTerrainManager_getCutSurfaceAnalysisFlag2)() ;
	extern VGT_EXPORT  bool TerrainManager_getCutSurfaceAnalysisFlag2() ;


	typedef void (*pfnTerrainManager_setCutSurfaceVisibilityFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCutSurfaceVisibilityFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getCutSurfaceVisibilityFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getCutSurfaceVisibilityFlag() ;

	typedef void (*pfnTerrainManager_setCutSurfaceVisibilityFlag2)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCutSurfaceVisibilityFlag2(const bool& enable);

	typedef bool (*pfnTerrainManager_getCutSurfaceVisibilityFlag2)() ;
	extern VGT_EXPORT  bool TerrainManager_getCutSurfaceVisibilityFlag2() ;

	typedef void (*pfnTerrainManager_setCutSurfaceLevellingFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCutSurfaceLevellingFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getCutSurfaceLevellingFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getCutSurfaceLevellingFlag() ;


	typedef void (*pfnTerrainManager_setCutAreaFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setCutAreaFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getCutAreaFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getCutAreaFlag() ;


	typedef void (*pfnTerrainManager_setBlendFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setBlendFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getBlendFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getBlendFlag() ;

	typedef float* (*pfnTerrainManager_getUserClipPlaneParam)();
	extern VGT_EXPORT  float* TerrainManager_getUserClipPlaneParam();

	typedef bool (*pfnTerrainManager_saveSelectVtrAndVgi)( const String& folderpath );
	extern VGT_EXPORT bool TerrainManager_saveSelectVtrAndVgi( const String& folderpath );

	typedef void (*pfnTerrainManager_setSaveMode)( bool bMode );
	extern VGT_EXPORT void TerrainManager_setSaveMode( bool bMode );

	typedef vgKernel::Vec2* (*pfnTerrainManager_getTerrainBoundCenter)();
	extern VGT_EXPORT vgKernel::Vec2* TerrainManager_getTerrainBoundCenter();

	typedef float (*pfnTerrainManager_getMaxLengthFromTerrainBoundingBox)();
	extern VGT_EXPORT float TerrainManager_getMaxLengthFromTerrainBoundingBox();

	typedef bool (*pfnTerrainManager_hasCutArea)();
	extern VGT_EXPORT bool TerrainManager_hasCutArea();


	//typedef void (*pfnTerrainManager_readProject)();
	//extern VGT_EXPORT  void TerrainManager_readProject();

	//typedef void (*pfnTerrainManager_saveProject)();
	//extern VGT_EXPORT  void TerrainManager_saveProject();


	typedef  vgKernel::Vec3* (*pfngetTerrainCoord)();
	extern VGT_EXPORT   vgKernel::Vec3* getTerrainCoord();



	typedef  vgTerritory::StructVtrHeader* (*pfngetMainFileHandleVtrHeader)();
	extern VGT_EXPORT   vgTerritory::StructVtrHeader* getMainFileHandleVtrHeader();


	typedef  vgTerritory::StructVtrHeader* (*pfngetMainFileHandleVtrHeader)();
	extern VGT_EXPORT   vgTerritory::StructVtrHeader* getMainFileHandleVtrHeader();



	typedef  void (*pfnrestoreInEditMode)();
	extern VGT_EXPORT  void restoreInEditMode();

	typedef  void (*pfnsaveInEditMode)();
	extern VGT_EXPORT  void saveInEditMode();


	typedef void* ElevationItemH;


	typedef ElevationItemH (*pfnElevationManager_getElevationItem)( const String& itemname ,
		const bool& return_empty_item );
	extern VGT_EXPORT  ElevationItemH ElevationManager_getElevationItem( const String& itemname ,
		const bool& return_empty_item );


	typedef void (*pfnElevationItem_getDisplaceParams)( ElevationItemH itm,
		float* param );
	extern VGT_EXPORT  void ElevationItem_getDisplaceParams(  ElevationItemH itm,
		float* param );

	typedef long (*pfngetCurrentHeightLayerNumber)();
	extern VGT_EXPORT long getCurrentHeightLayerNumber();

	typedef void (*pfnTerrainManager_setVerSectionAnaFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setVerSectionAnaFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getVerSectionAnaFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getVerSectionAnaFlag() ;

	typedef void (*pfnTerrainManager_setHorSectionAnaFlag)(const bool& enable);
	extern VGT_EXPORT  void TerrainManager_setHorSectionAnaFlag(const bool& enable);

	typedef bool (*pfnTerrainManager_getHorSectionAnaFlag)() ;
	extern VGT_EXPORT  bool TerrainManager_getHorSectionAnaFlag() ;

#ifdef __cplusplus
}
#endif


#define VTR_NAME_LENGTH 64


#define VGT_MAX(a,b)		(((a) > (b)) ? (a) : (b))
#define VGT_MIN(a,b)		(((a) < (b)) ? (a) : (b))

#define  VGT_OVERVIEW_DIVIDE		8

#define  VGT_ORIGIN_IMG_SIZE	2048	


#define VGT_VTR_MAX_FILENUM   2048

#define VGT_USE_MULTITHREAD	1

#define VGT_THREAD_NUM		4

#define VGT_MULTITHREAD_UI_REFRESH_WAIT	50

#define VGT_LEFT_UP		0
#define VGT_RIGHT_UP	1
#define VGT_LEFT_DOWN		2
#define VGT_RIGHT_DOWN		3


#define VGT_GEOMGR_TEMP_EXT		"png"




namespace vgTerritory {

	struct StructVtrHeader
	{
	public:

		char	_fourCC[4];
		int		_version;
		long	_sizeOfHeader;
		long	_sizeOfWholeFile;
		long	_numberOfBriefs;
		long	_lengthOfOneBrief;
		long	_positionOfBriefs;

		/**
			本地形文件名,最大为64长度的名称
		*/
		char name[ VTR_NAME_LENGTH ];


		/**
			本地形纹理文件名,最大为64长度的名称
			注意,这里要以vgi结尾.
			还要注意,默认的是name和imageFilename一一对应.
			在vgtFileWriterVgtrToVtr.h中还未留出写其他文件名的接口
		*/
		char imageFilename[ VTR_NAME_LENGTH ];

		/**
			N值,默认为8,即每层256个网格数
		*/
		long N;	

		/**
			每个cell对应的texture大小,注意是最精细层的.	
		*/
		long cellTexSize;

		/**
			一个可创建的center layer的个数
			因为要满足4个区块.所以公式如下:
			log( xTotalNum / pow(2, N) ) / log(2.0f) - 1; 
		*/
		long numOfCenterLayers;

		/**
			x和z方向数量
			注意!这里必须一样才行!
		*/
		uint xTotalNum;			
		uint zTotalNum;

		/**
			逻辑原点
		*/
		double originX;		
		double originY;
		double originZ;

		float cellsize;	// 间距

		// 使用_reserved1用来指代下一个链接的vtr文件
		// 例如, terrianname = "test" , 如果为0, 表示没有下一个链接文件.
		// 如果为1,表示下一个文件为test.part1.vtr
		long _nextVtrFileID;

		// 使用_reserved2用来代表填充颜色
		//long	_reserved2;
		uchar _filledColor[4];


		long	_reserved3;
		long	_reserved4;
	};
	
	typedef std::vector< vgKernel::Vec3 > Vec3Vector;
}



#endif // end of __VGTDEFINITION_H__