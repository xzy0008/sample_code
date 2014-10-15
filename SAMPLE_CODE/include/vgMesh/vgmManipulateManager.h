


#ifndef __VGMMANIPULATEMANAGER_H__
#define __VGMMANIPULATEMANAGER_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkUniqueID.h>
	
namespace vgMesh {


	using namespace vgKernel;
	/**
		@date 	2008/07/01  21:39	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGM_EXPORT ManipulateManager : public vgKernel::Singleton<ManipulateManager>
	{
		friend class vgKernel::Singleton<ManipulateManager>;
	private:
		ManipulateManager();
		~ManipulateManager();

	protected:

		virtual bool initialise();

		virtual bool shutdown();

	public:

		virtual void reset(){};

		UniqueIDVector* getSelectBuffer()
		{
			assert( _selectBuffer != NULL );
			return _selectBuffer;
		}

	private:

		UniqueIDVector* _selectBuffer;
		

	};

	
}// end of namespace vgMesh
	


#endif // end of __VGMMANIPULATEMANAGER_H__