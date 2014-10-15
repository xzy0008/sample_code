
#include <vgStableHeaders.h>
#include <vgGlobal/vggVgcamUtility.h>

#include <vgGlobal/vggGlobalUtility.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkPluginManager.h>

#include <vgCam/vgcaCamManager.h>
#include <vgCam/vgcaCamFacade.h>
#include <vgKernel/vgkSelectManager.h>

#include <vgEntry/vgEntryFactory.h>
#include <vgUIController/vgUIController.h>

#include <vgAviExportDialog.h>
#include <vgExportBMPDialog.h>

#include <vgTerritory/vgtDefinition.h>

namespace vgGlobal{
	using namespace vgCam;

	//----------------------------------------------------------------
	CamUtility::CamUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	CamUtility::~CamUtility()
	{

	}

	//----------------------------------------------------------------
	bool CamUtility::importVcrFile()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("vcr");
		vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

		if ( strVec.empty() )
		{
			return false;
		}

		if ( !importVcrBegin( strVec ) )
		{
			return false;
		}
		if ( !importVcrAni( strVec ) )
		{
			return false;
		}

		importVcrEnd( strVec[0] );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::exportBmp()
	{
		BMPExportDialog bmpExpDialog;

		if ( bmpExpDialog.DoModal() != IDOK)
		{
			return false;
		}

		// 开始记录BMP图片
		vgCam::CamManager::getSingleton().setExpBmpParam( bmpExpDialog.m_bmpFilePath.GetString(), 
														  bmpExpDialog.m_bmpWidth, 
														  bmpExpDialog.m_bmpHeight );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::exportAvi()
	{
		AviExportDialog expDialog;

		if (expDialog.DoModal() != IDOK)
		{
			return false;
		}

		vgCam::CamManager::getSingleton().setExpAviParam( expDialog.getFilePath().GetString(), 
														  expDialog.getCameraName().GetString(), 
														  expDialog.getFrameHeight(), 
														  expDialog.getFrameWidth(), 
														  expDialog.getCompressId(), 
														  expDialog.getQuality() );

		

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::createViewCam()
	{
		vgCam::ViewCam* items =
			vgCam::CamManager::getSingleton().saveCurrentCameraView();


		if ( items == NULL )
		{
			return false;
		}

		HTREEITEM	hRootCamera = vgUI::UIController::getSingleton().getEntryRootItemByType(CAMERA_VIEW);
		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( items );
		vgUI::UIController::getSingleton().AddNode( hRootCamera,entry );

		vgKernel::RendererManager::getSingleton().addRenderer( items );

		if (hRootCamera != NULL)
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootCamera );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootCamera);
		}	

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::switchViewCam( )
	{
		vgKernel::Renderer* pRenderer = GlobalUtility::getSelectedRendererByType(
			vgCam::RENDERER_TYPE_VIEWCAMERA);

		if ( pRenderer!=NULL )
		{
			vgCam::ViewCam from;

			vgCam::ViewCam*	to = dynamic_cast<vgCam::ViewCam*>(pRenderer);

			from.cloneCurrentCameraView();
			to->setToUnvisible();

			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera(&from,to);

			return true;
		}
		else
		{
			return false;
		}

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::switchToTopView()
	{
		using namespace vgKernel;

		Vec3 pos;

		vgCam::ViewCam from;
		vgCam::ViewCam* pTopViewCam = vgCam::CamManager::getSingleton().getTopViewCam();

		assert( pTopViewCam != NULL );
		if ( pTopViewCam == NULL )
		{
			return false;
		}

#if 0
		Plugin* _terrainPlugin = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( _terrainPlugin == NULL )
		{
			String msg = "没有加载地形模块";
			SystemUtility::showModelDialog( msg );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, hasTerrainData, pfnHasData );
		if ( (*pfnHasData)() )
		{ 
			// 用地形包围盒数据来转换到顶视图
			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, getTerrainBoundCenter, pfnCenter );
			assert( pfnCenter != NULL );

			Vec2* center = (*pfnCenter)();
			pos.x = center->x;
			pos.z = center->y;

			// 此处删除的指针为getTerrainBoundCenter接口申请的内存
			delete center;
			center = NULL;

			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, 
				getMaxLengthFromTerrainBoundingBox, pfnMaxLength );
			assert( pfnMaxLength != NULL );

			float length = (*pfnMaxLength)();

			pos.y = length/4;
		}
		else
		{
			// 用模型包围盒数据来转换到顶视图
			RendererPackage* renderPackage = 
				RendererManager::getSingletonPtr()->getAllRendererPackage();
			
			RendererQueue renderQuene;

			RendererPackage::iterator ipac = renderPackage->begin();
			RendererPackage::iterator ipac_end = renderPackage->end();

			for ( ; ipac != ipac_end; ipac++ )
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end; iter++ )
				{
					renderQuene.push_back( *iter );
				}
			}

			SelectManager::getSingleton().mergeBox( renderQuene );
			renderQuene.clear();

			Box box = SelectManager::getSingleton().getSelectedBox();
			
			pos.x = box.getCenter().x;
			pos.z = box.getCenter().z;

			Vec3 size = box.getSize();

			pos.y = size.x > size.z ? ( size.x/2 ) : ( size.z/2);
		}

#else
		// 用模型包围盒数据来转换到顶视图
		RendererPackage* renderPackage = 
			RendererManager::getSingletonPtr()->getAllRendererPackage();

		RendererQueue renderQuene;

		RendererPackage::iterator ipac = renderPackage->begin();
		RendererPackage::iterator ipac_end = renderPackage->end();

		for ( ; ipac != ipac_end; ipac++ )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end; iter++ )
			{
				renderQuene.push_back( *iter );
			}
		}

		SelectManager::getSingleton().mergeBox( renderQuene );
		renderQuene.clear();

		Box box = SelectManager::getSingleton().getSelectedBox();

		pos.x = box.getCenter().x;
		pos.z = box.getCenter().z;

		Vec3 size = box.getSize();

		pos.y = size.x > size.z ? ( size.x/4 ) : ( size.z/4);

#endif
		pTopViewCam->setPosition( pos );

		from.cloneCurrentCameraView();
		pTopViewCam->setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from,pTopViewCam );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::switchToPerspectiveView()
	{
		using namespace vgKernel;

		Vec3 pos;
		float _camhead;
		float _campitch;

		vgCam::ViewCam from;
		vgCam::ViewCam* pPerspectViewCam = vgCam::CamManager::getSingleton().getPerspectViewCam();

		assert( pPerspectViewCam != NULL );
		if ( pPerspectViewCam == NULL )
		{
			return false;
		}

#if 0
		Plugin* _terrainPlugin = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( _terrainPlugin == NULL )
		{
			String msg = "没有加载地形模块";
			SystemUtility::showModelDialog( msg );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, hasTerrainData, pfnHasData );
		if ( (*pfnHasData)() )
		{ 
			// 用地形包围盒数据来转换到顶视图
			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, getTerrainBoundCenter, pfnCenter );
			assert( pfnCenter != NULL );

			Vec2* center = (*pfnCenter)();

			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, 
				getMaxLengthFromTerrainBoundingBox, pfnMaxLength );
			assert( pfnMaxLength != NULL );

			float length = (*pfnMaxLength)();

			//转到包围盒左下角
			pos.x = center->x - length/4;
			pos.z = center->y + length/4;
			pos.y = length/4;

			_camhead = -atan((pos.x-center->x)/(pos.z-center->y));
			_campitch = atan( pos.y/sqrtf( (pos.x-center->x)*(pos.x-center->x)+(pos.z-center->y)*(pos.z-center->y) ) );
			
			
			// 此处删除的指针为getTerrainBoundCenter接口申请的内存
			delete center;
			center = NULL;

		}
		else
		{
			// 用模型包围盒数据来转换到顶视图
			RendererPackage* renderPackage = 
				RendererManager::getSingletonPtr()->getAllRendererPackage();

			RendererQueue renderQuene;

			RendererPackage::iterator ipac = renderPackage->begin();
			RendererPackage::iterator ipac_end = renderPackage->end();

			for ( ; ipac != ipac_end; ipac++ )
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end; iter++ )
				{
					renderQuene.push_back( *iter );
				}
			}

			SelectManager::getSingleton().mergeBox( renderQuene );
			renderQuene.clear();

			Box box = SelectManager::getSingleton().getSelectedBox();

			Vec3 size = box.getSize();

			//转到包围盒左下角
			pos.x = box.getCenter().x - size.x/4;
			pos.z = box.getCenter().z + size.z/4;
			pos.y = size.x > size.z ? size.x/4 : size.z/4;

			_camhead = -atan((pos.x-box.getCenter().x)/(pos.z-box.getCenter().z));
			_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );
	
		}
#else
		// 用模型包围盒数据来转换到顶视图
		RendererPackage* renderPackage = 
			RendererManager::getSingletonPtr()->getAllRendererPackage();

		RendererQueue renderQuene;

		RendererPackage::iterator ipac = renderPackage->begin();
		RendererPackage::iterator ipac_end = renderPackage->end();

		for ( ; ipac != ipac_end; ipac++ )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end; iter++ )
			{
				renderQuene.push_back( *iter );
			}
		}

		SelectManager::getSingleton().mergeBox( renderQuene );
		renderQuene.clear();

		Box box = SelectManager::getSingleton().getSelectedBox();

		Vec3 size = box.getSize();

		//转到包围盒左下角
		pos.x = box.getCenter().x - size.x/4;
		pos.z = box.getCenter().z + size.z/4;
		pos.y = size.x > size.z ? size.x/5 : size.z/5;

		_camhead = -atan((pos.x-box.getCenter().x)/(pos.z-box.getCenter().z));
		_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

#endif
		pPerspectViewCam->setPosition( pos );
		pPerspectViewCam->setHeadingDegrees(_camhead*180.0f/PI);
		pPerspectViewCam->setPitchDegrees(_campitch*180.0f/PI);

		from.cloneCurrentCameraView();
		pPerspectViewCam->setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from,pPerspectViewCam );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::switchToAxonoViewNorthWest()
	{
		//提供两套方案供选择
#if 0
		using namespace vgKernel;

		Vec3 pos;
		vgCam::ViewCam from;
		vgCam::ViewCam to;

		from.cloneCurrentCameraView();
		pos = from.getPosition();
		pos.y = 20;

		to.setPosition(pos);
		to.setHeadingDegrees(-45.0f);
		to.setPitchDegrees(10.0f);
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;
#else

		using namespace vgKernel;

		Vec3 pos;
		float _campitch;

		vgCam::ViewCam from;
		vgCam::ViewCam to;

#if 0
		Plugin* _terrainPlugin = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( _terrainPlugin == NULL )
		{
			String msg = "没有加载地形模块";
			SystemUtility::showModelDialog( msg );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, hasTerrainData, pfnHasData );
		if ( (*pfnHasData)() )
		{ 
			// 用地形包围盒数据来转换到顶视图
			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, getTerrainBoundCenter, pfnCenter );
			assert( pfnCenter != NULL );

			Vec2* center = (*pfnCenter)();

			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, 
				getMaxLengthFromTerrainBoundingBox, pfnMaxLength );
			assert( pfnMaxLength != NULL );

			float length = (*pfnMaxLength)();

			//转到包围盒右下角
			pos.x = center->x + length/4;
			pos.z = center->y + length/4;
			pos.y = length/4;

			_campitch = atan( pos.y/sqrtf( (pos.x-center->x)*(pos.x-center->x)+(pos.z-center->y)*(pos.z-center->y) ) );

			// 此处删除的指针为getTerrainBoundCenter接口申请的内存
			delete center;
			center = NULL;

		}
		else
		{
			// 用模型包围盒数据来转换到顶视图
			RendererPackage* renderPackage = 
				RendererManager::getSingletonPtr()->getAllRendererPackage();

			RendererQueue renderQuene;

			RendererPackage::iterator ipac = renderPackage->begin();
			RendererPackage::iterator ipac_end = renderPackage->end();

			for ( ; ipac != ipac_end; ipac++ )
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end; iter++ )
				{
					renderQuene.push_back( *iter );
				}
			}

			SelectManager::getSingleton().mergeBox( renderQuene );
			renderQuene.clear();

			Box box = SelectManager::getSingleton().getSelectedBox();

			Vec3 size = box.getSize();

			//转到包围盒右下角
			pos.x = box.getCenter().x + size.x/4;
			pos.z = box.getCenter().z + size.z/4;
			pos.y = size.x > size.z ? size.x/4 : size.z/4;

			_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

		}
#else
		// 用模型包围盒数据来转换到顶视图
		RendererPackage* renderPackage = 
			RendererManager::getSingletonPtr()->getAllRendererPackage();

		RendererQueue renderQuene;

		RendererPackage::iterator ipac = renderPackage->begin();
		RendererPackage::iterator ipac_end = renderPackage->end();

		for ( ; ipac != ipac_end; ipac++ )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end; iter++ )
			{
				renderQuene.push_back( *iter );
			}
		}

		SelectManager::getSingleton().mergeBox( renderQuene );
		renderQuene.clear();

		Box box = SelectManager::getSingleton().getSelectedBox();

		Vec3 size = box.getSize();

		//转到包围盒右下角
		pos.x = box.getCenter().x + size.x/4;
		pos.z = box.getCenter().z + size.z/4;
		pos.y = size.x > size.z ? size.x/8 : size.z/8;

		_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

#endif
		to.setPosition( pos );
		to.setHeadingDegrees(-45.0f);
		to.setPitchDegrees(_campitch*180.0f/PI);

		from.cloneCurrentCameraView();
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;

#endif
	}

	//----------------------------------------------------------------
	bool CamUtility::switchToAxonoViewSouthWest()
	{
		//提供两套方案供选择
#if 0
		using namespace vgKernel;

		Vec3 pos;
		vgCam::ViewCam from;
		vgCam::ViewCam to;

		from.cloneCurrentCameraView();
		pos = from.getPosition();
		pos.y = 20;

		to.setPosition(pos);
		to.setHeadingDegrees(-135.0f);
		to.setPitchDegrees(10.0f);
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;

#else

		using namespace vgKernel;

		Vec3 pos;
		float _campitch;

		vgCam::ViewCam from;
		vgCam::ViewCam to;
#if 0

		Plugin* _terrainPlugin = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( _terrainPlugin == NULL )
		{
			String msg = "没有加载地形模块";
			SystemUtility::showModelDialog( msg );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, hasTerrainData, pfnHasData );
		if ( (*pfnHasData)() )
		{ 
			// 用地形包围盒数据来转换到顶视图
			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, getTerrainBoundCenter, pfnCenter );
			assert( pfnCenter != NULL );

			Vec2* center = (*pfnCenter)();

			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, 
				getMaxLengthFromTerrainBoundingBox, pfnMaxLength );
			assert( pfnMaxLength != NULL );

			float length = (*pfnMaxLength)();

			//转到包围盒右上角
			pos.x = center->x + length/4;
			pos.z = center->y - length/4;
			pos.y = length/4;

			_campitch = atan( pos.y/sqrtf( (pos.x-center->x)*(pos.x-center->x)+(pos.z-center->y)*(pos.z-center->y) ) );

			// 此处删除的指针为getTerrainBoundCenter接口申请的内存
			delete center;
			center = NULL;

		}
		else
		{
			// 用模型包围盒数据来转换到顶视图
			RendererPackage* renderPackage = 
				RendererManager::getSingletonPtr()->getAllRendererPackage();

			RendererQueue renderQuene;

			RendererPackage::iterator ipac = renderPackage->begin();
			RendererPackage::iterator ipac_end = renderPackage->end();

			for ( ; ipac != ipac_end; ipac++ )
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end; iter++ )
				{
					renderQuene.push_back( *iter );
				}
			}

			SelectManager::getSingleton().mergeBox( renderQuene );
			renderQuene.clear();

			Box box = SelectManager::getSingleton().getSelectedBox();

			Vec3 size = box.getSize();

			//转到包围盒右上角
			pos.x = box.getCenter().x + size.x/4;
			pos.z = box.getCenter().z - size.z/4;
			pos.y = size.x > size.z ? size.x/4 : size.z/4;

			_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

		}
#else
		// 用模型包围盒数据来转换到顶视图
		RendererPackage* renderPackage = 
			RendererManager::getSingletonPtr()->getAllRendererPackage();

		RendererQueue renderQuene;

		RendererPackage::iterator ipac = renderPackage->begin();
		RendererPackage::iterator ipac_end = renderPackage->end();

		for ( ; ipac != ipac_end; ipac++ )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end; iter++ )
			{
				renderQuene.push_back( *iter );
			}
		}

		SelectManager::getSingleton().mergeBox( renderQuene );
		renderQuene.clear();

		Box box = SelectManager::getSingleton().getSelectedBox();

		Vec3 size = box.getSize();

		//转到包围盒右上角
		pos.x = box.getCenter().x + size.x/4;
		pos.z = box.getCenter().z - size.z/4;
		pos.y = size.x > size.z ? size.x/8 : size.z/8;

		_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

#endif
		to.setPosition( pos );
		to.setHeadingDegrees(-135.0f);
		to.setPitchDegrees(_campitch*180.0f/PI);

		from.cloneCurrentCameraView();
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;

#endif

	}

	//----------------------------------------------------------------
	bool CamUtility::switchToAxonoViewNorthEast()
	{
		//提供两套方案供选择
#if 0
		using namespace vgKernel;

		Vec3 pos;
		vgCam::ViewCam from;
		vgCam::ViewCam to;

		from.cloneCurrentCameraView();
		pos = from.getPosition();
		pos.y = 20;

		to.setPosition(pos);
		to.setHeadingDegrees(45.0f);
		to.setPitchDegrees(10.0f);
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;
#else
		using namespace vgKernel;

		Vec3 pos;
		float _campitch;

		vgCam::ViewCam from;
		vgCam::ViewCam to;

#if 0
		Plugin* _terrainPlugin = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( _terrainPlugin == NULL )
		{
			String msg = "没有加载地形模块";
			SystemUtility::showModelDialog( msg );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, hasTerrainData, pfnHasData );
		if ( (*pfnHasData)() )
		{ 
			// 用地形包围盒数据来转换到顶视图
			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, getTerrainBoundCenter, pfnCenter );
			assert( pfnCenter != NULL );

			Vec2* center = (*pfnCenter)();

			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, 
				getMaxLengthFromTerrainBoundingBox, pfnMaxLength );
			assert( pfnMaxLength != NULL );

			float length = (*pfnMaxLength)();

			//转到包围盒左下角
			pos.x = center->x - length/4;
			pos.z = center->y + length/4;
			pos.y = length/4;

			_campitch = atan( pos.y/sqrtf( (pos.x-center->x)*(pos.x-center->x)+(pos.z-center->y)*(pos.z-center->y) ) );

			// 此处删除的指针为getTerrainBoundCenter接口申请的内存
			delete center;
			center = NULL;

		}
		else
		{
			// 用模型包围盒数据来转换到顶视图
			RendererPackage* renderPackage = 
				RendererManager::getSingletonPtr()->getAllRendererPackage();

			RendererQueue renderQuene;

			RendererPackage::iterator ipac = renderPackage->begin();
			RendererPackage::iterator ipac_end = renderPackage->end();

			for ( ; ipac != ipac_end; ipac++ )
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end; iter++ )
				{
					renderQuene.push_back( *iter );
				}
			}

			SelectManager::getSingleton().mergeBox( renderQuene );
			renderQuene.clear();

			Box box = SelectManager::getSingleton().getSelectedBox();

			Vec3 size = box.getSize();

			//转到包围盒左下角
			pos.x = box.getCenter().x - size.x/4;
			pos.z = box.getCenter().z + size.z/4;
			pos.y = size.x > size.z ? size.x/4 : size.z/4;

			_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

		}
#else
		// 用模型包围盒数据来转换到顶视图
		RendererPackage* renderPackage = 
			RendererManager::getSingletonPtr()->getAllRendererPackage();

		RendererQueue renderQuene;

		RendererPackage::iterator ipac = renderPackage->begin();
		RendererPackage::iterator ipac_end = renderPackage->end();

		for ( ; ipac != ipac_end; ipac++ )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end; iter++ )
			{
				renderQuene.push_back( *iter );
			}
		}

		SelectManager::getSingleton().mergeBox( renderQuene );
		renderQuene.clear();

		Box box = SelectManager::getSingleton().getSelectedBox();

		Vec3 size = box.getSize();

		//转到包围盒左下角
		pos.x = box.getCenter().x - size.x/4;
		pos.z = box.getCenter().z + size.z/4;
		pos.y = size.x > size.z ? size.x/8 : size.z/8;

		_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

#endif
		to.setPosition( pos );
		to.setHeadingDegrees(45.0f);
		to.setPitchDegrees(_campitch*180.0f/PI);

		from.cloneCurrentCameraView();
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;

#endif
	}

	//----------------------------------------------------------------
	bool CamUtility::switchToAxonoViewSouthEast()
	{
		//提供两套方案供选择
#if 0
		using namespace vgKernel;

		Vec3 pos;
		vgCam::ViewCam from;
		vgCam::ViewCam to;

		from.cloneCurrentCameraView();
		pos = from.getPosition();
		pos.y = 20;

		to.setPosition(pos);
		to.setHeadingDegrees(135.0f);
		to.setPitchDegrees(10.0f);
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;
#else
		using namespace vgKernel;

		Vec3 pos;
		float _campitch;

		vgCam::ViewCam from;
		vgCam::ViewCam to;

#if 0
		Plugin* _terrainPlugin = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( _terrainPlugin == NULL )
		{
			String msg = "没有加载地形模块";
			SystemUtility::showModelDialog( msg );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, hasTerrainData, pfnHasData );
		if ( (*pfnHasData)() )
		{ 
			// 用地形包围盒数据来转换到顶视图
			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, getTerrainBoundCenter, pfnCenter );
			assert( pfnCenter != NULL );

			Vec2* center = (*pfnCenter)();

			VGK_DLL_DECLARE_CLASSFUNC( _terrainPlugin, TerrainManager, 
				getMaxLengthFromTerrainBoundingBox, pfnMaxLength );
			assert( pfnMaxLength != NULL );

			float length = (*pfnMaxLength)();

			//转到包围盒左上角
			pos.x = center->x - length/4;
			pos.z = center->y - length/4;
			pos.y = length/4;

			_campitch = atan( pos.y/sqrtf( (pos.x-center->x)*(pos.x-center->x)+(pos.z-center->y)*(pos.z-center->y) ) );

			// 此处删除的指针为getTerrainBoundCenter接口申请的内存
			delete center;
			center = NULL;

		}
		else
		{
			// 用模型包围盒数据来转换到顶视图
			RendererPackage* renderPackage = 
				RendererManager::getSingletonPtr()->getAllRendererPackage();

			RendererQueue renderQuene;

			RendererPackage::iterator ipac = renderPackage->begin();
			RendererPackage::iterator ipac_end = renderPackage->end();

			for ( ; ipac != ipac_end; ipac++ )
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end; iter++ )
				{
					renderQuene.push_back( *iter );
				}
			}

			SelectManager::getSingleton().mergeBox( renderQuene );
			renderQuene.clear();

			Box box = SelectManager::getSingleton().getSelectedBox();

			Vec3 size = box.getSize();

			//转到包围盒左上角
			pos.x = box.getCenter().x - size.x/4;
			pos.z = box.getCenter().z - size.z/4;
			pos.y = size.x > size.z ? size.x/4 : size.z/4;

			_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

		}
#else
		// 用模型包围盒数据来转换到顶视图
		RendererPackage* renderPackage = 
			RendererManager::getSingletonPtr()->getAllRendererPackage();

		RendererQueue renderQuene;

		RendererPackage::iterator ipac = renderPackage->begin();
		RendererPackage::iterator ipac_end = renderPackage->end();

		for ( ; ipac != ipac_end; ipac++ )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end; iter++ )
			{
				renderQuene.push_back( *iter );
			}
		}

		SelectManager::getSingleton().mergeBox( renderQuene );
		renderQuene.clear();

		Box box = SelectManager::getSingleton().getSelectedBox();

		Vec3 size = box.getSize();

		//转到包围盒左上角
		pos.x = box.getCenter().x - size.x/4;
		pos.z = box.getCenter().z - size.z/4;
		pos.y = size.x > size.z ? size.x/8 : size.z/8;

		_campitch = atan( (pos.y-box.getCenter().y)/sqrtf( (pos.x-box.getCenter().x)*(pos.x-box.getCenter().x)+(pos.z-box.getCenter().z)*(pos.z-box.getCenter().z) ) );

#endif
		to.setPosition( pos );
		to.setHeadingDegrees(135.0f);
		to.setPitchDegrees(_campitch*180.0f/PI);

		from.cloneCurrentCameraView();
		to.setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera( &from, &to );

		return true;

#endif
	}

	//----------------------------------------------------------------
	bool CamUtility::positionViewCamToRenderer()
	{
		return vgCam::CamFacade::gotoSelectedObject();
	}

	//----------------------------------------------------------------
	bool CamUtility::beginRecordVcr( )
	{
		vgCam::CamManager::getSingleton().beginRecordingVcr();

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::endRecordVcr()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("vcr");
		String str = vgKernel::SystemUtility::getFileSaveByDialog(strExts);

		if ( str.empty() )
		{
			return false;
		}
		exportVcrAni( str );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::runVcr( )
	{
		vgKernel::Renderer* pRenderer = GlobalUtility::getSelectedRendererByType(
			vgCam::RENDERER_TYPE_CAMRECORD);

		if ( pRenderer!=NULL )
		{
			vgCam::CameraRecord*	pSubRenderer = dynamic_cast<vgCam::CameraRecord*>(pRenderer);
			vgCam::CamManager::getSingleton().setCurrentCameraRecord(pSubRenderer);
			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->startPlaying();	

			return true;
		}
		else
		{
			return false;
		}
	}
	
	//----------------------------------------------------------------
	bool CamUtility::continueRunVcr( )
	{
		vgCam::CamManager::getSingleton().continueRunVcr();

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::stopRunVcr( )
	{
		vgCam::CamManager::getSingleton().stopRunVcr();

		return true;
	}
	
	//----------------------------------------------------------------
	bool CamUtility::accelerateVcrSpeed()
	{
		string vcrname;

		vcrname = vgCam::CamManager::getSingleton().getCurrentCameraRecord()->getName();

		vgCam::CamFacade::accelerateVCR(vcrname);

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::decelerateVcrSpeed()
	{
		string vcrname;

		vcrname = vgCam::CamManager::getSingleton().getCurrentCameraRecord()->getName();

		vgCam::CamFacade::decelerateVCR(vcrname);

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::setVcrCameraHeight()
	{
		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::onOrOffCollicition()
	{
		vgCam::CamManager::getSingleton().setCollisionOnOff(
			! vgCam::CamManager::getSingleton().getCollisionOnOff() );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::updateOnOrOffCollication()
	{
		return vgCam::CamManager::getSingleton().getCollisionOnOff();
	}
#if 0
	//----------------------------------------------------------------
	bool CamUtility::importVCRAnimation( const String& file_name )
	{
		vgCam::CameraRecord* pNode = vgCam::CamManager::getSingleton().
			addCameraRecordFromFile(file_name);;

		if (pNode == NULL)
		{
			return false;
		}

		HTREEITEM	hRootAni = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_VCR);
		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pNode );
		vgUI::UIController::getSingleton().AddNode( hRootAni, entry );

		if (hRootAni != NULL)
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootAni );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootAni);
		}	

		return true;

	}

	
	//----------------------------------------------------------------
	bool CamUtility::exportVCRAnimation( const String& file_name )
	{
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->finishRecording();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->
			saveVCR( file_name );

		importVCRAnimation(file_name);

		return true;
	}
#endif	
	//----------------------------------------------------------------
	bool CamUtility::importVcrBegin( const vgKernel::StringVector& strFilePaths )
	{
		//------------------------------------------
		// 开始导入
		//------------------------------------------
		if( strFilePaths.empty() )
			return false;

		//确保多个文件的扩展名都是vcr
		String ext = "";
		for ( vgKernel::StringVector::const_iterator itr = strFilePaths.begin();
			  itr != strFilePaths.end(); ++itr )
		{
			ext = vgKernel::StringUtility::getFileExtension( *itr );
			if ( ext != "vcr" )
			{
				AfxMessageBox("文件类型不正确，请打开.vcr文件！");
				return false;
			}
		}

		std::ostringstream o;
		o	<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		o << "\t\t正在执行 导入" << ext << "操作:\n";
#else
		o << "\t\tImporting "<< ext << ":\n";
#endif
		o	<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( o.str() );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::importVcrAni( const vgKernel::StringVector& strFilePaths )
	{
		if ( strFilePaths.empty() )
		{
			return false;
		}

		for ( vgKernel::StringVector::const_iterator itr = strFilePaths.begin(); 
			  itr != strFilePaths.end(); ++itr )
		{
			vgCam::CameraRecord* pNode = vgCam::CamManager::getSingleton().
				addCameraRecordFromFile( *itr );
			if (pNode == NULL)
			{
				std::ostringstream oEnd;
				oEnd << "\t导入文件:"<< *itr << " 失败\n";
				VGK_SHOW( oEnd.str() );

				return false;
			}
			else
			{	
				std::ostringstream oEnd;
				oEnd << "\t成功导入文件:"<< *itr << " \n";
				VGK_SHOW( oEnd.str() );
			}

			HTREEITEM	hRootAni = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_VCR);
			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pNode );
			vgUI::UIController::getSingleton().AddNode( hRootAni, entry );

			if (hRootAni != NULL)
			{
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootAni );
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootAni);
			}
		}

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::importVcrAni( const String& strFilePath )
	{
		if ( strFilePath.empty() )
		{
			return false;
		}

		vgCam::CameraRecord* pNode = vgCam::CamManager::getSingleton().
			addCameraRecordFromFile( strFilePath );
		if (pNode == NULL)
		{
			/*std::ostringstream oEnd;
			oEnd << "\t导入文件:"<< strFilePath << " 失败\n";
			VGK_SHOW( oEnd.str() );*/

			return false;
		}
		/*else
		{	
			std::ostringstream oEnd;
			oEnd << "\t成功导入文件:"<< strFilePath << " \n";
			VGK_SHOW( oEnd.str() );
		}*/

		HTREEITEM	hRootAni = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_VCR);
		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pNode );
		vgUI::UIController::getSingleton().AddNode( hRootAni, entry );

		if (hRootAni != NULL)
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootAni );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootAni);
		}

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::importVcrEnd( const String& strFilePath )
	{
		// 重新构树
		vgKernel::RendererManager::getSingleton().invalidate();

		String ext = vgKernel::StringUtility::getFileExtension( strFilePath );
		std::ostringstream oEnd;
		oEnd<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		oEnd<< "\t\t完成执行 导入"<< ext << "操作!\n";
#else
		oEnd<< "\t\tImport "<< ext << " Completed!\n";
#endif
		oEnd<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( oEnd.str() );

		vgKernel::SystemUtility::setCurrentDirectory( strFilePath );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::exportVcrAni( const String& strFilePath )
	{
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->finishRecording();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->saveVCR( strFilePath );
		
		vgKernel::StringVector strVec;
		strVec.push_back( strFilePath );
		if ( !importVcrAni( strVec ) )
		{
			std::ostringstream oEnd;
			oEnd << "\t导出文件:"<< strFilePath << " 失败\n";
			VGK_SHOW( oEnd.str() );

			return false;
		}
		else
		{
			std::ostringstream oEnd;
			oEnd << "\t成功导出文件:"<< strFilePath << " \n";
			VGK_SHOW( oEnd.str() );
		}

		vgKernel::SystemUtility::setCurrentDirectory( strFilePath );

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::setCenterOfScreen( const uint& centerx , const uint& centery )
	{
		vgCam::CamManager::getSingleton().setCenterOfScreen(centerx, centery);

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::setAviRecordCnt( int cnt )
	{
		vgCam::CamManager::getSingleton().setAviRecordCnt(0);

		return true;
	}

	//----------------------------------------------------------------
	bool CamUtility::setChannelNum( int par )
	{
		vgCam::CamManager::getSingleton().setChannelNum(par);

		return true;
	}
}//namespace vgXXX