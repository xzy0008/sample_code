
#include <vgStableHeaders.h>
#include <vgGIS3D/vggiPipeTripleHandling.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgGIS3D
{
	vgTripleHandling::~vgTripleHandling()
	{

	}

	void vgTripleHandling::renderOnceForDisplayList()
	{
		glDisable( GL_TEXTURE_2D );	
		glEnable(GL_DEPTH_TEST);
		glColor3f(colorInfo[0], colorInfo[1], colorInfo[2]);
		glPushMatrix();
		glTranslatef(m_centerPoint.x, m_centerPoint.y, m_centerPoint.z);	
		gluSphere(yuanqiu, 1.5*m_pipeRadius, 20, 20);
		glRotatef(m_angleVec[0], m_drecVec[0].x, m_drecVec[0].y, m_drecVec[0].z);
		gluCylinder(quadyuanzhu, 1.5*m_pipeRadius, 1.5*m_pipeRadius, 4*m_pipeRadius, 20, 20);

		glTranslatef(0.0f, 0.0f, 4*m_pipeRadius);					
		gluDisk(yuanhuan, 0.0, 1.5*m_pipeRadius, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(m_centerPoint.x, m_centerPoint.y, m_centerPoint.z);
		glRotatef(m_angleVec[1], m_drecVec[1].x, m_drecVec[1].y, m_drecVec[1].z);
		gluCylinder(quadyuanzhu, 1.5*m_pipeRadius, 1.5*m_pipeRadius, 4*m_pipeRadius, 20, 20);

		glTranslatef(0.0f, 0.0f, 4*m_pipeRadius);					
		gluDisk(yuanhuan, 0.0, 1.5*m_pipeRadius, 20, 20);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(m_centerPoint.x, m_centerPoint.y, m_centerPoint.z);
		glRotatef(m_angleVec[2], m_drecVec[2].x, m_drecVec[2].y, m_drecVec[2].z);
		gluCylinder(quadyuanzhu, 1.5*m_pipeRadius, 1.5*m_pipeRadius, 4*m_pipeRadius, 20, 20);

		glTranslatef(0.0f, 0.0f, 4*m_pipeRadius);					
		gluDisk(yuanhuan, 0.0, 1.5*m_pipeRadius, 20, 20);
		glPopMatrix();

	}

	void vgTripleHandling::initialColors()
	{
		colorInfo[0] = 0.0f;
		colorInfo[1] = 0.0f;
		colorInfo[2] = 1.0f;
	}

	void vgTripleHandling::renderUsingDisplayList()
	{
		VGK_CHECK_OPENGL_ERROR();

		if (m_TripleCallList == 0)
		{
			m_TripleCallList = glGenLists( 1 );   
			assert( m_TripleCallList != 0 );

			glNewList( m_TripleCallList, GL_COMPILE );
			renderOnceForDisplayList();
			glEndList();
		}

		VGK_CHECK_OPENGL_ERROR();

		assert(m_TripleCallList != 0);
		glPushMatrix();
		glCallList(m_TripleCallList);
		glPopMatrix();
	}

	void vgTripleHandling::revertSolidColor()
	{
		initialColors();
		invalidateRendering();
	}

	void vgTripleHandling::setSolidColor(bool update)
	{
		colorInfo[0] = 0.0f;
		colorInfo[1] = 0.0f;
		colorInfo[2] = 0.0f;

		if (update)
		{
			invalidateRendering();
			renderUsingDisplayList();
		}
	}

	void vgTripleHandling::invalidateRendering()
	{
		if (m_TripleCallList != 0)
		{
			VGK_CHECK_OPENGL_ERROR();

			glDeleteLists(m_TripleCallList, 1);
			m_TripleCallList = 0;

			VGK_CHECK_OPENGL_ERROR();
		}		
	}

	void vgTripleHandling::getBoxPosVec()
	{
		vgKernel::Vec3 pos;
		pos.x = m_centerPoint.x - 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y - 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z - 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x - 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y - 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z + 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y - 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z + 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y - 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z - 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x - 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y + 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z - 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x - 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y + 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z + 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y + 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z + 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);

		pos.x = m_centerPoint.x + 4.1*m_pipeRadius;
		pos.y = m_centerPoint.y + 1.6*m_pipeRadius;
		pos.z = m_centerPoint.z - 4.1*m_pipeRadius;
		m_boxPosVec.push_back(pos);			
	}

	void vgTripleHandling::mergeBox()
	{
		assert(!m_boxPosVec.empty());
		for (int i = 0; i < m_boxPosVec.size(); i++)
		{
			_box3d.merge(Vec3d(m_boxPosVec[i]));
		}
	}

}// end nameSpace