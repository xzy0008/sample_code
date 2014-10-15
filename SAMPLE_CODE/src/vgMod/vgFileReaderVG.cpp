
#include <vgStableHeaders.h>

#include <vgMod/vgFileReaderVG.h>
#include <vgMod/vgFileDefinitionVG.h>

#include <vgKernel/vgkStreamReader.h>

#include <vgSound/vgSoundManager.h>
#include <vgCam/vgcaCamManager.h>
#include <vgCoordinate.h>
#include <vgMovingManager.h>

#include <vgEffect/vgWaterNode.h>
#include <vgEffect/vgGlassNode.h>
#include <vgEffect/vgMirrorNode.h>
#include <vgEffect/vgMetalNode.h>
#include <vgEffect/vgBrightfloorNode.h>
#include <vgEffect/vgAviNode.h>
#include <vgEffect/vgSkyboxNode.h>
#include <vgEffect/vgDynamicTexNode.h>
#include <vgEffect/vgFire.h>
#include <vgEffect/vgFlag.h>
#include <vgEffect/vgFountain.h>
#include <vgEffect/vgSmoke.h>
#include <vgEffect/vgDynamicBillboardNode.h>
//#include <vgEntryFactory.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>

#include <vgMod/vgTriggerManager.h>
#include <vgMod/vgFileReaderMOD.h>
#include <vgMod/vgNode.h>
#include <vgMod/vgModEffectConvertor.h>
#include <vgMod/vgVersionControl.h>
#include <vgMod/vgModUtility.h>

#include <vgCam/vggCamManagerSaver.h>
//#include <vgMod/vggCamManagerSaver.h>
#include <vgSound/vggSoundManagerSaver.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgSound/vgSoundDefinition.h>
#include <vgDatabase/vgdProfileManager.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>
#include <vgAutoBuild/vgAutoBuildSaver.h>

namespace vgMod{

	
	//----------------------------------------------------------------
	FileReaderVG::FileReaderVG()
	{
		//m_pTempNodeIndexList = new NodeAbsPtrVec;
		//m_pTempNodeList = new NodePtrVec;
	}
	
	//----------------------------------------------------------------
	FileReaderVG::~FileReaderVG()
	{
		/*if (m_pTempNodeIndexList)
		{
		delete m_pTempNodeIndexList;
		}
		if (m_pTempNodeList)
		{
		delete m_pTempNodeList;
		}*/

	}

	
	//----------------------------------------------------------------
	bool	FileReaderVG::read( const String& open_absolute_path, 
		NodeAbsPtrVec*	pNodeIndexList ,
		NodePtrPackage* pNodePackage,
		bool bDirectly/* = false*/)
	{
		m_strFilePath	= open_absolute_path;
		m_pNodeIndexList	= pNodeIndexList;

		m_pNodePackage = pNodePackage;

		// case 1:	MFC_CFile*
#if 1
		CFile* pfile = new CFile;

		if (!pfile->Open(m_strFilePath.c_str(),CFile::modeRead )) 
		{
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "Read File Failed" ,
				"error", MB_OK);
			delete pfile;
			return	false;
		}

		m_pfile = vgKernel::StreamReaderFactory::createFromCFile( pfile,false);

#else
		// case 2:	C_FILE*
		m_pfile = vgKernel::StreamReaderFactory::createFromFile( save_absolute_path );
#endif

		if ( m_pfile.isNull() == true )
		{
			return false;
		}

		long filebeg = m_pfile->tell();


		//	Part 1：文件头，包括文件版本、四叉树存储位置（待计算）、节点总数目等3项
		if ( !m_fileHeader.read(m_pfile) )
		{
			return false;
		}

		//	Part 2:	其他模块的数据
		if (bDirectly)
		{
			vgMod::ModUtility::setFlagReadDirectly( true );

			readOherModulesDirectly();
		} 
		else
		{
			vgMod::ModUtility::setFlagReadDirectly( false );

			readOherModulesFromVg();
		}

		//  Part 3: Node模块
		readNodeModuleFromVg();

		// 写文件结束!
		m_pfile->close();

		return true;

	}

	
	//----------------------------------------------------------------
	bool	FileReaderVG::readOherModulesFromVg()
	{
		vgKernel::StreamReader*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamReader*)pcfile)->getCFilePointer();
#if 0
		String	otherModulesSubDir = "ProAttachdata";
		
		String	attachDataPath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(m_strFilePath);
		
		attachDataPath += otherModulesSubDir ;
		attachDataPath += "\\";
#endif

		String	attachDataPath = m_strFilePath;

		vgMod::ModEffectConvertor::setProDataPath(attachDataPath);

		vgKernel::StreamReaderPtr preader =
			vgKernel::StreamReaderFactory::createFromCFile( pfile , false );
		assert( preader.isNull() == false );

		// Part 1: 音效
		vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		if (plugin != NULL)
		{

			VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManagerSaver, readSoundMgrFromFile2, pfn1 );

			assert( pfn1 != NULL );

			(*pfn1)( preader, attachDataPath  , false);

		}

		// Part 2: 相机(视点和漫游动画)
		CamManagerSaver::readCamMgrFromFile( preader , attachDataPath );



		// Part 3: 全局中心坐标
		//vgCore::vgCoordinate::getSingleton().readFromFile(pfile );
		vgKernel::Vec3 vec;
		pfile->Read( &vec, sizeof(vgKernel::Vec3));


	
		// Part 4: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))
		vgCore::MovingManager::getSingleton().readFromFile(pfile, attachDataPath);


		String	vgVersion  = VersionControl::getVgVersionRead();
		if( vgVersion >= String("VRGIS.VERSION 2.17") )
		{
			vgAutoBuild::AutoBuildSaver::readAutoBuildFromFile(m_strFilePath, attachDataPath);
		}


		return true;
	}


	
	//----------------------------------------------------------------
	bool	FileReaderVG::readNodeModuleFromVg()
	{
		//	Part 1：抽象节点索引队列
		readAbstractNodesFromVG();

		//	Part 2：Node数据节点队列，由抽象节点索引队列遍历
		readDataNodesByAbstractNodeFromVG();

		
		//	Part 3：加入管理器
		addVgNodeToManager();


		//	Part 4：加入界面
		//addVgNodeToUI() ;

		return	true;
	}

	
	//----------------------------------------------------------------
	bool	FileReaderVG::readAbstractNodesFromVG( )
	{
		// 定位文件指针至索引数据块的位置
		m_pfile->seek(m_fileHeader.abstractNodePos);

		NodeAbstract * pNodeAbs = NULL;
		for (int i = 0; i < m_fileHeader.m_nodenum; i++)
		{
			pNodeAbs =  new NodeAbstract();

			// 读入一个节点对象的索引
			pNodeAbs->ReadFromFile( m_pfile);

			m_pNodeIndexList->push_back(pNodeAbs);

		}

		//m_pNodeIndexList->insert(m_pNodeIndexList->begin(),
		//	m_pTempNodeIndexList->begin(), m_pTempNodeIndexList->end());

		return true;
	}


	
	//----------------------------------------------------------------
	bool	FileReaderVG::readDataNodesByAbstractNodeFromVG( )
	{
		char	*strTempData= NULL;
		Node	*pNodeData	= NULL;
		
		//----------progress position------------------//
		long nodeNum = m_pNodeIndexList->size();
		long nCurPos = 0;
		float nStep = 0;
		//---------------------------------------------//

		for (NodeAbsPtrVec::iterator itr = m_pNodeIndexList->begin();
			itr != m_pNodeIndexList->end(); itr ++ )
		{
			strTempData		= new char[(*itr)->m_size];
			m_pfile->seek((*itr)->m_offset);
			m_pfile->read(strTempData , (*itr)->m_size);

			// 从内存构造一个节点对象，并附加到管理器和界面
			generateVgNodeFromBuffer( strTempData, &pNodeData);

			(*m_pNodePackage)[pNodeData->getCategory()].push_back(pNodeData);


			(*itr)->m_pNodeData	= pNodeData ;

			delete[] strTempData;
			strTempData = NULL;

			bool bReadDerectly = vgMod::ModUtility::getFlagReadDirectly( );
			if( !bReadDerectly )
			{
				//----------progress position------------------//
				nStep = (float)nCurPos/(float)nodeNum;
				nCurPos++;			 
				CAutoLoadDialog::SetPosWithRange(20, 70, nStep);
				//---------------------------------------------//
			}
			

		}//for


		return	true;
	}


	
	//----------------------------------------------------------------
	bool	FileReaderVG::generateVgNodeFromBuffer(char *pBuffer , Node** pNodeData)
	{
	
		// Stepl：读入节点长度和节点类型，根据类型生成不同对象
		unsigned long pos = 0;

		long nodelength = *(long *)(pBuffer + pos);	// 节点长度
		pos += sizeof(long);


		int nType;
		nType = *(int *)(pBuffer + pos);		//	节点类型
		pos += sizeof(int);

		Node*		pNewNode	= NULL;

		switch (nType)
		{

			// Object模型
		case	VG_OBJECT:
		case	VG_OBJECT_KEYFRAME:
			pNewNode	= new ObjFrameNode(VERSION_LATEST);
			break;

		case	VG_OBJECT_BAKED:
		case	VG_OBJECT_BAKED_KEY:		
			pNewNode	= new ObjectNodeBaked(VERSION_LATEST);
			break;

		case	VG_WATER:
			pNewNode	= new WaterNode(VERSION_LATEST);
			break;

		case	VG_GLASS:
			pNewNode	= new GlassNode(VERSION_LATEST);
			break;

		case	VG_METAL:
			pNewNode	= new MetalNode(VERSION_LATEST);
			break;

		case	VG_MIRROR:
			pNewNode	= new MirrorNode(VERSION_LATEST);
			break;

		case	VG_BRIGHTFLOOR:
			pNewNode	= new BrightfloorNode(VERSION_LATEST);
			break;

		case	VG_AVINODE:
			pNewNode	= new AviNode(VERSION_LATEST);
			break;

		case	VG_DYNAMICTEXNODE:
			pNewNode    = new DynamicTexNode(VERSION_LATEST);
			break;

		case	VG_SKYBOX:
			pNewNode	= new SkyboxNode(VERSION_LATEST);
			break;
		

			// Billboard
		case	VG_BILLBOARD:
			pNewNode	= new BillboardNode();
			break;


			//DynamicBillboard
		case VG_DYNAMICBILLBOARDNODE:
			pNewNode	= new DynamicBillboardNode();
			break;


			// Particle
		case VG_PARTICLE:
			{
				E_PARTICLE_TYPE subtype = *(E_PARTICLE_TYPE *)(pBuffer + pos);
				pos+=sizeof(E_PARTICLE_TYPE);

				switch(subtype)
				{
				case PARTICLE_FOUNTAIN://喷泉
					pNewNode = new vgFountain();
					break;

				case PARTICLE_FIRE://火
					pNewNode = new vgFire();
					break;

				case PARTICLE_SMOKE://烟
					pNewNode = new vgSmoke();
					break;

				case PARTICLE_FLAG://旗帜
					pNewNode = new vgFlag();
					break;

				default:
					return	false;	
					break;
				}// switch(subtype)
				
				pNewNode->setCategory( CategoryType(subtype) );

				vgParticle * pParticle = dynamic_cast<vgParticle *>(pNewNode);
				if ( NULL != pParticle )
				{
					pParticle->setSubType( subtype );
				}

			}//case VG_PARTICLE
			break;

		default:
			return	false;	
			break;
		}//switch(nType)

		pNewNode->nodelength = nodelength - 4;



		// Step2：从内存格式化成节点对象的数据
		pos += pNewNode->PositDataToNode(pBuffer + pos);
		
		/*vgMod::ObjectNode*pObjectNode	= dynamic_cast<vgMod::ObjectNode*>(pNewNode);
		if (pObjectNode!=NULL)
		{
			pObjectNode->setName( string( pObjectNode->GetName() ) );
		}*/
		vgKernel::Renderer* pRenderer = dynamic_cast<vgKernel::Renderer*>(pNewNode);
		if (pRenderer!=NULL)
		{
			pRenderer->setName( string( pNewNode->GetName() ) );
		}

		*pNodeData	=	pNewNode;

		return true;	
	}


	
	//----------------------------------------------------------------
	bool FileReaderVG::addVgNodeToManager()
	{

		// Step 1: 加入RendererManager
		static FileReaderMOD::TraverseVecForAddRender funAddRender;
		for (NodePtrPackage::iterator itr = m_pNodePackage->begin();
			itr != m_pNodePackage->end(); itr ++)
		{
			NodePtrVec* m_tempModList = &itr->second;

			for_each( m_tempModList->begin(), m_tempModList->end(), funAddRender);
		}


		NodePtrVec& m_tempModList = (*m_pNodePackage)[NODE_TYPE_MOD];
		for (NodePtrVec::iterator itr = m_tempModList.begin();
			itr != m_tempModList.end(); itr ++ )
		{
#if 1
			// Step 3: 数据库配置  add by lss
			using namespace vgKernel;
			Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

			if ( plg != NULL )
			{
				vgKernel::Renderer* renderer = dynamic_cast<vgKernel::Renderer*>(*itr);
				
				if( renderer!=NULL )
				{
					VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, InitRendererProfile, func_inirenderer );
					(*func_inirenderer)(renderer);

// 					vgDatabase::ProfileManager::getSingleton().InitRendererProfile(renderer);
				}
			}

#endif

			// Step 2: 加入触发器队列
			vgMod::ObjFrameNode* pFrameNode = dynamic_cast<vgMod::ObjFrameNode*>(*itr);
			if(pFrameNode && pFrameNode->getTriggerFlag() )
			{
				vgMod::TriggerManager::getSingleton().
					addTrigger(	pFrameNode);
			}
		}


		return true;
	}


	
	//----------------------------------------------------------------
	bool	FileReaderVG::readOherModulesDirectly()
	{
		
		vgKernel::StreamReader*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamReader*)pcfile)->getCFilePointer();
#if 0
		String	otherModulesSubDir = "ProAttachdata";

		String	attachDataPath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(m_strFilePath);

		attachDataPath += otherModulesSubDir ;
		attachDataPath += "\\";
#endif

		String	attachDataPath = m_strFilePath;

		vgMod::ModEffectConvertor::setProDataPath(attachDataPath);


		vgKernel::StreamReaderPtr preader =
			vgKernel::StreamReaderFactory::createFromCFile( pfile , false );
		assert( preader.isNull() == false );

		// Part 1: 音效
		vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		if (plugin != NULL)
		{

			VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManagerSaver, readSoundMgrFromFile2, pfn1 );

			assert( pfn1 != NULL );

			(*pfn1)( preader, attachDataPath ,true);

		}

		//SoundManagerSaver::readSoundMgrFromFile( preader , attachDataPath ,true);

		// Part 2: 相机(视点和漫游动画)
		CamManagerSaver::readCamMgrFromFile( preader , attachDataPath ,true);



		// Part 3: 全局中心坐标
		//vgCore::vgCoordinate::getSingleton().readFromFile(pfile );
		vgKernel::Vec3 vec;
		pfile->Read( &vec, sizeof(vgKernel::Vec3));



		// Part 4: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))e
		vgCore::MovingManager::getSingleton().readFromFile(pfile, attachDataPath);


		String	vgVersion  = VersionControl::getVgVersionRead();
		if( vgVersion >= String("VRGIS.VERSION 2.17") )
		{
//			vgAutoBuild::AutoBuildSaver::readAutoBuildFromFile(m_strFilePath, attachDataPath);
		}

		return true;
	}

}//namespace vgMod
