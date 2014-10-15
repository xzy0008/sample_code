


#ifndef __VGGISMATCHDRAWER_H__
#define __VGGISMATCHDRAWER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgMod/vgGisRoadMatch.h>

	

namespace vgCore {

	class vgMod::GisRoadMatch;

	using namespace vgKernel;


	typedef std::vector< Vec3 > Vec3Vector;

	/**
		@date 	2008/10/31  9:10	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT GisMatchDrawer : public vgKernel::InputHandler
	{
	public:
		GisMatchDrawer( vgMod::GisRoadMatch* gismatch );
		virtual ~GisMatchDrawer();
	
	
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);


		void render();

	private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec );
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );

	private:

		Vec3 _mouseVec;
		
		Vec3Vector _clickPoints;

		vgMod::GisRoadMatch* _gismatch;

		bool b_render;

	};

	
}// end of namespace 
	


#endif // end of __VGTGisMatchDrawer_H__