
#include <vgStableHeaders.h>
#include <vgGIS3D/vggiPipeValves.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgGIS3D
{
	vgPipeValves::~vgPipeValves()
	{

	}

	void vgPipeValves::renderOnceForDisplayList()
	{
		//glColor3f(0.5f, 0.0f, 1.0f);	
		glDisable( GL_TEXTURE_2D );	
		glEnable(GL_DEPTH_TEST);
		glColor3f(colorInfo[0][0], colorInfo[0][1], colorInfo[0][2]);
		glPushMatrix();
		glTranslatef(m_centerPoint.x, m_centerPoint.y, m_centerPoint.z);
		glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadyuanzhu, 0.8*m_pipeRadius, 0.8*m_pipeRadius, 2.0*m_pipeRadius, 20, 20);
		glTranslatef(0.0f, 0.0f, 2.0*m_pipeRadius);
		gluCylinder(quadyuanzhu, 1.4*m_pipeRadius, 1.4*m_pipeRadius, 0.4*m_pipeRadius, 20, 20);
		gluCylinder(quadyuanzhu, m_pipeRadius, m_pipeRadius, 0.4*m_pipeRadius, 20, 20);
		gluDisk(yuanhuan, 0.0f, 0.8*m_pipeRadius, 20, 20);
		gluDisk(yuanhuan, m_pipeRadius, 1.4*m_pipeRadius, 20, 20);
		glTranslatef(0.0f, 0.0f, 0.4*m_pipeRadius);
		gluDisk(yuanhuan, m_pipeRadius, 1.4*m_pipeRadius, 20, 20); 		

		//glColor3f(1.0f, 0.0f, 0.0f);
		glColor3f(colorInfo[1][0], colorInfo[1][1], colorInfo[1][2]);
		glTranslatef(0.0f, 0.0f, -0.2*m_pipeRadius);
		glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadyuanzhu, 0.2*m_pipeRadius, 0.2*m_pipeRadius, m_pipeRadius, 20, 20); 		 

		glRotatef(180.0, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadyuanzhu, 0.2*m_pipeRadius, 0.2*m_pipeRadius, m_pipeRadius, 20, 20); 		  

		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		gluCylinder(quadyuanzhu, 0.2*m_pipeRadius, 0.2*m_pipeRadius, m_pipeRadius, 20, 20);   

		glRotatef(180, 0.0f, 1.0f, 0.0f);
		gluCylinder(quadyuanzhu, 0.2*m_pipeRadius, 0.2*m_pipeRadius, m_pipeRadius, 20, 20); 	

		glPopMatrix();
	}

	void vgPipeValves::renderUsingDisplayList()
	{
		VGK_CHECK_OPENGL_ERROR();

		if (m_valvesCallList == 0)
		{
			m_valvesCallList = glGenLists( 1 );   
			assert( m_valvesCallList != 0 );

			glNewList( m_valvesCallList, GL_COMPILE );
			renderOnceForDisplayList();
			glEndList();
		}

		VGK_CHECK_OPENGL_ERROR();

		assert(m_valvesCallList != 0);
		glPushMatrix();
		glCallList(m_valvesCallList);
		glPopMatrix();
	}

	void vgPipeValves::revertSolidColor()
	{
		initialColors();
		invalidateRendering();
	}

	void vgPipeValves::setSolidColor(bool update)
	{
		for (int i = 0; i < 2; i++)
		{
			colorInfo[i][0] = 0.0f;
			colorInfo[i][1] = 0.0f;
			colorInfo[i][2] = 0.0f;
		}

		if (update)
		{
			invalidateRendering();
			renderUsingDisplayList();
		}
	}

	void vgPipeValves::invalidateRendering()
	{
		if (m_valvesCallList != 0)
		{
			VGK_CHECK_OPENGL_ERROR();

			glDeleteLists(m_valvesCallList, 1);
			m_valvesCallList = 0;

			VGK_CHECK_OPENGL_ERROR();
		}		
	}

	void vgPipeValves::getBoxPosVec()
	{
		vgKernel::Vec3 pos;
		pos.x = m_centerPoint.x - 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y;
		pos.z = m_centerPoint.z - 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x - 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y;
		pos.z = m_centerPoint.z + 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y;
		pos.z = m_centerPoint.z + 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y;
		pos.z = m_centerPoint.z - 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x - 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y + 3.0*m_pipeRadius;
		pos.z = m_centerPoint.z - 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x - 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y + 3.0*m_pipeRadius;
		pos.z = m_centerPoint.z + 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y + 3.0*m_pipeRadius;
		pos.z = m_centerPoint.z + 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 1.5*m_pipeRadius;
		pos.y = m_centerPoint.y + 3.0*m_pipeRadius;
		pos.z = m_centerPoint.z - 1.5*m_pipeRadius;
		m_boxPosVec.push_back(pos);			
	}

	void vgPipeValves::mergeBox()
	{
		assert(!m_boxPosVec.empty());
		for (int i = 0; i < m_boxPosVec.size(); i++)
		{
			_box3d.merge(Vec3d(m_boxPosVec[i]));
		}
	}

}// end nameSpace