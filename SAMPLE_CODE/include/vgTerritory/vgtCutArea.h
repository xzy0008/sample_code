


#ifndef __VGTCUTAREA_H__
#define __VGTCUTAREA_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkRenderer.h>


namespace vgTerritory {

		
	class TerrainManager;

	using namespace vgKernel;


	typedef std::vector< double* >   doublePtrVec;


	// 二维线段用于判断多边形是否自相交
	typedef struct tagSEGMENT
	{
		Vec2  start;
		Vec2  end;

	}Segment;

	/**
		@date 	2008/10/31  9:10	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT CutArea : public vgKernel::InputHandler
	{
	public:
		CutArea();
		~CutArea();
	
	
		virtual void OnKeyDown(int keyCode);
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnRBottonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);


		void render();

		void reset();

		Vec3Vector* getClickPoints()
		{
			return &_clickPoints;
		}


	private:

		void drawPoint( const Vec3& point );
		void drawLines( const Vec3Vector& points , const Vec3& mousevec );
		void fillArea( const Vec3Vector& points );  // 凹多边形填充
		void drawHeight( Vec3Vector* points );
		Vec3 get3dVecFrom2d( const CPoint& point_2d );
		void addClickPoint();

		// 以下两函数用于判断多边形是否自相交
		bool isSimplePolygon( const Vec3Vector& pointsVec );
		void createSegment( const Vec3Vector& pointsVec );
		
		void clearVecForTess();
		void clearDisplayList();
		void destroySegment();

	private:

		Vec3 _mouseVec;

		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;

		TerrainManager* _terrainMgr;


		ElevationBound _sceneBound;

		bool  _bStopRecord;         // 标识OnMouseMove是否要记录点

		bool           _bFillArea;   // 是否渲染填充的多边形
		GLuint         _callListId;
		doublePtrVec   _vecForTess;  // 用于凹多边形填充

		bool           _bHasSelectOperate;

		Segment*       _pSegment;

	};

	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTCUTAREA_H__
