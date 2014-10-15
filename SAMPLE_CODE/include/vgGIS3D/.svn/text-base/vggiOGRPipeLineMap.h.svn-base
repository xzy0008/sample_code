#pragma once

#include <vgGIS3D/vggiPipeLineMap.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkRenderer.h>

#include <vgGIS3D/vggiRouteInfo.h>
#include <vgGIS3D/vggiPrerequisite.h>
#include <vgGIS3D/PipeLineObject.h>
#include <vgGIS3D/PipelineDatabase.h>
#include <vgGIS3D/vggiOGRRouteMap.h>
#include <vgGis3d/vggiGeometry.h>
#include <vgGis3d/vggiLine.h>
#include <vgGis3d/vggiBuildingSolid.h>
#include <vgGis3d/vggiLayer.h>

#include <vgGIS3D/vggiPipeGeometry.h>
#include <vgGIS3D/vggiPipeValves.h>
#include <vgGIS3D/vggiPipeTripleHandling.h>
#include <vgGIS3D/vggiPipeFourHandling.h>
#include <vgGIS3D/vggiBuffer.h>


namespace vgGIS3D
{
   #ifndef PI
   #define PI 3.141592653589793f
   #endif

	class VGG_EXPORT OGRPipeLineMap : public PipeLineMap,
		public OGRRouteMap, public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( OGRPipeLineMap )
	public:
		OGRPipeLineMap(vgKernel::Renderer* pInnerRenderer = NULL);

		~OGRPipeLineMap();		

		int convertShapeLayerToPipe(string layerName);

		double getPipeLineLongth();

		//float    getPiPeLineRidius();
		//int readFromFile(string filePath);
		//int saveToFile(string filePath);

		
	public:
		//从renderer继承来的成员函数

		//virtual RendererType getType() {return -1;}
		//virtual String getTypeDesc() {return m_typeDesc;}

		virtual String getName() 
		{
			return m_layerName;
		}

		virtual String* getNamePtr() 
		{
			return &m_layerName;
		}		

		virtual void setName( const String& newname ) 
		{
			m_layerName = newname;
		}		

		Layer *getShapeLayer();

		virtual bool getVisible(){return true;}

		virtual vgKernel::UniqueID getUniqueID() {return m_uniqueID;}

		virtual void moveTo( const vgKernel::Vec3& newpos )
		{
			moveTo( newpos.x , newpos.y , newpos.z );
		}

		virtual void moveTo(const float& x, const float& y, const float& z) 
		{
			vgKernel::Vec3 center = getBoundingBox().getCenter();

			if ( center.x != x || center.y != y || center.z != z)
			{
				translate(x-center.x, y-center.y, z-center.z);
			}
		}

		virtual void translate(const float& x, const float& y, const float& z) {}

		virtual void rotateSelf(const float& angle, 
			const float& x, const float& y, const float& z) {}

		virtual void scale(const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) {}

		virtual void rotate(const float& angle, 
			const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) {}


		virtual vgKernel::Box getBoundingBox() 
		{
            return _dynamicBox;
		}

		virtual long getNumOfTriangles() {return 0;}

		/**
		注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  ) {return 0;}

		//virtual void	render() = 0;

		virtual bool testPointInObject(const vgKernel::Vec3& point) { return false; }

		virtual bool testIntersectWithTriangles( 
			const vgKernel::Segment3& segment )
		{
			return false;			
		}

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray )
		{
			return vgKernel::Math::intersects( ray , getBoundingBox() );
		}

		virtual vgKernel::Vec3 getPosition()
		{
			return getBoundingBox().getCenter();
		}

		virtual void render();

	public:
		vgKernel::Box _dynamicBox;
		vgKernel::Box _staticBox;

		vgKernel::UniqueID	m_uniqueID;

		float _transX;
		float _transY;
		float _transZ;

		bool _inEditMode;
		bool _inAnalysisMode;

		Layer *m_player;

	public:
		void createDigraphAdjList();		

		void getPipeLineDrection(vgKernel::Vec3 ptr1, vgKernel::Vec3 ptr2);

		void DrawEachPipeLine(RingStruct m_ring, double pipeRadius);

		void CalculateCoordinateOnPipeLine(vgKernel::Vec3 pt3D1, vgKernel::Vec3 pt3D2, vgKernel::Vec3 pt3D3, std::vector<vgKernel::Vec3>& pt3DArray);
		
		double CalculateAngleBetweenTwoLines(vgKernel::Vec3 pt1, vgKernel::Vec3 pt2, vgKernel::Vec3 pt3);
		
		void renderContactPipeLine(float pipeRadius);		

		void pushGeometry( Geometry* geo );

		void turnSelectLineToRing();

	public:	
		PipeLineObject m_lineObject;		

		int _numOfPoints;

		float m_pipeLineRadius;

		GeometryPointerVec _geometries;

		vector<JointPointPtr> m_digraphAdjList;  //有向图邻接表

		vgKernel::Mat4 _matrix;

		GeometryPointerVec _selectedGeometries;
		std::vector <RingStruct> m_selectedRing;

	public:
		Geometry* testIntersectWithGeometry( 
			const RayLine3d& rayline );

		void setSelectedGeometry( Geometry* selected_geo );
		// 内部保证了插入的唯一性
		void addSelectedGeometry( Geometry* add_geo );
		void delSelectedGeometry( Geometry* del_geo );

		void clearSelectedGeometry();

		void clearSelectedPoint();

		vector<JointPointPtr>* getJointArray()
		{
			return &m_jointArray;
		}

		std::vector <PointStruct>* getSelectedPointVec()
		{
			return &m_selectPointVec;
		}

		GeometryPointerVec* getSelectedGeometry()
		{
			return &_selectedGeometries;
		}

		GeometryPointerVec* getGeometries()
		{
			return & _geometries;
		}

		GeometryPointerVec& getGeometriesRef()
		{
			return _geometries;
		}

		vgKernel::Mat4 getMatrix() const 
		{
			return layerMatrix;
		}

		void setMatrix( const vgKernel::Mat4& matrix );

		void setEditMode( bool edit_mode )
		{
			if ( (_inEditMode == true && edit_mode == false ) ||
				( _inEditMode == false && edit_mode == true ) )
			{
				_inEditMode = edit_mode;				
			}

			return;
		}

		bool isInEditMode() const
		{
			return _inEditMode;
		}

		void setAnalysisMode( bool analysis_mode )
		{
			if ( (_inAnalysisMode == true && analysis_mode == false ) ||
				( _inAnalysisMode == false && analysis_mode == true ) )
			{
				_inAnalysisMode = analysis_mode;				
			}

			return;
		}

		bool isInAnalysisMode() const
		{
			return _inAnalysisMode;
		}
        
		void setPipeLineVisible(bool _visible) { m_enablePipeRender = _visible;}
		
		bool getPipeLineVisible() {return m_enablePipeRender;}		

		void calculatePressure(int index, vector<int> &tempVec, float rate, double preValue);

		void calEachPointPress(int id, double preValue);

		float calColorRateOfPipeLine();

		void drawDecreasing(float pipeRadius);

		double getEachMaxPress(RingStruct m_ring);

		void reCalPointPressure(vector<int> breakVec);

		bool getDecreasDrection(int root, int leaves, vector<int> preVisitedVec);

		void setPipeLineRadius(float Radius);

		float getPipeLineRadius();

		void drawPipeLineAnalysis();

		int getPointID(vgKernel::Vec3 pos);

		void addSelectPoints(PointStruct point);

		void renderSelectedPointsOnce();

		void renderAllPipeGeo();

		bool renderSelectPipeGeo(PointStruct potStruct);

		void callUpstreamPoint(int begID, int endID);

		void findUpstreamPoint(int upPoint, int downPoint);

		void restoreInitialRender();

		vgKernel::Box getPipeLineBox(LineString* linString);

		void addBuildingToAnalysis(string layerName);

		Layer *getBuildingName()
		{
			return m_buildingLayer;
		}

	protected:
		int checkExist(vgKernel::Vec3 point);			
		void testIntersectWithBuilding(RingStruct rings);
		void renderBuildingAnalysisResult(GeometryPointerVec& geoVec);
		void unrenderBuildingAnalysisResult();
		bool ifPipeLineInBreak(RingStruct m_ring);


		double maxPressure;
		double minPressure;
		//int sourcePoint;		

		//存放相交判断结果
	public:
		//std::vector <BuildingSolid*>  m_resultPolygon;
		GeometryPointerVec m_resultPolygon;
		RendererQueue m_resultModVec;

		struct GeometryColor
		{
			Geometry* pGeometry;
			COLORREF  fillColor;
			COLORREF  penColor;
		};
		typedef vector<GeometryColor>                GeomColorVec;

		GeomColorVec geoColors;
		
		//void cornerAutoSmooth();
	public:
		//add by KingHJ @2010.04.22
		PipeGeoPtrVector m_selectPipeGeoVec;
		std::vector<LineString*> m_pipeLineInView;

	private:
		vector<JointPointPtr> m_jointArray;

	public:
		//add by KingHJ @2010.04.22
		PipeGeoPtr testInterSectWithPipeGeo(RayLine3d rayline);		

		vgKernel::Box getPipeGeoBox(PipeGeoPtr pipeGeo);

		void drawSelectPipeGeoBox();

		void ifTheTwoGeoConnect(int upIndex, int downIndex);		

		PipeGeoPtrVector getSelectPipeGeo()
		{
			return m_selectPipeGeoVec;
		}

		void addSelectPipeGeo(PipeGeoPtr pipeGeo);

		void clearSelectPipeGeoVec()
		{
			if (!m_selectPipeGeoVec.empty())
			{
				m_selectPipeGeoVec.clear();
			}
		}

		PipeGeoPtr getPipeGeoIndex(int ID);

		PipeGeoPtrVector getAllPipeGeo()
		{
			return m_pipeGeoPtrVec;
		}

		void pipeRouteAnalysis();		

		bool programWithDijkstra(int startPotID, int endPotID);

		void drawShortestPath();

		void addPipeLineToView(LineString* pipeline);

		void renderViewPipeLineBox();

		void showPipeLayerAtrriList();

		void shapeModelAnalysis(Geometry *Geomertry,Layer* shapeLayer);

		void renderModelAnalysisResult( vgKernel::RendererQueue& renderResult );

		void unrenderModelAnalysisResult();
		
		void pushDataToDataBase(Layer *pLayer);
		
		int findIfPointInArray(vgKernel::Vec3 point);

		void constructFromBreakShapeLayer(string layerName);

		void OGRPipeLineMap::LightInit();
	protected:
		vgKernel::Mat4 layerMatrix;
		vgKernel::Vec3	drection;
		vector<RouteInfo> m_routeArray;
		vector<double> m_tranAngleVec;       //存储每个联通节点的旋转角度
		vector<vgKernel::Vec3> m_drecVec;  //存储每个联通节点的各方向向量

		std::vector <PointStruct> m_selectPointVec;
		std::vector <int> visitedVec;
		std::vector <int> m_blockPointsVec;
		std::vector <int> breakPointsVec;
		std::vector <int> m_sourceVec;
		std::vector <int> m_upstreamPtVec;

		Layer *m_buildingLayer;

		PipeLineLayer m_pipeLineLayer;
		GLUquadricObj *quadyuanzhu;
		GLUquadricObj *yuanqiu;
		GLUquadricObj *yuanhuan;
		//GLuint _PipeListID;
		GLuint m_PipeLineEditID;
		GLuint m_PipeLineSectionID;
		GLuint m_pipeAnalysisID;

		bool m_enablePipeRender;
		bool m_enablePipeLineSection;
		bool m_pipeAnalysisEnable;
		bool m_decreasFlag;		

		double m_distance;
		double Tran_angle;
		double Axis[3] ;	
		float m_dRadius;

		string m_layerName;	

		RenderColorVec rendererColors;		

		PipeGeoPtrVector m_pipeGeoPtrVec;
	};

	VGK_RENDERER_OUT_DECLARE( OGRPipeLineMap )

	typedef vgKernel::SharePtr<OGRPipeLineMap> PipeLinePtr;

	//typedef std::vector<PipeLinePtr> PipeLinePtrVector;

}
