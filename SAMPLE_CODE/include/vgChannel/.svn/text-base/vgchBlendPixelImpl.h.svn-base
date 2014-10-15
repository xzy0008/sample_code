#pragma once

#include <vgChannel/vgchPixelBuffer.h>
#include <vgChannel/vgchDoublePixelBuffer.h>
#include <vgChannel/vgchNurbsCorrectImpl.h>
#include <vgChannel/vgchEdgeBlendGpuProgram.h>
#include <vgChannel/vgchFrameBuffer.h>

namespace vgChannel
{
	typedef struct ScreenPixel_t
	{
		float texCoodX;
		float texCoodY;

		float posX;
		float posY;
		float posZ;

	}ScreenPixel;

	class BlendPixelImpl
	{
	public:
		BlendPixelImpl();
		~BlendPixelImpl();

		void setEdgeBlendEnable(bool b) { m_edgeBlendEnable = b; }
		bool getEdgeBlendEnable() { return m_edgeBlendEnable; }

		void setScreenSize(int width, int height);
		void setProjectorPos(float x, float y);

		void setLeftGama(float gamma) { m_edgeBlender.setLeftGama(gamma); }
		float getLeftGama() { return m_edgeBlender.getLeftGama(); }

		void setRightGama(float gamma) { m_edgeBlender.setRightGama(gamma); }
		float getRightGama() { return m_edgeBlender.getRightGama(); }

		void setLeftEdge(float width) { m_edgeBlender.setLeftEdgeLen(width); }
		float getLeftEdge() { return m_edgeBlender.getLeftEdgeLen(); }

		void setRightEdge(float rightEdge) { m_edgeBlender.setRightEdgeLen(rightEdge); }
		float getRightEdge() { return m_edgeBlender.getRightEdgeLen(); }

		void setRedGamma(float rg) { m_edgeBlender.setRedGama(rg); }
		float getRedGamma() { return m_edgeBlender.getRedGama(); }

		void setBlueGamma(float bg) { m_edgeBlender.setBlueGama(bg); }
		float getBlueGamma() { return m_edgeBlender.getBlueGama(); }

		void setGreenGamma(float gg) { m_edgeBlender.setGreenGama(gg); }
		float getGreenGama() { return m_edgeBlender.getGreenGama(); }

		void setFullScreenGamma(float fg) { m_edgeBlender.setFullScreenGama(fg); }
		float getFullScreenGamma() { return m_edgeBlender.getFullScreenGama(); }
		bool renderBegin();

		// 边缘融合及几何校正
		bool blendPixelBegin();
		bool blendPixelEnd();
		void initBlendParam();	//@FengYK	2009/10/31 10:21
		void SaveToXml();
		CString TurnFloatToCstr(float floatValue);
		void SetKeyValueToXml();
		void SetBlendKeyToXml();

		// NurbsCorrectImpl* getNurbsPtr() { return &m_nurbsAdjustImpl; }

	private:
		GLuint m_newTexture;

		// 显示器像素尺寸
		int m_width;
		int m_hegiht;
 
		PixelBuffer			m_pixelBuffer;
		DoublePixelBuffer	m_dpBuffer;
		FrameBuffer			*m_pFrameBuffer;
		EdgeBlendGpuProgram m_edgeBlender;

		bool m_edgeBlendEnable;
		
		CString Xmlfilename;
		CString Xmlsectionname;
		CString strFileName;
		std::vector<CString> m_mXmlBlendKeyName;
		std::vector<CString> m_xmlBlendKeyValue;

		// Nurbs 曲面校正
		// NurbsCorrectImpl  m_nurbsAdjustImpl;
	};
}