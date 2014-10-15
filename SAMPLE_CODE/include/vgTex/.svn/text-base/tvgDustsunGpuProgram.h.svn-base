

#ifndef __TVGDUSTSUNGPUPROGRAM_H__
#define __TVGDUSTSUNGPUPROGRAM_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgGpuSupport.h>
#include <vgTex/tvgGpuProgram.h>
#include <vgTex/tvgGpuManager.h>

namespace vgCore {

	class DustsunGpuProgram : public GpuProgram
	{
	public:
			
	static char *vertex_source;

	static char *pixel_source;

	public:
		DustsunGpuProgram()
		{
			setDefault();
			GpuSupport::checkCgErrorStack();
		}
		~DustsunGpuProgram()
		{
			GpuSupport::checkCgErrorStack();
			this->destroy();
		}

		void setParametersOnce( const String &lastsunmap, const String& dustsunMap  ,
			const String& skyDecalMap )
		{
			mLastsunMapID = buildDecalMapID(lastsunmap);
			assert( mLastsunMapID != 0);

 			mDustsunMapID = buildDecalMapID( dustsunMap );
 			assert(mDustsunMapID != 0);

			mDecalMapID = buildDecalMapID( skyDecalMap );
			assert(mDecalMapID != 0 );

			m_ratio = 0.0;
		}

		bool init();

		void setParametersEveryFrame( float _ratio )
		{
			if ( _ratio >= 0 && _ratio <= 1.0)
			{
				m_ratio = _ratio;
			}
		}

		virtual void useBindBegin( );

		virtual void useBindEnd();


		void destroy();

		void setDefault()
		{
			mCgPixelProgram = NULL;
			mCgVertexProgram = NULL;

			mDecalMapID = 0;
			mDustsunMapID = 0;
			mLastsunMapID = 0;


		}

	private:

		static GLuint buildDecalMapID( const String& decalmap );

		static bool buildFaceTextureUsingGDI( const String& filename , GLenum target );
	private:

		CGprofile mVertexProfile;
		CGprofile mPixelProfile;

		CGprogram mCgPixelProgram;
		CGprogram mCgVertexProgram;

		GpuSupportPtr mSupportPtr;

		GLuint mDecalMapID;
		GLuint mDustsunMapID;
		GLuint mLastsunMapID;

		float m_ratio;

		CGparameter g_CGparam_userClipPlaneParam;
	};

	typedef SharedPtr<DustsunGpuProgram> DustsunGpuProgramPtr;

	
	
	
}// end of namespace vgCore

#endif // end of __TVGDustsunGpuProgram_H__