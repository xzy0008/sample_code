


#ifndef __VGSHSELECTOR_H__
#define __VGSHSELECTOR_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshLayer.h>

	
namespace vgShape {


	using namespace vgKernel;


	typedef std::vector< Vec3d > Vec3dVector;

	/**
		@date 	2009/02/20  9:21	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGSH_EXPORT Selector : public vgKernel::InputHandler
	{
	public:
		Selector( Layer* layer );
		virtual ~Selector();


		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);

		void selectLayerGeometry( CPoint position , bool add_before_clear );

		void render();

		Layer* getLayerPtr()
		{
			assert( _layer != NULL );
			return _layer;
		}
		

	private:

		static void drawPoint( const Vec3d& point );
		static void drawLines( const Vec3dVector& points , const Vec3d& mousevec );
		static void drawHeight( Vec3dVector* points );
		static Vec3d get3dVecFrom2d( const CPoint& point_2d );

		void SelectRectObject();

	private:

		Layer* _layer;

		bool _LBtnDown;

		float	m_start_x;
		float	m_start_y;
		float	m_drag_x;
		float	m_drag_y;
		float	m_end_x;
		float	m_end_y;

		int		m_window_width;
		int		m_window_height;


		Vec3d _mouseVec;


		Vec3dVector _clickPoints;

		Vec3dVector* _heightRender;

		//TerrainManager* _terrainMgr;


		//ElevationBound _sceneBound;

	};
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHSELECTOR_H__