
/************************************************************************/
/*	vgtMagicTree.h	—— 神奇树类的定义								    */
/************************************************************************/



#ifndef __VGTMAGICTREE_H__
#define __VGTMAGICTREE_H__


	


#if 0

#include <vgKernel/vgkForward.h>
#include <vgTree/vgtAbstractTree.h>
#include <vgCam/vgcaCamManager.h>
#include <vgModelStruct.h>

namespace vgTree{

	using namespace vgKernel;
	
	//// 树节点属性类
	class	vgTreeNodeProp
	{
	public:
		// 构造/赋值
		vgTreeNodeProp()
			:m_uFaceCount(0)
			,m_uNodeCount(0)
			,m_uTreeDepth(0)
			,m_eNodeType(TREENODE_PARENT) 
		{
		}

		vgTreeNodeProp( const vgTreeNodeProp& pProp )	{	*this = pProp;}

		inline	vgTreeNodeProp& operator = ( const vgTreeNodeProp& pProp )
		{
			m_vNodeIndex	= pProp.m_vNodeIndex;
			
			m_uNodeCount	= pProp.m_uNodeCount;
			m_uTreeDepth	= pProp.m_uTreeDepth;
			m_eNodeType		= pProp.m_eNodeType;
			m_uFaceCount	= pProp.m_uFaceCount;
			m_oTreeBox		= pProp.m_oTreeBox;
			return	*this;
		}

	public:
		// 获取/设置属性项
		inline	unsigned int&		GetNodeCount()	{ return m_uNodeCount; }
		RendererPackage*		GetNodeIndex()	{ return &m_vNodeIndex; }
		inline	unsigned int&		GetFaceCount()	{ return m_uFaceCount;}
		inline	BoundingBox&		GetBoundingBox(){ return m_oTreeBox;}
		
		inline	unsigned int&		GetTreeDepth()	{ return m_uTreeDepth; }
		inline	E_TREENODE_TYPE&	GetNodeType()	{ return m_eNodeType; }
		
		inline	void	SetNodeCount(unsigned int	uNodeCount)	{ m_uNodeCount	= uNodeCount; }
		inline	void	SetNodeIndex(RendererPackage*	vNodeIndex)	
		{ 
			//m_vNodeIndex	= vNodeIndex; 
			ClearNodeIndex();
			RendererPackage::iterator	itrMap = vNodeIndex->begin();
			for (;itrMap!=vNodeIndex->end(); itrMap++)
			{
				RendererQueue*  pQueue = getRenderQueue(itrMap->first);
				pQueue->insert(pQueue->end(),
					itrMap->second->begin(), itrMap->second->end());
			}
		}
		inline	void	SetFaceCount(unsigned int	uFaceCount)	{ m_uFaceCount	= uFaceCount; }
		inline	void	SetBoundingBox(BoundingBox	oTreeBox)	{ m_oTreeBox	= oTreeBox; }
		
		inline	void	SetTreeDepth(unsigned int	uTreeDepth)	{ m_uTreeDepth	= uTreeDepth; }
		inline	void	SetNodeType	(E_TREENODE_TYPE	eNodeType)	{ m_eNodeType	= eNodeType; }
		
	public:
		// 获取/设置节点索引点
		inline	void	InsertNodeIndex(RendererPackage& vNodeIndex)
		{ 
			vgKernel::RendererPackage::iterator ipac = vNodeIndex.begin();
			vgKernel::RendererPackage::iterator ipac_end = vNodeIndex.end();

			vgKernel::RendererPackage::iterator outipac = m_vNodeIndex.begin();

			for ( ; ipac != ipac_end ; ++ipac , ++ outipac )
			{
				outipac->second->insert(outipac->second->end(), 
								ipac->second->begin(), ipac->second->end() );
				m_uNodeCount += ipac->second->size();
			}
		}
		inline	void	PushNodeVector( Renderer* pRender)		
		{ 
			RendererQueue*	pQueue	= getRenderQueue(pRender->getType());
			pQueue->push_back(pRender); 
			m_uNodeCount ++;
		}
		RendererQueue* getRenderQueue( const RendererType& type)
		{
			RendererPackage::iterator iter = m_vNodeIndex.find( type );

			if ( iter != m_vNodeIndex.end() )
			{
				return iter->second;
			}

			RendererQueue* queueNew = new RendererQueue;
			m_vNodeIndex.insert( std::make_pair( type , queueNew ) );

			return queueNew;
		}
		// 重置
		inline	void Reset( void )
		{
			ClearNodeIndex();
			m_uTreeDepth		= 0;
			m_eNodeType			= TREENODE_PARENT;
		}
		inline	void	ClearNodeIndex()
		{
			RendererPackage::iterator iter = m_vNodeIndex.begin();
			RendererPackage::iterator iter_end = m_vNodeIndex.end();
			for ( ; iter != iter_end ; ++iter )
			{
				iter->second->clear();
			}
			m_uNodeCount = m_uFaceCount = 0;
		}
		// 更新属性
		inline	void	UpdateTreeProperty()
		{
			m_uNodeCount = m_uFaceCount = 0;
			m_oTreeBox		=	BoundingBox();

			vgKernel::RendererPackage::iterator ipac = m_vNodeIndex.begin();
			vgKernel::RendererPackage::iterator ipac_end = m_vNodeIndex.end();

			for ( ; ipac != ipac_end ; ++ipac )
			{
				RendererQueue* queue = ipac->second;

				RendererQueue::iterator iter = queue->begin();
				RendererQueue::iterator iter_end = queue->end();

				for ( ; iter != iter_end ; ++iter )
				{
					Renderer* curleaf = *iter;
					m_oTreeBox.merge( BoundingBox(curleaf->getBoundingBox() ));
					m_uFaceCount	+= curleaf->getNumOfTriangles();
				}
				m_uNodeCount += queue->size();
			}//for
		}
		
		// 定义属性值
	public:
		BoundingBox			m_oTreeBox ;
		unsigned int		m_uFaceCount ;

		unsigned int		m_uNodeCount;
		RendererPackage		m_vNodeIndex;
		//RendererQueue		m_vNodeIndex;
		//vector<int>			m_vNodeIndex;
		//NodeAbstractSet		m_vNodeIndex;

		unsigned int		m_uTreeDepth;
		E_TREENODE_TYPE		m_eNodeType;

		HTREEITEM			m_hTreeNode;

	};//class	vgDataNodeProp 树节点属性类


	class	vgMagicTree;
	class	MagicTreeNode;

	typedef	MagicTreeNode*		MagicTreeNodePtr;

	class	MagicTreeNode 
	{
	// 对外数据
	public:
		// 用途 ：储存节点属性
		// 包括 ：节点数目、节点索引、包围盒、总面数、树的深度 5个子项
		vgTreeNodeProp	m_oTreeNodeProperty;


	// 内部数据
	private:
		// 用途：储存指针->子结点									   z轴
		// 包括：指向第一、二、三、四象限的子结点的指针 4个指针
		MagicTreeNodePtr		m_pSubtreeQuad1;	//第一象限  		T
		MagicTreeNodePtr		m_pSubtreeQuad2;	//第二象限	  2nd	|   1st 
		MagicTreeNodePtr		m_pSubtreeQuad3;	//第三象限    ------|------->x轴
		MagicTreeNodePtr		m_pSubtreeQuad4;	//第四象限	  3rd	|	4th 
		MagicTreeNodePtr		m_pParent;

	// 对外函数
	public:	
		// 功能 ：无参构造函数
		MagicTreeNode(
			MagicTreeNodePtr	pParentNode	= NULL, 
			E_TREENODE_TYPE		eNodeType	= TREENODE_PARENT )
			:m_pSubtreeQuad1(NULL)
			,m_pSubtreeQuad2(NULL)
			,m_pSubtreeQuad3(NULL)
			,m_pSubtreeQuad4(NULL)
			,m_pParent(pParentNode)
		{ 
			// 初始化深度、节点类型 
			// 无父节点说明该节点自身是父节点，深度为0；否则该节点是子结点，深度增1；
			if (!pParentNode)
			{
				GetNodePropertyPtr()->SetTreeDepth( 0 );
				GetNodePropertyPtr()->SetNodeType( TREENODE_PARENT );
			}
			else
			{	
				GetNodePropertyPtr()->SetTreeDepth(pParentNode->GetNodePropertyPtr()->GetTreeDepth() +1);
				GetNodePropertyPtr()->SetNodeType(eNodeType );
				
				vgKernel::RendererPackage::iterator ipac = 
					pParentNode->GetNodePropertyPtr()->GetNodeIndex()->begin();
				vgKernel::RendererPackage::iterator ipac_end = 
					pParentNode->GetNodePropertyPtr()->GetNodeIndex()->end();
				for ( ; ipac != ipac_end ; ++ipac )
				{	
					GetNodePropertyPtr()->getRenderQueue(ipac->first);
				}
			}
		}

		// 功能 ：析构函数
		~MagicTreeNode() 
		{
			Reset();
		};

		// 功能 ：重置节点
		void	Reset(void)
		{
			m_oTreeNodeProperty.Reset();

			RemoveQuads();
		}

		void	RemoveQuads(void)
		{
			if(m_pSubtreeQuad1)
			{
				delete	m_pSubtreeQuad1;
				m_pSubtreeQuad1	=	NULL;
			}
			if(m_pSubtreeQuad2)
			{
				delete	m_pSubtreeQuad2;
				m_pSubtreeQuad2	=	NULL;
			}
			if(m_pSubtreeQuad3)
			{
				delete	m_pSubtreeQuad3;
				m_pSubtreeQuad3	=	NULL;
			}
			if(m_pSubtreeQuad4)
			{
				delete	m_pSubtreeQuad4;
				m_pSubtreeQuad4	=	NULL;
			}
		}
		void	FormatToLeaf(void)
		{
			m_oTreeNodeProperty.SetNodeType(TREENODE_LEAF);
			if(m_pSubtreeQuad1)
			{
				delete	m_pSubtreeQuad1;
				m_pSubtreeQuad1	=	NULL;
			}
			if(m_pSubtreeQuad2)
			{
				delete	m_pSubtreeQuad2;
				m_pSubtreeQuad2	=	NULL;
			}
			if(m_pSubtreeQuad3)
			{
				delete	m_pSubtreeQuad3;
				m_pSubtreeQuad3	=	NULL;
			}
			if(m_pSubtreeQuad4)
			{
				delete	m_pSubtreeQuad4;
				m_pSubtreeQuad4	=	NULL;
			}
		}

		// 功能 ：获取数据成员
		MagicTreeNodePtr	&Quad1()			{ return m_pSubtreeQuad1; }
		MagicTreeNodePtr	&Quad2()			{ return m_pSubtreeQuad2; }
		MagicTreeNodePtr	&Quad3()			{ return m_pSubtreeQuad3; }
		MagicTreeNodePtr	&Quad4()			{ return m_pSubtreeQuad4; }
		MagicTreeNodePtr	&Parent()			{ return m_pParent;		  }
		vgTreeNodeProp*		GetNodePropertyPtr()	{ return &m_oTreeNodeProperty; }
		// 功能 ：声明神奇树类为该结构体的友元类，
		// 使神奇树类拥有对这个结构体私有数据的访问权限
		friend class vgMagicTree;

	};//结束定义结构体：class MagicTreeNode


	
	
	class	vgMagicTree	: public vgTree::AbstractTree
	{	

	public:

		virtual void setRendererPackage(  vgKernel::RendererPackage* package );
		virtual void invalidate();
		virtual void getVisibleSet( vgKernel::RendererPackage* visible_set );
		virtual void renderTreeStruct(bool bDrawStruct = false);
		virtual void switchTreeStruct( );

		bool isUseTree();
		TREE_TYPE	getType()	{	return TREE_QUAD; }
	private:
		RendererPackage* _allRenderers;

		//RendererQueue* _leaves;
		vgCam::ViewFrustum* _frustum;
	
	public:
	//////////////////////////////////////////////////////////////////////////
	/*< 外部接口函数：		功能：
	（1：_mBuildWholeTree	构树		）
	（2：_mReset			销毁		）	
	（3：_m_mCollectVisibleSet	筛选可见集	）									
	（4：_m_mClearVisibleSet	清空可见集	）									>*/

		// 功能 ：外部接口1 构造神奇树，关联一个具体场景
		// 参数1：场景对象指针，确立神奇树的管理目标，必须设置不得缺省；
		// 参树2：神奇树的明确类型，即线性树（缺省）、二叉树、四叉树、八叉树
		// 参数3：抖动因子控制划分四颗子树的不均匀度
		// 返回 ：调用成功RETURN_SUCCESS,失败RETURN_FAIL,参数无效RETURN_ABORT

		E_RETURN_TYPE		_mBuildWholeTree(
			vgKernel::RendererPackage*	pCurrentRendererQueue  /* = NULL		*/,
			E_DIVIDE_TYPE		eDefaultDivideType	= DIVIDE_NONE	,
			float				filterBigNode		= 0.1,
			unsigned int	uDitheringLevel			= 50		);

		// 功能 ：外部接口2 重置神奇树，准备将神奇树关联到新场景或空场景
		// 参数1：树节点的对象指针，值为NULL（默认）表示重置根节点；
		// 返回 ：调用成功RETURN_SUCCESS,失败RETURN_FAIL,参数无效RETURN_ABORT
		E_RETURN_TYPE		_mReset( MagicTreeNodePtr	pParentNode =	NULL );

		// 功能 ：外部接口3 计算可视集，遍历神奇树选出场景中的可视节点集
		// 参数 ：无
		// 返回 ：可视集所含数据节点的数目
		unsigned int	_mCollectVisibleSet( vgKernel::RendererPackage* visible_set );
		void			_mClearVisibleSet(void);

		void			_mRenderObject(bool bUseTree = false, bool bRenderNodeBox = false, bool bRenderTreeBox = false);
	//////////////////////////////////////////////////////////////////////////
	/*< 外部接口函数：						功能：
	（1：GetNodeCountVisible				获取 可视节点数		）
	（2：GetNodeIndexVisible				获取 可视节点索引	）	
	（3：GetFaceCountVisible				获取 可视面数		）									
	（4：GetTreeNodeBox						获取 包围盒			）			>*/
		
		// 功能 ：外部接口4 获取可视集
		unsigned int		GetNodeCountVisible(void);
		RendererPackage& GetNodeIndexVisible(void);
		unsigned int		GetFaceCountVisible(void);
		unsigned int		GetFaceCountTotal(void);
		unsigned int		GetNodeCountTotal( void );
		/*map<IndexType, NodeAbstract*>			GetNodeMapVisible(void);
		map<IndexType, NodeAbstract*>*			GetNodeMapVisiblePtr(void);*/
		multimap<E_TREENODE_TYPE, BoundingBox>	GetTreeBoxVisible(void);
		multimap<E_TREENODE_TYPE, BoundingBox>*	GetTreeBoxVisiblePtr(void);
		vector<BoundingBox>&	getTreeBox();

		// 功能 ：外部接口5 获取树包围盒
		BoundingBox			GetTreeNodeBox(MagicTreeNodePtr	pParentNode =	NULL);

		// 功能 ：外部接口6 获取树根节点
		MagicTreeNodePtr	GetRootTreeNode(void);

		// 功能 ：初始化/析构神奇树
		// 参数1：父节点对象指针，值为DIVIDE_NONE（缺省）表示不细分树根节点；
		// 返回 ：无
		vgMagicTree( E_DIVIDE_TYPE	eDefaultDivideType	= DIVIDE_QUAD );
		~vgMagicTree();

	protected:
	//////////////////////////////////////////////////////////////////////////
	/*< 内部接口函数(集)：	功能：
	（1：IsNeedDivide		细分条件	）
	（2：Divide				细分		）	
	（3：_mBuildVisableSet	筛选可见集	）	
	（4：CreateRootNode		由全局场景生成根节点）
	（5：vgMagicTree		构造/析构	）									>*/

		// 功能 ：内部接口1 判断是否需要划分子树，并判定划分方式（二叉、四叉等），供细分子树内部接口(Divide)调用
		// 参数1：传入缺省的划分类型，返回经过判定被修正的划分类型
		// 参数2：划分精细度
		// 参数3：父节点对象指针
		// 返回 ：需要划分返回true，否则返回false
		E_RETURN_TYPE IsNeedDivide( 
			MagicTreeNodePtr	pCurrentNode		= NULL,
			E_DIVIDE_TYPE*		eDefaultDivideType	= NULL );

		// 功能 ：内部接口集2 细分神奇树的一个节点，逐级生成0个、2个、4个或8个分叉，供外部接口1(_mBuildWholeTree)调用
		// 参数1：父节点对象指针
		// 参数2：细分方式，0个（缺省）、2个、4个或8个分叉
		// 返回 ：调用成功RETURN_SUCCESS,失败RETURN_FAIL,参数无效RETURN_ABORT
		E_RETURN_TYPE	Divide(
			MagicTreeNodePtr	pParentNode = NULL,
			E_DIVIDE_TYPE			eDefaultDivideType	= DIVIDE_NONE );
			
		E_RETURN_TYPE	DivideTwo(MagicTreeNodePtr  pParentNode = NULL);

		E_RETURN_TYPE	DivideFour(MagicTreeNodePtr  pParentNode = NULL );



		// 功能 ：内部接口集3 遍历神奇树内部实现，选出场景节点的可视集，供外部接口3(_mBuildVisableSet)调用
		// 参数 ：无
		// 返回 ：可视集所含数据节点的数目
		void		CollectVisibleSet( vgKernel::RendererPackage* visible_set, MagicTreeNodePtr	pParentNode );	
		void		CollectVisibleSetLinear( vgKernel::RendererPackage* visible_set, MagicTreeNodePtr	pParentNode  = NULL);

		// 功能 ：填充可见集，将叶子节点中的数据节点索引队列加入可见集，供外部接口3(_mBuildVisableSet)调用
		// 参数1：叶子节点对象指针
		void		PushVisableSet( vgKernel::RendererPackage* visible_set, MagicTreeNodePtr  pParentNode = NULL );


		// 功能 ：内部接口集4 生成/删除结点（根节点或子结点），供其它内外接口调用(_mBuildWholeTree、Divide)
		// 参数1：父节点对象指针
		// 参数2：节点类型
		// 返回 ：调用成功RETURN_SUCCESS,失败RETURN_FAIL,参数无效RETURN_ABORT
		MagicTreeNodePtr	InitializeRootNode( vgKernel::RendererPackage*	pCurrentRendererQueue );
		void				SeparateLargeNodeFromRoot();
		MagicTreeNodePtr	CreateRootNodeLarge();

		E_RETURN_TYPE	NewbornChildren(
			MagicTreeNodePtr	pParentNode =	NULL ,
			E_TREENODE_TYPE		eNodeType	=	TREENODE_QUAD1234 );

		E_RETURN_TYPE	AbandonChildren( 
			MagicTreeNodePtr	pParentNode =	NULL ,
			E_TREENODE_TYPE		eNodeType	=	TREENODE_QUAD1234 );

		void		RenderObject(bool bRenderNodeBox = false, bool bRenderTreeBox = false);
		void		RenderFrameBox(BoundingBox	oBox, Vector3 oColor);
		

		void		ExcludeLargeNodeFromRoot( );
		void		TestTraslateLargeNode( );

		// 四叉树可视化
		void		PrintTreeStruct(MagicTreeNodePtr pParentTreeNode);
		HTREEITEM	PrintTreeStruct(MagicTreeNodePtr pParentTreeNode, HTREEITEM hParentItem);
		void		ResetTreeStruct();

	protected:
		//////////////////////////////////////////////////////////////////////////
		/*< 内部数据														   >*/

		// 用途：遍历时是否使用树
		bool				m_bUseTree;

		// 用途：储存指针->(神奇树的)根节点和当前节点
		MagicTreeNode		m_oRootTreeNode;
		MagicTreeNodePtr	m_pCurrentTreeNode;
		MagicTreeNode		m_oRootTreeNodeLarge;

		// 用途：指针指向->(被挂接到神奇树上的)场景
		//SceneData*			m_pCurrentSceneData;
		RendererQueue	m_vRenderTotal;



		// 用途：储存默认的神奇树划分类型，划分类型含无树、二叉树、四叉树、八叉树四种
		E_DIVIDE_TYPE			m_eDefaultDivideType;
		// 用途：存储均分子树时的不均匀度控制因子
		unsigned int		m_uDitheringLevel;
		float				m_fFilterBigNode;

		// 用途：存储树的最大深度、总树枝数、总叶子数、首片叶子所在层
		unsigned int		m_uTreeDepthMax;
		unsigned int		m_uTreeQuadCount;
		unsigned int		m_uTreeLeafCount;
		unsigned int		m_uLevelOfFirstLeaf;


		// 用途：构树时收集大物体
		vector<int>			m_vLargeNodeID;
		unsigned int		m_uLargeNodeCount, m_uLargeNodeCountPre;
		RendererQueue*	m_dLargeNodeID;

		vgKernel::RendererPackage		m_pLargeNode;
		vector<int>			m_vLargeCount;
		RendererPackage::iterator	m_itrMap, m_itrMap2;
		bool				m_bNeedRebuild;

		bool				m_bDrawStruct;
		// 用途：存储视景体，用于视锥裁剪
//		CFrustum			m_oCurrentFrustum;

		// 用途：可视节点集 数目与索引
		unsigned int		m_uNodeCountVisible;
		vector<int>			m_vNodeIndexVisible;
		unsigned int		m_uFaceCountVisible;
		
		// 可视集new
		RendererPackage		m_vNodeVisible;
		RendererQueue::iterator				m_itrDeque;
		
		multimap<E_TREENODE_TYPE, BoundingBox>				m_mapTreeBox;
		multimap<E_TREENODE_TYPE, BoundingBox>::iterator	m_iteratorMapTreeBox;
		typedef pair<E_TREENODE_TYPE, BoundingBox>			m_pairTreeBox;
		vector<BoundingBox>		m_vTreeBox;

		const float			BOUNDINGBOXZOOM	;/*0.04f*/
		
		HTREEITEM			m_hCurrentItem;
		HTREEITEM			m_hParentItem;
		string				m_sCurrentItemValue;
		HTREEITEM			m_hSubRootItem;
	
	private:
		// 用途：储存频繁使用的临时变量
		unsigned int		m_tempNodeCount;	// (数据节点的)数目
		vector<int>			m_tempNodeIndex;	// (数据节点的)索引
		BoundingBox			m_tempBoundingBox;	// (数据节点的)总包围盒
		unsigned int		m_tempFaceCount;	// (数据节点的)总面数
		unsigned int		m_tempTreeDepth;	// (  树节点的)深度
		E_TREENODE_TYPE		m_tempNodeType;		// (  树节点的)类型

		unsigned int		m_tempLoopCount;


	};//结束定义类：class vgMagicTree






}//	namespace vgTree



#endif // end of __VGTMAGICTREE_H__

#endif