
#include <vgStableHeaders.h>
#include <vgMod/vgNodeManager.h>

#include <vgMod/vgModUtility.h>
#include <vgMod/vgModMisc.h>
#include <vgKernel/vgkRendererManager.h>

#include <vgBillBoard.h>
#include <vgEffect/vgParticle.h>
#include <vgEffect/vgFountain.h>
#include <vgEffect/vgSmoke.h>
#include <vgEffect/vgFire.h>
#include <vgEffect/vgFlag.h>
#include <vgEffect/vgDynamicBillBoardNode.h>

#include <vgDlgTreeSet.h>
#include <vgDlgTreeDis.h>

#include <vgPhys/vgphCollisionObject.h>
#include <vgPhys/vgphPhysManager.h>


#include <vgEntry/vgEntryFactory.h>


#include "vgMod/vgobjframenode.h"


namespace vgMod {

	//----------------------------------------------------------------
	void	NodeManager::setDefault()
	{
		vector<CategoryType>	types;
		types.push_back(NODE_TYPE_MOD);
		types.push_back(NODE_TYPE_BB);
		types.push_back(NODE_TYPE_PARTICLE);
		types.push_back(NODE_TYPE_FOUNTAIN);
		types.push_back(NODE_TYPE_FIRE);
		types.push_back(NODE_TYPE_SMOKE);
		types.push_back(NODE_TYPE_FLAG);
		types.push_back(NODE_TYPE_MOD_EFFECT);

		for (vector<CategoryType>::iterator itr = types.begin();
			itr != types.end(); itr ++)
		{
			m_nodeAll.insert( std::make_pair( *itr , NodePtrVec() ));
		}

	}

	//----------------------------------------------------------------
	void	NodeManager::reset()
	{
		uninitBeforeOpenGLDestroy();

		setDefault();
	}

	//----------------------------------------------------------------
	NodeAbsPtrVec* NodeManager::getSelectNodeItemIndexList()
	{
		return &m_selectNodeItemIndexList;
	}

	//----------------------------------------------------------------
	NodeAbsPtrVec* NodeManager::getNodeItemIndexList()
	{
		return &m_nodeItemIndexList;
	}

	//----------------------------------------------------------------
	ModItemPtrVec* NodeManager::getModItemList()
	{
		return &m_modItemListTemp;
	}

	
	//----------------------------------------------------------------
	NodePtrPackage*	NodeManager::getNodeItemList()
	{
		return &m_nodeAll;
	}


	
	//----------------------------------------------------------------
	NodePtrVec*	NodeManager::getNodeItemList(
		const CategoryType& type ,
		const bool& add_if_needed )
	{
		NodePtrPackage::iterator iter = m_nodeAll.find( type );

		if ( iter != m_nodeAll.end() )
		{
			// 此时含有相应的队列,只要返回这个队列即可.
			return &iter->second;
		}

		if ( add_if_needed == false )
		{
			return NULL;
		}

		m_nodeAll.insert( std::make_pair( type , NodePtrVec() ));


		return &m_nodeAll[type];
	}
		
	//----------------------------------------------------------------
	void	NodeManager::render()
	{
#if 0
		if(m_modItemList.empty() )
			return;

		static struct TraverseVecForRender renderfunc;

		for_each( m_modItemList.begin() , 
			m_modItemList.end() , 
			renderfunc );
#endif
	}

	
	//----------------------------------------------------------------
	bool	NodeManager::onDeleteRenderer( vgKernel::Renderer *render )
	{
		if ( render->getType() != RENDERER_TYPE_MODOJBECT 
			&& render->getType() != RENDERER_TYPE_BILLBOARD 
			&& render->getType() != RENDERER_TYPE_PARTICLE
			&& render->getType() != RENDERER_TYPE_DYNAMICBILLBOARD)
		{
			return false;
		}

//		vgMod::TriggerManager::getSingleton().deleteTrigger(render);

		vgPhys::CollisionObject* pObject = dynamic_cast<vgPhys::CollisionObject*>(render);
		vgPhys::PhysMananger::getSingleton().removeCollisionObject(pObject);

		Node* pNode = dynamic_cast<Node*>(render);
		if( pNode!=NULL )
		{
			deleteNodeItem(pNode);
		}

		return true;
	}

	
	//----------------------------------------------------------------
	bool	NodeManager::deleteNodeItem(Node* pNode)
	{
		if ( pNode == NULL )
		{
			return false;
		}

		NodePtrVec* pNodeItemList = getNodeItemList( pNode->getCategory(), false);

		assert( pNodeItemList!=NULL );

		NodePtrVec::iterator find_res = find( pNodeItemList->begin(),pNodeItemList->end(),pNode );
		if ( find_res == pNodeItemList->end() )
		{
			return false;
		}


		NodeAbsPtrVec::iterator itr = m_nodeItemIndexList.begin();
		for( ;itr != m_nodeItemIndexList.end(); itr ++ )
		{
			if( (*itr)->getNodeData() == pNode )
				break;			
		}

		if ( itr == m_nodeItemIndexList.end() )
		{
			return false;
		}		
		
		delete *itr;
		m_nodeItemIndexList.erase( itr );

		delete pNode;
		pNodeItemList->erase( find_res );

		return true;
	}

	
	//----------------------------------------------------------------
	void	NodeManager::appendNode( Node* pNode , const CategoryType& type)
	{
		NodeAbstract * pNodeAbs=new NodeAbstract();

		ModUtility::generateNodeIndexFromNode( pNode, &pNodeAbs);

		m_nodeItemIndexList.push_back(pNodeAbs);

		NodePtrVec* pNodeList = getNodeItemList( type, true);
		
		pNodeList->push_back(pNode);
	}

	//----------------------------------------------------------------
	NodePtrVec NodeManager::addDyanamicBillboard( CPoint &point )
	{

		NodePtrVec tempNodes;

		String filepath = ModMisc::getSingleton().getDlgDynBillboard()->m_DtxFilePath.GetBuffer(0);

		if (filepath.empty() == true)
		{
			MessageBox(NULL, "设置中的文件路径参数为空." , "提示", MB_OK );
			return tempNodes;
		}

		Vector3 pos; 
		vgKernel::Vec3 pt3D = vgKernel::Math::trans2DPointTo3DVec(point.x, point.y);
		pos = pt3D;

		DynamicBillboardNode *dynbill;

		dynbill = new DynamicBillboardNode();

		dynbill->m_Position = pos;

		dynbill->m_prePositon = pos;

		dynbill->m_width = ModMisc::getSingleton().getDlgDynBillboard()->m_dynwidth;

		dynbill->m_height = ModMisc::getSingleton().getDlgDynBillboard()->m_dynheight;

		dynbill->m_StrDtxPath = ModMisc::getSingleton().getDlgDynBillboard()->m_DtxFilePath.GetBuffer(0);

		dynbill->m_StrDtx_basename = dynbill->m_StrDtxPath.substr(
			dynbill->m_StrDtxPath.find_last_of("\\/") + 1 , String::npos );

		dynbill->Initialize();

		dynbill->ComputeBoundBox();


		//	 特效名字///////////////////////////////////////
		//int k = GetNodeId();
		int k = getNodeItemList(NODE_TYPE_FOUNTAIN, true)->size();
		char buffer[6];
		itoa(k,buffer,10);
		String	strbillboardName(dynbill->m_name);
		strbillboardName += '*';
		strbillboardName += buffer;
		strcpy_s(dynbill->m_name, 19, strbillboardName.c_str());

		appendNode(dynbill, NODE_TYPE_FOUNTAIN);

		vgKernel::RendererManager::getSingleton().addRenderer( dynbill );

		tempNodes.push_back(dynbill);

		return	tempNodes;

	}

	//----------------------------------------------------------------
	NodePtrVec	NodeManager::addTree(CPoint &point)
	{
		Vector3 pp ;//= Trans2DTo3D(point);
		
		vgKernel::Vec3 pt3D = vgKernel::Math::trans2DPointTo3DVec(point.x, point.y);

		pp = pt3D;
		
		return	addTree(pp);
	}

	
	//----------------------------------------------------------------
	NodePtrVec	NodeManager::addTree( const Vector3 &pos )
	{
		NodePtrVec tempNodes;

		BillboardNode *tempbill;

		tempbill = new BillboardNode();

		tempbill->m_Position = pos;

		tempbill->m_texturename = ModMisc::getSingleton().getDlgTreeSet()->GetTexturePath();

		tempbill->m_width = ModMisc::getSingleton().getDlgTreeSet()->GetTreeWidth();

		tempbill->m_height = ModMisc::getSingleton().getDlgTreeSet()->GetTreeHeight();


		tempbill->m_prePositon = pos;

		tempbill->ComputeBoundBox();

		tempbill->Initialize();

		//	 特效名字///////////////////////////////////////
		int k = getNodeItemList(NODE_TYPE_BB, true)->size();
		//m_oCurrentScene.vgLayerList[0]->m_uiBillboardCount;
		
		char buffer[6];
		itoa(k,buffer,10);
		
		String	strParticleName(tempbill->m_name);
		strParticleName += '*';
		strParticleName += buffer;
		strcpy_s(tempbill->m_name, 19, strParticleName.c_str());

		appendNode(tempbill, NODE_TYPE_BB);
		
		vgKernel::RendererManager::getSingleton().addRenderer( tempbill );
		
		tempNodes.push_back(tempbill);

		return	tempNodes;


	}

	
	//----------------------------------------------------------------
	NodePtrVec	NodeManager::addTreeInLine()
	{
		NodePtrVec tempNodes;

		float dis = ModMisc::getSingleton().getDlgTreeDis()->getTreeDis();

		Vector3Vec* pVector3Vec = ModMisc::getSingleton().getDlgTreeDis()->getPlantPosVec();

		Vector3Vec::iterator iter = pVector3Vec->begin();
		Vector3Vec::iterator iter_end = pVector3Vec->end();

		if ( dis == 0.0f )
		{
			MessageBox( NULL , "树间间距太小!" , "提示" , MB_OK );
			pVector3Vec->clear();
			return	tempNodes;
		}

		// 所点的点不够的情况，直接返回。
		if ( pVector3Vec->empty() || 
			pVector3Vec->size() == 1 )
		{
			pVector3Vec->clear();
			return	tempNodes;
		}


		for ( ; iter != iter_end - 1  ; ++ iter )
		{
			Vector3& pos1 = *iter;
			Vector3& pos2 = *(iter+1);

			Vector3 direction = pos2 - pos1 ;

			int n = direction.length() / dis;

			direction.normalise();

			for ( int i = 0 ; i < n ; ++ i )
			{
				Vector3 aimpos = pos1 + direction * i * dis;

				NodePtrVec	pRenderers = addTree( aimpos );
				tempNodes.insert( tempNodes.end(), pRenderers.begin(), pRenderers.end() );

				//add by ZhouZY 2009-11-6 21:07
				m_plantTreeList.insert( m_plantTreeList.end(), pRenderers.begin(), pRenderers.end() );  

			}
		}

		//pVector3Vec->clear();

		return	tempNodes;
	}

	
	//----------------------------------------------------------------
	bool NodeManager::removeTreeInLine()
	{
		if ( m_plantTreeList.empty() )
		{
			return true;
		}

		NodePtrVecItr iter = m_plantTreeList.begin();
		NodePtrVecItr iter_end = m_plantTreeList.end();

		for ( ; iter != iter_end; iter++ )
		{	
			vgKernel::Renderer* pRender = dynamic_cast<vgKernel::Renderer*>(*iter);
			vgKernel::RendererManager::getSingleton().deleteRenderer( pRender );
		}

		//清空树节点数组
		m_plantTreeList.clear();

		return true;
	}

	//----------------------------------------------------------------
	NodePtrVec	NodeManager::addParticleToScene(CPoint &point, 
		E_PARTICLE_TYPE	particleType)
	{
		NodePtrVec tempNodes;
	
		Vector3 pp ;//= Trans2DTo3D(point);

		vgKernel::Vec3 pt3D = vgKernel::Math::trans2DPointTo3DVec(point.x, point.y);

		pp = pt3D;

		vgParticle*		pParticle = NULL;

		int  nIndexParticle = 0;
		switch(particleType)
		{
		case	PARTICLE_FOUNTAIN:
			pParticle = new vgFountain();
			break;

		case	PARTICLE_FIRE:
			pParticle = new vgFire();
			break;

		case	PARTICLE_SMOKE:
			pParticle = new vgSmoke();
			break;

		case	PARTICLE_FLAG:
			pParticle = new vgFlag();
			break;

		default:
			break;
		}

		CategoryType catType =  CategoryType(particleType) ;
		pParticle->setCategory( catType );


		pParticle->SetPosition(pp);

		pParticle->m_prePositon = pp;
		pParticle->ComputeBoundBox();
		pParticle->Initialize();

		//	 特效名字///////////////////////////////////////
		nIndexParticle = getNodeItemList( catType, true)->size();
		char buffer[6];
		itoa(nIndexParticle,buffer,10);
		String	strParticleName(pParticle->m_name);
		strParticleName += '*';
		strParticleName += buffer;
		strcpy_s(pParticle->m_name, 19, strParticleName.c_str());

		//AddParticle(pParticle, particleType);
		appendNode(pParticle, catType);


		vgKernel::RendererManager::getSingleton().addRenderer( pParticle );
	

		tempNodes.push_back(pParticle);

		return	tempNodes;
	}

	//----------------------------------------------------------------
	void NodeManager::uninitBeforeOpenGLDestroy()
	{
		/*for (NodeAbsPtrVec::iterator itr = m_nodeItemIndexList.begin();
			itr != m_nodeItemIndexList.end(); itr ++)
		{
			if ((*itr) != NULL)
			{
				delete (*itr);

				(*itr) = NULL;
			}
		}

		m_nodeItemIndexList.clear();*/

		clearNodeIndexList( &m_nodeItemIndexList );
		clearNodeIndexList( &m_selectNodeItemIndexList );

		for ( NodePtrPackage::iterator itr1 = m_nodeAll.begin();
			itr1 != m_nodeAll.end(); itr1++)
		{
			NodePtrVec *pp = &itr1->second;

			if ( pp != NULL )
			{
				for (NodePtrVec::iterator itr2 = pp->begin();
					itr2 != pp->end(); itr2 ++)
				{
					if ( (*itr2) != NULL )
					{
						delete (*itr2);

						(*itr2) = NULL;
					}

				}

				pp->clear();
			}
		}

		m_nodeAll.clear();

	}

	//----------------------------------------------------------------
	void NodeManager::initAfterOpenGLSetup()
	{
		
	}

	//----------------------------------------------------------------
	void NodeManager::clearNodeIndexList( NodeAbsPtrVec* nodeList )
	{
		NodeAbsPtrVec::iterator itr = nodeList->begin();

		for ( ; itr != nodeList->end(); itr++ )
		{
			if ( (*itr) != NULL )
			{
				delete (*itr);
				(*itr) = NULL;
			}
		}

		nodeList->clear();
	}
}// end of namespace vgMod
