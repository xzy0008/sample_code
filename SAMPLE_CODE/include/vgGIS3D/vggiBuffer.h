


#ifndef __VGGIBUFFER_H__
#define __VGGIBUFFER_H__




#include <vgGis/vggisDefinition.h>
#include <vgGis3D/vggiVec3d.h>
#include <vgkernel/vgkMat4.h>
#include <vgGis3D/vggiGeometry.h>
#include <gdal/ogr_geometry.h>

#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgGis3D/vggiLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <vgKernel/vgkColorableObject.h>

namespace vgGIS3D {

	using namespace std;
	using namespace vgKernel;

	typedef vector< OGRGeometry* >               OGRGeoPtrVec;
	typedef vector< Vec3* >                      Vec3PtrVec;
	typedef vector< Vec3PtrVec >                 Vec3PtrVecVec;

	typedef vector< Vec3d* >                     Vec3dPtrVec;

	struct GeometryColor
	{
		Geometry* pGeometry;
		COLORREF  fillColor;
		COLORREF  penColor;
	};
	typedef vector<GeometryColor>                GeomColorVec;

	struct RendererColor 
	{
		Renderer* pRenderer;
		RgbaQuad  color;
		bool      colorState;
	};
	typedef vector<RendererColor>                RenderColorVec;


	class VGG_EXPORT Buffer
	{

	public:

		Buffer();
		virtual ~Buffer();


	private:
		enum SideType
		{
			LEFT,
			RIGHT
		};

	public:
	
		// 缓冲区可视化
		void render();

		// 生成缓冲区
		bool genBuffer( const GeometryPointerVec* pGeoVec, double radius, int nQuadSegs = 30 );

		// 生成左右缓冲半径不相等的缓冲区
		bool genLeftRightBuffer( const GeometryPointerVec* pGeoVec, double leftRadius, 
			double rightRadius, int nQuadSegs = 30 );

		// 提供给分析用的OGRGeometry
		OGRGeoPtrVec* getBufferVec();
		
		void setRenderOutline( bool bRender )
		{
			m_bRenderOutline = bRender;
		}

		void setRenderBuffer( bool bRender )
		{
			m_bRenderBuffer = bRender;
		}


		//缓冲区地物分析接口
		void modelAnalysis(Layer* shapeLayer);
		//缓冲区矢量分析接口
		void shapeAnalysis(Layer* shapeLayer);

	private:

		void renderOnceForDisplayList();  // 生成渲染列表

		bool bufferUnion();               // 合并缓冲区

		void checkTerrainLoad();          // 检测是否帖地处理

		void attachToTerrain();           // 缓冲区帖地

		void getDataFromOgrGeo( const OGRGeometry* pOgrGeo );  // 从OGRGeometry 中读取点数据

		bool readWkbData( uchar* buf , int buf_size );         // 从wkbBuffer中读数据

		void interpolation( int ptNum, double* addr );         // 帖地前插值

		void clearDisplayList();                               // 清空显示列表

		void clearRecoverableData();                           // 清空wkbBuffer 临时数据

	
		/////////////////////////以下生成左右缓冲半径不相等的缓冲区

		// 生成单边缓冲区
		void genSingleSideBuffer( Geometry* pGeo, Vec3PtrVec& vec, SideType type, 
			double radius, int nQuadSegs = 30 );

		// 从OGR的Buffer轮廓中提取需要的那一半
		bool genOutlinePt( const double* addr, const RingStruct& rs, Vec3PtrVec& vec,
			SideType type, double radius, int numPts );

		// 用于生成Buffer的原始线作为结果轮廓的一部分
		void appendLinePt( Geometry* pGeo, Vec3PtrVec& vec );

		// 计算目标轮廓线的两端点
		void calculateTowEndpoint( const RingStruct& rs, double radius, Vec3& firstPt, Vec3& lastPt );  

		// 查找离目标轮廓线的两端点最近的点的索引号
		void findStartAndEndIndex( const double* addr, int numPts, const Vec3& firstPt, const Vec3 lastPt,
			int& sIndex, int& eIndex );

		// 构造OGRGeometry用于分析 
		void constructOgrGeo();

		// 发生错误时清空空间
		void unInit();  

		void clearPtDataVec();

		void destroyOgrGeo();


		/////////////////////////以下供缓冲区分析调用///////////////////////////
		//缓冲区与矢量图相交分析，供矢量分析调用,返回值不同
		OGRGeoPtrVec bufferShapeAnalysis(Layer* shapeLayer);
		GeometryPointerVec bufferShapeAnalysis2(Layer* shapeLayer);

		//矢量图与模型相交分析，供地物分析调用
		void shapeModelAnalysis(OGRGeometry* bufferGeometry,Layer* shapeLayer);

		//显示分析结果，供地物分析调用
		void renderModelAnalysisResult(vgKernel::RendererQueue& renderResult);

		//恢复模型原渲染状态，供地物分析调用
		void unrenderModelAnalysisResult();

		//显示矢量分析结果，供矢量分析调用
		void renderShapeAnalysisResult(GeometryPointerVec& geoVec);

		//恢复矢量原渲染状态，供矢量分析调用
		void unrenderShapeAnalysisResult();

		//得到矢量平移量，供地物分析调用
		Vec3 getTranslateModeltoShapeOffset();

	private:

		bool                m_bRenderOutline;    // 是否渲染轮廓线
		
		bool                m_bRenderBuffer;     // 是否渲染缓冲区

		GLuint              m_callListId;        // 显示列表ID

		OGRGeoPtrVec        m_ogrGeoPtrVec;      // 传给分析用的OgrGeomtry数组


		int                 m_wkbSize;
		uchar*              m_wkbBuffer;
		
		Vec3PtrVecVec       m_ptDataVec;         // 用于可视化的点数据


		vgKernel::Plugin*   m_pPlugin;

		bool           m_bLoadTerrainDLL;        // 平台是否加载了TerrainDLL

		bool           m_bHasTerrain;            // 场景中是否有地形数据

		float          m_terrainCellSize;        // 地形网格大小

		Vec3dPtrVec    m_vecForTess;             // 用于多边形填充

		vgKernel::Mat4 m_matrix;
		//////////////////////////////////////////////////////////////////////////
		bool      m_bNeedLine;        // 将用于生成缓冲区的线也作为轮廓线的一部分

		bool      m_bLeftRightBuffer; // 生成左右不相等的缓冲区

		bool      m_bNeedDestroyOgr;  


		//存放缓冲区分析结果////////////////////////////////////////////////////
		std::ostringstream o;
		
		vgKernel::RendererQueue resultQueue;
		
		GeometryPointerVec resultShapeGeomtrys;

		GeomColorVec geoColors;

		RenderColorVec rendererColors;


		// 用于分析的矢量图层
		Layer*   m_pAnalsisLayer;
	};




}// end of namespace vgGIS3D



#endif // end of __VGGIBUFFER_H__
