


#ifndef __VGMARKBUILDHANDLE_H__
#define __VGMARKBUILDHANDLE_H__



#include <vgMod/vgdepDefinition.h>

#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkVec3.h>
#include <vgAutoBuild/vgMarkBuildNode.h>

/********************************************************************
@date:		2010/04/03
@author:	YUXIN
@brief 	
@see  
*********************************************************************/

namespace vgAutoBuild {


	class VGDEP_EXPORT MarkBuildHandler : public vgKernel::InputHandler
	{
	public:
		MarkBuildHandler();
		
		virtual ~MarkBuildHandler();
	
	
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnRBottonUp(UINT nFlags, CPoint position);
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		void    render();
		void	renderPolygon();
		void    renderDynamicPoint();


	private:

		vgKernel::Vec3   m_selectedPoint;
		vgKernel::Vec3   m_dynamicPoint;

		MarkBuildNode*   m_markbuilding;
		bool			 m_bOperationDone;

	};
	
}// end of namespace vgAutoBuild
	


#endif // end of __VGAUTOBUILDHANDLE_H__