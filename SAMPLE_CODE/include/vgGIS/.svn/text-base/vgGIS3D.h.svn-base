#ifndef _VGGIS3D_H_INCLUDED_
#define _VGGIS3D_H_INCLUDED_
#if 0
#include <vgGis/vggisDefinition.h>

#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkVec3.h>

//#include <vgCore/vgSingleton.h>
#include <vgGIS/vggisAnalysisHandle.h>


namespace vgGIS3D//vgGIS3D命名空间
{
	using namespace vgKernel;

	//enum EGisState{	GisNone,GisCoordinate,GisDistance,GisArea,GisVolume,GisWaterArea,\
	//	GisWaterVolume,GisSoilVolume,GisP2PVisibility,GisSection,/*GisTerrainLeveling,*/\
	//	GisContour,GisAddVertexString,GisEditVertexString,GisTerLeveling,\
	//	GisHideVec};

	typedef std::vector<vgKernel::Vec3>	PointsArray;
	class  VGG_EXPORT GIS3D: public vgKernel::Singleton<GIS3D>
//		 ,public vgKernel::InputHandler//  [11/6/2008 zhu]
	{
		friend class vgKernel::Singleton<GIS3D>;
		//成员函数
	public :
		GIS3D();
		virtual ~GIS3D();

	protected:
		virtual bool initialise()
		{
			avh=0;
			return true;
		}
		virtual bool shutdown()
		{
			//VertexRecord.clear();
			return true;
		}
	public:
		virtual void reset();
		//============================
		//实现继承InputHandle的代码
		/*virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		virtual void OnRBottonDown(UINT nFlags, CPoint position) ;*/

		//============================
	public :
		void init();//初始化
		// 鼠标操作和渲染 [10/24/2008 zhu]
		void GisLBtDn(CPoint point);
		void GisLBtDblClk(CPoint point);
		void GisMsMv(CPoint point);
		void GisMouseWheel(short zDelta);
		//////////////////////////////////////////////////////////////////////////
		void  renderGisElements();
		void KeyBDWater();
		//////////////////////////////////////////////////////////////////////////
		//主要接口函数
		//////////////////////////////////////////////////////////////////////////
		void pickAndAppendPoint(CPoint point);//左键单击获得一个数值
		void MousePoint(CPoint point);
		void getDynamicPoint(CPoint point);
		void OnePoint(CPoint point);
		void ThreePoints(CPoint point);
		//////////////////////////////
		//查询计算
		//////////////////////////////
		float  getDistance();
		float  getArea();
		double  getVolume();
		void PreCalculation();
		void renderTT();

		float getWaterArea( );
		///////////////////////
		//不规则体积
		/////////////////////////////
		float getSoilVolume( );
		float getWaterVolume( );
		//////////////////////////////
		void ShowMessage();


		///////////////////////////////////////////////////////////////////////////
		//下面是辅助计算面积的函数
		///////////////////////////////////////////////////////////////////////////
		float calcdist(vgKernel::Vec3 v1,vgKernel::Vec3 v2);//那时还不知道直接调用现成的呢
		float detxz(vgKernel::Vec3 p0,vgKernel::Vec3 p1,vgKernel::Vec3 p2);
		float detxy(vgKernel::Vec3 p0,vgKernel::Vec3 p1,vgKernel::Vec3 p2);
		float detyz(vgKernel::Vec3 p0,vgKernel::Vec3 p1,vgKernel::Vec3 p2);
		float areaxz(/*int n,std::Vec3<vgKernel::Vec3>& p*/);
		float areaxy(int n,PointsArray& p);
		float areayz(int n,PointsArray& p); 
		int pdcz(PointsArray& p);
		float mycos(int a,PointsArray& p);
		float area(int n,PointsArray& p);
		///////////////////////////////////////////////////////////////////////////
		//下面是辅助计算通透的函数
		///////////////////////////////////////////////////////////////////////////
		float hailun(vgKernel::Vec3 a,vgKernel::Vec3 b,vgKernel::Vec3 c);
		bool dmn(vgKernel::Vec3 m[3],vgKernel::Vec3 p1);
		float dmjl(vgKernel::Vec3 m[3],vgKernel::Vec3 p1);
		bool tcpd(vgKernel::Vec3 m[3],vgKernel::Vec3 p1,vgKernel::Vec3 p2);
		bool dyzdpd(vgKernel::Vec3 m[3],vgKernel::Vec3 p1,vgKernel::Vec3 p2);
		bool zdpd(vgKernel::Vec3 p1,vgKernel::Vec3 p2,float a,float b,float c);
		void Freshdata();
		bool seeornot(vgKernel::Vec3 p1,vgKernel::Vec3 p2);

		EGisState getGisState();

		bool	setGisState(EGisState gisState);

		//void	setCurrentVertexStringPtr(VertexString *pVert);
		//成员变量
	public:
		//int gis_state;//gis_state=1是测量坐标
		EGisState m_gis_state;
		int gis_cut;
		int gis_plane;
		bool dhk;
		vgKernel::Vec2 pos2[50];
		//vgKernel::Vec3 pos3[50],m_endPoint;
		vgKernel::Vec3	m_endPoint;

		//GLdouble rect[50][3];
		int psnum;
		float WaterHeight;
		int newMouseY;
		bool bMouseMove;
		bool btm;
		bool gis_tt;
		bool gis_ss;
		GLuint waterterID;
		float xx[1100],yy[1100],zz[1100],zzmax,zzmin;
		int hjmnum;
		bool hjm;
		//vgMath::Math mymath;
		GLUtesselator *basetess;
		float avh;
		
		//vgKernel::Vec3 *SelectedPoint;
		//vgKernel::Vec3	m_mousePoint;
		

		//vgKernel::Vec3	Trans2DTo3D(CPoint &point);
		
		void NewLevelPoly();
		
		//void PolyTerPlane(int num, vgKernel::Vec3* pos);
		double **rect;

		// add by lss 2009年6月22日20:55:35
	private:
		void	renderPoint();
		void	renderLine();
		void	renderPolygon();
		void	renderBody();

		void	renderWaterSurface();
		void	renderWaterBody();

		void	renderPoint2PointVisible();

		void    renderEqualHeightLine();

		void	renderPointsByMode(const PointsArray& points, int nRenderMode,
			bool bOperationDone = false, bool bCloseRing = false);
		
		// add by lss 2009年6月22日20:55:35
	private:
		bool			m_bOperationDone;
		bool			m_bCloseRing;
		PointsArray		m_pointsInLine;
		vgKernel::Vec3	m_pointDynamic;

	private:
		GisAnalysis*	_gisAnalysis;

	public:
		bool	setGisAnalysis( EGisState eType);

		GisAnalysis*	getGisAnalysis();
		EGisState		getAnalysisType();

	}; //class GIS3D
}//vgGIS3D命名空间


#endif//_VGMGIS_H_INCLUDED_
#endif