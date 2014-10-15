



#include <vgStableHeaders.h>
#include <vgAutoBuild/vgSolidBuildHandle.h>

#include <vgKernel/vgkInputCodeDef.h>

#include <vgKernel/vgkMath.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>
#include <vgKernel/vgkSelectManager.h>
namespace vgAutoBuild {
	
	

	//----------------------------------------------------------------
	SolidBuildHandler::SolidBuildHandler()
	{
		m_solidbuilding = NULL;
		m_dynamicPoint = vgKernel::Vec3();
		m_bElevationDone = false;
		m_bOperationDone = false;

		SetHandleStatus( VG_INPUT_AUTOBUILD_SELECTOR );

		vgKernel::InputSystem::getSingleton().registerHandle( this );

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_AUTOBUILD_SELECTOR |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );


	}
	//----------------------------------------------------------------
	SolidBuildHandler::~SolidBuildHandler()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();
		
	}
	// ÊäÈëÄ£¿é ---------------------------------------------------
	void SolidBuildHandler::OnLButtonDown(UINT nFlags, CPoint position)
	{
		vgKernel::Vec3 tempVec = vgKernel::Math::
			trans2DPointTo3DVec(position.x, position.y);

		m_selectedPoints.push_back( tempVec );
		return;
	}
	//----------------------------------------------------------------
	void SolidBuildHandler::OnLButtonDbClick(UINT nFlags, CPoint position)
	{
		m_solidbuilding = new SolidBuildNode(m_selectedPoints);

		AutoBuildManager::getSingleton().addSolidBuildNode(m_solidbuilding);

		vgKernel::InputSystem::getSingleton().setCurrentStatus(VG_INPUT_AUTOBUILD_SELECTOR | VG_INPUTMODE_UI );
		
		m_bElevationDone = false;
		m_selectedPoints.clear();

		return;
	}
	//----------------------------------------------------------------
	void SolidBuildHandler::OnRBottonUp(UINT nFlags, CPoint position)
	{
		m_selectedPoints.clear();

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_AUTOBUILD_SELECTOR |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );
		m_bElevationDone = true;

		return;
	}

	//----------------------------------------------------------------
	void SolidBuildHandler::OnMouseMove(UINT nFlags, CPoint position)
	{
		if ( !m_bOperationDone )
		{
			m_dynamicPoint = vgKernel::Math::
				trans2DPointTo3DVec(position.x, position.y);;
		}
		return;
	}
	//----------------------------------------------------------------
	void SolidBuildHandler::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
	{
		if (m_bElevationDone)
		{
			return;
		}
		if (m_solidbuilding == NULL)
		{
			return;
		}

		if (zDelta > 0)
		{
			m_solidbuilding->setFloor(m_solidbuilding->getFloor()+1);
		}
		else
		{
			m_solidbuilding->setFloor(m_solidbuilding->getFloor()-1);
		}

	}
	//äÖÈ¾Ä£¿é----------------------------------------------------------
	void SolidBuildHandler::renderPolygon()
	{
		if (m_selectedPoints.empty())
		{
			return;
		}

		glColor3f(1,1,0);

		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glPushAttrib(GL_CURRENT_BIT);
		glPointSize(3.0);

		glBegin(GL_LINE_LOOP);
		for(PointsArray::const_iterator iter = m_selectedPoints.begin();
			iter != m_selectedPoints.end(); iter ++)
		{
			glVertex3fv(iter->v);
		}

		glVertex3fv(m_dynamicPoint.v);

		glEnd();

		glPopAttrib();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void SolidBuildHandler::renderDynamicPoint()
	{
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		glPushAttrib(GL_CURRENT_BIT);
		glPointSize(3.0);

		glColor3f(100, 0, 0);
		glBegin(GL_POINTS);
			glVertex3fv(m_dynamicPoint.v);
		glEnd();

		glPopAttrib();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void SolidBuildHandler::render()
	{
		renderPolygon();

		if (!m_bOperationDone)
		{
			renderDynamicPoint();
		}
	}

	
}// end of namespace vgAutoBuild
