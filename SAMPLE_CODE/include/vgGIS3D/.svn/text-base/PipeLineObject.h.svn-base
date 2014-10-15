
// PipeLineObject.h: interface for the PipeLineObject class.
/**
@date 	2009/09/05  13:41	
@author  KingHJ

@brief 	 属于另一套用四边形画管线的类，暂时没有使用

@see    
*/
//////////////////////////////////////////////////////////////////////

#pragma  once

#include <vgGIS3D/PipelineDatabase.h>
#include <vgGIS3D/vggiPrerequisite.h>
#include <vgGIS3D/vggiPipeLineMap.h>
// #include <vgGIS3D/vggiOGRPipeLineMap.h>
#include <vgKernel/vgkSharePtr.h>
//#include <vgGIS3D/vggiOGRRouteMap.h>


//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

//#define PI 3.141592653589793238462643383279

namespace vgGIS3D
{
	#ifndef PI
	#define PI 3.141592653589793f
	#endif

	class PipeLineObject		
	{
	public:
		PipeLineObject();
		virtual ~PipeLineObject();

	protected:	
		float m_dRadius;
		UINT m_nPointsNum;
	protected:
		

	public:	
		std::vector <vgKernel::Vec3> ptCircleCentre3DArray;

		std::vector <vgKernel::Vec3> ptCentre3DArray;

		std::vector <vgKernel::Vec3> ptVertexNormalArray;

		std::vector <vgKernel::Vec3> ptContactVertexNormalArray;

		std::vector <LINE3D> ptLines3d;

		std::vector <LINE3D> ptPipeLinesNormal;

		std::vector <LINE3D> ptLinesCurveCentre;

		//std::vector <vgKernel::Vec3> contactBottomArray3D;
		//std::vector <vgKernel::Vec3> contactTopArray3D;
		std::vector <vgKernel::Vec3> midPipeArray3D;
		std::vector <vgKernel::Vec3> frontPipeArray3D;
		std::vector <vgKernel::Vec3> backPipeArrray3D;

	public:
		//vgKernel::Vec3 pMapCenter;

	public:
		void CalNextNodeOnCurve(vgKernel::Vec3 FCentre3D,vgKernel::Vec3 NCentre3D,std::vector <vgKernel::Vec3>& FirstArray3D,std::vector<vgKernel::Vec3>& NextArray3D,vgKernel::Vec3& ptCurveTangent);

		void CalCurveTangent(vgKernel::Vec3& ptPlaneNormal,vgKernel::Vec3& ptCurveCentre,vgKernel::Vec3& ptPoint3D,vgKernel::Vec3& ptCurveTangent);

		void CalNextNodeOnBeeline(vgKernel::Vec3 FCentre3D,vgKernel::Vec3 NCentre3D,std::vector <vgKernel::Vec3>& FirstArray3D,std::vector <vgKernel::Vec3>& NextArray3D);

		double CalAzimuth(double Dx,double Dy);

		void DrawPipeSection();

		double CalculateAngleBetweenTwoLines(vgKernel::Vec3 pt1,vgKernel::Vec3 pt2,vgKernel::Vec3 pt3);

		void CalculateCoordinateOnPipeLine(vgKernel::Vec3 pt3D1, vgKernel::Vec3 pt3D2, vgKernel::Vec3 pt3D3,std::vector <vgKernel::Vec3>&pt3DArray);

		void CalculateRotateParameter(vgKernel::Vec3 ptBottom,vgKernel::Vec3 ptTop,double dCosAngles[][3]);

		void CalVertexesNormal();

		void CalPlaneNormal(vgKernel::Vec3 &ptTop1,vgKernel::Vec3 &ptIntersect,vgKernel::Vec3 &ptTop2,vgKernel::Vec3 &ptPlaneNormal);

		float RadiusRand(int Max);

		void DrawPipeLine(PipeLineLayer m_pipeLineLayer);

		void calContactVertexesNormal(vgKernel::Vec3 ptTest1, vgKernel::Vec3 ptTest2, double m_dContactRadius);
		
		void drawContactPipeLine(CString flag, vgKernel::Vec3 ptTest1, vgKernel::Vec3 ptTest2, double m_dContactRadius);
		
		void drawContactPipeLine();
		
		//void renderContactPipeLine();
	};

}
