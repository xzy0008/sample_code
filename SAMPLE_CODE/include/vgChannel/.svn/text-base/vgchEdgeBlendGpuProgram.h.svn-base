#pragma once

#include <Cg/cg.h>
#include <vgKernel/vgkGpuSupport.h>

namespace vgChannel
{
	class EdgeBlendGpuProgram
	{
	private:
		static const char* s_fragmentSource;

	public:
		EdgeBlendGpuProgram();
		~EdgeBlendGpuProgram();
		
		bool init();
		void setDefault();

		void bind();
		void unbind();
		
		void setTexEveryFrame(GLuint texture);

		void setScreenWidth(float width);
		void setLeftEdgeLen(float leftLen);
		void setRightEdgeLen(float rightLen);

		void setRedGama(float redGama);
		void setBlueGama(float blueGama);
		void setGreenGama(float greenGama);
		void setFullScreenGama(float fGamma);

		void setLeftGama(float gama);
		void setRightGama(float gamma);

		float getLeftGama() { return m_leftGama; }
		float getRightGama() { return m_rightGama; }

		float getScreenWidth() { return m_screenWidth; }
		float getLeftEdgeLen() { return m_leftEdge; }
		float getRightEdgeLen() { return m_rightEdge; }
		float getRedGama() { return m_gamaRed; }
		float getBlueGama() { return m_gamaBlue; }
		float getGreenGama() { return m_gamaGreen; }
		float getFullScreenGama() { return m_fullScreenGamma; }

	private:
		// char			*m_cgFileName;

		CGprofile		m_PixelProfile;
		CGprogram		m_CgPixelProgram; 
		
		CGparameter 	m_blendPixelParam_sw;

		CGparameter		m_blendPixelParam_lbw;
		CGparameter		m_blendPixelParam_rbw;

		CGparameter		m_blendPixelParam_leftGa;
		CGparameter     m_blendPixelParam_rightGa;
		CGparameter     m_blendPixelParam_fullGa;

		CGparameter		m_blendPixelParam_redGa;
		CGparameter		m_blendPixelParam_greenGa;
		CGparameter		m_blendPixelParam_blueGa;
		CGparameter		m_blendPixelParam_tex;

		vgKernel::GpuSupport*	m_gpuSupportPtr;
	
	private:
		GLuint			m_textureId;	
		
		float			m_screenWidth;
		float			m_rightEdge;
		float			m_leftEdge;

		float			m_leftGama;
		float			m_rightGama;

		float			m_gamaRed;
		float			m_gamaGreen;
		float			m_gamaBlue;

		float			m_fullScreenGamma;
	};
}