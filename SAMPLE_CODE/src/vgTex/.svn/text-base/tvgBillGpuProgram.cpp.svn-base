
#include <vgStableHeaders.h>


#include <vgTex/tvgBillGpuProgram.h>


#include <olectl.h>

namespace vgCore {



	GLenum  BillGpuProgram::FaceTarget[6] = {  
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };



		char *BillGpuProgram::vertex_source = "\
												uniform float4x4 modelViewProj : state.matrix.mvp;\
												uniform float4x4 modelview : state.matrix.modelview;\
												void main(\
														  float4 in_position	:   POSITION ,\
														  float2 in_texCoord	:   TEXCOORD0 , \
														  float4 in_color  : COLOR,\
														  float3 in_normal   : NORMAL,\
												\
														  out float4 out_Position	: POSITION ,\
														  out float2 out_TexCoord  : TEXCOORD0,\
														  out float4 out_color   : COLOR\
														  )\
												{\
													float x,y,z,v,width,height;\
													x = in_position[0];\
													y = in_position[1];\
													z = in_position[2];\
													width = floor(in_normal[2]) / 100.0;\
													height = frac(in_normal[2]) * 100.0;\
													float3 aa = modelview._m00_m01_m02;\
													aa = aa * width * 0.5 ;\
													float3 bb = modelview._m10_m11_m12;\
													bb = bb * height * 0.5;\
													float3 cc = float3(x,y,z) + in_normal[0] * aa + in_normal[1] * bb;\
													in_position = float4(cc[0],cc[1]+ height / 2.0,cc[2] ,in_position[3]);\
													out_Position = mul(modelViewProj, in_position);\
													out_TexCoord = in_texCoord;\
													out_color = in_color;\
												}";

		char *BillGpuProgram::pixel_source = "\
											  void main(\
											  float2 in_texCoord : TEXCOORD0,\
											  float3 R		: TEXCOORD1 ,\
											  float4 in_color  :	COLOR,\
											  uniform sampler2D decalMap,\
											  \
											  out float4 out_Color : COLOR )\
											  {\
											  out_Color = tex2D(  decalMap , in_texCoord );\
											  }";



		//----------------------------------------------------------------


		bool BillGpuProgram::init()
		{
			GpuManager& gpuMgr = GpuManager::getSingleton();
			mSupportPtr = gpuMgr.getGpuSupportPtr();

			this->mVertexProfile = mSupportPtr->getVertexProfile();
			this->mPixelProfile = mSupportPtr->getPixelProfile();


			mIsValid = true;

			/// 初始化CGprogram程序
			mCgVertexProgram = 	cgCreateProgram( 
				mSupportPtr->getGpuContextPtr()->getContext(),
				CG_SOURCE,
				vertex_source,
				mVertexProfile,
				NULL, NULL );

			GpuSupport::checkCgErrorStack();

			mCgPixelProgram = 	cgCreateProgram( 
				mSupportPtr->getGpuContextPtr()->getContext(),
				CG_SOURCE,
				pixel_source,
				mPixelProfile,
				NULL, NULL );

			GpuSupport::checkCgErrorStack();

			cgGLLoadProgram( mCgVertexProgram );

			GpuSupport::checkCgErrorStack();

			cgGLLoadProgram( mCgPixelProgram );

			GpuSupport::checkCgErrorStack();

			return true;
		}
		//----------------------------------------------------------------

		void BillGpuProgram::destroy()
		{
			GpuSupport::checkCgErrorStack();
			if ( mCgPixelProgram != NULL )
			{
				cgDestroyProgram(mCgPixelProgram);
				GpuSupport::checkCgErrorStack();
				mCgPixelProgram = NULL;
			}

			if ( mCgVertexProgram != NULL )
			{
				cgDestroyProgram(mCgVertexProgram);
				GpuSupport::checkCgErrorStack();
				mCgVertexProgram = NULL;
			}

			//------------------------------------------
			// 删除纹理
			//------------------------------------------

			if ( mDecalMapID != 0 )
			{
				glDeleteTextures( 1 , &mDecalMapID );
				mDecalMapID = 0;
			}
			setDefault();
		}

		void BillGpuProgram::useBindBegin()
		{
			cgGLEnableProfile( mVertexProfile );
			cgGLEnableProfile( mPixelProfile );

			cgGLBindProgram( mCgPixelProgram );
			cgGLBindProgram( mCgVertexProgram );

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "decalMap") );

		}
		//----------------------------------------------------------------









}// end of namespace vgCore
