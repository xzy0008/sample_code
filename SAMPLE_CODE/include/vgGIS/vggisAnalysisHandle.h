


#ifndef __VGGISANALYSIS_H__
#define __VGGISANALYSIS_H__



#include <vgGis/vggisDefinition.h>

#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkVec3.h>

#include <vgGis3D/vggiBuffer.h>
#include <vgGIS3D/vggiFaecherAnalysisDlg.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkSystemUtility.h>



namespace vgGIS3D {


	typedef std::vector<vgKernel::Vec3>	PointsArray;

	class VGG_EXPORT GisAnalysis : public vgKernel::InputHandler
	{
	public:
		GisAnalysis( EGisState eType);
		
		virtual ~GisAnalysis();
	
	
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnRBottonUp(UINT nFlags, CPoint position);

		void		renderGisElements();

		void		reset();
		
		EGisState	getGisState();
		bool		setGisState(EGisState eGisState);

		void		calculateControlHeight( float fht );
	
		PointsArray GetPoints();
		void SetbOperationDone(bool isDone);

	private:

		void	pickAndAppendPoint(CPoint point);
		void	getDynamicPoint(CPoint point);
		
		void	showResult();

		float	calculateDistance(const PointsArray& points);
		float	calculateArea(const PointsArray& points);
		float	calculateVolume(const PointsArray& points);
		
		float	calculateAngleCos(const PointsArray& points);	// 求一个平面(至少输入平面上的3个点)和水平面的夹角的余弦
		float	calculateVerDistance(const PointsArray& points);// calculate vertical distance
		float	calculateHorDistance(const PointsArray& points);// calculate horizontal distance
		float	calculateSlope(vgKernel::Vec3 pt1, vgKernel::Vec3 pt2);//求坡度(两个点组成的线与水平面的夹角),返回(度)
		void	calculateMousePtRounding();							// 求鼠标单击点的范围的矩形
		bool    showFaecher(const PointsArray& points);

		void	renderPoint(const PointsArray& points);
		void	renderLine(const PointsArray& points);
		void	renderPolygon(const PointsArray& points);
		void	renderPointsByMode(const PointsArray& points, int nRenderMode,
					bool bOperationDone = false, bool bCloseRing = false);
		
		void	renderRedLine(const PointsArray& points, bool bDone = false);
		void	renderYellowLine(const PointsArray& points);
		void	renderControlHeiPolygon();	// 控高平面

		//void    genBuffer();
		void    bufferShapeAnalysis();
		void    bufferModelAnalysis();
		void    renderBuffer();             // 渲染缓冲区

	private:

		EGisState		m_eGisState;

		bool			m_bOperationDone;
		bool			m_bCloseRing;
		PointsArray		m_pointsInLine;
		vgKernel::Vec3	m_pointDynamic;

		vgGIS3D::Buffer* m_buffer;
		bool            m_bHasBuffer;

		bool			m_bFirstClick;	// 在水平(垂直)距离测量中用到
		PointsArray		m_RedLinePt;	// 红色线中的点
		PointsArray		m_YellowLinePt;
		PointsArray		m_ControlHeightPts;
		PointsArray		m_ControlHeightPts2;
		PointsArray		m_PointsTemp; // 扇面分析中使用 [5/10/2010 22:04:34 ZhaoQ]

		
		FaecherAnalysisDlg* m_pFaecherAnalysisDlg;
	};
	
}// end of namespace vgGIS3D
	


#endif // end of __VGGISANALYSIS_H__
