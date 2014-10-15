



#ifndef __VGMODMANAGER_H__
#define __VGMODMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkRendererHolder.h>

#include <vgMod/vgObjNode.h>
#include <vgMod/vgNode.h>
#include <vgEffect/vgParticle.h>
#include <vgMod/vgModMisc.h>



namespace vgMod {




	

	class VGDEP_EXPORT		NodeManager : public vgKernel::Singleton<NodeManager>
		,public vgKernel::RendererHolder
	{
		friend class vgKernel::Singleton<NodeManager>;
	private:
		NodeManager() 
			: Singleton<NodeManager>( VGK_SINGLETON_LEFE_MODMANAGER ) 
		{
			VGK_TRACE(_T("NodeManager created."));
			setDefault();
		}
		~NodeManager()
		{
			VGK_TRACE(_T("NodeManager destroyed."));
			reset();
		}

	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown()
		{
			return true;
		}

	public:

		void initAfterOpenGLSetup();

		void	setDefault();

		void	reset();

		void	uninitBeforeOpenGLDestroy();

		void  stopDemoCreate() {return  ModMisc::getSingleton().StopCreate();}

		int   getStatus()  {return ModMisc::getSingleton().getStatus();}

	public:
		void	appendNode(Node* pNode, const CategoryType& type);

		bool	deleteNodeItem(Node* pNode);

		void	render();
		
		virtual bool onDeleteRenderer( vgKernel::Renderer* renderer );
	
		NodePtrVec	addTree(CPoint &point);
		NodePtrVec	addTree(const Vector3 &pos);
		NodePtrVec	addTreeInLine();

		//add by ZhouZY 2009-11-6 20:11
		bool        removeTreeInLine();   
		NodePtrVec*  getPlantTreeList() 
		{ 
			return &m_plantTreeList; 
		}


		NodePtrVec	addParticleToScene(CPoint &point, E_PARTICLE_TYPE	particleType = PARTICLE_OTHER);
		
		NodePtrVec  addDyanamicBillboard(CPoint &point);

	public:

		// 用于场景切块保存  add by ZhouZY   2009-12-30  19:56
		NodeAbsPtrVec*  getSelectNodeItemIndexList();

		NodeAbsPtrVec*	getNodeItemIndexList();
		ModItemPtrVec*	getModItemList();
		
		NodePtrPackage*	getNodeItemList();
		NodePtrVec*		getNodeItemList( const CategoryType& type , const bool& add_if_needed );
	
		void            clearNodeIndexList( NodeAbsPtrVec* nodeList );

	protected:
		struct TraverseVecForRender
		{
			inline void operator() (ObjectNode* item) 
			{
				item->render();
			}
		};
	private:
		NodeAbsPtrVec	m_nodeItemIndexList;

		NodeAbsPtrVec   m_selectNodeItemIndexList;

		NodePtrPackage	m_nodeAll;

		ModItemPtrVec	m_modItemListTemp;

		//用于记录沿线植树时生成的树节点
		NodePtrVec  m_plantTreeList; //add by ZhouZY 2009-11-6 20:11

	};

}// end of namespace vgGlobal



#endif // end of __VGGGLOBALFACADE_H__