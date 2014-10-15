
#include <vgStableHeaders.h>

#include <vgMod/vgFileReaderMOD.h>

#include <vgMod/vgFileDefinitionVG.h>
#include <vgMod/vgModUtility.h>
#include <vgMod/vgobjframenode.h>
#include <vgMod/vgObjNodeBaked.h>

#include <vgKernel/vgkStreamReader.h>
#include <vgBillBoard.h>
#include <vgUIController/vgUIController.h>
#include <vgMod/vgNodeManager.h>
#include <vgEntry/vgEntryFactory.h>
//#include <vgMovingManager.h>
//#include <vgMod/vgQuadtreeSceneManager.h>


namespace vgMod{

	
	//----------------------------------------------------------------
	FileReaderMOD::FileReaderMOD()
	{
		m_pNodeIndexList = NULL;
		m_pNodeList = NULL;

		m_pTempNodeIndexList = new NodeAbsPtrVec;
		m_pTempNodeList = new NodePtrVec;
		//m_pModListTemp	= new ModItemPtrVec;
	}
	
	//----------------------------------------------------------------
	FileReaderMOD::~FileReaderMOD()
	{
		if (m_pTempNodeIndexList)
		{
			delete m_pTempNodeIndexList;
		}
		if (m_pTempNodeList)
		{
			delete m_pTempNodeList;
		}
		/*if (m_pModListTemp)
		{
			delete m_pModListTemp;
		}*/
	}

	//----------------------------------------------------------------
	bool	FileReaderMOD::read( const String& open_absolute_path, 
		NodeAbsPtrVec*	pNodeIndexList,
		NodePtrVec* pNodeList,
		ModItemPtrVec* pModListTemp)
	{
		m_strFilePath	= open_absolute_path;
		m_pNodeIndexList= pNodeIndexList;
		m_pNodeList		= pNodeList;
		m_pModListTemp	= pModListTemp;

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


		//	Part 1：文件头，包括文件格式、模型数目、模型类型等6项
		if ( !m_fileHeader.read( m_pfile ) )
		{
			return false;
		}
		
		
		//	Part 2:	MOD模块的数据
		readObjectNodeFromMOD();

		
		//	Part 3:	生成索引
		generateNodeIndex();

		
		//	Part 4:	附加到管理器和界面
		addModNodeToManager();

		
		//	Part 5:	附加到管理器和界面
		//addModNodeToUI();

		// 写文件结束!
		m_pfile->close();

		return true;

	}
	
	//----------------------------------------------------------------
	bool	FileReaderMOD::readObjectNodeFromMOD()
	{
		vgKernel::StreamReader*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamReader*)pcfile)->getCFilePointer();

		ObjectNode*	pObjectNode = NULL;

		m_pTempNodeList->clear();
		m_pModListTemp->clear();

		for (int indexMod = 0; indexMod < m_fileHeader.uiObjectCount; indexMod++)
		{	
			//	Step0：定位文件指针到某个节点的数据块位置
			pfile->Seek(m_fileHeader.arrModPosIndex[indexMod] , CFile::begin);

			//	Step1：根据不同的节点类型，生成物体对象
			if( m_fileHeader.uiFileVersion > VERSION_MOD(2008,5) )
			{
				uint ffff;
				if ( indexMod == 4 )
				{
					ffff = m_fileHeader.arrModType[indexMod].nType;
				}
				

				if ( (m_fileHeader.arrModType[indexMod].nType & OBJ_KEYFRAME)  )
				{
					if ( (m_fileHeader.arrModType[indexMod].nType & OBJ_BAKED)  )
					{
						pObjectNode	=	new ObjectNodeBaked(m_fileHeader.uiFileVersion);
					}
					else
					{
						pObjectNode	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
					}

					//pObjectNode	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
				}
				else if ( !(m_fileHeader.arrModType[indexMod].nType & OBJ_BAKED)  )
				{
					pObjectNode	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
				}
				else
				{
					pObjectNode	=	new ObjectNodeBaked(m_fileHeader.uiFileVersion);
				}
			}
			else
			{
				if ( !m_fileHeader.arrModType[indexMod].bType  )
				{
					pObjectNode	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
				}
				else
				{
					pObjectNode	=	new ObjectNodeBaked(m_fileHeader.uiFileVersion);
				}
			}

			
			//	Step2：按块大小读入内存
			pObjectNode->ReadObjectFromMod(*pfile);
			
			pObjectNode->setName( string( pObjectNode->GetName() ) );

			bool isTree = convertModTree2Billbaoard( pObjectNode );

			if ( isTree )
			{
				continue;
			}

			m_pTempNodeList->push_back(pObjectNode);
			m_pModListTemp->push_back(pObjectNode);
			
		}//uiObjectCount


		return	true;
	}
	
	//----------------------------------------------------------------
	bool	FileReaderMOD::generateNodeIndex()
	{
		//添加到索引中
		for (NodePtrVec::iterator itr = m_pTempNodeList->begin();
			itr != m_pTempNodeList->end(); itr ++ )
		{
			NodeAbstract * pNodeAbs=new NodeAbstract();

			ModUtility::generateNodeIndexFromNode( *itr, &pNodeAbs);

			m_pTempNodeIndexList->push_back(pNodeAbs);
		}


		return true;
	}

	
	//----------------------------------------------------------------
	bool	FileReaderMOD::addModNodeToManager()
	{

		m_pNodeIndexList->insert(m_pNodeIndexList->begin(),
			m_pTempNodeIndexList->begin(), m_pTempNodeIndexList->end());
		
		m_pNodeList->insert(m_pNodeList->begin(),m_pTempNodeList->begin(), m_pTempNodeList->end());

		static TraverseVecForAddRender funAddRender;
		for_each(m_pTempNodeList->begin(), m_pTempNodeList->end(), funAddRender);

		vgKernel::RendererManager::getSingleton().invalidate();

		
		return true;
	}
	//---------------------------------------------------------------
	bool	FileReaderMOD::convertModTree2Billbaoard( ObjectNode*	pObjectNode )
	{
		std::string nodeName(pObjectNode->GetName());
		std::string sub_str(nodeName.substr(0,3));		// 获取名称的前3个字符
		std::string str_material;						// 贴图名称
		
		// 转换成小写
		std::transform(sub_str.begin(), sub_str.end(), sub_str.begin(), tolower);

		TRACE("%s\n", sub_str.c_str());

		if ( sub_str == "bb-" )	// 如果是以"bb-"开头的(全部转换为小写),则认为是树模型,转换为BillBoard树
		{
			for ( int i = 0; i < pObjectNode->m_numOfMat; i++ )
			{
				std::string str_material1(pObjectNode->pMats[i].materialinfo.strFile);
				str_material = str_material1;
			}

			vgMath::Vector3 tree_pos = pObjectNode->m_Position;

			vgMath::BoundingBox tree_BoundBox = pObjectNode->m_BoundryBox;

			vgMod::BillboardNode *tempbill;

			tempbill = new vgMod::BillboardNode();

			tempbill->m_Position = tree_pos;

			tempbill->m_texturename = str_material;

			float xlength = tree_BoundBox.maxPoint.x - tree_BoundBox.minPoint.x;
			float zlength = tree_BoundBox.maxPoint.z - tree_BoundBox.minPoint.z;

			tempbill->m_width = sqrt(xlength * xlength + zlength *zlength);

			tempbill->m_height = tree_BoundBox.maxPoint.y - tree_pos.y;

			tempbill->m_Position.y = tree_pos.y - tempbill->m_height;

			tempbill->m_height = tempbill->m_height * 2;

			tempbill->m_prePositon = tree_pos;

			tempbill->ComputeBoundBox();

			tempbill->Initialize();

			//	 特效名字///////////////////////////////////////
			//int k = getNodeItemList(NODE_TYPE_BB, true)->size();
			//m_oCurrentScene.vgLayerList[0]->m_uiBillboardCount;

			//char buffer[6];
			//itoa(k,buffer,10);

			//String	strParticleName(tempbill->m_name);
			//strParticleName += '*';
			//strParticleName += buffer;
			strcpy_s(tempbill->m_name, /*19,*/ nodeName.c_str());

			vgMod::NodeManager::getSingleton().appendNode( tempbill, NODE_TYPE_BB );

			vgKernel::RendererManager::getSingleton().addRenderer( tempbill );

			CategoryType nCat = tempbill->getCategory();

			HTREEITEM hRootNodeUI = NULL;

			hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_BILLBOARD_PLANT);

			vgKernel::Renderer* pRenderer = dynamic_cast<vgKernel::Renderer*>( tempbill );

			if ( !pRenderer )
			{
				return false;
			}

			pRenderer->setName( nodeName );

			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pRenderer );

			vgMod::ObjFrameNode* pFrameNode = NULL;
			pFrameNode = dynamic_cast<vgMod::ObjFrameNode*>( tempbill );

			if( nCat == NODE_TYPE_MOD 
				&&  pFrameNode 
				&& !pFrameNode->getTriggerFlag() 
				&& !pFrameNode->hasKeyFrame()
				)
			{//普通MOD
				String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
					"" );
				vgUI::UIController::getSingleton().AddNode( shortname, entry ,hRootNodeUI);
			}
			else
			{
				vgUI::UIController::getSingleton().AddNode( hRootNodeUI, entry );
			}

			if (hRootNodeUI != NULL)
			{
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootNodeUI );
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootNodeUI);
			}

			//-----------------------------------------------------------
			return true;

		}
		
		return false;
	}
	
}//namespace vgMod
