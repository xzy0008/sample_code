



#include <vgStableHeaders.h>
#include <vgAutoBuild/vgMarkBuildHandle.h>

#include <vgKernel/vgkInputCodeDef.h>

#include <vgKernel/vgkMath.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>
#include <vgKernel/vgkSelectManager.h>
namespace vgAutoBuild {
	
	

	//----------------------------------------------------------------
	MarkBuildHandler::MarkBuildHandler()
	{
		m_markbuilding = NULL;
		m_dynamicPoint = vgKernel::Vec3();
		m_bOperationDone = false;

		SetHandleStatus( VG_INPUT_LANDMARKBUILD_SELECTOR );

		vgKernel::InputSystem::getSingleton().registerHandle( this );

		vgKernel::InputSystem::getSingleton().AddHandleStatus(VG_INPUT_LANDMARKBUILD_SELECTOR);

	}
	//----------------------------------------------------------------
	MarkBuildHandler::~MarkBuildHandler()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().RemoveHandleStatus(VG_INPUT_LANDMARKBUILD_SELECTOR);
		
	}
	// ÊäÈëÄ£¿é ---------------------------------------------------
	void MarkBuildHandler::OnLButtonDown(UINT nFlags, CPoint position)
	{
		return;
	}
	//----------------------------------------------------------------
	void MarkBuildHandler::OnLButtonDbClick(UINT nFlags, CPoint position)
	{
		if (m_markbuilding == NULL)
		{
			m_selectedPoint = vgKernel::Math::
				trans2DPointTo3DVec(position.x, position.y);

			m_markbuilding = new MarkBuildNode(m_selectedPoint);

			AutoBuildManager::getSingleton().addMarkBuildNode(m_markbuilding);

			m_bOperationDone = true;
		}

		return;
	}
	//----------------------------------------------------------------
	void MarkBuildHandler::OnRBottonUp(UINT nFlags, CPoint position)
	{
		return;
	}

	//----------------------------------------------------------------
	void MarkBuildHandler::OnMouseMove(UINT nFlags, CPoint position)
	{
		if ( !m_bOperationDone )
		{
			m_dynamicPoint = vgKernel::Math::
				trans2DPointTo3DVec(position.x, position.y);;
		}

		return;
	}
	//----------------------------------------------------------------
	void MarkBuildHandler::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
	{
		return;
	}
	//äÖÈ¾Ä£¿é----------------------------------------------------------
	void MarkBuildHandler::renderDynamicPoint()
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
	void MarkBuildHandler::render()
	{
		if (!m_bOperationDone)
		{
			renderDynamicPoint();
		}
	}

	
}// end of namespace vgAutoBuild
