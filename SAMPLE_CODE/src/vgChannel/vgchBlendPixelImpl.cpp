#include <vgStableHeaders.h>
#include <vgChannel/vgchBlendPixelImpl.h>
#include <vgKernel/vgkSystemUtility.h>

#define ctan(X) (1/tan(X))

namespace vgChannel
{
	BlendPixelImpl::BlendPixelImpl() 
		: m_pixelBuffer(100,100),m_dpBuffer(100,100)
	{
		// ÏÔÊ¾Æ÷ÏñËØ³ß´ç
		m_width = 0;
		m_hegiht = 0;

		m_newTexture = 0;
		m_pFrameBuffer = NULL;
		m_edgeBlendEnable = false;

		m_pFrameBuffer = new FrameBuffer(100, 100);
		m_pFrameBuffer->create();
		//--
		CString strExtension = _T(".xml");

		char exebuf[512];
		DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

		assert( getret < 512 );
		assert( getret > 0 );

		String exestr( exebuf );
		String exepath = exestr.substr( 0 , 
			exestr.find_last_of("\\/")  + 1);

		CString path;
		path.Format("%s", exepath.c_str());
		
		Xmlfilename =  _T("Channel");		//@FengYK	2009/10/31 10:21
		strFileName = path + Xmlfilename + strExtension ;
		Xmlsectionname = _T("Edge blending correction");
		//--
		if (vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(strFileName)&&
			vgConfig::XMLConfigManager::getSingleton().FindSection(Xmlsectionname))
		{				
			initBlendParam();
		}

	}

	BlendPixelImpl::~BlendPixelImpl()
	{
		if (m_pFrameBuffer != NULL)
		{
			delete m_pFrameBuffer;
		}
	}

	void BlendPixelImpl::initBlendParam()	//@FengYK	2009/10/31 10:21
	{
		vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(Xmlsectionname);

		float leftEdge = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_leftEdge"));
		float rightEdge = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_rightEdge"));
		float red = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_red"));
		float green = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_green"));
		float blue = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_blue"));
		float leftGamma = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_leftGamma"));
		float rightGamma = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_rightGamma"));

		float fullScreenGamma = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_fullScreenGamma"));

		setLeftEdge(leftEdge);
		setRightEdge(rightEdge);
		setRedGamma(red);
		setGreenGamma(green);
		setBlueGamma(blue);
		setLeftGama(leftGamma);
		setRightGama(rightGamma);
		setFullScreenGamma(fullScreenGamma);
	}

	void BlendPixelImpl::setScreenSize(int width, int height)
	{
		m_width = width; 
		m_hegiht = height; 

		m_pixelBuffer.reSize(m_width, m_hegiht);
		m_dpBuffer.reSize(m_width, m_hegiht);

		m_edgeBlender.setScreenWidth(width);

		if (m_width == 0)
		{
			m_width = 1;
		}

		if (m_hegiht == 0)
		{
			m_hegiht = 1;
		}

		if (m_pFrameBuffer != NULL)
		{
			delete m_pFrameBuffer;
		}

		m_pFrameBuffer = new FrameBuffer(m_width, m_hegiht);
		m_pFrameBuffer->create();
		m_pFrameBuffer->bind();
		m_pFrameBuffer->unbind();
	}

	bool BlendPixelImpl::blendPixelBegin()
	{
		// BYTE* buf = m_dpBuffer.getBufferData();
// 		m_pixelBuffer.pack();
// 		BYTE *buf = m_pixelBuffer.mapBuffer();
// 
// 		// glReadPixels(0, 0, m_width, m_hegiht, GL_BGR, GL_UNSIGNED_BYTE, buf);
// 
// 
// 		glEnable(GL_TEXTURE_2D);
// 
// 		glBindTexture(GL_TEXTURE_2D, m_newTexture);  
// 		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_width, m_hegiht, 0, GL_BGR, GL_UNSIGNED_BYTE, buf);
// 		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL ); 
// 		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// ÏßÐÎÂË²¨
// 		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// ÏßÐÎÂË²¨
// 
// 		// m_dpBuffer.unmap();
// 		m_pixelBuffer.unmapBuffer();
		
		if (m_pFrameBuffer != NULL)
		{
			m_newTexture = m_pFrameBuffer->getTextureId();
			m_pFrameBuffer->unbind();
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_newTexture);  

		if (m_edgeBlendEnable)
		{
			m_edgeBlender.setTexEveryFrame(m_newTexture);

			m_edgeBlender.bind();
		}

		return true;
	}

	bool BlendPixelImpl::blendPixelEnd()
	{
		m_edgeBlender.unbind();
		
		glDisable(GL_TEXTURE_2D);
		glFinish();

		return true;
	}

	bool BlendPixelImpl::renderBegin()
	{
		m_pFrameBuffer->bind();

		return true;
	}

	void BlendPixelImpl::SetBlendKeyToXml()	//@FengYK	2009/10/31 10:24 
	{
		m_mXmlBlendKeyName.clear();

		m_mXmlBlendKeyName.push_back(_T("m_leftEdge"));
		m_mXmlBlendKeyName.push_back(_T("m_rightEdge"));
		m_mXmlBlendKeyName.push_back(_T("m_red"));
		m_mXmlBlendKeyName.push_back(_T("m_green"));
		m_mXmlBlendKeyName.push_back(_T("m_blue"));
		m_mXmlBlendKeyName.push_back(_T("m_leftGamma"));
		m_mXmlBlendKeyName.push_back(_T("m_rightGamma"));
		m_mXmlBlendKeyName.push_back(_T("m_fullScreenGamma"));

	}

	void BlendPixelImpl::SetKeyValueToXml()
	{
		float leftEdge = getLeftEdge();
		float rightEdge = getRightEdge();
		float red = getRedGamma();
		float green = getGreenGama();
		float blue = getBlueGamma();
		float leftGamma = getLeftGama();
		float rightGamma = getRightGama();
		float fullScreenGamma = getFullScreenGamma();

		m_xmlBlendKeyValue.clear();

		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(leftEdge));
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(rightEdge));
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(red));	 
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(green));
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(blue));
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(leftGamma));
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(rightGamma));
		m_xmlBlendKeyValue.push_back(TurnFloatToCstr(fullScreenGamma));

	}

	CString BlendPixelImpl::TurnFloatToCstr(float floatValue)
	{
		CString keyvalue;
		keyvalue.Format("%f", floatValue);
		return keyvalue;
	}

	void BlendPixelImpl::SaveToXml()
	{
		SetBlendKeyToXml();
		SetKeyValueToXml();	
		vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(strFileName);
		for (int i = 0; i < m_mXmlBlendKeyName.size(); i ++)
		{
			vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("Edge blending correction"), 
				m_mXmlBlendKeyName[i], m_xmlBlendKeyValue[i]);
		}

		vgConfig::XMLConfigManager::getSingleton().SaveXML(strFileName);
	}
}