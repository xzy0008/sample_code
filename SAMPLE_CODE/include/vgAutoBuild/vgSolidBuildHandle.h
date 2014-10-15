


#ifndef __VGAUTOBUILDHANDLE_H__
#define __VGAUTOBUILDHANDLE_H__



#include <vgMod/vgdepDefinition.h>

#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkVec3.h>
#include <vgAutoBuild/vgSolidBuildNode.h>

/********************************************************************
@date:		2010/04/03
@author:	YUXIN
@brief 	
@see  
*********************************************************************/

namespace vgAutoBuild {


	typedef std::vector<vgKernel::Vec3>	PointsArray;

	class VGDEP_EXPORT SolidBuildHandler : public vgKernel::InputHandler
	{
	public:
		SolidBuildHandler();
		
		virtual ~SolidBuildHandler();
	
	
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnRBottonUp(UINT nFlags, CPoint position);
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		void    render();
		void	renderPolygon();
		void    renderDynamicPoint();


	private:

		PointsArray      m_selectedPoints;
		vgKernel::Vec3   m_dynamicPoint;

		SolidBuildNode*  m_solidbuilding;
		bool			 m_bElevationDone;
		bool			 m_bOperationDone;

	};
	
}// end of namespace vgAutoBuild
	


#endif // end of __VGAUTOBUILDHANDLE_H__