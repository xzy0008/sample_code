#include <vgStableHeaders.h>
#include <vgKernel/vgkGpuManager.h>
#include <vgChannel/vgchEdgeBlendGpuProgram.h>

namespace vgChannel
{
	const char *EdgeBlendGpuProgram::s_fragmentSource = "\
		void main(float2 texCoord  : TEXCOORD0,   \
		out float4 color : COLOR,				\
		uniform float		screenWidth,		\
		uniform float		leftEdgeWidth,		\
		uniform float		rightEdgeWidth,		\
		uniform float	    leftGammaVal,        \
		uniform float       rightGammaVal,		\
		uniform float		redGama,			\
		uniform float		greenGama,			\
		uniform float		blueGama,			\
		uniform float       fullScreenGama,		\
		uniform sampler2D	tex : TEX0)			\
	{																\
		float leftEdge = leftEdgeWidth / screenWidth;				\
		float rightEdge = 1.f - rightEdgeWidth / screenWidth;		\
		float gammaVal;												\
																	\
		if (texCoord.x > leftEdge && texCoord.x < rightEdge)		\
		{															\
			color = tex2D(tex,texCoord);							\
		}															\
		else														\
		{															\
			float blendFactor;										\
			float cusor;											\
																	\
			if (texCoord.x < leftEdge)								\
			{														\
				cusor = texCoord.x / leftEdge;						\
				gammaVal = leftGammaVal;							\
			}														\
			else													\
			{														\
				 cusor =											\
					1 - (texCoord.x - rightEdge) / (rightEdgeWidth / screenWidth);	\
				 gammaVal = rightGammaVal;							\
			}														\
																	\
			if ( cusor < 0.5)										\
			{														\
				blendFactor = gammaVal * (2 * cusor) * (2 * cusor); \
			}														\
			else													\
			{														\
				blendFactor											\
					= 1.f - (1-gammaVal) * (2 * (1-cusor)) * (2 * (1-cusor));   \
			}														\
																	\
			color = tex2D(tex,texCoord);							\
			color.xyz = color.xyz * blendFactor;					\
																	\
																	\
		}															\
																	\
		color.x *= redGama;											\
		color.y *= greenGama;										\
		color.z *= blueGama;										\
		color.x = pow(color.x, 1.0/fullScreenGama);					\
		color.y = pow(color.y, 1.0/fullScreenGama);					\
		color.z = pow(color.z, 1.0/fullScreenGama);					\
	}																\
";

	EdgeBlendGpuProgram::EdgeBlendGpuProgram()
	{
		init();
		setDefault();
	}

	EdgeBlendGpuProgram::~EdgeBlendGpuProgram()
	{
// 		if ( m_CgPixelProgram != NULL )
// 		{ 
// 			cgDestroyProgram(m_CgPixelProgram);
// 			m_CgPixelProgram = NULL;
// 		}
	}

	void EdgeBlendGpuProgram::setDefault()
	{
		m_textureId = GL_INVALID_VALUE;	
		
		m_screenWidth = 1024;
		m_leftEdge = 128;
		m_rightEdge = 128;

		m_gamaRed = 1.f;
		m_gamaGreen = 1.f;
		m_gamaBlue = 1.f;

		m_leftGama = .5f;
		m_rightGama = .5f;
		m_fullScreenGamma = 1.f;

		m_blendPixelParam_redGa = cgGetNamedParameter(m_CgPixelProgram, "redGama");
		cgSetParameter1f(m_blendPixelParam_redGa, m_gamaRed);

		m_blendPixelParam_greenGa = cgGetNamedParameter(m_CgPixelProgram, "greenGama");
		cgSetParameter1f(m_blendPixelParam_greenGa, m_gamaGreen);

		m_blendPixelParam_blueGa = cgGetNamedParameter(m_CgPixelProgram, "blueGama");
		cgSetParameter1f(m_blendPixelParam_blueGa, m_gamaBlue);

		m_blendPixelParam_sw  = cgGetNamedParameter(m_CgPixelProgram, "screenWidth");
		cgSetParameter1f(m_blendPixelParam_sw, m_screenWidth);

		m_blendPixelParam_lbw = cgGetNamedParameter(m_CgPixelProgram, "leftEdgeWidth");
		cgSetParameter1f(m_blendPixelParam_lbw, m_leftEdge);

		m_blendPixelParam_rbw = cgGetNamedParameter(m_CgPixelProgram, "rightEdgeWidth");
		cgSetParameter1f(m_blendPixelParam_rbw, m_rightEdge);

		m_blendPixelParam_leftGa  = cgGetNamedParameter(m_CgPixelProgram, "leftGammaVal");
		cgSetParameter1f(m_blendPixelParam_leftGa, m_leftGama);

		m_blendPixelParam_rightGa  = cgGetNamedParameter(m_CgPixelProgram, "rightGammaVal");
		cgSetParameter1f(m_blendPixelParam_rightGa, m_rightGama);

		m_blendPixelParam_fullGa = cgGetNamedParameter(m_CgPixelProgram, "fullScreenGama");
		cgSetParameter1f(m_blendPixelParam_fullGa, m_fullScreenGamma);

		m_blendPixelParam_tex = cgGetNamedParameter(m_CgPixelProgram, "tex");
	}

	bool EdgeBlendGpuProgram::init()
	{
		vgKernel::GpuManager& gpuMgr = vgKernel::GpuManager::getSingleton();
		
		m_gpuSupportPtr = gpuMgr.getGpuSupport();
	
		assert( m_gpuSupportPtr != NULL );

		m_PixelProfile = m_gpuSupportPtr->getPixelProfile();

		assert( m_PixelProfile == CG_PROFILE_FP40 );

		/// ³õÊ¼»¯CGprogram³ÌÐò

		m_CgPixelProgram = 	cgCreateProgram( 
			m_gpuSupportPtr->getGpuContextPointer()->getContext(),
			CG_SOURCE,
			s_fragmentSource,
			m_PixelProfile,
			NULL, NULL );	

		CGerror error;
		cgGLLoadProgram( m_CgPixelProgram );
		const char *string = cgGetLastErrorString(&error);
		if (error != CG_NO_ERROR)
		{
			AfxMessageBox("error");
		}
		
		return true;
	}

	void EdgeBlendGpuProgram::setTexEveryFrame(GLuint texture)
	{
		m_textureId = texture;
	}

	void EdgeBlendGpuProgram::bind()
	{
		cgGLBindProgram(m_CgPixelProgram);
		cgGLEnableProfile(m_PixelProfile);

		cgGLSetTextureParameter(m_blendPixelParam_tex, m_textureId);
	}

	void EdgeBlendGpuProgram::unbind()
	{
		cgGLDisableTextureParameter( m_blendPixelParam_tex );
		cgGLDisableProfile( m_PixelProfile );
	}

	void EdgeBlendGpuProgram::setScreenWidth(float width)
	{
		m_screenWidth = width;
		cgSetParameter1f(m_blendPixelParam_sw, width);
	}

	void EdgeBlendGpuProgram::setLeftEdgeLen(float leftLen)
	{
		m_leftEdge = leftLen;
		cgSetParameter1f(m_blendPixelParam_lbw, leftLen);
	}

	void EdgeBlendGpuProgram::setRightEdgeLen(float rightLen)
	{
		m_rightEdge = rightLen;
		cgSetParameter1f(m_blendPixelParam_rbw, rightLen);
	}

	void EdgeBlendGpuProgram::setRedGama(float redGama)
	{
		m_gamaRed = redGama;
		cgSetParameter1f(m_blendPixelParam_redGa, redGama);
	}

	void EdgeBlendGpuProgram::setBlueGama(float blueGama)
	{
		m_gamaBlue = blueGama;
		cgSetParameter1f(m_blendPixelParam_blueGa, blueGama);
	}

	void EdgeBlendGpuProgram::setGreenGama(float greenGama)
	{
		m_gamaGreen = greenGama;
		cgSetParameter1f(m_blendPixelParam_greenGa, greenGama);
	}

	void EdgeBlendGpuProgram::setLeftGama(float gmma)
	{
		m_leftGama = gmma;
		cgSetParameter1f(m_blendPixelParam_leftGa, gmma);
	}

	void EdgeBlendGpuProgram::setRightGama(float gmma)
	{
		m_rightGama = gmma;
		cgSetParameter1f(m_blendPixelParam_rightGa, gmma);
	}

	void EdgeBlendGpuProgram::setFullScreenGama(float fGamma)
	{
		m_fullScreenGamma = fGamma;
		cgSetParameter1f(m_blendPixelParam_fullGa, fGamma);
	}
}