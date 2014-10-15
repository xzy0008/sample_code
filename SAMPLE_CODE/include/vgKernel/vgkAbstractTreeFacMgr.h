


#ifndef __VGKABSTRACTTREEFACMGR_H__
#define __VGKABSTRACTTREEFACMGR_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>

	
namespace vgKernel {

	class AbstractTreeFac;
	/**
		@date 	2009/06/03  10:48	
		@author  xy
	
		@brief 	本类负责释放
	
		@see    
	*/
	class VGK_EXPORT AbstractTreeFacMgr : 
		public Singleton<AbstractTreeFacMgr>
	{
		friend class vgKernel::Singleton<AbstractTreeFacMgr>;
	public:
		AbstractTreeFacMgr();
		virtual~AbstractTreeFacMgr();
	
	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown();

	public:

		virtual void reset(){};

		AbstractTreeFac* getAbstractTreeFac()
		{
			assert( _fac != NULL );
			return _fac;
		}

		void registerAbstractTreeFac( AbstractTreeFac* fac )
		{
			assert( _fac == NULL );
			_fac = fac;
		}

	private:

		AbstractTreeFac* _fac;
	
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKABSTRACTTREEFACMGR_H__