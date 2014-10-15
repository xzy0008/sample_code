
#include <vgStableHeaders.h>

#include <vgMod/vgFileWriterVGUpdate.h>
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
//#include <vgSound/vggSoundManagerSaver.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgSound/vgSoundDefinition.h>
#include <vgAutoBuild/vgAutoBuildSaver.h>


namespace vgMod{

	
	//----------------------------------------------------------------
	FileWriterVGUpdate::FileWriterVGUpdate()
	{

	}
	
	//----------------------------------------------------------------
	FileWriterVGUpdate::~FileWriterVGUpdate()
	{

	}


	//----------------------------------------------------------------
	bool	FileWriterVGUpdate::writeOherModulesToVg()
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

		bool bDirect = vgMod::ModUtility::getFlagReadDirectly();

		// Part 1: 音效
		vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		if (plugin != NULL)
		{

			VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManagerSaver, writeSoundMgrToFile, pfn1 );

			assert( pfn1 != NULL );

			(*pfn1)( m_strFilePath, attachDataPath, bDirect);

		}

		// Part 2: 相机(视点和漫游动画)
		CamManagerSaver::writeCamMgrToFile( m_strFilePath , attachDataPath, bDirect);


		// Part 3: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))
		vgCore::MovingManager::getSingleton().writeToFile(m_strFilePath, attachDataPath);


		// Part 4: 自动建模节点写入
		vgAutoBuild::AutoBuildSaver::writeAutoBuildToFile(m_strFilePath, attachDataPath);

		return true;
		
	}

	bool FileWriterVGUpdate::writeOherModulesDirectly()
	{
		vgKernel::StreamWriter*	pcfile = m_pfile.getPointer();
		CFile*	pfile = ((vgKernel::CFileStreamWriter*)pcfile)->getCFilePointer();


		// Part 0: 新建附件存储目录
#if 0
		String	attachDataPath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(m_strFilePath);

		attachDataPath += otherModulesSubDir ;
		attachDataPath += "\\";

		vgKernel::SystemUtility::createDirectory(attachDataPath.c_str());
#endif

		String	attachDataPath = m_strFilePath;

		vgMod::ModEffectConvertor::setProDataPath(attachDataPath);


		bool bDirect = vgMod::ModUtility::getFlagReadDirectly();

		// Part 1: 音效
		VGK_DLL_RUN_CLASSFUNC( VGSOUND_DLL_NAME, SoundManagerSaver, 
			writeSoundMgrToFile)( m_strFilePath , attachDataPath, bDirect)
		//vgSound::SoundManagerSaver::writeSoundMgrToFile( m_strFilePath , attachDataPath , true);

		
		// Part 2: 相机(视点和漫游动画)
		CamManagerSaver::writeCamMgrToFile( m_strFilePath , attachDataPath, bDirect);


		// Part 4: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))
		vgCore::MovingManager::getSingleton().writeToFile(m_strFilePath, attachDataPath);


		// Part 5: 自动建模节点
		//		vgAutoBuild::AutoBuildSaver::writeAutoBuildToFile(m_strFilePath, attachDataPath);

		return true;
	}

	
}//namespace vgMod
