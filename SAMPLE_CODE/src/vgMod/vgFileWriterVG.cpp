
#include <vgStableHeaders.h>

#include <vgMod/vgFileWriterVG.h>
#include <vgMod/vgFileDefinitionVG.h>
#include <vgMod/vgModEffectConvertor.h>
#include <vgMod/vgModUtility.h>

#include <vgKernel/vgkStreamWriter.h>

#include <vgSound/vgSoundManager.h>
#include <vgCam/vgcaCamManager.h>
#include <vgMovingManager.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>

#include <vgCam/vggCamManagerSaver.h>
//#include <vgMod/vggCamManagerSaver.h>
//#include <vgMod/vggSoundManagerSaver.h>
#include <vgSound/vggSoundManagerSaver.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgSound/vgSoundDefinition.h>
#include <vgAutoBuild/vgAutoBuildSaver.h>

namespace vgMod{

	
	//----------------------------------------------------------------
	FileWriterVG::FileWriterVG()
	{

	}
	
	//----------------------------------------------------------------
	FileWriterVG::~FileWriterVG()
	{

	}

	//----------------------------------------------------------------
	bool	FileWriterVG::write( const String& save_absolute_path, 
		NodeAbsPtrVec*	pNodeIndexList,
		bool bDirectly/* = false*/)
	{
		m_strFilePath	= save_absolute_path;
		m_pNodeIndexList	= pNodeIndexList;

		//if( m_pNodeIndexList->IsEmpty() )
		//	return true;

		// case 1:	MFC_CFile*
#if 1
		DeleteFile(m_strFilePath.c_str());

		CFile* pfile = new CFile;

		if (! pfile->Open(m_strFilePath.c_str(),CFile::modeWrite ))
		{
			if (!pfile->Open(m_strFilePath.c_str(),CFile::modeWrite | CFile::modeCreate)) 
			{
				MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "Write File Failed" ,
					"error", MB_OK);
				return	false;
			}

		}

		m_pfile = vgKernel::StreamWriterFactory::createFromCFile( pfile,false);
		
#else
		// case 2:	C_FILE*
		m_pfile = vgKernel::StreamWriterFactory::createFromFile( save_absolute_path );
#endif
		
		if ( m_pfile.isNull() == true )
		{
			return false;
		}

		long filebeg = m_pfile->tell();


		//	Part 1：文件头，包括文件版本、四叉树存储位置（待计算）、节点总数目等3项
		m_fileHeader.write(m_pfile);//WriteHeadInfoToVG(m_pfile);

		//	Part 2:	其他模块的数据
		if (bDirectly)
		{
			vgMod::ModUtility::setFlagReadDirectly( true );

			writeOherModulesDirectly();
		} 
		else
		{
			vgMod::ModUtility::setFlagReadDirectly( false );

			writeOherModulesToVg();
		}

		//  Part 3: MOD模块
		writeModModuleToVg();

		// 写文件结束!
		m_pfile->close();

		return true;

	}

	//----------------------------------------------------------------
	bool	FileWriterVG::writeOherModulesDirectly()
	{
		vgKernel::StreamWriter*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamWriter*)pcfile)->getCFilePointer();


		// Part 0: 新建附件存储目录
#if 0
		String	otherModulesSubDir = "ProAttachdata";

		String	attachDataPath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(m_strFilePath);

		attachDataPath += otherModulesSubDir ;
		attachDataPath += "\\";

		vgKernel::SystemUtility::createDirectory(attachDataPath.c_str());
#endif
		String	attachDataPath = m_strFilePath;

		vgMod::ModEffectConvertor::setProDataPath(attachDataPath);


		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromCFile( pfile , false );
		assert( pwriter.isNull() == false );

		bool bDirect = vgMod::ModUtility::getFlagReadDirectly();

		// Part 1: 音效
		vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		if (plugin != NULL)
		{

			VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManagerSaver, writeSoundMgrToFile2, pfn1 );

			assert( pfn1 != NULL );

			(*pfn1)( pwriter, attachDataPath, bDirect);

		}
		//vgSound::SoundManagerSaver::writeSoundMgrToFile( pwriter , attachDataPath);

		// Part 2: 相机(视点和漫游动画)
		CamManagerSaver::writeCamMgrToFile( pwriter , attachDataPath, bDirect);

		// Part 3: 全局中心坐标
		vgKernel::Vec3 vec ;
		pfile->Write(&vec, sizeof(vgKernel::Vec3));


		// Part 4: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))
		vgCore::MovingManager::getSingleton().writeToFile(pfile, attachDataPath);


		// Part 5: 自动建模节点
//		vgAutoBuild::AutoBuildSaver::writeAutoBuildToFile(m_strFilePath, attachDataPath);

		return true;

	}

	//----------------------------------------------------------------
	bool	FileWriterVG::writeOherModulesToVg()
	{
		vgKernel::StreamWriter*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamWriter*)pcfile)->getCFilePointer();

		
		// Part 0: 新建附件存储目录
#if 0
		String	otherModulesSubDir = "ProAttachdata";
		
		String	attachDataPath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(m_strFilePath);

		attachDataPath += otherModulesSubDir ;
		attachDataPath += "\\";

		vgKernel::SystemUtility::createDirectory(attachDataPath.c_str());
#endif
		
		String	attachDataPath = m_strFilePath;

		vgMod::ModEffectConvertor::setProDataPath(attachDataPath);


		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromCFile( pfile , false );
		assert( pwriter.isNull() == false );

		bool bDirect = vgMod::ModUtility::getFlagReadDirectly();

		// Part 1: 音效
		vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		if (plugin != NULL)
		{

			VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManagerSaver, writeSoundMgrToFile2, pfn1 );

			assert( pfn1 != NULL );

			(*pfn1)( pwriter, attachDataPath, bDirect);

		}

		// Part 2: 相机(视点和漫游动画)
		CamManagerSaver::writeCamMgrToFile( pwriter , attachDataPath, bDirect);


		// Part 3: 全局中心坐标
		vgKernel::Vec3 vec ;
		pfile->Write(&vec, sizeof(vgKernel::Vec3));


#if VG_NEW	
		// Part 4: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))
		vgCore::MovingManager::getSingleton().writeToFile(m_strFilePath, attachDataPath);
#else
		vgCore::MovingManager::getSingleton().writeToFile(pfile, attachDataPath);
#endif

		// Part 5: 自动建模节点写入
		vgAutoBuild::AutoBuildSaver::writeAutoBuildToFile(m_strFilePath, attachDataPath);

		return true;
		
	}


	//----------------------------------------------------------------
	bool	FileWriterVG::writeModModuleToVg()
	{
		//	Part 1：MOD数据节点队列，由抽象节点索引队列遍历
		writeDataNodesByAbstractNodeToVG();

		//	Part 2：抽象节点索引队列
		m_fileHeader.abstractNodePos = m_pfile->tell();
		m_fileHeader.m_nodenum	= writeAbstractNodesToVG();

		//	Part 3：更新文件头：节点索引实际位置 和 实际节点总数
		m_pfile->seek( sizeof(m_fileHeader.vgfileheader));

		m_pfile->write(&m_fileHeader.abstractNodePos , sizeof(unsigned long));
		m_pfile->write(&m_fileHeader.m_nodenum , sizeof(int));

		return	true;
	}
	//----------------------------------------------------------------
	unsigned int FileWriterVG::writeAbstractNodesToVG( )
	{
		NodeAbstract	*pCurrentNodeAbs	= NULL;
		Node			*pCurrentNodeData	= NULL;
		unsigned int	nNodeCount			= 0;

		for ( int i = 0; i < m_pNodeIndexList->size(); i++)
		{
			if ( pCurrentNodeAbs = m_pNodeIndexList->at(i), 
				pCurrentNodeAbs )
			{
				if( pCurrentNodeData	= pCurrentNodeAbs->m_pNodeData,
					pCurrentNodeData )
				{
					// 将一个节点对象的索引写入文件
					m_pNodeIndexList->at(i)->WriteToFile(m_pfile);
					nNodeCount ++;
				}
			}
		}
		return	nNodeCount;
	}


	//----------------------------------------------------------------
	bool	FileWriterVG::writeDataNodesByAbstractNodeToVG( )
	{
		vgKernel::StreamWriter*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamWriter*)pcfile)->getCFilePointer();

		NodeAbstract	*pCurrentNodeAbs	= NULL;
		Node			*pCurrentNodeData	= NULL;
		unsigned	int	nPositionInFile		= 0;
		for ( int i = 0; i < m_pNodeIndexList->size(); i++)
		{
			if ( pCurrentNodeAbs = m_pNodeIndexList->at(i), 
				pCurrentNodeAbs )
			{
				if( pCurrentNodeData	= pCurrentNodeAbs->m_pNodeData,
					pCurrentNodeData )
				{
					nPositionInFile	= m_pfile->tell();
					pCurrentNodeAbs->m_offset	= nPositionInFile;

					// 将一个节点对象的数据写入文件
					pCurrentNodeData->WriteNodeToVG(*pfile);

					pCurrentNodeAbs->m_size	= m_pfile->tell() - nPositionInFile;
				}
			}
		}

		return true;
	}




	//----------------------------------------------------------------
}//namespace vgMod
