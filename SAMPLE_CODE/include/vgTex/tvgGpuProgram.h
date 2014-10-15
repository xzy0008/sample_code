

#ifndef __TVGGPUPROGRAM_H__
#define __TVGGPUPROGRAM_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgGpuSupport.h>
#include <vgCore/vgSharedPtr.h>


namespace vgCore {

	/**
		@date 	2007/05/10  10:03	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT GpuProgram
	{
	public:

		enum GpuProgramTypes
		{
			GPU_PROGRAM_UNKOWN,
			GPU_PROGRAM_VERTEX,
			GPU_PROGRAM_PIXEL
		};

		GpuProgram()
		{
			this->setParametersDefault();
		}
		virtual ~GpuProgram()
		{

		}
	
		virtual void useBindBegin( const CGprofile& profile )
		{
			//bind the cg program
			assert( isValid() );

			cgGLBindProgram( mCgProgram );
			if ( this->mProgramType == GPU_PROGRAM_VERTEX )
			{
				cgGLEnableProfile( profile );
			}
			else
			{
				cgGLEnableProfile( profile );
			}
			
		}

		virtual void useBindEnd()
		{

		}
	
	//private:
	protected:
		
		void setParametersDefault()
		{
			this->mIsValid = false;
			this->mProgramType = GPU_PROGRAM_UNKOWN;
		}

		inline const bool isValid() const
		{
			if ( this->mProgramType == GPU_PROGRAM_UNKOWN )
			{
				return false;
			}
			return this->mIsValid;
		}

	//private:
	protected:
	
		bool mIsValid;

		GpuProgramTypes mProgramType;

		CGprogram mCgProgram;
	
	};

	typedef SharedPtr<GpuProgram> GpuProgramPtr;






	
}// end of namespace vgCore

#endif // end of __TVGGPUPROGRAM_H__