

#ifndef __TVGGPUMANAGER_H__
#define __TVGGPUMANAGER_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSingleton.h>
#include <vgTex/tvgGpuProgram.h>
#include <vgTex/tvgGpuSupport.h>

#include <vgKernel/vgkTrace.h>

namespace vgCore {

	/**
		@date 	2007/05/14  20:26	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT GpuManager : public ::Singleton<GpuManager>
	{
	public:
		GpuManager()
		{
			mInitialised = false;
			VGK_TRACE("***** GpuManager created!");
		}
		~GpuManager()
		{
			VGK_TRACE("***** GpuManager destroyed!");
		}
	


		bool initialise()
		{
			this->mGpuSupportPtr.bind( new GpuSupport );
			mInitialised = true;
			return true;
		}
		
 		GpuSupportPtr getGpuSupportPtr() const 
 		{
 			assert( isValid() );
 			return this->mGpuSupportPtr;
 		}

		bool isValid() const
		{
			return this->mInitialised;
		}

		/**
			static functions which can make singleton pattern.
		*/
		static GpuManager& getSingleton(void);
		static GpuManager* getSingletonPtr(void);

	private:
	
		bool mInitialised;
 		GpuSupportPtr mGpuSupportPtr;

	
	};
	
	
	
	
}// end of namespace vgCore

#endif // end of __TVGGPUMANAGER_H__