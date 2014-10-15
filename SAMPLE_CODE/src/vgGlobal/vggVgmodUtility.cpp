
#include <vgStableHeaders.h>
#include <vgGlobal/vggVgmodUtility.h>

#include <vgGlobal/vggSceneFileUtility.h>

#include <vgMod/vgModUtility.h>
#include <vgMod/vgNodeManager.h>
#include <vgMod/vgModMisc.h>
#include <vgMod/vgModEffectConvertor.h>
#include <vgMod/vgobjframenode.h>


#include <vgAutoBuild/vgvAutoBuildManager.h>

#include <vgKernel/vgkInputSystem.h>

#include <vgEntry/vgEntryFactory.h>
#include <vgUIController/vgUIController.h>

#include <vgObjectEntry.h>
#include <vgMovingEntry.h>

#include <vgParticleEntry.h>
#include <vgBillboardEntry.h>
#include <vgDynamicBillboardEntry.h>
#include <vgGPUSpecialEntry.h>

namespace vgGlobal{



	//----------------------------------------------------------------
	ModUtility::ModUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	ModUtility::~ModUtility()
	{

	}

	//----------------------------------------------------------------
	bool ModUtility::importModFile()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("mod");
		vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

		if (strVec.empty())
		{
			return false;
		}
		if( !importModBegin( strVec ) )  //判断多个文件是否全是mod
		{
			return false;
		}
		if ( !importModData( strVec ) )  //支持导入多个mod文件
		{
			return false;
		}
		importModEnd( strVec[0] );

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::importModFile(const String& strFilePath)
	{
		vgMod::ModUtility::AddModelToScene( strFilePath );

		addModNodeToUI(NodeManager::getSingleton().getModItemList(), strFilePath);

		return true;
	}
	
	//----------------------------------------------------------------
	bool ModUtility::importVgFile( const String& strFilePath )
	{
		unsigned int uiUpdateTime = vgGlobal::SceneFileUtility::getUpdateTime();

		if ( !vgMod::ModUtility::readSceneFromVG( strFilePath ,uiUpdateTime) )
		{
			return false;
		}

		addNodeToUI(strFilePath);

		return true;
	}
	
	//----------------------------------------------------------------
	bool ModUtility::addNodeToUI( const string& strFilePath )
	{

		HTREEITEM hRootNodeUI = NULL;
		int indexSubType = 0;

		NodePtrPackage* pNodePackage = NodeManager::getSingleton().getNodeItemList();

		for (NodePtrPackage::iterator itr = pNodePackage->begin();
			itr != pNodePackage->end(); itr ++)
		{
			addNodeToUI( itr->first, &itr->second, strFilePath);
		}

		return true;
	}


	
	//----------------------------------------------------------------
	bool ModUtility::addNodeToUI( CategoryType catType, NodePtrVec* pNodeList, 
		const string& strFilePath )
	{
		HTREEITEM hRootNodeUI = NULL;

		for (NodePtrVec::iterator itrNode = pNodeList->begin();
			itrNode != pNodeList->end(); itrNode ++)
		{
			switch (catType)
			{
			case NODE_TYPE_BB:
				{
					hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_BILLBOARD_PLANT);
				}
				break;

			case NODE_TYPE_FOUNTAIN:	
				{
					hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_PARTICLE_FOUNTAIN);;
				}
				break;
			case NODE_TYPE_FIRE:		
				{
					hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_PARTICLE_FIRE);;
				}
				break;
			case NODE_TYPE_SMOKE:		
				{
					hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_PARTICLE_SMOKE);;
				}
				break;
			case NODE_TYPE_FLAG:
				{
					hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_PARTICLE_FLAG);;
				}
				break;


			case NODE_TYPE_MOD_EFFECT:
				{
					int nNodeType = (*itrNode)->getNodeType();
					
					if (nNodeType == VG_OBJECT_KEYFRAME)
					{
						hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_KEYFRAME);
					}
					else
					{
						EDynamicEntryType entryType = (EDynamicEntryType)(nNodeType + EFFECT_MOD_WATER - 10);

						hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(entryType);
					}
				}
				break;

			case NODE_TYPE_MOD:
				{
					vgMod::ObjFrameNode* pFrameNode = NULL;
					pFrameNode = dynamic_cast<vgMod::ObjFrameNode*>(*itrNode);

					if( pFrameNode->getTriggerFlag() )
					{//触发器
						hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(EFFECT_MOD_TRIGGER);
					}
					else if( pFrameNode->hasKeyFrame() )
					{
						hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_KEYFRAME);
					}
					else
					{
						hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(MODEL_MOD);
					}

				}
				break;

			default:
				break;
			}//switch

			vgKernel::Renderer* pRenderer = dynamic_cast<vgKernel::Renderer*>( *itrNode );
			if ( !pRenderer )
			{
				continue;
			}
			pRenderer->setName( (*itrNode)->GetName() );

			//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pRenderer );
			vgBaseEntry* entry = (vgBaseEntry*)rendererToEntry( pRenderer );


			vgMod::ObjFrameNode* pFrameNode = NULL;
			pFrameNode = dynamic_cast<vgMod::ObjFrameNode*>(*itrNode);
			if( catType == NODE_TYPE_MOD 
				&&  pFrameNode 
				&& !pFrameNode->getTriggerFlag() 
				&& !pFrameNode->hasKeyFrame()
				)
			{//普通MOD
				String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
					strFilePath );
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
		}//for




		return true;
	}

	
	//----------------------------------------------------------------
	bool ModUtility::exportVgFile( const String& strFilePath )
	{
		unsigned int uiUpdateTime = vgGlobal::SceneFileUtility::getUpdateTime();
		return	vgMod::ModUtility::saveSceneToVG( strFilePath,uiUpdateTime );
	}

	
	//----------------------------------------------------------------
	bool ModUtility::responseLButtonDown( UINT nFlags, CPoint point )
	{
		NodePtrVec	tempNodes;

		int nMode = vgMod::ModMisc::getSingleton().getCurrentMode();
		switch ( nMode )
		{
		case VG_STATUS_PLANT_TREE:
			{
				tempNodes = vgMod::NodeManager::getSingleton().addTree(point);
				break;
			}
		case VG_STATUS_PLANT_IN_LINE:
			{
				vgMod::ModMisc::getSingleton().addPlantPosition(point);
				break;
			}

		case VG_STATUS_DYNBILLBOARD_GENERATE:
			{
				tempNodes = vgMod::NodeManager::getSingleton().addDyanamicBillboard(point);
				break;
			}

		case VG_STATUS_FOUNTAIN:
			{
				tempNodes = vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_FOUNTAIN);
				break;
			}
		case VG_STATUS_FIRE:
			{
				tempNodes = vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_FIRE);
				break;
			}
		case VG_STATUS_SMOKE:
			{
				tempNodes = vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_SMOKE);
				break;
			}
		case VG_STATUS_FLAG:
			{
				tempNodes = vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_FLAG);
				break;
			}

		default:
			break;

		}

		// ui
		if ( tempNodes.empty() )
		{
			return false;
		}

		CategoryType nCat = tempNodes[0]->getCategory();
		
		addNodeToUI( nCat, &tempNodes, "");

		return true;
	}

	
	//----------------------------------------------------------------
	bool ModUtility::responseLButtonDblClk( UINT nFlags, CPoint point, CWnd* pwnd )
	{		
		int nMode = vgMod::ModMisc::getSingleton().getCurrentMode();
		switch ( nMode )
		{
		case VG_STATUS_PLANT_IN_LINE:
			{
				//创建距离设置对话框
				bool status;
				VGMSGBOX( status = vgMod::ModMisc::getSingleton().getDlgTreeDis()->createAndShowDlg(); );
				if ( !status )
				{
					//创建失败则清空坐标点数组
					vgMod::ModMisc::getSingleton().getPlantPosForDrawLine()->clear();
					vgMod::ModMisc::getSingleton().clearTreeDisPosVec();

					return false;
				}

				//按距离对话框中输入的距离值计算产生的billboard树，并加入渲染队列
				NodePtrVec	tempNodes = 
					vgMod::NodeManager::getSingleton().addTreeInLine();
				
				//清空用于画线的坐标点数组
				vgMod::ModMisc::getSingleton().getPlantPosForDrawLine()->clear();
				

#if 0
				int status;
				VGMSGBOX( status = vgMod::ModMisc::getSingleton().
				getDlgTreeDis()->DoModal(); );

				if( status )
				{
					NodePtrVec	tempNodes
					 = vgMod::NodeManager::getSingleton().addTreeInLine();

					// ui
					if ( tempNodes.empty() )
					{
						return false;
					}

					CategoryType nCat = tempNodes[0]->getCategory();

					addNodeToUI( nCat, &tempNodes, "");
				}
				else
				{
					Vector3Vec* pVector3Vec = ModMisc::getSingleton().getPlantPosVec();

					pVector3Vec->clear();
				}

				vgMod::ModMisc::getSingleton().setCurrentMode( 1 );
#endif
				break;
			}
		default:
			break;
		}//switch
		
		return true;
	}

	
	//----------------------------------------------------------------
	bool ModUtility::responseLButtonUp( UINT nFlags, CPoint point )
	{

		return true;
	}

	
	//----------------------------------------------------------------
	bool ModUtility::convertSelectedObjectToEffectNode( int nEffectType )
	{
		ModItemPtrVec	tempMods;

		switch ( nEffectType )
		{
		case VG_WATER:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToWaterNode();
				break;
			}

		case VG_GLASS:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToGlassNode();
				break;
			}

		case VG_AVINODE:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToAviNode();
				break;
			}

		case VG_MIRROR:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToMirrorNode();
				break;
			}

		case VG_METAL:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToMetalNode();
				break;
			}

		case VG_BRIGHTFLOOR:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToFloorNode();
				break;
			}

		case VG_DYNAMICTEXNODE:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToDynamicTexNode();
				break;
			}

		case VG_SKYBOX:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToSkyboxNode();
				break;
			}

		case VG_AUTOBUILD:
			{
				tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToAutoBuildNode();
				return true;
				break;
			}

		default:
			break;

		}
		
		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	
	//----------------------------------------------------------------
	vgKernel::AbstractEntry* ModUtility::rendererToEntry( vgKernel::Renderer* renderer )
	{
		vgKernel::RendererType type = 
			renderer->getType();

		vgBaseEntry* ret = NULL;

		vgMod::ObjFrameNode*	pObjFrameNode = NULL;

		switch( type )
		{
			// Mod 
		case vgMod::RENDERER_TYPE_MODOJBECT:
			pObjFrameNode = dynamic_cast<vgMod::ObjFrameNode*>(renderer);
			//assert( pObjNode != NULL );
			if( pObjFrameNode && pObjFrameNode->hasKeyFrame() )
			{
				ret = new vgMovingEntry<vgMod::ObjFrameNode>( pObjFrameNode );
			}
			else
			{
				vgMod::ObjectNode* pObjNode = dynamic_cast<vgMod::ObjectNode*>(renderer);

				ret = new vgMod::vgObjectEntry( pObjNode );
			}
			break;


		case vgMod::RENDERER_TYPE_BILLBOARD:
			ret = new vgMod::vgBillboardEntry((vgMod::BillboardNode*) renderer);
			break;

		case vgMod::RENDERER_TYPE_DYNAMICBILLBOARD:
			ret = new vgMod::vgDynamicBillboardEntry((vgMod::DynamicBillboardNode*) renderer);
			break;

		case vgMod::RENDERER_TYPE_PARTICLE:
			ret = new vgMod::vgParticleEntry( (vgMod::vgParticle*)renderer );
			break;


		case vgMod::RENDERER_TYPE_GPUSPECIAL_WARTER:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::WaterNode>( (vgMod::WaterNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_SKYNODE:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::SkyboxNode>( (vgMod::SkyboxNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_MIRROR:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::MirrorNode>( (vgMod::MirrorNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_METAL:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::MetalNode>( (vgMod::MetalNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_FLOOR:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::BrightfloorNode>( (vgMod::BrightfloorNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_AVI:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::AviNode>( (vgMod::AviNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_GLASS:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::GlassNode>( (vgMod::GlassNode*)renderer );
			break;


		//case vgAutoBuild::RENDERER_TYPE_AUTOBUILD:
		//	ret = new vgCore::vgAutoBuildEntry((vgAutoBuild::AutoBuildNode*)renderer);
		//	break;

		default:
			break;
		}

		return ret;
	}

	
	//----------------------------------------------------------------
	bool ModUtility::importVgFileDirectly( const String& strFilePath )
	{
		unsigned int uiUpdateTime = vgGlobal::SceneFileUtility::getUpdateTime();

		if ( vgMod::ModUtility::readSceneFromVGDirectly( strFilePath ,uiUpdateTime) )
		{
			return false;
		}

		return true;
	}

	
	//----------------------------------------------------------------
	bool ModUtility::exportVgFileDirectly( const String& strFilePath )
	{
		unsigned int uiUpdateTime = vgGlobal::SceneFileUtility::getUpdateTime();

		return	vgMod::ModUtility::saveSceneToVGDirectly( strFilePath,uiUpdateTime );
	}

	bool ModUtility::exportVgImgFile(const String& strFilePath )
	{
		vgMod::ModUtility::saveVGIMG(strFilePath);

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::addModNodeToUI( ModItemPtrVec* pNodeList , const string& strFilePath)
	{

		HTREEITEM hRootNodeUI = NULL;

		for (ModItemPtrVec::iterator itrNode = pNodeList->begin();
			itrNode != pNodeList->end(); itrNode ++)
		{
			//	加入界面
			vgKernel::Renderer*	pRenderer = dynamic_cast<vgKernel::Renderer*>( *itrNode );
			if(!pRenderer)
			{
				return false;
			}
			pRenderer->setName( (*itrNode)->GetName() );

			//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pRenderer );
			vgBaseEntry* entry = (vgBaseEntry*)rendererToEntry( pRenderer );

			vgMod::ObjFrameNode* pFrameNode = NULL;
			pFrameNode = dynamic_cast<vgMod::ObjFrameNode*>(*itrNode);
			if ( pFrameNode->hasKeyFrame() )
			{
				//hRootNodeUI = vgUI::UIController::getSingleton().GetRootKeyframe();
				hRootNodeUI = vgUI::UIController::getSingleton().getEntryRootItemByType(ANIMATION_KEYFRAME);
				vgUI::UIController::getSingleton().AddNode( hRootNodeUI, entry);
			}
			else
			{
				String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
					strFilePath );

				hRootNodeUI	= vgUI::UIController::getSingleton().getEntryRootItemByType(MODEL_MOD);
				vgUI::UIController::getSingleton().AddNode( shortname, entry ,hRootNodeUI);
			}

			if (hRootNodeUI != NULL)
			{
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootNodeUI );
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootNodeUI);
			}
		}//for



		return true;
	}


	//----------------------------------------------------------------
	bool ModUtility::importModBegin( const vgKernel::StringVector& strFilePaths )
	{
		//------------------------------------------
		// 开始导入
		//------------------------------------------
		if( strFilePaths.empty() )
			return false;

		//确保所有文件的扩展名都是mod
		String ext = "";
		vgKernel::StringVector::const_iterator itr = strFilePaths.begin();
		vgKernel::StringVector::const_iterator itr_end = strFilePaths.end();
		for ( itr; itr != itr_end; ++itr )
		{
			ext = vgKernel::StringUtility::getFileExtension( *itr );
			if ( ext != "mod" )
			{
				AfxMessageBox("文件类型不正确，请打开.mod文件!");
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
	bool ModUtility::importModData( const vgKernel::StringVector& strFilePaths )
	{
		for (vgKernel::StringVector::const_iterator itr = strFilePaths.begin();
			itr != strFilePaths.end() ; itr ++)
		{
			if ( !vgMod::ModUtility::AddModelToScene( *itr ) )
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

			addModNodeToUI( NodeManager::getSingleton().getModItemList(), *itr );

		}
		
		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::importModEnd( const String& strFilePath )
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
	bool ModUtility::convertToWater()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToWaterNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToGlass()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToGlassNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToMirror()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToMirrorNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToMetal()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToMetalNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToBrightFloor()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToFloorNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToSkybox()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToSkyboxNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToAviTex()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToAviNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToDynTex()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToDynamicTexNode();

		NodePtrVec	tempNodes;
		for(ModItemPtrVec::iterator itr = tempMods.begin();
			itr != tempMods.end(); itr ++)
		{
			tempNodes.push_back(*itr);

			NodeManager::getSingleton().appendNode( *itr, true);
		}

		addNodeToUI( NODE_TYPE_MOD_EFFECT, &tempNodes, "");

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::convertToAutoBuild()
	{
		ModItemPtrVec	tempMods;
		tempMods = vgMod::ModEffectConvertor::convertSelectedObjectToAutoBuildNode();

		return true;
	}

	//----------------------------------------------------------------
	bool ModUtility::cloneAutoBuildObj()
	{
		if (vgKernel::SelectManager::getSingleton().getSelectedItems().size() == 0)
		{
			return false;
		}

		vgKernel::Renderer *pRenderer = vgKernel::SelectManager::getSingleton().getSelectedItems().front();

		if (pRenderer->getType() == vgAutoBuild::RENDERER_TYPE_AUTOBUILD)
		{
			vgAutoBuild::AutoBuildNode *pNewNode = new vgAutoBuild::AutoBuildNode;

			vgAutoBuild::AutoBuildNode *pSrcNode = dynamic_cast<vgAutoBuild::AutoBuildNode*>(pRenderer);

			if (pSrcNode == NULL)
			{
				return false;
			}

			pNewNode->cloneFromAutobuildNode(pSrcNode);

			vgAutoBuild::AutoBuildManager::getSingleton().addAutoBuildNode(pNewNode);
		}

		vgKernel::SelectManager::getSingleton().clearSelection();

		return true;
	}

	//----------------------------------------------------------------
	void ModUtility::generateSolidBuild()
	{
		vgAutoBuild::AutoBuildManager::getSingleton().generateSolidBuild();
	}

	//----------------------------------------------------------------
	void ModUtility::generateMarkBuild()
	{
		vgAutoBuild::AutoBuildManager::getSingleton().generateMarkBuild();
	}

	//----------------------------------------------------------------
	bool ModUtility::getGenerateBuildFlag()
	{
		return vgAutoBuild::AutoBuildManager::getSingleton().getGenerateBuildFlag();
	}

	//----------------------------------------------------------------
	void ModUtility::setSaveMode( bool bMode )
	{
		vgMod::ModUtility::setSaveMode( bMode );
	}

	//----------------------------------------------------------------
	bool ModUtility::getSaveMode()
	{
		return vgMod::ModUtility::getSaveMode();
	}
	//----------------------------------------------------------------
	bool ModUtility::changeWaterDirection()
	{
		return vgMod::ModEffectConvertor::changeWaterDirec();
	}

	void ModUtility::enableAllLandMark(bool enable)
	{

		vgAutoBuild::AutoBuildManager::getSingleton().setAllMarkEnable(enable);
	}

	bool ModUtility::getAllLandMarkFlag()
	{
		return vgAutoBuild::AutoBuildManager::getSingleton().getAllMarkEnable();
	}
}//namespace vgXXX
