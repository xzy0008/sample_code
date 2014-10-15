


#ifndef __VGMO_MESHMANAGER_H__
#define __VGMO_MESHMANAGER_H__




#include <vgModel/vgmoDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgModel/vgmoModelItem.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkRenderer.h>

#include <vgKernel/vgkRendererObserver.h>
#include<vgKernel/vgkRendererHolder.h>

#include <vgModel/vgmoDefinition.h>

#include <vgKernel/vgkRenderCommand.h>


namespace vgModel {

	using namespace vgKernel;

	class ModelObserver;
	class FileHandleVmd;

	/**
		@date 	2008/07/01  19:09	
		@author  leven
	
		@brief 	负责所有ModelItem的删除.
	
		@see    
	*/

	class  VGMO_EXPORT ModelManager 
		: public vgKernel::Singleton<ModelManager>, 
		public vgKernel::ObserverContainer, 
		public vgKernel::RendererHolder
	{
		friend class vgKernel::Singleton<ModelManager>;
	public:
		typedef std::map<String,FileHandleVmd*> FileHandleVmdMap;
		typedef std::pair<FileHandleVmdMap::iterator , bool > FileHandleVmdMapInsertRes;

	private:
		ModelManager();
	public:
		~ModelManager();

	protected:

		virtual bool initialise();
		virtual bool shutdown();
	
		vgKernel::RenderCommand *m_pModelRenderCmd;

	public:
		virtual void reset(){};
		virtual bool onDeleteRenderer( Renderer *render);

		/**
			重要函数,在OpenGL配置环境结束之前,要删除所有的data
		*/
		void unloadAllModelItems();


		// only for testing
		void dumpAllModelItemInfo();

		virtual void render();

		/**
			返回量是纹理的列表,用于保存纹理数据
			注意,本函数不负责返回纹理名称的重复性剔除.
		*/
		vgKernel::StringVectorPtr  saveItemsToVmd( const String& absolute_path );

		/**
			得到的ModelItem客户端不能够删除
		*/
		ModelItem* getModelItem( const UniqueID& uuid );

		/**
			通过创建FileHandleVmd来添加ModelItems
		*/
		//FileHandleVmd* addItemsByFileHandle( const String& absolute_file_path );


		

		// 返回的指针客户端不能够删除
		ModelItemMap* getModelItemMap()
		{
			return &_items;
		}

		FileHandleVmdMap* getFileHandleVmdMap()
		{
			return &_filehandlers;
		}

		bool addItemsAndRegisterFileHandlerVmd( FileHandleVmd* handle );


		void invalidateItemTextures();

		void readProject(const String& projpath , const String& projname);

		void saveProject();

	private:

		bool deleteModelItem( ModelItem* item );

		bool addModelItem( ModelItem* item );

		/**
			register包括和IoServer的Associate
		*/
		void renderAllModelItems();

		bool registerAndAssociateFileHandleVmd( FileHandleVmd* handle ); 
		bool exist( const UniqueID& uuid );
		bool exist( vgAsyn::FileHandle* handle );

		struct TraverseMapForRender
		{
			inline void operator() (std::pair<UniqueID, ModelItem*> item) 
			{
				item.second->render();
			}
		};

		struct TraverseVecForRender
		{
			inline void operator() ( vgKernel::Renderer* item) 
			{
				((ModelItem*)item)->render();
			}
		};

	private:

		/**
			从Renderermanager中得到
		*/
		RendererQueue* _culledModelRenderQueue;

		FileHandleVmdMap _filehandlers;
	
		ModelItemMap _items;
	};
	
	
	
}// end of namespace vgModel

#endif // end of __VGMO_MESHMANAGER_H__