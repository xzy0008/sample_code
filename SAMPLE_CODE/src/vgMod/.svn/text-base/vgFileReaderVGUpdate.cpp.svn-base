
#include <vgStableHeaders.h>

#include <vgMod/vgFileReaderVGUpdate.h>
#include <vgMod/vgFileDefinitionVG.h>

#include <vgKernel/vgkStreamReader.h>


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

//#include <vgEntryFactory.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>

#include <vgMod/vgTriggerManager.h>
#include <vgMod/vgFileReaderMOD.h>
#include <vgMod/vgNode.h>
#include <vgMod/vgModEffectConvertor.h>
#include <vgMod/vgVersionControl.h>

#include <vgMod/vgNodeManager.h>
#include <vgMod/vgModUtility.h>

#include <vgCam/vggCamManagerSaver.h>

#include <vgSound/vggSoundManagerSaver.h>
#include <vgSound/vgSoundManager.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgSound/vgSoundDefinition.h>
#include <vgDatabase/vgdProfileManager.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>
#include <vgAutoBuild/vgAutoBuildSaver.h>

namespace vgMod{

	
	//----------------------------------------------------------------
	FileReaderVGUpdate::FileReaderVGUpdate()
	{
		//m_pTempNodeIndexList = new NodeAbsPtrVec;
		//m_pTempNodeList = new NodePtrVec;
	}
	
	//----------------------------------------------------------------
	FileReaderVGUpdate::~FileReaderVGUpdate()
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
	bool	FileReaderVGUpdate::readOherModulesFromVg()
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
			
		// Part 1: 音效
		vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		if (plugin != NULL)
		{

			VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManagerSaver, readSoundMgrFromFile, pfn1 );

			assert( pfn1 != NULL );

			(*pfn1)( m_strFilePath, attachDataPath , false);
		}
		else
		{
 			//assert(0);
			//AfxMessageBox("声音模块动态库未加载，将略过声音模块数据的读取!");
			
			std::ostringstream o;
			o << "声音模块动态库未加载，将略过声音模块数据的读取! \n\n";
			VGK_SHOW(o.str());
		}

		// Part 2: 相机(视点和漫游动画)
		vgMod::CamManagerSaver::readCamMgrFromFile( m_strFilePath , attachDataPath );


		// Part 3: 动态模型(骨骼动画和道路匹配、关键帧动画(暂未使用))		
		vgCore::MovingManager::getSingleton().readFromFile(m_strFilePath, attachDataPath);


		// Part 4: 自动建模节点
		String	vgVersion  = VersionControl::getVgVersionRead();
		if( vgVersion >= String("VRGIS.VERSION 2.17") )
		{
			vgAutoBuild::AutoBuildSaver::readAutoBuildFromFile(m_strFilePath, attachDataPath);
		}


		return true;
	}

	//----------------------------------------------------------------
	

}//namespace vgMod
