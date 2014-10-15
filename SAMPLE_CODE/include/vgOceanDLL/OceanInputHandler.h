//
//
//
#ifndef __OCEANINPUTHANDLER_H__
#define __OCEANINPUTHANDLER_H__



#include <VOdefinition.h>

#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkVec3.h>

namespace VR_Ocean {


	typedef std::vector<vgKernel::Vec3>	PointsArray;

	/*********************************************
	use   : handler for input of keyboard and mouse
	author: livenson 
	date  : 2009.11.25
	  
	*********************************************/

	class VO_EXPORT COceanInputHandler : public vgKernel::InputHandler
	{
	public:
		COceanInputHandler(int a);

		virtual ~COceanInputHandler();


		//virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		void COceanInputHandler::OnKeyDown(int keyCode);
		//virtual void OnLButtonDbClick(UINT nFlags, CPoint position);

	private:
	/*	void	pickAndAppendPoint(CPoint point);
		void	getDynamicPoint(CPoint point);

		void	showResult();

		float	calculateDistance(const PointsArray& points);
		float	calculateArea(const PointsArray& points);
		float	calculateVolume(const PointsArray& points);
		float	calculateAngleCos(const PointsArray& points);

		void	renderPoint(const PointsArray& points);
		void	renderLine(const PointsArray& points);
		void	renderPolygon(const PointsArray& points);
		void	renderPointsByMode(const PointsArray& points, int nRenderMode,
			bool bOperationDone = false, bool bCloseRing = false);


	private:

		bool			m_bOperationDone;
		bool			m_bCloseRing;
		PointsArray		m_pointsInLine;
		vgKernel::Vec3	m_pointDynamic;*/
	};


}// end of namespace VR_Ocean


#endif // end of __OCEANINPUTHANDLER_H__


