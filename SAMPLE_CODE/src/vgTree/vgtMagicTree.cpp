
/************************************************************************/
/*	vgtMagicTree.cpp	——神奇树类的实现                                 */
/************************************************************************/

#include "vgStableHeaders.h"

#if 0
#include "vgTree/vgtMagicTree.h"


#include "vgRootEntry.h"
#include "vgBaseEntry.h"

namespace vgTree{

	vgMagicTree::vgMagicTree(E_DIVIDE_TYPE	eDefaultDivideType /*	= DIVIDE_NONE */ )
		:m_eDefaultDivideType(eDefaultDivideType)
		,m_uTreeDepthMax(0), m_uTreeLeafCount(0), m_uTreeQuadCount(0)
		,BOUNDINGBOXZOOM(0.04f)
		,m_bUseTree(true)
		,m_uLevelOfFirstLeaf(UINT_MAX)
		,m_uNodeCountVisible(0), m_uFaceCountVisible(0)
		,m_uDitheringLevel(0), m_uLargeNodeCount(0)
	{	
		_allRenderers = NULL;

		_frustum = vgCam::CamManager::getSingleton().getCurrentFrustum();
	}//vgMagicTree(构造神奇树)

	vgMagicTree::~vgMagicTree()
	{
		_mReset();
	}//~vgMagicTree(析构神奇树)	
	
	//  继承自AbstractTree--------------------------------------------------------
	void vgMagicTree::setRendererPackage( vgKernel::RendererPackage* package )
	{
		_allRenderers = package;
	}
	void vgMagicTree::invalidate()
	{
		if (_allRenderers->empty())
		{
			return;
		}
		_mBuildWholeTree(_allRenderers, DIVIDE_QUAD, 0.01);
		//_mBuildWholeTree(_allRenderers, DIVIDE_NONE);
	}
	void vgMagicTree::getVisibleSet( vgKernel::RendererPackage* visible_set )
	{
		assert( visible_set != NULL );
		assert( _allRenderers != NULL );
		assert( _frustum != NULL );

		_mClearVisibleSet();
		_mCollectVisibleSet( visible_set);
		
	}
	//void vgMagicTree::getVisibleSet( vgKernel::RendererPackage* visible_set )
	//{
	//	assert( visible_set != NULL );
	//	assert( _allRenderers != NULL );
	//	assert( _frustum != NULL );

	//	assert( _allRenderers->size() == visible_set->size() );
	//	
	//	int	nNodeCount = m_oRootTreeNode.GetNodePropertyPtr()->GetNodeCount();

	//	if (0 == nNodeCount)
	//	{
	//		return;
	//	}
	//	vgKernel::RendererPackage*	pAllRenderers = m_oRootTreeNode.GetNodePropertyPtr()->GetNodeIndex();
	//	vgKernel::RendererPackage::iterator ipac = pAllRenderers->begin();
	//	vgKernel::RendererPackage::iterator ipac_end = pAllRenderers->end();

	//	vgKernel::RendererPackage::iterator outipac = visible_set->begin();

	//	for ( ; ipac != ipac_end ; ++ipac , ++ outipac )
	//	{
	//		assert( outipac != visible_set->end() );

	//		RendererQueue* queue = ipac->second;
	//		RendererQueue* visible_queue = outipac->second;

	//		assert( visible_queue->empty() == true );

	//		RendererQueue::iterator iter = queue->begin();
	//		RendererQueue::iterator iter_end = queue->end();

	//		for ( ; iter != iter_end ; ++iter )
	//		{
	//			Renderer* curleaf = *iter;

	//			if( _frustum->testBoxInFrustum( curleaf->getBoundingBox() ) == true )
	//			{
	//				vgKernel::Vec3 viewpos = 
	//					vgCam::CamManager::getSingleton().getCurrentPosition();

	//				float distance = curleaf->setDistanceToViewer( viewpos );

	//				if ( distance <= 100.0f )
	//				{
	//					visible_queue->push_front( curleaf );
	//				}
	//				else
	//				{
	//					visible_queue->push_back( curleaf );
	//				}

	//				m_uNodeCountVisible	++;
	//				m_uFaceCountVisible	+= curleaf->getNumOfTriangles();

	//				//m_mapTreeBox.insert( m_pairTreeBox( (E_TREENODE_TYPE)m_oRootTreeNode.GetNodePropertyPtr()->GetNodeType(),
	//				//	m_oRootTreeNode.GetNodePropertyPtr()->GetBoundingBox() )  );	
	//			}
	//		}
	//	}

	//}


	void vgMagicTree::renderTreeStruct(bool bDrawStruct /*= false*/)
	{
		vector<BoundingBox>::iterator iter		= m_vTreeBox.begin();
		vector<BoundingBox>::iterator iterEnd	= m_vTreeBox.end();
		for (; iter!= iterEnd; iter++)
		{
			iter->render();
		}
		/*m_bDrawStruct = bDrawStruct;
		_mRenderObject(true, false, bDrawStruct);*/
	}
	void vgMagicTree::switchTreeStruct( )
	{
		m_bUseTree = !m_bUseTree;
	}
	//----------------------------------------------------------------
	bool vgMagicTree::isUseTree()
	{
		return	m_bUseTree;
	}


	E_RETURN_TYPE		vgMagicTree::_mBuildWholeTree(
		vgKernel::RendererPackage*	pCurrentRendererQueue		/* = NULL		*/,
		E_DIVIDE_TYPE		eDefaultDivideType	/* = DIVIDE_NONE*/,
		float				filterBigNode		/*= 0.1*/,		
		unsigned int	uDitheringLevel			/*= 50	*/	)
	{

		// 析构上一次生成的树，从根节点到叶子节点
		_mReset();

		// 构造大节点空队列
		/*m_pLargeNode = *_allRenderers;
		for (m_itrMap = m_pLargeNode.begin(); 
			m_itrMap != m_pLargeNode.end(); m_itrMap++)
		{
			m_itrMap->second->clear();
		}*/

		m_eDefaultDivideType	= eDefaultDivideType;
		m_uDitheringLevel		= uDitheringLevel;
		m_fFilterBigNode		= filterBigNode;

		// 由当前场景计算树根节点信息 
		m_pCurrentTreeNode = InitializeRootNode(pCurrentRendererQueue);

		if (0 == m_oRootTreeNode.GetNodePropertyPtr()->GetNodeCount())
		{
			return RETURN_ABORT;
		}

		// 将大节点从根节点出来，原因是大节点影响构树
		m_tempLoopCount = 0;
		SeparateLargeNodeFromRoot();

		// 由根节点判断是否需要向下划分子树，并判定划分方式（1，2，4叉）
		if( IsNeedDivide( &m_oRootTreeNode, &m_eDefaultDivideType) )
		{
			Divide( &m_oRootTreeNode, m_eDefaultDivideType );
		}

		// 不再需要细分子树，或者细分完成，说明成功构造神奇树
		//if(m_bDrawStruct)
		//	PrintTreeStruct(&m_oRootTreeNode);

		// 由收集的大物体队列计算大物体树根节点信息
		m_pCurrentTreeNode = CreateRootNodeLarge();
		//TestTraslateLargeNode();

		// 由根节点判断是否需要向下划分子树，并判定划分方式（1，2，4叉）
		/*if( IsNeedDivide( m_pCurrentTreeNode, &m_eDefaultDivideType) )
		{
		Divide( m_pCurrentTreeNode, m_eDefaultDivideType );
		}*/
		// 不再需要细分子树，或者细分完成，说明成功构造神奇树的大节点树，接着返回
		//if(m_bDrawStruct)
		//	PrintTreeStruct(&m_oRootTreeNodeLarge);


		return	RETURN_SUCCESS;

	}//BuildWholeTree(构建整棵神奇树)



	
	void			vgMagicTree::_mRenderObject(bool bUseTree/* = false*/, bool bRenderNodeBox/* = false*/, bool bRenderTreeBox/* = false*/)
	{
		//m_bUseTree	= bUseTree;
		if( !m_oRootTreeNode.GetNodePropertyPtr()->GetNodeCount() )
			return;
		//_mClearVisibleSet();
		//_mCollectVisibleSet();
		RenderObject(bRenderNodeBox, bRenderTreeBox);
	}
	
	unsigned int	vgMagicTree::_mCollectVisibleSet( vgKernel::RendererPackage* visible_set )
	{

#ifdef	_DEBUG
		m_vTreeBox.push_back(m_oRootTreeNode.GetNodePropertyPtr()->GetBoundingBox());
		m_vTreeBox.push_back(m_oRootTreeNodeLarge.GetNodePropertyPtr()->GetBoundingBox());
#endif

		m_tempNodeCount	= 0;

		if( 
			m_eDefaultDivideType != DIVIDE_NONE
			&& (TREENODE_LEAF != m_oRootTreeNode.GetNodePropertyPtr()->GetNodeType())
			)
		{
			CollectVisibleSet( visible_set, &m_oRootTreeNode  );
		}
		else
		{
			CollectVisibleSetLinear( visible_set );
		}

		CollectVisibleSetLinear( visible_set, &m_oRootTreeNodeLarge);

		return	m_uNodeCountVisible = visible_set->size();
	}//_mCollectVisibleSet()


	
	void			vgMagicTree::_mClearVisibleSet( void )
	{
		m_uFaceCountVisible	= 0;
		m_uNodeCountVisible	= 0;
		
		m_vNodeVisible.clear();
		m_mapTreeBox.clear();

		m_vTreeBox.clear();
	}


	
	E_RETURN_TYPE	vgMagicTree::_mReset(MagicTreeNodePtr  pParentNode /*= NULL*/)
	{
	
		if( pParentNode )
		{
			switch( pParentNode->GetNodePropertyPtr()->GetNodeType() )
			{
			case TREENODE_QUAD1:
				pParentNode->Parent()->Quad1() = NULL;
				break;
			case TREENODE_QUAD2:
				pParentNode->Parent()->Quad2() = NULL;
				break;
			case TREENODE_QUAD3:
				pParentNode->Parent()->Quad3() = NULL;
				break;
			case TREENODE_QUAD4:
				pParentNode->Parent()->Quad4() = NULL;
				break;
			default:
				break;
			} 
			delete pParentNode;
			pParentNode = NULL;
		}
		else
		{
			m_oRootTreeNode.Reset();		

			m_pCurrentTreeNode	= NULL;
			m_uTreeDepthMax		= 0;
			m_uTreeQuadCount	= 0;
			m_uTreeLeafCount	= 0;
			 
			m_uNodeCountVisible	= 0;
			m_uFaceCountVisible	= 0;
			m_uLargeNodeCount	= 0;

			m_vLargeNodeID.clear();
			m_pLargeNode.clear();
//			ResetTreeStruct();
		}
		return	RETURN_SUCCESS;
	}//Reset(重置神奇树，释放所有节点，包括根节点)


	
	void			vgMagicTree::RenderObject(bool bRenderNodeBox/* = false*/, bool bRenderTreeBox/* = false*/)
	{	
		
		unsigned int  	nNodeID			= 0;
		Renderer*		pCurrentNode	= NULL;
		Vector3			oColor;
		Vector3			oColorInit	= Vector3(0.25f,0.5f,0.25f);

//		for ( m_itrDeque  = m_vNodeVisible.begin();
//			m_itrDeque != m_vNodeVisible.end();
//			m_itrDeque ++ )
//		{
//			pCurrentNode	= *m_itrDeque ;
//			if (!pCurrentNode)
//			{
//				continue;
//			}		
////			pCurrentNode->render();
//
//			if( bRenderNodeBox )
//			{// 线框包围盒
//				oColor	= Vector3(1.0f, 1.0f, 1.0f) - oColorInit;
////				RenderFrameBox( pCurrentNode->GetNodePropertyPtr()->GetBoundingBox(), oColor);
//			}
//		}//for(节点可视集)


		// 树包围盒
		if( bRenderTreeBox  )
		{
			for ( m_iteratorMapTreeBox	= m_mapTreeBox.begin();
				m_iteratorMapTreeBox	!= m_mapTreeBox.end();
				m_iteratorMapTreeBox ++ )
			{
				switch( m_iteratorMapTreeBox->first )
				{
				case TREENODE_QUAD1:
					oColorInit = Vector3(1.0f, 1.0f, 1.0f);
					break;

				case TREENODE_QUAD2:
					oColorInit = Vector3(1.0f, 0.0f, 0.0f);
					break;

				case TREENODE_QUAD3:
					oColorInit = Vector3(0.0f, 1.0f, 0.0f);
					break;

				case TREENODE_QUAD4:
					oColorInit = Vector3(0.0f, 0.0f, 1.0f);
					break;

				default:
					oColorInit = Vector3(0.25f, 0.5f, 0.25f);
					break;
				}//switch
				RenderFrameBox( m_iteratorMapTreeBox->second, oColorInit);
			}//for
		}//if

	}//_mRenderObject(渲染一帧 进行)




	


	void	vgMagicTree::RenderFrameBox	(BoundingBox	oBox, Vector3 oColor)
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_1D);
		glPushMatrix();

		//glColor3f(1,0,0);
		//glColor3f(_colorRed, _colorYel, _colorBlu);
		glColor3f( oColor.x, oColor.y, oColor.z );

		glLineWidth(1.0);

		Vector3& m_max = oBox.maxPoint;
		Vector3& m_min = oBox.minPoint;

		glBegin(GL_LINES);
		{

			glVertex3f( m_max.x , m_max.y , m_max.z );
			glVertex3f( m_min.x , m_max.y , m_max.z );

			glVertex3f( m_max.x , m_max.y , m_max.z );
			glVertex3f( m_max.x , m_min.y , m_max.z );

			glVertex3f( m_max.x , m_max.y , m_max.z );
			glVertex3f( m_max.x , m_max.y , m_min.z );

			glVertex3f( m_min.x , m_min.y , m_min.z );
			glVertex3f( m_max.x , m_min.y , m_min.z );

			glVertex3f( m_min.x , m_min.y , m_min.z );
			glVertex3f( m_min.x , m_max.y , m_min.z );

			glVertex3f( m_min.x , m_min.y , m_min.z );
			glVertex3f( m_min.x , m_min.y , m_max.z );

			glVertex3f( m_min.x , m_max.y , m_max.z );
			glVertex3f( m_min.x , m_max.y , m_min.z );

			glVertex3f( m_min.x , m_max.y , m_max.z );
			glVertex3f( m_min.x , m_min.y , m_max.z );


			glVertex3f( m_max.x , m_min.y , m_max.z );
			glVertex3f( m_max.x , m_min.y , m_min.z );

			glVertex3f( m_max.x , m_min.y , m_max.z );
			glVertex3f( m_min.x , m_min.y , m_max.z );

			glVertex3f( m_max.x , m_min.y , m_min.z );
			glVertex3f( m_max.x , m_max.y , m_min.z );

			glVertex3f( m_min.x , m_max.y , m_min.z );
			glVertex3f( m_max.x , m_max.y , m_min.z );
		}
		glEnd();

		//Vec3 center = getCenter();
		//glColor3f(0, 1, 0);
		//glTranslatef(center.x, center.y, center.z);
		//glutSolidSphere(5, 20, 20);

		glPopMatrix();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_1D);

	}
	E_RETURN_TYPE	vgMagicTree::NewbornChildren( 
		MagicTreeNodePtr	pParentNode	/* = NULL			*/,
		E_TREENODE_TYPE		eNodeType	/* = TREENODE_QUAD1234*/)
	{
		m_pCurrentTreeNode	=	pParentNode;
		switch( eNodeType )
		{
		case TREENODE_QUAD1234:
			NewbornChildren(pParentNode,TREENODE_QUAD1);
			NewbornChildren(pParentNode,TREENODE_QUAD2);
			NewbornChildren(pParentNode,TREENODE_QUAD3);
			NewbornChildren(pParentNode,TREENODE_QUAD4);
			break;

		case TREENODE_QUAD12:
			NewbornChildren(pParentNode,TREENODE_QUAD1);
			NewbornChildren(pParentNode,TREENODE_QUAD2);
			break;

		case TREENODE_QUAD1:
			AbandonChildren(pParentNode,TREENODE_QUAD1);
			pParentNode->Quad1()	=	new	MagicTreeNode(pParentNode,TREENODE_QUAD1 );
			break;

		case TREENODE_QUAD2:
			AbandonChildren(pParentNode,TREENODE_QUAD2);
			pParentNode->Quad2()	=	new	MagicTreeNode(pParentNode,TREENODE_QUAD2 );			
			break;

		case TREENODE_QUAD3:
			AbandonChildren(pParentNode,TREENODE_QUAD3);
			pParentNode->Quad3()	=	new	MagicTreeNode(pParentNode,TREENODE_QUAD3 );			
			break;

		case TREENODE_QUAD4:
			AbandonChildren(pParentNode,TREENODE_QUAD4);
			pParentNode->Quad4()	=	new	MagicTreeNode(pParentNode,TREENODE_QUAD4 );
			break;

		default:
			break;

		}//switch( 子树节点的类型 )

		return	RETURN_SUCCESS;
	}//GenerateFourSons(新生四个子结点)


	
	E_RETURN_TYPE	vgMagicTree::AbandonChildren(
		MagicTreeNodePtr	pParentNode	/* =	NULL*/ ,
		E_TREENODE_TYPE		eNodeType	/*=	TREENODE_QUAD1234*/  )
	{
		if( !pParentNode )
		{
			return	RETURN_ABORT;
		}

		switch( eNodeType )
		{
		case TREENODE_QUAD1234:
			AbandonChildren( pParentNode, TREENODE_QUAD1);
			AbandonChildren( pParentNode, TREENODE_QUAD2);
			AbandonChildren( pParentNode, TREENODE_QUAD3);
			AbandonChildren( pParentNode, TREENODE_QUAD4);
			break;

		case TREENODE_QUAD1:
			m_pCurrentTreeNode	= pParentNode->Quad1();
			if( m_pCurrentTreeNode )
			{
				delete	m_pCurrentTreeNode;
				m_pCurrentTreeNode = NULL;
			}
			break;

		case TREENODE_QUAD2:
			m_pCurrentTreeNode	= pParentNode->Quad2();
			if( m_pCurrentTreeNode )
			{
				delete	m_pCurrentTreeNode;
				m_pCurrentTreeNode = NULL;
			}
			break;

		case TREENODE_QUAD3:
			m_pCurrentTreeNode	= pParentNode->Quad3();
			if( m_pCurrentTreeNode )
			{
				delete	m_pCurrentTreeNode;
				m_pCurrentTreeNode = NULL;
			}
			break;

			m_pCurrentTreeNode	= pParentNode->Quad4();
			if( m_pCurrentTreeNode )
			{
				delete	m_pCurrentTreeNode;
				m_pCurrentTreeNode = NULL;
			}
			break;

		default:
		    break;		

		}//switch( 子树节点的类型 )	

		return	RETURN_SUCCESS;
	}//DeleteFourSons(递归析构子结点)



	
	
	// 计算并设置树根节点的属性信息,其中包含当前正在渲染的场景的所有节点数目、节点索引、总面数、包围盒信息	
	MagicTreeNodePtr	vgMagicTree::InitializeRootNode( vgKernel::RendererPackage*	pCurrentRendererQueue )
	{
		m_pCurrentTreeNode	= &m_oRootTreeNode;

		// 获取属性对象的指针，准备设置
		vgTreeNodeProp* m_pNodePropertyTemp	= m_pCurrentTreeNode->GetNodePropertyPtr();

		// 计算根节点各项信息，使用整个场景的全局信息
		m_pNodePropertyTemp->SetNodeIndex(pCurrentRendererQueue);
		m_pNodePropertyTemp->UpdateTreeProperty();

		// debug add by lss when 2008-10-17 12:38:53
		//m_vTreeBox.push_back(m_pNodePropertyTemp->GetBoundingBox());


		// 构造大节点空队列
		for (m_itrMap  = m_pLargeNode.begin(); 
			m_itrMap  != m_pLargeNode.end();
			m_itrMap++)
		{
			m_itrMap->second->clear();
		}	
		m_pLargeNode.clear();

		vgKernel::RendererType	renderType;
		for (m_itrMap  = _allRenderers->begin(); 
			m_itrMap  != _allRenderers->end();
			m_itrMap++)
		{
			renderType = m_itrMap->first;
			RendererPackage::iterator iter = m_pLargeNode.find( renderType );

			if ( iter == m_pLargeNode.end() )
			{
				RendererQueue* queueNew = new RendererQueue;
				m_pLargeNode.insert( std::make_pair( renderType , queueNew ) );
			}
		}
		CreateRootNodeLarge();

		return	m_pCurrentTreeNode;

	}//CreateRootNode(计算并设置树根节点)



	
	void	vgMagicTree::SeparateLargeNodeFromRoot()
	{
		m_bNeedRebuild = true;
		do
		{
			m_uLargeNodeCountPre	= 0;
			for (m_itrMap = m_pLargeNode.begin(); m_itrMap!=m_pLargeNode.end();
				m_itrMap++)
			{
				m_uLargeNodeCountPre += m_itrMap->second->size();
			}
			
			ExcludeLargeNodeFromRoot();
			if( IsNeedDivide( &m_oRootTreeNode, &m_eDefaultDivideType) )
			{
				Divide( &m_oRootTreeNode, m_eDefaultDivideType );
			}
		
			m_uLargeNodeCount	= 0;
			for (m_itrMap = m_pLargeNode.begin(); m_itrMap!=m_pLargeNode.end();
				m_itrMap++)
			{
				m_uLargeNodeCount += m_itrMap->second->size();
			}

			m_tempLoopCount ++;
		}while( (m_uLargeNodeCountPre != m_uLargeNodeCount) && (m_tempLoopCount < 2) );

		m_bNeedRebuild = false;
		return;
	}
	
	
	MagicTreeNodePtr	vgMagicTree::CreateRootNodeLarge()
	{
		m_pCurrentTreeNode	= &m_oRootTreeNodeLarge;
		
		// 获取属性对象的指针，准备设置
		vgTreeNodeProp* m_pNodePropertyTemp	= m_pCurrentTreeNode->GetNodePropertyPtr();
		m_pNodePropertyTemp->SetNodeIndex(&m_pLargeNode);

		m_pNodePropertyTemp->UpdateTreeProperty();

		//m_vTreeBox.push_back(m_pNodePropertyTemp->GetBoundingBox());


		return	m_pCurrentTreeNode;
	}
	
	E_RETURN_TYPE		vgMagicTree::IsNeedDivide( 
		MagicTreeNodePtr	pCurrentNode		/*	= NULL	*/,
		E_DIVIDE_TYPE*		eDefaultDivideType	/*	= NULL	*/)
	{
		unsigned int	nNodeCount;
		unsigned int	nFaceCount;

		BoundingBox	oBoundingBox;
		float	fLongEdge, fShortEdge,fTempSwap;

		// 获取当前根节点信息
		m_pCurrentTreeNode	= pCurrentNode;

		nNodeCount	= m_pCurrentTreeNode->GetNodePropertyPtr()->GetNodeCount();
		nFaceCount	= m_pCurrentTreeNode->GetNodePropertyPtr()->GetFaceCount();
		oBoundingBox= m_pCurrentTreeNode->GetNodePropertyPtr()->GetBoundingBox();


		// 不需要划分的条件成立，4种情况
		// 情况0，细分进入死循环（节点数不再减少），父节点设为叶子，结束
		if ( m_pCurrentTreeNode->Parent() && 
			nNodeCount	>= m_pCurrentTreeNode->Parent()->GetNodePropertyPtr()->GetNodeCount()*0.95  )
		//if ( m_pCurrentTreeNode->GetNodePropertyPtr()->GetTreeDepth() > 10)
		{
			m_pCurrentTreeNode->Parent()->FormatToLeaf();
			return	RETURN_ABORT;
		}
		
		// 情况1，当前树节点没有数据节点，重置该节点
		if( nNodeCount ==0 )
		{
			_mReset(m_pCurrentTreeNode);
			return	RETURN_FALSE;
		}

		// 情况2，当前节点不需细分，设为叶子
		if(   (*eDefaultDivideType	== DIVIDE_NONE) //	参数指定不需要划分
			||( nNodeCount			<= 3 )			//	当前树节点只含1个数据节点
			||( nFaceCount			<= /*10*/500 )		//	当前树节点面数小于500
			//||( pCurrentNode->GetNodePropertyPtr()->GetBoundingBox().getArea() < 1.0e2 )// 节点密集程度超过阈值
			//||( pCurrentNode->GetNodePropertyPtr()->GetTreeDepth() >= 0 )// 树深超过阈值
		  )
		{
			m_pCurrentTreeNode->GetNodePropertyPtr()->SetNodeType( TREENODE_LEAF); //细分结束，标记该节点为叶子节点
			return	RETURN_FALSE;
		}
		
		// 否则，需要划分并进一步明确划分方式（二叉、四叉）
		fLongEdge	= oBoundingBox.getSize().x ;
		fShortEdge	= oBoundingBox.getSize().z ;
		if( fLongEdge	< fShortEdge )
		{
			fTempSwap	= fLongEdge;
			fLongEdge	= fShortEdge;
			fShortEdge	= fTempSwap;
		}

		if( fLongEdge /fShortEdge > sqrt(2.0f) )
		{// 若长宽比 > 2^(1/2)=1.414f，则下一步细分方式设为二叉
			*eDefaultDivideType	=	DIVIDE_BINARY; 
			return	RETURN_TRUE;
		}
		else
		{// 若长宽比 <= 2^(1/2)=1.414f，则下一步细分方式设为四叉
			*eDefaultDivideType	=	DIVIDE_QUAD; 
			return	RETURN_TRUE;
		}//if(二叉)else(四叉)

	}//IsNeedDivide(是否需要继续细分子树)


	
	E_RETURN_TYPE		vgMagicTree::Divide(
		MagicTreeNodePtr	pParentNode			/*	= NULL			*/,
		E_DIVIDE_TYPE			eDefaultDivideType	/*	= DIVIDE_NONE	*/ )
	{
		m_pCurrentTreeNode	= pParentNode;

		switch(eDefaultDivideType)
		{
		case	DIVIDE_BINARY:
			// 根节点第一次划分生成2个分叉, 随后转成4叉至叶子节点
			DivideTwo(m_pCurrentTreeNode); 
			break;

		case	DIVIDE_QUAD:
			// 根节点第一次划分生成4个分叉，随后一直4叉至叶子节点
			DivideFour(m_pCurrentTreeNode);
			break;

		default:
			break;

		}//switch( 神奇数的构树类型 )
		
		return	RETURN_SUCCESS;
	}//Divide()


	

	E_RETURN_TYPE		vgMagicTree::DivideTwo(MagicTreeNodePtr  pParentNode)
	{
		MagicTreeNodePtr	m_pTreeNodeTemp1 = NULL;	// 临时节点指针
		MagicTreeNodePtr	m_pTreeNodeTemp2 = NULL;	// 临时节点指针

		// 由父节点生成2个子结点
		m_pCurrentTreeNode	= pParentNode;
		NewbornChildren(m_pCurrentTreeNode, TREENODE_QUAD12);
		m_pCurrentTreeNode	= pParentNode;


		// 获取父节点包围盒信息
		m_tempBoundingBox = m_pCurrentTreeNode->GetNodePropertyPtr()->GetBoundingBox();;
		Vector3			oBoxSize(m_tempBoundingBox.getSize() );

		// 均分四叉树时加入抖动因子
		srand( (unsigned long)time(NULL) );
		int		nRandDelta		=	rand()%m_uDitheringLevel - int(m_uDitheringLevel*0.5f);
		float	fDelta			=	0.5f + nRandDelta/1024.0f;

		// 计算并设置第一、二象限子树节点 m_pSubtreeQuad2 的包围盒
		BoundingBox		tempBox1(m_tempBoundingBox), tempBox2(m_tempBoundingBox);
		if ( oBoxSize.x > oBoxSize.z )
		{
			tempBox1.minPoint.x	= m_tempBoundingBox.minPoint.x + 
				m_tempBoundingBox.getSize().x * fDelta;
			tempBox2.maxPoint.x	= tempBox1.minPoint.x;
		} 
		else
		{
			tempBox1.minPoint.z	= m_tempBoundingBox.minPoint.z + 
				m_tempBoundingBox.getSize().z * fDelta;
			tempBox2.maxPoint.z	= tempBox1.minPoint.z;
		}

		m_pTreeNodeTemp1	=	m_pCurrentTreeNode->Quad1();
		m_pTreeNodeTemp1->GetNodePropertyPtr()->SetBoundingBox(tempBox1);	

		m_pTreeNodeTemp2	=	m_pCurrentTreeNode->Quad2();
		m_pTreeNodeTemp2->GetNodePropertyPtr()->SetBoundingBox(tempBox2);


		// 顺序遍历父节点中的场景数据节点，填充2个子树节点
		RendererQueue		vLargeNodeID;
		float				fNodeBoxArea		= 0.0f;
		float				fTreeBoxArea		= m_tempBoundingBox.getArea();
//		Vector3				oBoxSize	;
		unsigned int		nIndexSon			= 0;
		BoundingBox			oCurrentNodeBox	 ;
		
		vgKernel::RendererPackage*	vNodeIndex = m_pCurrentTreeNode->m_oTreeNodeProperty.GetNodeIndex();
		vgKernel::RendererPackage::iterator ipac = vNodeIndex->begin();
		vgKernel::RendererPackage::iterator ipac_end = vNodeIndex->end();

		m_itrMap = m_pLargeNode.begin();

		for ( ; ipac != ipac_end ; ++ipac ,m_itrMap++)
		{
			RendererQueue* pQueue = ipac->second;

			RendererQueue::iterator iter = pQueue->begin();
			RendererQueue::iterator iter_end = pQueue->end();

			for ( ; iter != iter_end ; ++iter )
			{

				// 判断该数据节点应该挂接到哪颗子树，根据该数据节点的包围盒信息
				oCurrentNodeBox = (*iter)->getBoundingBox();

				// 首先判断是不是大物体，然后判断中心点完全落在第一、二象限的某个
				fNodeBoxArea	= oCurrentNodeBox.getArea();
				oBoxSize		= oCurrentNodeBox.getSize();
				if ( 
					oBoxSize.y * oBoxSize.y / fNodeBoxArea < /*100.0f*/m_fFilterBigNode/*0.01f*//*.01f*/
					//|| (( fTreeBoxArea - fNodeBoxArea )/ fTreeBoxArea < 0.15f*(1+m_tempLoopCount)
					//&& m_bNeedRebuild)
					)
				{
					nIndexSon	= 0;
				}
				else if ( tempBox1.IsPoint3Include(oCurrentNodeBox.getCenter() ) )
				{
					nIndexSon	= 1;
				}
				else //if (  tempBox2.IsBoxInclude(oCurrentNodeBox.getCenter() ) )
				{
					nIndexSon	= 2;
				}

				// 挂接到以上判定的某颗具体子树，假如在边界上则两颗树分别挂接一次
				switch( nIndexSon )
				{
				case 0:
					m_itrMap->second->push_back( *iter );
					break;

				case 1:
					m_pTreeNodeTemp1->GetNodePropertyPtr()->PushNodeVector(*iter);
					break;

				case 2:
					m_pTreeNodeTemp2->GetNodePropertyPtr()->PushNodeVector(*iter);
					break;

				default:
					break;

				}//switch(该节点挂接在哪颗子树)
			}
		}//for(父节点包含的节点)

		m_pTreeNodeTemp1->GetNodePropertyPtr()->UpdateTreeProperty();
		m_pTreeNodeTemp2->GetNodePropertyPtr()->UpdateTreeProperty();


		// 以上完成1次二叉划分
		// --------------------------------------------------------------------------
		// 以下判断是否需要继续划分，需要则递归划分
		// 子树1
		E_RETURN_TYPE		eDivide ;
		eDivide = IsNeedDivide( m_pTreeNodeTemp1, &m_eDefaultDivideType );
		if( RETURN_TRUE == eDivide )
		{
			Divide( m_pTreeNodeTemp1, m_eDefaultDivideType );
		}
		else if (RETURN_ABORT == eDivide )
		{
			return	RETURN_ABORT;
		}

		// 子树2
		eDivide = IsNeedDivide( m_pTreeNodeTemp2, &m_eDefaultDivideType );
		if( RETURN_TRUE == eDivide )
		{
			Divide( m_pTreeNodeTemp2, m_eDefaultDivideType );
		}
		else if (RETURN_ABORT == eDivide )
		{
			return	RETURN_ABORT;
		}

		// 不再需要细分子树，或者细分完成，说明成功构造神奇树，接着返回
		return	RETURN_SUCCESS;

	}//DivideTwo


	
	E_RETURN_TYPE		vgMagicTree::DivideFour( MagicTreeNodePtr pParentNode)
	{
		MagicTreeNodePtr	m_pTreeNodeTemp1 = NULL;	// 临时节点指针
		MagicTreeNodePtr	m_pTreeNodeTemp2 = NULL;	// 临时节点指针
		MagicTreeNodePtr	m_pTreeNodeTemp3 = NULL;	// 临时节点指针
		MagicTreeNodePtr	m_pTreeNodeTemp4 = NULL;	// 临时节点指针

		// 由父节点生成4个子结点
		m_pCurrentTreeNode	= pParentNode;
		NewbornChildren(m_pCurrentTreeNode, TREENODE_QUAD1234);
		m_pCurrentTreeNode	= pParentNode;


		// 获取父节点包围盒信息
		m_tempBoundingBox = m_pCurrentTreeNode->GetNodePropertyPtr()->GetBoundingBox();;

		// 均分四叉树时加入抖动因子
		srand( (unsigned long)time(NULL) );	
		int		nRandDelta		=	rand()%m_uDitheringLevel - int(m_uDitheringLevel*0.5f);
		float	fDeltaX			=	0.5f + nRandDelta/1024.0f;

		nRandDelta				=	rand()%m_uDitheringLevel - int(m_uDitheringLevel*0.5f);
		float	fDeltaZ			=	0.5f + nRandDelta/1024.0f;


		// 计算四个子树节点的包围盒
		// 计算并设置第一象限子树节点 m_pSubtreeQuad1 的包围盒	, 
		// 第二、三、四象限子树的包围盒通过它在X轴或Z轴平移得到
		BoundingBox		tempBox1(m_tempBoundingBox);
		tempBox1.minPoint.x	= m_tempBoundingBox.minPoint.x + 
			m_tempBoundingBox.getSize().x * fDeltaX;
		tempBox1.minPoint.z	= m_tempBoundingBox.minPoint.z + 
			m_tempBoundingBox.getSize().z * fDeltaZ;

		m_pTreeNodeTemp1		= m_pCurrentTreeNode->Quad1();
		m_pTreeNodeTemp1->GetNodePropertyPtr()->SetBoundingBox(tempBox1);	


		// 计算并设置第二象限子树节点 m_pSubtreeQuad2 的包围盒
		BoundingBox		tempBox2(tempBox1);
		tempBox2.maxPoint.x	= tempBox1.minPoint.x;
		tempBox2.minPoint.x	= m_tempBoundingBox.minPoint.x;

		m_pTreeNodeTemp2	=	m_pCurrentTreeNode->Quad2();
		m_pTreeNodeTemp2->GetNodePropertyPtr()->SetBoundingBox(tempBox2);


		// 计算并设置第三象限子树节点 m_pSubtreeQuad3 的包围盒
		BoundingBox		tempBox3(tempBox2);		
		tempBox3.maxPoint.z	= tempBox2.minPoint.z;
		tempBox3.minPoint.z	= m_tempBoundingBox.minPoint.z;

		m_pTreeNodeTemp3	=	m_pCurrentTreeNode->Quad3();
		m_pTreeNodeTemp3->GetNodePropertyPtr()->SetBoundingBox(tempBox3);


		// 计算并设置第四象限子树节点 m_pSubtreeQuad4 的包围盒
		BoundingBox		tempBox4(tempBox3);		
		tempBox4.minPoint.x	= tempBox3.maxPoint.x;
		tempBox4.maxPoint.x	= m_tempBoundingBox.maxPoint.x;

		m_pTreeNodeTemp4	=	m_pCurrentTreeNode->Quad4();
		m_pTreeNodeTemp4->GetNodePropertyPtr()->SetBoundingBox(tempBox4);

		// 顺序遍历父节点中的场景数据节点，填充4个子树节点
		unsigned int		nIndexSon			= 0;
		BoundingBox 		oCurrentNodeBox	;
		float				fTreeBoxArea		= m_tempBoundingBox.getArea() ;	
		float				fNodeBoxArea;
		RendererQueue			vLargeNodeID;
		Vector3				oBoxSize;

		RendererPackage*	vNodeIndex = m_pCurrentTreeNode->m_oTreeNodeProperty.GetNodeIndex();
		vgKernel::RendererPackage::iterator ipac =		vNodeIndex->begin();
		vgKernel::RendererPackage::iterator ipac_end = 	vNodeIndex->end();

		m_itrMap = m_pLargeNode.begin();

		for ( ; ipac != ipac_end ; ++ipac ,m_itrMap++)
		{
			RendererQueue* pQueue = ipac->second;

			RendererQueue::iterator iter = pQueue->begin();
			RendererQueue::iterator iter_end = pQueue->end();

			for ( ; iter != iter_end ; ++iter )
			{

				// 判断该数据节点应该挂接到哪颗子树，根据该数据节点的包围盒信息
				oCurrentNodeBox = (*iter)->getBoundingBox();

				// 首先判断是不是大物体，然后判断中心点完全落在第一、二象限的某个
				fNodeBoxArea	= oCurrentNodeBox.getArea();
				oBoxSize		= oCurrentNodeBox.getSize();
				if ( 
					oBoxSize.y * oBoxSize.y / fNodeBoxArea < /*100.0f*/m_fFilterBigNode/*0.01f*//*.01f*/
					//|| (( fTreeBoxArea - fNodeBoxArea )/ fTreeBoxArea < 0.15f*(1+m_tempLoopCount)
					//&& m_bNeedRebuild)
					)
				{					
					nIndexSon	= 0;
				}
				else if ( tempBox1.IsPoint3Include(oCurrentNodeBox.getCenter() ) )
				{
					nIndexSon	= 1;
				}
				else if ( tempBox2.IsPoint3Include(oCurrentNodeBox.getCenter() ) )
				{
					nIndexSon	= 2;
				}
				else if ( tempBox3.IsPoint3Include(oCurrentNodeBox.getCenter() ) )
				{
					nIndexSon	= 3;
				}
				else //if ( tempBox4.IsPoint3Include(oCurrentNodeBox.getCenter() ) )
				{
					nIndexSon	= 4;
				}

				// 挂接到以上判定的某颗具体子树，假如在边界上则两颗树分别挂接一次，假如在跨越四个象限则挂接四次
				switch( nIndexSon )
				{
				case 0:
					m_itrMap->second->push_back( *iter );
					break;

				case 1:
					m_pTreeNodeTemp1->GetNodePropertyPtr()->PushNodeVector(*iter);
					break;

				case 2:
					m_pTreeNodeTemp2->GetNodePropertyPtr()->PushNodeVector(*iter );
					break;

				case 3:
					m_pTreeNodeTemp3->GetNodePropertyPtr()->PushNodeVector(*iter);
					break;

				case 4:
					m_pTreeNodeTemp4->GetNodePropertyPtr()->PushNodeVector(*iter );
					break;

				default:
					break;

				}//switch( 该节点挂接在哪颗子树 )
			}

		}//for(父节点包含的节点)

		// 更新 子结点包围盒 及 父节点id队列
		m_pTreeNodeTemp1->GetNodePropertyPtr()->UpdateTreeProperty();
		m_pTreeNodeTemp2->GetNodePropertyPtr()->UpdateTreeProperty();
		m_pTreeNodeTemp3->GetNodePropertyPtr()->UpdateTreeProperty();
		m_pTreeNodeTemp4->GetNodePropertyPtr()->UpdateTreeProperty();


		// 以上完成1次四叉划分
		// --------------------------------------------------------------------------
		// 以下判断是否需要继续划分，需要则递归划分
		// 子树1
		E_RETURN_TYPE		eDivide ;
		eDivide = IsNeedDivide( m_pTreeNodeTemp1, &m_eDefaultDivideType );
		if( RETURN_TRUE == eDivide )
		{
			Divide( m_pTreeNodeTemp1, m_eDefaultDivideType );
		}
		else if (RETURN_ABORT == eDivide )
		{
			return	RETURN_ABORT;
		}

		// 子树2
		eDivide = IsNeedDivide( m_pTreeNodeTemp2, &m_eDefaultDivideType );
		if( RETURN_TRUE == eDivide )
		{
			Divide( m_pTreeNodeTemp2, m_eDefaultDivideType );
		}
		else if (RETURN_ABORT == eDivide )
		{
			return	RETURN_ABORT;
		}

		// 子树3
		eDivide = IsNeedDivide( m_pTreeNodeTemp3, &m_eDefaultDivideType );
		if( RETURN_TRUE == eDivide )
		{
			Divide( m_pTreeNodeTemp3, m_eDefaultDivideType );
		}
		else if (RETURN_ABORT == eDivide )
		{
			return	RETURN_ABORT;
		}

		// 子树4
		eDivide = IsNeedDivide( m_pTreeNodeTemp4, &m_eDefaultDivideType );
		if( RETURN_TRUE == eDivide )
		{
			Divide( m_pTreeNodeTemp4, m_eDefaultDivideType );
		}
		else if (RETURN_ABORT == eDivide )
		{
			return	RETURN_ABORT;
		}

		// 不再需要细分子树，或者细分完成，说明成功构造神奇树，接着返回
		if (! (	pParentNode->Quad1() || pParentNode->Quad2() 
			||	pParentNode->Quad3() || pParentNode->Quad4() )	)
		{
			pParentNode->GetNodePropertyPtr()->SetNodeType( TREENODE_LEAF );
		}
		return	RETURN_SUCCESS;

	}//DivideFour





	
	void		vgMagicTree::CollectVisibleSetLinear( vgKernel::RendererPackage* visible_set, MagicTreeNodePtr	pParentNode/* = NULL*/)
	{
		if(!pParentNode)
		{
			pParentNode = &m_oRootTreeNode;
		}
		BoundingBox	oRootBox;

		Renderer*	nNodeID	= NULL ;
		vgKernel::RendererPackage*	vNodeIndex = pParentNode->m_oTreeNodeProperty.GetNodeIndex();
		vgKernel::RendererPackage::iterator ipac = vNodeIndex->begin();
		vgKernel::RendererPackage::iterator ipac_end = vNodeIndex->end();
		
		vgKernel::RendererPackage::iterator outipac = visible_set->begin();

		for ( ; ipac != ipac_end ; ++ipac  , ++ outipac)
		{
			RendererQueue* pQueue = ipac->second;
			RendererQueue* visible_queue = outipac->second;

			RendererQueue::iterator iter = pQueue->begin();
			RendererQueue::iterator iter_end = pQueue->end();

			for ( ; iter != iter_end ; ++iter )
			{
				nNodeID			= *iter;
				oRootBox		= nNodeID->getBoundingBox();

				if ( _frustum->testBoxInFrustum( oRootBox )  )
				{
					vgKernel::Vec3 viewpos = /*vgKernel::Vec3(-5000, 5000, -5000);*/
						vgCam::CamManager::getSingleton().getCurrentPosition();

					float distance = nNodeID->setDistanceToViewer( viewpos );

					if ( distance <= 100.0f )
					{
						visible_queue->push_front( nNodeID );
					}
					else
					{
						visible_queue->push_back( nNodeID );
					}
			
					m_uNodeCountVisible	++;
					m_uFaceCountVisible	+= nNodeID->getNumOfTriangles();
					
					//m_mapTreeBox.insert( m_pairTreeBox( (E_TREENODE_TYPE)pParentNode->GetNodePropertyPtr()->GetNodeType(),
					//	pParentNode->GetNodePropertyPtr()->GetBoundingBox() )  );
					m_vTreeBox.push_back(oRootBox);
				}
			}//for
		}//for


	}//CollectVisibleSetLinear

	void		vgMagicTree::CollectVisibleSet( vgKernel::RendererPackage* visible_set, MagicTreeNodePtr	pParentNode )
	{
		m_pCurrentTreeNode	=	pParentNode;

		BoundingBox	oRootBox = m_pCurrentTreeNode->GetNodePropertyPtr()->GetBoundingBox();;
		E_TREENODE_TYPE	eTreeNodeType;
		Renderer		*pNode= NULL;
		
		unsigned int	nTreeDepth;
		// 层次包围盒是否可见，
		// 若不可见则退出遍历；
		// 若可见则进一步判断是否到叶子节点，若是叶子则加入可见集，否则继续递归遍历子结点；
		if( _frustum->testBoxInFrustum( oRootBox ) )
		{
			eTreeNodeType	=	m_pCurrentTreeNode->GetNodePropertyPtr()->GetNodeType();
			
			if ( _frustum->testBoxIncludedInFrustum( oRootBox ) ||  //完全位于视锥
				 TREENODE_LEAF == eTreeNodeType )					     //遍历至叶子节点
			{
				PushVisableSet( visible_set, m_pCurrentTreeNode );
				nTreeDepth	=	m_pCurrentTreeNode->GetNodePropertyPtr()->GetTreeDepth();

				m_vTreeBox.push_back(oRootBox);
				return ;
			}
			else
			{
				m_pCurrentTreeNode	= pParentNode->Quad1();
				if (m_pCurrentTreeNode)
				{
					CollectVisibleSet( visible_set, m_pCurrentTreeNode);
				}
				m_pCurrentTreeNode	= pParentNode->Quad2();
				if (m_pCurrentTreeNode)
				{
					CollectVisibleSet( visible_set, m_pCurrentTreeNode);
				}
				m_pCurrentTreeNode	= pParentNode->Quad3();
				if (m_pCurrentTreeNode)
				{
					CollectVisibleSet( visible_set, m_pCurrentTreeNode);
				}
				m_pCurrentTreeNode	= pParentNode->Quad4();
				if (m_pCurrentTreeNode)
				{
					CollectVisibleSet( visible_set, m_pCurrentTreeNode);
				}
			}
		}//if(可见)
		
		//m_uNodeCountVisible	= unsigned int(m_mapNodeVisible.size());

	}//CollectVisibleSet( 根节点 )


	void		vgMagicTree::PushVisableSet(  vgKernel::RendererPackage* visible_set, MagicTreeNodePtr pParentNode /*= NULL*/ )
	{
		//RendererQueue&	tempNodeIndex	=	pParentNode->GetNodePropertyPtr()->GetNodeIndex();

		m_tempNodeCount		=	pParentNode->GetNodePropertyPtr()->GetNodeCount();
		m_tempFaceCount		=	pParentNode->GetNodePropertyPtr()->GetFaceCount();

		m_uNodeCountVisible	+=	m_tempNodeCount;
		m_uFaceCountVisible	+=	m_tempFaceCount;

		vgKernel::RendererPackage*	vNodeIndex = m_pCurrentTreeNode->m_oTreeNodeProperty.GetNodeIndex();
		vgKernel::RendererPackage::iterator ipac = vNodeIndex->begin();
		vgKernel::RendererPackage::iterator ipac_end = vNodeIndex->end();
		
		vgKernel::RendererPackage::iterator outipac = visible_set->begin();

		for ( ; ipac != ipac_end ; ++ipac , ++ outipac )
		{
			RendererQueue* pQueue = ipac->second;
			RendererQueue* visible_queue = outipac->second;

			RendererQueue::iterator iter = pQueue->begin();
			RendererQueue::iterator iter_end = pQueue->end();

			for ( ; iter != iter_end ; ++iter )
			{			
				Renderer* curleaf = *iter;

				vgKernel::Vec3 viewpos = 
					vgCam::CamManager::getSingleton().getCurrentPosition();

				float distance = curleaf->setDistanceToViewer( viewpos );

				if ( distance <= 100.0f )
				{
					visible_queue->push_front( curleaf );
				}
				else
				{
					visible_queue->push_back( curleaf );
				}
			}
		}
		//visible_set->insert( visible_set->end(), tempNodeIndex.begin(), tempNodeIndex.end() );


		//m_mapTreeBox.insert( m_pairTreeBox(pParentNode->GetNodePropertyPtr()->GetNodeType(),
		//	pParentNode->GetNodePropertyPtr()->GetBoundingBox() )  );

	}//PushVisableSet( 根节点中的数据节点索引)

	
	void		vgMagicTree::PrintTreeStruct(MagicTreeNodePtr pParentTreeNode)
	{
		//ResetTreeStruct();
		m_pCurrentTreeNode	= pParentTreeNode;
		//m_hParentItem		= m_pUIManager->m_TreeLissset[1]->GetRootHit();
		m_hParentItem		= vgUI::UIController::getSingleton().GetRootQuadtree();

		m_uTreeDepthMax		= m_uTreeLeafCount = m_uTreeQuadCount = 0;
		m_uLevelOfFirstLeaf = UINT_MAX;

		HTREEITEM	hSubRoot = PrintTreeStruct(m_pCurrentTreeNode, m_hParentItem);
			
		CString		strNodeValueItem;
		strNodeValueItem.Format("TreeNode_Root@@@@TotalDepthCount:%d  TotalQuadCount:%d TotalLeafCount:%d LevelOfFirstLeaf:%d" , 
			m_uTreeDepthMax +1, m_uTreeQuadCount, m_uTreeLeafCount, m_uLevelOfFirstLeaf +1); 
		m_sCurrentItemValue = strNodeValueItem;

		//vgBaseEntry*	node = new vgRootEntry(m_sCurrentItemValue);
		//m_hRootNode = vgUI::UIController::getSingleton().AddNode(hSubRoot, node, 2);

		vgUI::UIController::getSingleton().GetWorkSpaceBar()->
			GetTree(2).SetItemText(hSubRoot, m_sCurrentItemValue.c_str() );

//		m_pUIManager->m_TreeLissset[1]->m_wndTree.ExpandTree( m_hParentItem ,true);
	}
		
	HTREEITEM		vgMagicTree::PrintTreeStruct(MagicTreeNodePtr pParentTreeNode, HTREEITEM hParentItem)
	{
#if 0
		HTREEITEM	tempParentItem	= hParentItem, tempPropertyItem,tempPropertyItemSub;
		//string		tempNodeValue("\"[");

		unsigned	int	uNodeCount	= pParentTreeNode->GetNodePropertyPtr()->GetNodeCount(), uNodeIndex = 0;
		//vector<int>		vNodeIndex	= pParentTreeNode->GetNodePropertyPtr()->GetNodeIndex();
		BoundingBox		oTreeBox	= pParentTreeNode->GetNodePropertyPtr()->GetBoundingBox();
		unsigned	int uFaceCount	= pParentTreeNode->GetNodePropertyPtr()->GetFaceCount();
		unsigned	int uTreeDepth	= pParentTreeNode->GetNodePropertyPtr()->GetTreeDepth();
		
		CString			strNodeValue, strNodeValueItem;  
		
		//NodeAbstract*	pNodeAbstract = NULL;
		//IMAGETYPE		eImageType	= IMG_QUADTREE;	
		
		uTreeDepth > m_uTreeDepthMax ? m_uTreeDepthMax = uTreeDepth : m_uTreeDepthMax ;
		
		// Part 1:节点头标识及关键属性
		switch( pParentTreeNode->GetNodePropertyPtr()->GetNodeType() )
		{
		case	TREENODE_QUAD1:
			m_sCurrentItemValue	= "SubtreeQuad1@@@@" ;
			m_uTreeQuadCount ++;
			break;
		case	TREENODE_QUAD2:
			m_sCurrentItemValue	= "SubtreeQuad2@@@@";
			m_uTreeQuadCount ++;
			break;
		case	TREENODE_QUAD3:
			m_sCurrentItemValue	= "SubtreeQuad3@@@@";
			m_uTreeQuadCount ++;
			break;
		case	TREENODE_QUAD4:
			m_sCurrentItemValue	= "SubtreeQuad4@@@@";
			m_uTreeQuadCount ++;
			break;
		case	TREENODE_LEAF:
			m_sCurrentItemValue	= "TreeNode_Leaf@@@@";
			//eImageType	= IMG_TREELEAF;
			m_uTreeLeafCount ++;
			uTreeDepth < m_uLevelOfFirstLeaf ? m_uLevelOfFirstLeaf = uTreeDepth : m_uLevelOfFirstLeaf ;

			break;
		case	TREENODE_PARENT:
			m_sCurrentItemValue	= "TreeNode_Root@@@@";
			break;
		default:
			m_sCurrentItemValue	= "???";
			break;
		}//switch
		strNodeValueItem.Format("Level:%d ", uTreeDepth ); 
		strNodeValue += strNodeValueItem;

		m_sCurrentItemValue	+=strNodeValue;
		//tempParentItem		= m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempParentItem, m_sCurrentItemValue, eImageType);
		vgBaseEntry*	node = new vgRootEntry(m_sCurrentItemValue);
		tempParentItem = vgUI::UIController::getSingleton().AddNode(tempParentItem, node, 2);


		// Part 2:该节点的属性结构体
		m_sCurrentItemValue = "TreeNodeProperty";
		//tempPropertyItem	= m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	/*tempHTreeItem*/tempParentItem, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		tempPropertyItem = vgUI::UIController::getSingleton().AddNode(tempParentItem, node, 2);

		//包含节点数
		m_sCurrentItemValue = "NodeCount";
		strNodeValueItem.Format("\t=%d", uNodeCount);
		m_sCurrentItemValue	+=strNodeValueItem;		
		//m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItem, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		vgUI::UIController::getSingleton().AddNode(tempPropertyItem, node, 2);

		//名字列表
		m_sCurrentItemValue = "NodeNameList";
		//tempPropertyItemSub	= m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItem, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		tempPropertyItemSub	= vgUI::UIController::getSingleton().AddNode(tempPropertyItem, node, 2);

		//for( uNodeIndex = 0; uNodeIndex < uNodeCount; uNodeIndex ++ )
		//{
		//	pNodeAbstract		= QuadtreeSceneManager::getSingletonPtr()->GetNodeAbstract(vNodeIndex[uNodeIndex]);
		//	m_sCurrentItemValue = pNodeAbstract->GetNodePropertyPtr()->GetNodeName() ; 
		//	strNodeValueItem.Format("*%d",vNodeIndex[uNodeIndex] ); 
		//	m_sCurrentItemValue += strNodeValueItem;

		//	//m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	//	tempPropertyItemSub, m_sCurrentItemValue, IMG_TREEPROP);
		//	node = new vgRootEntry(m_sCurrentItemValue);
		//	vgUI::UIController::getSingleton().AddNode(tempPropertyItemSub, node, 2);
		//}

		//包围盒
		m_sCurrentItemValue = "TreeBox";
		//tempPropertyItemSub	= m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItem, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		tempPropertyItemSub	= vgUI::UIController::getSingleton().AddNode(tempPropertyItem, node, 2);
		
		m_sCurrentItemValue = "MinPoint";
		strNodeValueItem.Format("\t=(%.3f, %.3f, %.3f)",oTreeBox.minPoint.x , 
			oTreeBox.minPoint.y , oTreeBox.minPoint.z);
		m_sCurrentItemValue	+=strNodeValueItem;
		//m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItemSub, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		vgUI::UIController::getSingleton().AddNode(tempPropertyItemSub, node, 2);
		
		m_sCurrentItemValue = "MaxPoint";
		strNodeValueItem.Format("\t=(%.3f, %.3f, %.3f)",oTreeBox.maxPoint.x , 
			oTreeBox.maxPoint.y , oTreeBox.maxPoint.z);
		m_sCurrentItemValue	+=strNodeValueItem;		
		//m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItemSub, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		vgUI::UIController::getSingleton().AddNode(tempPropertyItemSub, node, 2);

		//树深
		m_sCurrentItemValue = "TreeDepth";
		strNodeValueItem.Format("\t=%d", uTreeDepth);
		m_sCurrentItemValue	+=strNodeValueItem;		
		//m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItem, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		vgUI::UIController::getSingleton().AddNode(tempPropertyItem, node, 2);

		//包含面数
		m_sCurrentItemValue = "FaceCount";
		strNodeValueItem.Format("\t=%d", uFaceCount);
		m_sCurrentItemValue	+=strNodeValueItem;		
		//m_pUIManager->m_TreeLissset[1]->AddUITreenode(
		//	tempPropertyItem, m_sCurrentItemValue, IMG_TREEPROP);
		node = new vgRootEntry(m_sCurrentItemValue);
		vgUI::UIController::getSingleton().AddNode(tempPropertyItem, node, 2);


		// Part 3:该节点的子结点
		m_pCurrentTreeNode	= pParentTreeNode->Quad1();
		if( m_pCurrentTreeNode )
		{
			PrintTreeStruct(m_pCurrentTreeNode, tempParentItem);
		}
		m_pCurrentTreeNode	= pParentTreeNode->Quad2();
		if( m_pCurrentTreeNode )
		{
			PrintTreeStruct(m_pCurrentTreeNode, tempParentItem);
		}
		m_pCurrentTreeNode	= pParentTreeNode->Quad3();
		if( m_pCurrentTreeNode )
		{
			PrintTreeStruct(m_pCurrentTreeNode, tempParentItem);
		}
		m_pCurrentTreeNode	= pParentTreeNode->Quad4();
		if( m_pCurrentTreeNode )
		{
			PrintTreeStruct(m_pCurrentTreeNode, tempParentItem);
		}
		return tempParentItem;

#endif

		assert(0);
		return 0;

	}//PrintTreeStruct(pParentTreeNode, hParentItem)

	
	void		vgMagicTree::ResetTreeStruct()
	{
		//vgUI::UIController::getSingleton().GetWorkSpaceBar()->
		//	GetTree(2).DeleteAllItems();

		//vgBaseEntry* node = new vgRootEntry("四叉树视图");
		//HTREEITEM hRootQuadtree = vgUI::UIController::getSingleton().AddNode(node, 2);
		//vgUI::UIController::getSingleton().SetRootQuadtree(hRootQuadtree);
	}
	
	unsigned int		vgMagicTree::GetNodeCountVisible( void ){	return	m_uNodeCountVisible;}
	RendererPackage&	vgMagicTree::GetNodeIndexVisible( void ){	return	m_vNodeVisible;}
	unsigned int		vgMagicTree::GetFaceCountVisible( void ){	return	m_uFaceCountVisible;}
	unsigned int		vgMagicTree::GetNodeCountTotal( void )
	{
		return m_vRenderTotal.size();
	}
	unsigned int		vgMagicTree::GetFaceCountTotal( void )
	{
		return	0;
	}
	
	BoundingBox			vgMagicTree::GetTreeNodeBox(MagicTreeNodePtr	pParentNode/* =	NULL*/)
	{
		return pParentNode->GetNodePropertyPtr()->GetBoundingBox();
	}

	MagicTreeNodePtr	vgMagicTree::GetRootTreeNode(void)
	{
		return	&m_oRootTreeNode;
	}

	multimap<E_TREENODE_TYPE, BoundingBox>	vgMagicTree::GetTreeBoxVisible(void)
	{
		return	m_mapTreeBox;
	}

	multimap<E_TREENODE_TYPE, BoundingBox>*	vgMagicTree::GetTreeBoxVisiblePtr(void)
	{
		return	&m_mapTreeBox;
	}


	vector<BoundingBox>&	vgMagicTree::getTreeBox()
	{
		return	m_vTreeBox;
	}

	void				vgMagicTree::ExcludeLargeNodeFromRoot()
	{
		RendererPackage*	vNodeIndex	= m_oRootTreeNode.GetNodePropertyPtr()->GetNodeIndex();

		for (m_itrMap = m_pLargeNode.begin(), m_itrMap2 = vNodeIndex->begin() ; 
			m_itrMap != m_pLargeNode.end(); 
			m_itrMap++, m_itrMap2++)
		{
			m_dLargeNodeID	= m_itrMap->second;
			RendererQueue*pTempDeque = m_itrMap2->second;
			
			for( m_itrDeque	= m_dLargeNodeID->begin(); 
				m_itrDeque	!= m_dLargeNodeID->end();
				m_itrDeque	++ )
			{		
				RendererQueue::iterator	new_end = remove(pTempDeque->begin(), 
					pTempDeque->end(), *m_itrDeque);
				pTempDeque->erase(new_end, pTempDeque->end() );
			}//for

		}//for

		m_oRootTreeNode.RemoveQuads();
		m_oRootTreeNode.GetNodePropertyPtr()->UpdateTreeProperty();

	}//ExcludeLargeNodeFromRoot



	void				vgMagicTree::TestTraslateLargeNode( )
	{
		Vector3		oBoxSize	= m_oRootTreeNode.GetNodePropertyPtr()->GetBoundingBox().getSize();

		//ObjectNode*	pObjectNode	= NULL;
		//pObjectNode			= (ObjectNode*)pCurrentNode->GetNodeAbsState().GetNodeDataPtr();
		//pObjectNode->translate( oBoxSize*2.0f );
		//pCurrentNode->GetNodePropertyPtr()->SetBoundingBox( 
		//	pObjectNode->GetNodeDataProperty().GetBoundingBox() );
		//pCurrentNode->GetNodePropertyPtr()->SetPosition( 
		//	pObjectNode->GetNodeDataProperty().GetPosition() );

		RendererPackage* vNodeIndex = m_oRootTreeNodeLarge.GetNodePropertyPtr()->GetNodeIndex();
		for (m_itrMap = vNodeIndex->begin(); m_itrMap != vNodeIndex->end(); 
			m_itrMap++)
		{
			RendererQueue*	pQueue = m_itrMap->second;
			for (m_itrDeque = pQueue->begin(); m_itrDeque!= pQueue->end();
				m_itrDeque++)
			{
				(*m_itrDeque)->translate(oBoxSize.x*2.0f, oBoxSize.y*2.0f, oBoxSize.z*2.0f);
			}
		}
	}


	
}//namespace vgTree

#endif