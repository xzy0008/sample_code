
#include <vgStableHeaders.h>
#include "vgeffect/vgCloud.h"


// class vgCloud
namespace vgMod
{
	
	
	vgCloud::vgCloud()
	{
		m_Position.x		= 0.0f;
		m_Position.y		= 300.0f;
		m_Position.z		= 0.0f;

		cloudBound.width	= 100.0f;
		cloudBound.height	= 100.0f/*5.0f*/;
		
		bcloudOpen			= FALSE;
		m_texturename		= "data/deepcloud.bmp";
	}
	
	vgCloud::~vgCloud()
	{
		
	}
	
	
	void vgCloud::SetBound( CLOUDBOUND cloudBound )
	{
		cloudBound.width  = cloudBound.width;
		cloudBound.height	= cloudBound.height;
	}
	
	void vgCloud::SetBound( GLfloat fogStart, GLfloat fogEnd )
	{
		cloudBound.width  = fogStart;
		cloudBound.height	= fogEnd;	
	}

	void vgCloud::SetCenter(float x, float y, float z)
	{
		m_Position.x = x ;
		m_Position.y = y ;
		m_Position.z = z ;
	}	//	SetCenter(float x, float y, float z)
	
	void vgCloud::SetCenter(Vector3 pos)
	{
		m_Position = pos;
	}
	
	void vgCloud::Init()
	{			
	
		assert( m_pTexture.isNull() );
		m_pTexture = 
			vgCore::TextureManager::getSingleton().getTexturePtr( m_texturename );
	}
	
	void vgCloud::Render()
	{
		glEnable(GL_TEXTURE_2D) ;
		m_pTexture->useBind();
		
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		
		glBegin(GL_TRIANGLE_STRIP);						
		glTexCoord2d(1,1); 
		glVertex3f(m_Position.x+cloudBound.width, 
			m_Position.y, m_Position.z+cloudBound.height); 
		glTexCoord2d(0,1); 
		glVertex3f(m_Position.x-cloudBound.width, 
			m_Position.y, m_Position.z+cloudBound.height); 
		glTexCoord2d(1,0); 
		glVertex3f(m_Position.x+cloudBound.width, 
			m_Position.y, m_Position.z-cloudBound.height); 
		glTexCoord2d(0,0); 
		glVertex3f(m_Position.x-cloudBound.width, 
			m_Position.y, m_Position.z-cloudBound.height); 
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
		
	}

	
	
}	//namespace vgCore
