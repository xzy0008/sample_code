


#ifndef __VGMMESHMANAGER_H__
#define __VGMMESHMANAGER_H__




#include <vgMesh/vgmDefinition.h>



#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgMesh/vgmMeshItem.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkRenderer.h>

#include <vgKernel/vgkRendererObserver.h>
#include<vgKernel/vgkRendererHolder.h>

#include <vgMesh/vgmSmallMeshReferencer.h>
#include <vgMesh/vgmDefinition.h>

#include <vgKernel/vgkRenderCommand.h>


namespace vgMesh {

	using namespace vgKernel;

	class MeshObserver;
	class FileHandleVgm;

	/**
		@date 	2008/07/01  19:09	
		@author  leven
	
		@brief 	负责所有MeshItem的删除.
	
		@see    
	*/

	class  VGM_EXPORT MeshManager : public vgKernel::Singleton<MeshManager>
		, public vgKernel::ObserverContainer, public vgKernel::RendererHolder
	{
		friend class vgKernel::Singleton<MeshManager>;
	public:/*private:*/
		typedef std::map<String,FileHandleVgm*> FileHandleVgmMap;
		typedef std::pair<FileHandleVgmMap::iterator , bool > FileHandleVgmMapInsertRes;

	private:
		MeshManager();
		virtual ~MeshManager();

	protected:

		virtual bool initialise();
		virtual bool shutdown();

		vgKernel::RenderCommand *m_pRenderMeshCmd;

	public:

		void reset();
		void initAfterOpenGLSetup();

		virtual bool onDeleteRenderer( Renderer *render);

		/**
			清除当前裁剪的PrevRenderQueue,用在下列情况:
			导入新的纹理包vgi之后,mesh需要更新.
			此时全部写在一次重新载入即可.
		*/
		void clearPrevRenderQueue();

		/**
			重要函数,在OpenGL配置环境结束之前,要删除所有的data
		*/
		void unloadAllMeshItems();

		// only for testing
		void addRefToAllMeshItems();

		// only for testing
		void dumpAllMeshItemInfo();

		//void setupRenderEnvironment();

		void render();

		/**
			返回量是纹理的列表,用于保存纹理数据
			注意,本函数不负责返回纹理名称的重复性剔除.
		*/
		vgKernel::StringVectorPtr  saveItemsToVgm( const String& absolute_path );

		/**
			得到的MeshItem客户端不能够删除
		*/
		MeshItem* getMeshItem( const UniqueID& uuid );

		/**
			通过创建FileHandleVgm来添加MeshItems
		*/
		//FileHandleVgm* addItemsByFileHandle( const String& absolute_file_path );


		bool deleteMeshItem( MeshItem* item );

		// 返回的指针客户端不能够删除
		MeshItemMap* getMeshItemMap()
		{
			return &_items;
		}

		// 返回用户选定的vgm模型
		MeshItemMap* getSelectMeshItemMap()
		{
			return &_selectItems;
		}
		
		void clearSelectItemMap();

		void setSaveMode( bool bMode )
		{
			_bSaveSelectNode = bMode;
		}

		FileHandleVgmMap* getFileHandleVgmMap()
		{
			return &_filehandlers;
		}

		// 返回的指针客户端只能用于遍历,不能用于编辑
		//RendererDeque* getCulledRenderers()
		//{
		//	return &_prevMeshRenderQueue;
		//}

		bool addItemsAndRegisterFileHandlerVgm( FileHandleVgm* handle );


		void readProject(const String& projpath , const String& projname);

		void saveProject();

	private:

		// 收集用户选定的vgm模型
		bool collectSelectItem( const vgKernel::RendererQueue& renderQuene );

		bool addMeshItem( MeshItem* item );

		//void copyMeshItemsToLeafDeque();

		/**
			register包括和IoServer的Associate
		*/

		void renderAllMeshItems();

		bool registerAndAssociateFileHandleVgm( FileHandleVgm* handle ); 
		bool exist( const UniqueID& uuid );
		bool exist( vgAsyn::FileHandle* handle );

		struct TraverseMapForRender
		{
			inline void operator() (std::pair<UniqueID, MeshItem*> item) 
			{
				item.second->render();
			}
		};

		struct TraverseMapForAddRef
		{
			inline void operator() (std::pair<UniqueID, MeshItem*> item) 
			{
				item.second->addViewRef();
			}
		};

		struct TraverseVecForAddRef
		{
			inline void operator() ( vgKernel::Renderer* item) 
			{
				((MeshItem*)item)->addViewRef();
			}
		};

		struct TraverseVecForReleaseRef
		{
			inline void operator() ( vgKernel::Renderer* item) 
			{
				((MeshItem*)item)->releaseViewRef();
			}
		};

		struct TraverseVecForRender
		{
			inline void operator() ( vgKernel::Renderer* item) 
			{
				((MeshItem*)item)->render();
			}
		};



	private:

		SmallMeshReferencer _smallMeshes;

		/**
			自己保存的列表
		*/
		RendererQueue* _prevCulledMeshRenderQueue;
		//RendererDeque _meshRenderQueue;

		/**
			从Renderermanager中得到
		*/
		RendererQueue* _culledMeshRenderQueue;


		FileHandleVgmMap _filehandlers;
	
		/**
			注意,下面两个量一一对应.
			_leaves用于和vgTree接口使用.
		*/
		MeshItemMap _items;
		//RendererDeque _renderers;

		/**
			add by ZhouZY 2010-1-3
			用于切块保存vgm
		*/
		MeshItemMap _selectItems;

		bool        _bSaveSelectNode;

	};
	
	
	
}// end of namespace vgMesh

#endif // end of __VGMMESHMANAGER_H__