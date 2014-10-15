


#ifndef __VGKCAMMGRHOLDER_H__
#define __VGKCAMMGRHOLDER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>

	
namespace vgKernel {

	class CamMgrImpl;


	/**
		@date 	2009/06/03  10:30	
		@author  xy
	
		@brief 	不负责释放
	
		@see    
	*/
	class VGK_EXPORT CamMgrHolder : public Singleton<CamMgrHolder>
	{
		friend class Singleton<CamMgrHolder>;
	private:
		CamMgrHolder();

	public:
		virtual~CamMgrHolder();

		virtual void reset(){};//need to write

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

		CamMgrImpl* getCamManager()
		{
			assert( _camImpl != NULL );
			return _camImpl;
		}

		void registerCamMgr( CamMgrImpl* impl )
		{
			assert( _camImpl == NULL );
			assert( impl != NULL );
			_camImpl = impl;
		}

	private:
	
		CamMgrImpl* _camImpl;
	
	};
	
	
}// end of namespace vgKernel
	




#endif // end of __VGKCAMMGRHOLDER_H__