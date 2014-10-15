



#include <vgStableHeaders.h>
#include <vgMod/vgModEffectConvertor.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>
#include <vgMod/vgNodeManager.h>

#include <vgDlgWater.h>
#include <vgDlgGlass.h>
#include <vgDlgAviNode.h>
#include <vgDlgMirror.h>
#include <vgDlgMetal.h>
#include <vgDlgBrightfloor.h>
#include <vgDlgAutoBuild.h>
#include <vgDlgDynamicTexNode.h>

#include <vgEffect/vgWaterNode.h>
#include <vgEffect/vgSkyboxNode.h>
#include <vgEffect/vgAviNode.h>
#include <vgEffect/vgMirrorNode.h>
#include <vgEffect/vgMetalNode.h>
#include <vgEffect/vgBrightfloorNode.h>
#include <vgAutoBuild/vgAutoBuildNode.h>
#include <vgEffect/vgDynamicTexNode.h>

#include <vgDeprecatedMFCDLL/DlgWaterChangeUV.h>

namespace vgMod {

	String	ModEffectConvertor::m_strProDataPath;

	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToEffectNode2()
	{
		ModItemPtrVec	result_nodes;
		ModItemPtrVec	origin_nodes;

		if (vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true)
		{
			MessageBox( NULL , "请选择物体" , "警告" , MB_OK );
			return result_nodes; 
		}


		std::deque<vgKernel::Renderer*>::iterator iter 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().begin();

		std::deque<vgKernel::Renderer*>::iterator iter_end 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().end();


		for ( ; iter!= iter_end ; ++iter )
		{


			if ( (*iter) == NULL )
			{
				MessageBox(NULL , "选择错误!" , "警告", MB_OK );

				continue;
			}

			if (	!((*iter)->getType() == RENDERER_TYPE_MODOJBECT )  )
			{
				ostringstream ErrorMes;

				ErrorMes<< (*iter)->getName() 
					<<"并非MOD物体，无法转换！将滤除该物体，继续转换下一个...";

				AfxMessageBox(ErrorMes.str().c_str());

				continue;
			}



			ObjFrameNode* obj_node = (ObjFrameNode*)(*iter);


			WaterNode* effect_node = new WaterNode();

			bool convert_result = effect_node->cloneFromObjectNode( obj_node );

			//effect_node->setCategory( NODE_TYPE_MOD_EFFECT );

			if ( convert_result == false )
			{
				assert(0&&"不应该发生这个错误");
				MessageBox(NULL , "转换失败!" , "Error", MB_OK );
				return result_nodes;
			}

			result_nodes.push_back( effect_node );
			origin_nodes.push_back( obj_node );

			vgKernel::RendererManager::getSingleton().addRenderer( effect_node );

		}

		if (result_nodes.size() == 0)
		{
			return result_nodes;
		}
		VG_CHECK_OPENGL_ERROR();


		DlgWater dd( result_nodes );
		int dlg_result = dd.DoModal();


		if ( dlg_result == IDCANCEL )
		{
			assert( result_nodes.size() == origin_nodes.size() );

			vgKernel::SelectManager::getSingleton().getSelectedItems().clear();

			for (int i =0; i != result_nodes.size(); ++i)
			{
				vgKernel::SelectManager::getSingleton().getSelectedItems().push_back( 
					result_nodes[i] );
			}

			{
				vgKernel::SelectManager::getSingleton().deleteSelectedRenderers( false );
			}

			result_nodes.clear();

			return result_nodes;
		}

		//------------------------------------------
		// 开始遍历
		//------------------------------------------
		assert( result_nodes.size() == origin_nodes.size() );

		vgKernel::SelectManager::getSingleton().clearSelection();

		for (int i =0; i != origin_nodes.size(); ++i)
		{
			ObjectNode* obj_node = origin_nodes[i];
			vgKernel::SelectManager::getSingleton().getSelectedItems().push_back( obj_node );
		}
		//删除原来结点
		{
			vgKernel::SelectManager::getSingleton().deleteSelectedRenderers( false );
		}

		assert( vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true );


		vgKernel::RendererManager::getSingleton().invalidate();

		return result_nodes;
	}	


	
	//--------------------------------------------------------------------------------------------
	template <typename EFFECT_TYPE , typename DLG_TYPE/*, IMAGETYPE EFFECT_IMAGE_TYPE */>
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToEffectNode()
	{
		ModItemPtrVec	result_nodes;
		ModItemPtrVec	origin_nodes;

		if (vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true)
		{
			MessageBox( NULL , "请选择物体" , "警告" , MB_OK );
			return result_nodes; 
		}


		std::deque<vgKernel::Renderer*>::iterator iter 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().begin();

		std::deque<vgKernel::Renderer*>::iterator iter_end 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().end();


		for ( ; iter!= iter_end ; ++iter )
		{


			if ( (*iter) == NULL )
			{
				MessageBox(NULL , "选择错误!" , "警告", MB_OK );

				continue;
			}


			//ObjectNode* obj_node = (ObjectNode*)(*iter);
			//if (obj_node->TYPE != VG_OBJECT)
			if ( !((*iter)->getType() == RENDERER_TYPE_MODOJBECT )  )
			{
				MessageBox(NULL , "选择错误!非Object物体." , "警告", MB_OK );
				continue;
			}


			EFFECT_TYPE* effect_node = new EFFECT_TYPE();

			ObjFrameNode* obj_node = (ObjFrameNode*)(*iter);
			bool convert_result = effect_node->cloneFromObjectNode( obj_node );

			//effect_node->setCategory( NODE_TYPE_MOD_EFFECT );

			if ( convert_result == false )
			{
				assert(0&&"不应该发生这个错误");
				MessageBox(NULL , "转换失败!" , "Error", MB_OK );
				return result_nodes;
			}

			result_nodes.push_back( effect_node );
			origin_nodes.push_back( obj_node );

			vgKernel::RendererManager::getSingleton().addRenderer( effect_node );

		}

		if (result_nodes.size() == 0)
		{
			return result_nodes;
		}
		VG_CHECK_OPENGL_ERROR();


		DLG_TYPE dd( result_nodes );
		int dlg_result = dd.DoModal();


		if ( dlg_result == IDCANCEL )
		{
			assert( result_nodes.size() == origin_nodes.size() );

			vgKernel::SelectManager::getSingleton().getSelectedItems().clear();

			for (int i =0; i != result_nodes.size(); ++i)
			{
				//EFFECT_TYPE* obj_node = result_nodes[i];
				vgKernel::SelectManager::getSingleton().getSelectedItems().push_back( result_nodes[i] );
			}

			{
				vgKernel::SelectManager::getSingleton().deleteSelectedRenderers( false );
			}

			result_nodes.clear();

			return result_nodes;
		}

		//------------------------------------------
		// 开始遍历
		//------------------------------------------
		assert( result_nodes.size() == origin_nodes.size() );

		vgKernel::SelectManager::getSingleton().clearSelection();

		for (int i =0; i != origin_nodes.size(); ++i)
		{
			ObjectNode* obj_node = origin_nodes[i];
			vgKernel::SelectManager::getSingleton().getSelectedItems().push_back( obj_node );
		}
		//删除原来结点
		{
			vgKernel::SelectManager::getSingleton().deleteSelectedRenderers( false );
		}

		assert( vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true );


		vgKernel::RendererManager::getSingleton().invalidate();

		return result_nodes;
	}




	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToWaterNode()
	{
		//return convertSelectedObjectToEffectNode2();
		return convertSelectedObjectToEffectNode<WaterNode, DlgWater/*, IMG_WATER*/>();
	}	

	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToGlassNode()
	{
		return convertSelectedObjectToEffectNode<GlassNode, DlgGlass/*, IMG_GLASS*/>();
	}

	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToAviNode()
	{
		return convertSelectedObjectToEffectNode<AviNode, DlgAviNode/*, IMG_AVINODE*/>();
	}

	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToMirrorNode()
	{
		return convertSelectedObjectToEffectNode<MirrorNode, DlgMirror /*, IMG_MIRROR*/>();
	}

	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToMetalNode()
	{
		return convertSelectedObjectToEffectNode<MetalNode, DlgMetal/* , IMG_METAL*/>();
	}


	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToFloorNode()
	{
		return convertSelectedObjectToEffectNode<BrightfloorNode, DlgBrightfloor/*, IMG_BRIGHTFLOOR*/>();
	}


	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToDynamicTexNode()
	{
		return convertSelectedObjectToEffectNode<DynamicTexNode, DlgDynamicTexNode/*, IMG_DYNAMICTEX*/>();
	}


	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToAutoBuildNode()
	{
		ModItemPtrVec	result_nodes;
		ModItemPtrVec	origin_nodes;


		if (vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true)
		{
			MessageBox( NULL , "请选择物体" , "警告" , MB_OK );
			return result_nodes; 
		}


		vgDlgAutoBuild dlg;

		if (dlg.DoModal() == IDCANCEL)
		{
			return result_nodes;
		}


		std::deque<vgKernel::Renderer*>::iterator iter 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().begin();

		std::deque<vgKernel::Renderer*>::iterator iter_end 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().end();


		for ( ; iter!= iter_end ; ++iter )
		{


			if ( (*iter) == NULL )
			{
				MessageBox(NULL , "选择错误!" , "警告", MB_OK );

				continue;
			}


			ObjectNode* obj_node = (ObjectNode*)(*iter);
			ObjectNode* effect_node;
			bool convert_result = false;

			if (obj_node->TYPE == VG_OBJECT)
			{
				effect_node = new ObjectNode();
				convert_result = effect_node->cloneFromObjectNode( obj_node );
				if (vgKernel::RendererManager::getSingleton().deleteRenderer(effect_node))
				{
					AfxMessageBox("Bug here");
				}

			}
			else 
			{
				MessageBox(NULL , "选择错误!非Object物体." , "警告", MB_OK );
				return result_nodes;
			}

			if ( convert_result == false )
			{
				assert(0&&"不应该发生这个错误");
				MessageBox(NULL , "转换失败!" , "Error", MB_OK );
				return result_nodes;
			}

			result_nodes.push_back( effect_node );
			origin_nodes.push_back( obj_node );

			//vgKernel::RendererManager::getSingleton().addRenderer( effect_node );
		}

		if (result_nodes.size() == 0)
		{
			return result_nodes;
		}
		VG_CHECK_OPENGL_ERROR();

		//------------------------------------------
		// 开始遍历
		//------------------------------------------
		assert( result_nodes.size() == origin_nodes.size() );

		vgKernel::SelectManager::getSingleton().clearSelection();

		for (int i =0; i != origin_nodes.size(); ++i)
		{
			ObjectNode* obj_node = origin_nodes[i];
			//obj_node->setVisible(false);

			vgKernel::SelectManager::getSingleton().getSelectedItems().push_back( obj_node );
		}
		//删除原来结点
		{
			if (vgKernel::SelectManager::getSingleton().getSelectedItems().size() == 0)
			{
				assert(0);
			}
			vgKernel::SelectManager::getSingleton().deleteSelectedRenderers( false );
		}

		assert( vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true );


		vgAutoBuild::AutoBuildNode* result_node2 = new vgAutoBuild::AutoBuildNode();

		if (result_nodes.size() == 2)
		{
			// 无底部情况
			result_nodes.push_back(NULL);
		}
		else if (result_nodes.size() == 1)
		{
			// 只有中部情况
			result_nodes.push_back(NULL);
			result_nodes.push_back(NULL);
			result_nodes[1] = result_nodes[0];

			result_nodes[0] = NULL;
		}

		result_node2->constructFromObjectNodes(result_nodes[0], result_nodes[1], result_nodes[2]);

		result_node2->setUnit(dlg.GetUnit());
		
		//UI
		vgAutoBuild::AutoBuildManager::getSingleton().addAutoBuildNode(result_node2);

		

		vgKernel::RendererManager::getSingleton().invalidate();

		return result_nodes;
	}


	
	//--------------------------------------------------------------------------------------------
	ModItemPtrVec	ModEffectConvertor::convertSelectedObjectToSkyboxNode()//chunyongma//天空球特殊
	{
		ModItemPtrVec	result_nodes;
		ModItemPtrVec	origin_nodes;

		if (vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true)
		{
			MessageBox( NULL , "请选择物体" , "警告" , MB_OK );
			return result_nodes; 
		}



		std::deque<vgKernel::Renderer*>::iterator iter 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().begin();

		std::deque<vgKernel::Renderer*>::iterator iter_end 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().end();


		for ( ; iter!= iter_end ; ++iter )
		{


			if ( (*iter) == NULL )
			{
				MessageBox(NULL , "选择错误!" , "警告", MB_OK );

				continue;
			}


			ObjectNode* obj_node = (ObjectNode*)(*iter);
			if (obj_node->TYPE != VG_OBJECT)
			{
				MessageBox(NULL , "选择错误!非Object物体." , "警告", MB_OK );
				continue;
			}

			SkyboxNode* effect_node = new SkyboxNode();

			bool convert_result = effect_node->cloneFromObjectNode( obj_node );

			//effect_node->setCategory( NODE_TYPE_MOD_EFFECT );

			effect_node->_oldPosX = 
				//QuadtreeSceneManager::getSingleton().GetCurrentCamera().getCurrentPosition().x;
				vgCam::CamManager::getSingleton().getCurrentPosition().x;
			effect_node->_oldPosZ = 
				//QuadtreeSceneManager::getSingleton().GetCurrentCamera().getCurrentPosition().z;
				vgCam::CamManager::getSingleton().getCurrentPosition().z;

			effect_node->setCamera(
				vgCam::CamManager::getSingletonPtr() );

			if ( convert_result == false )
			{
				assert(0&&"不应该发生这个错误");
				MessageBox(NULL , "转换失败!" , "Error", MB_OK );
				return result_nodes;
			}

			result_nodes.push_back( effect_node );
			origin_nodes.push_back( obj_node );

			vgKernel::RendererManager::getSingleton().addRenderer( effect_node );

		}

		//------------------------------------------
		// 开始遍历
		//------------------------------------------

		assert( result_nodes.size() == origin_nodes.size() );

		vgKernel::SelectManager::getSingleton().getSelectedItems().clear();

		for (int i =0; i != origin_nodes.size(); ++i)
		{
			ObjectNode* obj_node = origin_nodes[i];
			vgKernel::SelectManager::getSingleton().getSelectedItems().push_back( obj_node );
		}
		//删除原来结点
		{
			vgKernel::SelectManager::getSingleton().deleteSelectedRenderers( false );
		}

		assert( vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true );

		vgKernel::RendererManager::getSingleton().invalidate();

		return result_nodes;
	}

	
	//--------------------------------------------------------------------------------------------
	String& ModEffectConvertor::getProDataPath()
	{
		return m_strProDataPath;
	}

	
	//--------------------------------------------------------------------------------------------
	void ModEffectConvertor::setProDataPath( String& path )
	{
		m_strProDataPath = path;
	}
	
	//--------------------------------------------------------------------------------------------
	bool ModEffectConvertor::changeWaterDirec()
	{
		if (vgKernel::SelectManager::getSingleton().getSelectedItems().empty() == true)
		{
			MessageBox( NULL , "请选择物体" , "警告" , MB_OK );
			return false; 
		}

		std::vector<vgMod::WaterNode*> _nodeList;
		vgMod::WaterNode* _currentNode;

		std::deque<vgKernel::Renderer*>::iterator iter 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().begin();

		std::deque<vgKernel::Renderer*>::iterator iter_end 
			= vgKernel::SelectManager::getSingleton().getSelectedItems().end();


		for ( ; iter!= iter_end ; ++iter )
		{

			// 测试发现得到的水面节点的Type 也是RENDERER_TYPE_MODOJBECT,
			// 即使转换成Mod::WaterNode之后，得到的Type也是RENDERER_TYPE_MODOJBECT
			// 没有得到vgMod::RENDERER_TYPE_GPUSPECIAL_WATER 的时候,
			// 无法正确的判断水面节点，只能判断是不是Mod 节点
			if ( !((*iter)->getType() == vgMod::RENDERER_TYPE_MODOJBECT 
				||(*iter)->getType() == vgMod::RENDERER_TYPE_GPUSPECIAL_WARTER)  )
			{
				MessageBox(NULL , "选择错误!非水面节点." , "警告", MB_OK );
				return false;
			}
 			else
 			{
 				_currentNode = (vgMod::WaterNode*)(*iter);
 				_nodeList.push_back(_currentNode);
 			}

		}

		DlgWaterChangeUV dlg( _nodeList ); // 弹出修改水流方向对话框
		dlg.DoModal();

		return true;
	}

	//--------------------------------------------------------------------------------------------
}// end of namespace vgMod
