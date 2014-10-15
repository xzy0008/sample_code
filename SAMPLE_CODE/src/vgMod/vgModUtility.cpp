



#include <vgStableHeaders.h>
#include <vgMod/vgModUtility.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkRendererManager.h>

#include <vgTex/tvgArchiveManager.h>

#include <vgMod/vgNodeManager.h>
#include <vgMod/vgModEffectConvertor.h>
#include <vgMod/vgTriggerManager.h>

#include <vgMod/vgFileWriterVG.h>
#include <vgMod/vgFileReaderVG.h>
#include <vgMod/vgFileReaderMOD.h>
#include <vgMod/vgFileReaderVG.h>

#include <vgMod/vgFileWriterVGUpdate.h>
#include <vgMod/vgFileReaderVGUpdate.h>

#include <vgMod/vgNodeManager.h>
#include <vgMod/vgObjFrameNode.h>
#include <vgMod/vgVersionControl.h>

#include <vgSound/vgSoundDefinition.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkSelectManager.h>

#include <vgEffect/vgDynamicBillBoardNode.h>
#include <vgEffect/vgParticle.h>
#include <vgEffect/vgGlassNode.h>

#include <vgBillBoard.h>
#include <vgMovingManager.h>

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_PATH_ROOT		"DataPathRoot"

#define VGDATA_PATHCONF_TEXTURE_PATH	"TexturePath"

namespace vgMod {

	bool ModUtility::b_readVgOrMod = true;
	bool ModUtility::b_readDirectly= false;
	bool ModUtility::m_bSaveSelectNode = false;
	vector<vgCore::MetaFile> ModUtility::m_metaFileInfoVec;

	//--------------------------------------------------------------------------------------------
	bool	ModUtility::saveSceneToVG( const string& filepath ,
		unsigned int uiUpdateTime)
	{ 

		string prefix = 
			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( filepath );

		string filenamewithext = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( filepath );

		string folderpath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename( filepath );

		string dirpath = "VRGIS_" + prefix + '\\'; 
		string tempfolderpath = folderpath + dirpath;
		BOOL createok = vgKernel::SystemUtility::createDirectory(tempfolderpath);

		if ( createok == FALSE )
		{
			return false;
		}


		folderpath = folderpath + "\\" + dirpath;

		// 复制其它文件（路径动画、背景音效、数据库文件等）
		String pathbuffer = vgKernel::SystemUtility::getCurrentProcessPath();
	
#if 0
		String srcpath = pathbuffer + "ProAttachdata";
		dirpath = folderpath + "\\ProAttachdata";
#else
		String dataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_ROOT);

		String srcpath = pathbuffer + dataPath;
		dirpath = folderpath + "\\" + dataPath;
#endif
		vgKernel::SystemUtility::createDirectory(dirpath);
		vgKernel::SystemUtility::copyDirectory(dirpath, srcpath);


		String strFilePath	=	folderpath + "\\" + filenamewithext;
		
		//saveVGIMG(strFilePath);



		// 模型*.vg
		String strModPathName(strFilePath);
		strModPathName.erase( strModPathName.find_last_of("\\.")+1, std::string::npos);
		strModPathName += "vg";

		vgMod::FileWriterVGAbstract*	pFileWriter = NULL;

		switch( uiUpdateTime )
		{
		case 0:
			pFileWriter = new vgMod::FileWriterVG;
			break;

		case 1:
			pFileWriter = new vgMod::FileWriterVGUpdate;
			break;

		default:
			break;
		}

		NodeAbsPtrVec* pNodeAbsPtrVec = NULL;

		if ( !m_bSaveSelectNode ) // 保存所有节点
		{
			pNodeAbsPtrVec = vgMod::NodeManager::getSingleton().getNodeItemIndexList();
		}
		else // 保存选定节点
		{
			bool bOk = generateNodeIndexFromRender( 
				vgKernel::SelectManager::getSingleton().getCurrentSelectedItems()/*SelectedItems()*/, 
				vgMod::NodeManager::getSingleton().getSelectNodeItemIndexList() );

			if ( !bOk )
			{
				string msg = "保存vg失败！无法生成节点Index.";
				vgKernel::SystemUtility::showModelDialog( msg );
				return false;
			}
			pNodeAbsPtrVec = vgMod::NodeManager::getSingleton().getSelectNodeItemIndexList();
		}

		if( !pFileWriter->write( strFilePath, pNodeAbsPtrVec ) )
		{
			delete pFileWriter;
			pFileWriter = NULL;

			return false;
		}

		// 保存纹理 .vgimg ( 注意顺序先模型后纹理 )
		saveVGIMG(strFilePath);


		vgKernel::SystemUtility::setCurrentDirectory(strFilePath);

		delete pFileWriter;
		pFileWriter = NULL;

		return true;

	}//saveSceneToVG



	
	//--------------------------------------------------------------------------------------------
	bool	ModUtility::readSceneFromVG( const string& strFilePath ,
		unsigned int uiUpdateTime/* = 0*/)
	{
		b_readVgOrMod = true;
		
		readVGIMG(strFilePath);

		chenkVersionAndUpdate( strFilePath );

		vgMod::FileReaderVGAbstract*	pFileReader = NULL;

		switch( uiUpdateTime )
		{
		case 0:
			pFileReader = new vgMod::FileReaderVG;
			break;

		case 1:
			pFileReader = new vgMod::FileReaderVGUpdate;
			break;

		default:
			break;
		}
		// 读vg
		if( !pFileReader->read(strFilePath, 
			NodeManager::getSingleton().getNodeItemIndexList(),
			NodeManager::getSingleton().getNodeItemList()
			) )
		{
			return false;	
		}

		vgKernel::RendererManager::getSingleton().invalidate();

		// Part 3：加入UI
		//addNodeToUI(strFilePath);

		vgKernel::SystemUtility::setCurrentDirectory(strFilePath);


		return true;
	}



	//--------------------------------------------------------------------------------------------
	bool	ModUtility::AddModelToScene( const string& strFilePath )
	{
		// Part 0：标记读文件的类型(非vg)
		b_readVgOrMod = false;


		// Part 1：将mod文件目录加入纹理路径队列，供纹理搜素
		vgCore::ArchiveManager &archmgr = vgCore::ArchiveManager::getSingleton();
		String filePath = strFilePath.substr( 0,  strFilePath.find_last_of("\\/") );
		vgCore::ArchivePtr parch( new vgCore::FileSystemArchive( filePath ,"filesystem") );
		parch->load();
		static int weight = 400;
		archmgr.addArchive( weight ++ , parch );


		// Part 2：读mod
		vgMod::FileReaderMOD	vgFileReader;
		if( !vgFileReader.read( strFilePath
			, NodeManager::getSingleton().getNodeItemIndexList()
			, NodeManager::getSingleton().getNodeItemList(NODE_TYPE_MOD, true)
			, NodeManager::getSingleton().getModItemList() ) )
			return false;

		vgKernel::RendererManager::getSingleton().invalidate();


		vgKernel::SystemUtility::setCurrentDirectory(strFilePath);

		return true;
	}

	
	//--------------------------------------------------------------------------------------------
	void ModUtility::generateNodeIndexFromNode( Node* pNodeIn, NodeAbstract** pNodeAbsOut )
	{
		NodeAbstract * pNodeAbs=new NodeAbstract(pNodeIn->m_id,pNodeIn->m_RenderTypeInt,pNodeIn->m_Position, 
			pNodeIn->GetBoundryBox(), 0, pNodeIn->TYPE,pNodeIn->m_numOfFaces,pNodeIn->m_name,
			pNodeIn);

		*pNodeAbsOut = pNodeAbs;
	}

	//----------------------------------------------------------------
	bool ModUtility::generateNodeIndexFromRender( const vgKernel::RendererQueue& renderQuene,
		NodeAbsPtrVec* pNodeAbsPtrVec )
	{
		using namespace vgKernel;

		RendererQueue::const_iterator iter = renderQuene.begin();
		RendererQueue::const_iterator iter_end = renderQuene.end();

		Node* pNode = NULL;

		for ( ; iter != iter_end; iter++ )
		{
			RendererType type = (*iter)->getType();
			bool bConvert = false;

			switch( type )
			{
			case RENDERER_TYPE_MODOJBECT:
			case RENDERER_TYPE_GPUSPECIAL_WARTER:
			case RENDERER_TYPE_GPUSPECIAL_SKYNODE:
			case RENDERER_TYPE_GPUSPECIAL_MIRROR:
			case RENDERER_TYPE_GPUSPECIAL_METAL:
			case RENDERER_TYPE_GPUSPECIAL_FLOOR:
			case RENDERER_TYPE_GPUSPECIAL_AVI:
			case RENDERER_TYPE_GPUSPECIAL_GLASS:
				{
					ObjectNode* pObjNode = dynamic_cast<ObjectNode*>(*iter);
					assert( pObjNode != NULL );

					pNode = dynamic_cast<Node*>( pObjNode );
					assert( pNode != NULL );

					bConvert = true;
				}
				break;

			case RENDERER_TYPE_BILLBOARD:
			case RENDERER_TYPE_DYNAMICBILLBOARD:
			case RENDERER_TYPE_PARTICLE:
				{
					pNode = dynamic_cast<Node*>( *iter );
					bConvert = true;
				}
				break;

			default:
				break;
			} // end switch

			if ( bConvert )
			{
				assert( pNode != NULL );
				NodeAbstract* pNodeAbstract = new NodeAbstract();
				
				// 生成节点索引
				generateNodeIndexFromNode( pNode, &pNodeAbstract );

				// 加入节点索引队列( 由NodeManager负责管理选定节点索引队列 )
				assert( pNodeAbstract != NULL );
				pNodeAbsPtrVec->push_back( pNodeAbstract );
			}
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------
	bool ModUtility::generateSelectTexNameVec( const NodeAbsPtrVec* pNodeAbsPtrVec, 
		TextureNameMap* pTexNameMap )
	{
		assert( pNodeAbsPtrVec != NULL );
		if ( pNodeAbsPtrVec == NULL )
		{
			return false;
		}

		vgKernel::StringVector texNameVec;

		NodeAbsPtrVec::const_iterator iter = pNodeAbsPtrVec->begin();
		NodeAbsPtrVec::const_iterator iter_end = pNodeAbsPtrVec->end();

		for ( ; iter != iter_end; iter++ )
		{
			Node* pNode = (*iter)->m_pNodeData;
			assert( pNode != NULL );

			switch( pNode->getCategory() )
			{
			case NODE_TYPE_MOD:
				{
					switch( pNode->TYPE )
					{
					case VG_OBJECT:  // 普通Mod
					case VG_OBJECT_KEYFRAME:
						{
							for ( int i = 0; i < pNode->m_numOfMat; i++ )
							{
								string strFile = (string)(pNode->pMats[i].materialinfo.strFile);
								texNameVec.push_back( strFile );

								string alphaFile = (string)(pNode->pMats[i].materialinfo.alphaFile);
								texNameVec.push_back( alphaFile );

							} // end for i
						}
						break;

					case VG_OBJECT_BAKED:    // 烘培物体
					case VG_OBJECT_BAKED_KEY:
						{
							ObjectNodeBaked *pObjBakeNode = dynamic_cast<ObjectNodeBaked*>(pNode);
							assert( pObjBakeNode != NULL );

							for ( int i = 0; i < pNode->m_numOfMat; i++ )
							{
								string strFile = (string)(pObjBakeNode->pMaterialStruct2[i].materialinfo.strFile);
								texNameVec.push_back( strFile );

								string alphaFile = (string)(pObjBakeNode->pMaterialStruct2[i].materialinfo.alphaFile);
								texNameVec.push_back( alphaFile );

								string bakeFile = (string)(pObjBakeNode->pMaterialStruct2[i].materialinfo.strFileBaked);
								texNameVec.push_back( bakeFile );

							} // end for i
						}
						break;

					default:
						break;
					}
				}
				break;

			case NODE_TYPE_BB: // Billboard
				{
					BillboardNode *pBillboard = dynamic_cast<BillboardNode*>(pNode);
					assert( pBillboard != NULL );

					string texName = pBillboard->getTextureName();
					texNameVec.push_back( texName );
				}
				break;

			case NODE_TYPE_MOD_EFFECT:  // mod特效
				{
					vgKernel::StringVector tempTexVec;

					ObjectNode* pObjNode = dynamic_cast<ObjectNode*>(pNode);
					assert( pObjNode != NULL );

					tempTexVec = pObjNode->getTexNameVec();

					for ( int i = 0; i < tempTexVec.size(); i++ )
					{
						texNameVec.push_back( tempTexVec[i] );
					}
				}
				break;

			default:
				break;
			}
		} // end switch pNode->getCategory()


		for ( int j = 0; j < texNameVec.size(); j++ )
		{
			if ( texNameVec[j] != "" )
			{
				StringPtr stringPtr = StringUtil::createStringPtr(texNameVec[j]);

				TextureNameMap::iterator itr = pTexNameMap->find( stringPtr );

				if ( itr == pTexNameMap->end() )
				{
					pTexNameMap->insert( std::make_pair( stringPtr, stringPtr ) );
				}

			} // end if texNameVec[j]

		} // end for j

		return true;
	}

	//--------------------------------------------------------------------------------------------
	void ModUtility::readVGIMG( const string& strFilePath )
	{
		// 读vgimg
		//readMaterialsFromVGIMG(strFilePath);
		// 以下为纹理文件(*.vgimg)的读取
		String ImgPathName = strFilePath;

		String::size_type kk = ImgPathName.length();
		ImgPathName.erase(kk - 2, String::npos);

		ImgPathName = ImgPathName + "vgimg";

		// 先读入所有的vgimg header
		FILE *fp = fopen(ImgPathName.c_str(), "rb");

		if (fp == NULL)
		{
			return ;
		}


		// 读取头文件信息
		Header metaHead;
		size_t readcount = fread(&metaHead,sizeof(Header), 1 , fp );

		/*assert( readcount == sizeof(Header) )*/;

		if ( strcmp( metaHead.mFourCC , "VGIMG") != 0 )
		{
			// 出错
			assert(0);

			return;
		}

		// 申请索引区域内存
		int metaFileNum = metaHead.mFilesNum;
		vgCore::MetaFile *pMetaFileInfo = new vgCore::MetaFile[ metaFileNum ];
		assert( (sizeof( vgCore::MetaFile ) * metaFileNum ) == metaHead.mMetaFieldLength );

		if ( metaFileNum == 0 )
		{
			return;
		}

		// 跳转到索引区域
		fseek(fp, metaHead.mMetaFieldBegin, SEEK_SET );

		size_t rd_indx_field = 
			fread(pMetaFileInfo , metaHead.mMetaFieldLength , 1, fp);

		for (int i=0; i<metaFileNum; i++)
		{
			m_metaFileInfoVec.push_back(pMetaFileInfo[i]);
		}
		delete [] pMetaFileInfo;
// 
// 		if( rd_indx_field != metaHead.mMetaFieldLength )
// 		{
// 			MessageBox( NULL , "vgimg文件损坏!" , "致命错误" , MB_OK );
// 			assert(0);
// 
// 			return;
// 		}
		
		fclose(fp);

		String _proAttachedData = strFilePath;
		_proAttachedData.erase( _proAttachedData.find_last_of("\\/") , String::npos); 
		//_proAttachedData += "\\ProAttachdata";
		String texturePath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_TEXTURE_PATH);

		_proAttachedData += texturePath;


		try
		{
			//------------------------------------------
			// check file exist
			//------------------------------------------
			if( vgKernel::SystemUtility::checkFileExist( ImgPathName ) == false )
			{
				String notExist(ImgPathName);

#if VGK_LANG_CHS
				notExist += ", vgimg文件不存在!";
#else
				notExist += ", vgimg do not exist!";
#endif

				VG_EXCEPT( vgCore::Exception::ERR_FILE_NOT_FOUND , 
					notExist , "ModUtility::readSceneFromVG( const string& strFilePath)");
			}

			vgCore::ArchiveManager &archmgr = vgCore::ArchiveManager::getSingleton();
			vgCore::ArchivePtr parch( new vgCore::VgimgArchive(ImgPathName ,"vgimg") );
			parch->load();

			// parch.setNull();
			archmgr.addArchive( 300, parch );

			vgCore::ArchivePtr parch2( 
				new vgCore::FileSystemArchive( _proAttachedData ,"filesystem") );

			parch2->load();

			vgCore::ArchiveManager::getSingleton().addArchive( 8000 , parch2 );

		}
		catch (vgCore::Exception &e)
		{
			MessageBox( NULL , e.getFullDescription().c_str() , "ERROR" , MB_OK );
		}
	}

		
	//--------------------------------------------------------------------------------------------
	void ModUtility::saveVGIMG( const string& strFilePath )
	{
		// ArchiveManager::getSingleton().clear();

		// 纹理写入 vgimg
		string ImgPathName(strFilePath);
		ImgPathName.erase( ImgPathName.find_last_of("\\.")+1, std::string::npos);
		ImgPathName = ImgPathName + "vgimg";
		//VG_TRACE( TextureManager::getSingletonPtr()->getDetails());

		try
		{
			vgCore::StringPairListPtr pstr( new StringPairList() );

			vgCore::StringVectorPtr pnames;

			if ( !m_bSaveSelectNode )
			{
				pnames = vgCore::TextureManager::getSingleton().getNamesDetails();
			}
			else
			{
				bool bOk = generateSelectTexNameVec( vgMod::NodeManager::getSingleton().getSelectNodeItemIndexList(),
					vgCore::TextureManager::getSingleton().getTextureNameMap() );
				
				if ( !bOk )
				{
					string msg = "保存vg失败！无法生成纹理列表.";
					vgKernel::SystemUtility::showModelDialog( msg );
					return;
				}

				pnames = vgCore::TextureManager::getSingleton().getSelectNamesDetails();
			}

			assert( !pnames.isNull() );

			vgCore::StringVector::iterator iter = pnames->begin() ;
			vgCore::StringVector::iterator iter_end = pnames->end() ;

			for ( ; iter != iter_end ; ++iter )
			{
				pstr->push_back( std::make_pair( *iter , *iter ) );
			}

			vgCore::StreamWriterPtr pw = vgCore::StreamFactory::createWriterFromFile(ImgPathName);
			vgCore::ArchiveSaver saver( pw , pstr );

			//VG_TRACE( TextureManager::getSingleton().getDetails() );

			if( saver.beginToWrite() == false )
			{
				assert(0);
			}

			pw->close();

			vgCore::ArchivePtr fileimg( new vgCore::VgimgArchive(ImgPathName,"vgimg") );

			assert( !fileimg.isNull() );

			fileimg->load();

		}
		catch (vgCore::Exception &e)
		{
			MessageBox( NULL , e.getFullDescription().c_str() , "ModUtility::saveSceneToVG() ERROR" , MB_OK );
		}
	}

	//--------------------------------------------------------------------------------------------
	bool ModUtility::saveSceneToVGDirectly( const string& filepath , unsigned int uiUpdateTime )
	{
		String strModPathName(filepath);
		strModPathName.erase( strModPathName.find_last_of("\\.")+1, std::string::npos);
		strModPathName += "vg";

		vgMod::FileWriterVGAbstract*	pFileWriter = NULL;

		switch( uiUpdateTime )
		{
		case 0:
			pFileWriter = new vgMod::FileWriterVG;
			break;

		case 1:
			pFileWriter = new vgMod::FileWriterVGUpdate;
			break;

		default:
			break;
		}

		NodeAbsPtrVec* pNodeAbsPtrVec = NULL;

		if ( !m_bSaveSelectNode ) // 保存所有节点
		{
			pNodeAbsPtrVec = vgMod::NodeManager::getSingleton().getNodeItemIndexList();
		}
		else // 保存选定节点
		{
			bool bOk = generateNodeIndexFromRender( 
				vgKernel::SelectManager::getSingleton().getSelectedItems(),
				vgMod::NodeManager::getSingleton().getSelectNodeItemIndexList() );

			if ( !bOk )
			{
				string msg = "保存vg失败！无法生成节点Index.";
				vgKernel::SystemUtility::showModelDialog( msg );
				return false;
			}
			pNodeAbsPtrVec = vgMod::NodeManager::getSingleton().getSelectNodeItemIndexList();
		}

		if( !pFileWriter->write(filepath, pNodeAbsPtrVec, true ) )
		{
			delete pFileWriter;
			pFileWriter = NULL;

			return false;
		}

		delete pFileWriter;
		pFileWriter = NULL;

		return true;
	}


	
	//--------------------------------------------------------------------------------------------
	bool ModUtility::readSceneFromVGDirectly( const string& strFilePath , unsigned int uiUpdateTime )
	{
		b_readVgOrMod = true;

		vgMod::FileReaderVGAbstract*	pFileReader = NULL;

		switch( uiUpdateTime )
		{
		case 0:
			pFileReader = new vgMod::FileReaderVG;
			break;

		case 1:
			pFileReader = new vgMod::FileReaderVGUpdate;
			break;

		default:
			break;
		}
		// 读vg
		if( !pFileReader->read(strFilePath, 
			NodeManager::getSingleton().getNodeItemIndexList(),
			NodeManager::getSingleton().getNodeItemList(),
			true
			) )
		{
			return false;	
		}


		return true;
	}

	
	//----------------------------------------------------------------
	bool	ModUtility::chenkVersionAndUpdate( const string& strFilePath )
	{
		// 如果程序执行到这里，说明需要版本更新...
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(strFilePath);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(strFilePath);
		fileName += ".cam";

		filePath += fileName;

		bool isFileExist = vgKernel::SystemUtility::checkFileExist(filePath);

		if (isFileExist)
		{
			return true;
		}

		//	Part 1：文件头，包括文件版本、四叉树存储位置（待计算）、节点总数目等3项
		VGFileHeader fileHeader;
		if ( !fileHeader.read(strFilePath) )
		{
			return false;
		}

		if( VersionControl::getVgVersionRead() == VersionControl::getVgVersionWrite() )
		{
			return true;
		}

		// 以下版本升级...
		{
			std::ostringstream oStr;

			oStr << "\n\tVG文件:"<< strFilePath << "格式过旧！\n"
				<< "请用VG转换器转换场景文件。\n";

			VGK_SHOW( oStr.str() );

			if( IDYES == MessageBox( NULL,
				"VG格式过旧, 是否升级至最新格式？注意：请根据需要在升级前先做好备份。" ,
				"VG格式升级提示", 
				MB_YESNO))
			{
				vgMod::ModUtility::setFlagReadDirectly(true);

				vgMod::ModUtility::readSceneFromVGDirectly(strFilePath, 0);

				vgMod::ModUtility::saveSceneToVGDirectly( strFilePath,1 );

				//vgSound::SoundManager::getSingleton().reset();
				VGK_DLL_RUN_CLASSFUNC( VGSOUND_DLL_NAME , SoundManager, reset )( );


				vgMod::NodeManager::getSingleton().reset();
				vgCore::MovingManager::getSingleton().reset();

				vgMod::TriggerManager::getSingleton().reset();

				vgKernel::RendererManager::getSingleton().reset();

				vgMod::ModUtility::setFlagReadDirectly(false);

			}
			else
			{
				return false;
			}
		}

		return true;
	}


}// end of namespace vgMod
