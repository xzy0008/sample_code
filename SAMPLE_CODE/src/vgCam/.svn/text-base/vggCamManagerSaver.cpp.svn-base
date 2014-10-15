


#include <vgStableHeaders.h>
#include <vgCam/vgcaCamManager.h>
#include <vgCam/vggCamManagerSaver.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>

#include <vgUIController/vgUIController.h>
#include <vgUIController/vgWorkSpaceBar.h>
#include <vgEntry/vgEntryFactory.h>


#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_PATH_CAMERA		"CameraPath"

namespace vgMod {
	
	
	
	//----------------------------------------------------------------
	bool CamManagerSaver::writeCamMgrToFile( 
		vgKernel::StreamWriterPtr pwriter , const String& attachDataPath,
		bool bReadDerectly )
	{
		using namespace vgCam;

		String abs_path = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(attachDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_CAMERA);

		abs_path += g_DataPath;

		CamManager* mgr = 
			CamManager::getSingletonPtr();

		// Part 1: 拷贝漫游动画文件
		if ( !bReadDerectly )
		{
			mgr->copyRecordfile(abs_path);
		}


		CameraRecordPtrVector& _VCRvector = 
			*mgr->getCameraRecords();

		// Part 2: 写入漫游动画名字队列
		int kk = _VCRvector.size();
		pwriter->write( &kk, sizeof(int) );
		vector<CameraRecordPtr>::iterator vcrItr = _VCRvector.begin();
		vector<CameraRecordPtr>::iterator vcrItrEnd = _VCRvector.end();
		for( ; vcrItr != vcrItrEnd; ++vcrItr )
		{
			(*vcrItr)->writeToStream( pwriter , 0 ,"" );
		}

		// Part 3: 写入视点队列
		ViewCamPtrVector& _viewCams = *mgr->getViewCams();

		kk = _viewCams.size();
		pwriter->write( &kk, sizeof(int) );
		vector<ViewCamPtr>::iterator viewItr = _viewCams.begin();
		vector<ViewCamPtr>::iterator viewItrEnd = _viewCams.end();
		for( ; viewItr != viewItrEnd; ++viewItr )
		{
			(*viewItr)->writeToStream( pwriter, 0 , "" );
		}

		// Part 4: 写入当前相机
		mgr->dumpInfoToStream( pwriter );

		//------------------------------------------
		// 最后写viewfrustum
		//------------------------------------------
		float fov = mgr->getFov();
		float fnear = mgr->getNear();
		float ffar = mgr->getFar();
		pwriter->write( &fov , sizeof(float) );
		pwriter->write( &fnear , sizeof(float) );
		pwriter->write( &ffar , sizeof(float) );


		bool m_enableCollisionDetection = 
			mgr->getCollisionOnOff();
		pwriter->write( &m_enableCollisionDetection , sizeof( bool ) );

		return true;
	}

	
	//----------------------------------------------------------------
	bool CamManagerSaver::writeCamMgrToFile(
		const String& save_absolute_path, const String& attachDataPath,
		bool bReadDerectly
		)
	{
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(save_absolute_path);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(save_absolute_path);
		fileName += ".cam";

		filePath += fileName;

		vgKernel::StreamWriterPtr m_pfile = 
			vgKernel::StreamWriterFactory::createFromFile( filePath );

		return writeCamMgrToFile( m_pfile, attachDataPath, bReadDerectly);

	}
	
	//----------------------------------------------------------------
	bool CamManagerSaver::readCamMgrFromFile( 
		vgKernel::StreamReaderPtr preader , const String& attachDataPath ,
		bool bReadDirectly /*= false*/ )
	{

		using namespace vgCam;


		String abs_path = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(attachDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_CAMERA);

		abs_path += g_DataPath;

		CamManager* mgr = 
			CamManager::getSingletonPtr();

		int k;
		String	recordFullName;
		String	errorFiles;

		// 漫游动画
		preader->read( &k, sizeof(int) );
		for (int i =0; i < k; i++)
		{
			CameraRecordPtr newone( new CameraRecord() );

			newone->readFromStream( preader , 0 , "" );
			
			recordFullName = abs_path + newone->getVcrFileName();

			if ( !vgKernel::SystemUtility::checkFileExist( recordFullName) )
			{
				errorFiles += recordFullName;
				errorFiles += '\n';
				continue;
			}
			
			newone->loadVCR(recordFullName);


			mgr->addCameraRecord(newone);

			// UI
			if( !bReadDirectly )
			{
				HTREEITEM	hRootAni = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_VCR);
				vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( newone.getPointer() );

				assert( entry != NULL );

				if ( entry != NULL )
				{
					vgUI::UIController::getSingleton().AddNode( hRootAni, entry );

					if (hRootAni != NULL)
					{
						vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootAni );
						vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootAni);
					}	
				}


			}

		}

		if ( !errorFiles.empty())
		{
			errorFiles += "缺失！";
			AfxMessageBox( errorFiles.c_str() );
		}

		// 视点队列
		preader->read( &k, sizeof(int) );
		for (int i =0; i < k; i++)
		{
			ViewCamPtr	newone( new ViewCam() );
			
			newone->readFromStream( preader, 0 , "" );
			
			mgr->addViewCamPtr(newone);

			// UI
			if( !bReadDirectly )
			{
				HTREEITEM	hRootCamera = vgUI::UIController::getSingleton().getEntryRootItemByType(CAMERA_VIEW);
				vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( newone.getPointer() );
				vgUI::UIController::getSingleton().AddNode( hRootCamera,entry );

				vgKernel::RendererManager::getSingleton().addRenderer( newone.getPointer() );

				if (hRootCamera != NULL)
				{
					vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootCamera );
					vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootCamera);
				}	

			}
		}

		// 当前相机
		mgr->readInfoFromStream(  preader );


		//------------------------------------------
		// 最后读viewfrustum
		//------------------------------------------
		float fov;
		float fnear;
		float ffar;
		bool m_enableCollisionDetection;
		preader->read( &fov , sizeof(float) );
		preader->read( &fnear , sizeof(float) );
		preader->read( &ffar , sizeof(float) );

		preader->read( &m_enableCollisionDetection , sizeof( bool ) );

		mgr->setCollisionOnOff( m_enableCollisionDetection );
		mgr->setFov( fov );
		mgr->setNear( fnear );
		mgr->setFar( ffar );

		return true;
	}

	
	//----------------------------------------------------------------
	bool CamManagerSaver::readCamMgrFromFile(
		const String& save_absolute_path, const String& attachDataPath ,
		bool bReadDirectly /*= false*/)
	{
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(save_absolute_path);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(save_absolute_path);
		fileName += ".cam";

		filePath += fileName;

		bool isFileExist = vgKernel::SystemUtility::checkFileExist(filePath);

		if (!isFileExist)
		{
			std::ostringstream oStr;
#if VGK_LANG_CHS
			oStr << "\n\t相机模块文件:"<< filePath << "不存在！\n";
#else
			oStr << "\n\tFile: "<< filePath << "Does Not Exist! \n";
#endif
			VGK_SHOW( oStr.str() );
			return false;
		}

		vgKernel::StreamReaderPtr m_pfile = 
			vgKernel::StreamReaderFactory::createFromFile( filePath );

		return readCamMgrFromFile( m_pfile, attachDataPath, bReadDirectly);

	}

}// end of namespace vgGlobal
