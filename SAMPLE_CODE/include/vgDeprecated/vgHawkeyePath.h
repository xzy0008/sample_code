// HawkeyePath.h: interface for the HawkeyePath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGPATH_H__38E4CB97_5E40_4CB2_8C41_732F619C24D9__INCLUDED_)
#define AFX_VGPATH_H__38E4CB97_5E40_4CB2_8C41_732F619C24D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <vgStableHeaders.h>
#include <vgTex/tvgNormalImage.h>
#include <vgSmallMap.h>

namespace vgCore
{

	struct ImagePoint 
	{
		int x,y;
	};

	struct PointControl 
	{
		ImagePoint point;

		int m_ID;
	};

	struct PathEdgeSet 
	{
		RGBQUAD Color;

		int count;

		vector<ImagePoint> Pointset;

	};

	class HawkeyePath  
	{
	public:
		HawkeyePath();
		virtual ~HawkeyePath();

	public:
		void PathAnalyse();
		void DrawStartPoint();
		void DrawEndPoint();
		void DrawLine();
		ImagePoint StartPoint,EndPoint;	

		float start3dx,start3dy,end3dx,end3dy;

		int DotCount;

		bool b_drawstart,b_drawend;

		vector<ImagePoint> PathPointSet;

		vector<Vector3> pointsInScene;

		void Draw();

	private:
		ImagePoint TheBlockInLine(int StartX, int EndX, int StartY, int EndY);
		bool IsinsameLine(ImagePoint &front,ImagePoint &mid,ImagePoint &back);
		void ElasticFun();
		void GetSection();
		void GenIniPath();
		void GetTheIntersectionPoint(int StartX, int EndX, int StartY, int EndY);
		void QueueProc(int i);
		void ListGrow();
		void IniEdgeDataset(DWORD width,DWORD height);
		void ImageProc();
		void IniSecondPoint(int k);   //第二个点肯定在第一个点的上方。。。？？？
		CximagePtr pcximage;

		vector<PathEdgeSet> m_edgeset;

		vector<ImagePoint> IntersectionPointSet;

		vector<ImagePoint>::iterator pathitr;

		int m_pathpos;

		vector<ImagePoint> tempset;

		PointControl m_front,m_mid,m_back,m_last;

	public:
		void GetPoints(const CPoint &point,SmallMap *pvgMap);
		void DrawInScene();

		bool b_PathFly;

		void showpath();

		void Disshowpath();



	};
}
#endif // !defined(AFX_VGPATH_H__38E4CB97_5E40_4CB2_8C41_732F619C24D9__INCLUDED_)
