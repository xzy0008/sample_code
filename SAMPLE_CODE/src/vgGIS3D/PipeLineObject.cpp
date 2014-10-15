// PipeLineObject.cpp: implementation of the PipeLineObject class.
//属于另一套用四边形画管线的类，暂时没有使用
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
#include <vgGIS3D/PipeLineObject.h>

#include "string.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace vgGIS3D
{
	PipeLineObject::PipeLineObject()
	{
		m_dRadius = 4;

		//yuanqiu= gluNewQuadric();

	}

	PipeLineObject::~PipeLineObject()
	{	

	}

	float PipeLineObject::RadiusRand(int Max)
	{
		int nRand = rand();
		float fVal = (float)Max / RAND_MAX;
		float fElevation = (float)nRand * fVal + 0.5F;
		return fElevation;
	}

	void PipeLineObject::DrawPipeLine(PipeLineLayer m_pipeLineLayer)
	{
		//divide the circle into 6 parts use small arc to imitate circle
		//decide the slopdirection and slopangle by the adjacent two point
		LINE3D aLine;

		std::vector <RingStruct> ::iterator iter = m_pipeLineLayer.pipeLineVec.begin();
		std::vector <RingStruct> ::iterator iter_end = m_pipeLineLayer.pipeLineVec.end();
		for (; iter != iter_end; iter++)
		{
			vgKernel::Vec3 pt3D1, pt3D2, pt3D3;

			int m_nPointsNum = (*iter)._numPoints;

			if (m_nPointsNum < 3)
			{
				pt3D1.x = (*iter)._pointsBeginAddr[0];
				pt3D1.z = -(*iter)._pointsBeginAddr[1];
				pt3D1.y = (*iter)._pointsBeginAddr[2];

				pt3D2.x = (*iter)._pointsBeginAddr[3];
				pt3D2.z = -(*iter)._pointsBeginAddr[4];
				pt3D2.y = (*iter)._pointsBeginAddr[5];

				ptCentre3DArray.push_back(pt3D1);
				ptCentre3DArray.push_back(pt3D2);		
			}
			else
			{
				pt3D1.x = (*iter)._pointsBeginAddr[0];
				pt3D1.z = -(*iter)._pointsBeginAddr[1];
				pt3D1.y = (*iter)._pointsBeginAddr[2]; 

				ptCentre3DArray.push_back(pt3D1);
				for (int j = 0; j < m_nPointsNum - 2; j++)
				{
					pt3D1.x = (*iter)._pointsBeginAddr[3*j];
					pt3D1.z = -(*iter)._pointsBeginAddr[3*j+1];
					pt3D1.y = (*iter)._pointsBeginAddr[3*j+2];

					pt3D2.x = (*iter)._pointsBeginAddr[3*(j+1)];
					pt3D2.z = -(*iter)._pointsBeginAddr[3*(j+1)+1];
					pt3D2.y = (*iter)._pointsBeginAddr[3*(j+1)+2];

					pt3D3.x = (*iter)._pointsBeginAddr[3*(j+2)];
					pt3D3.z = -(*iter)._pointsBeginAddr[3*(j+2)+1];
					pt3D3.y = (*iter)._pointsBeginAddr[3*(j+2)+2];

					CalculateCoordinateOnPipeLine(pt3D1,pt3D2,pt3D3,ptCentre3DArray);
				}
				pt3D1.x = (*iter)._pointsBeginAddr[3*(m_nPointsNum-1)];
				pt3D1.z = -(*iter)._pointsBeginAddr[3*(m_nPointsNum-1)+1];
				pt3D1.y = (*iter)._pointsBeginAddr[3*(m_nPointsNum-1)+2];

				ptCentre3DArray.push_back(pt3D1);
			}			

			std::vector <vgKernel::Vec3> ::iterator iter1 = ptCentre3DArray.begin();
			std::vector <vgKernel::Vec3> ::iterator iter_end1 = ptCentre3DArray.end();
			aLine.PointArray.assign(iter1, iter_end1);
			ptLines3d.push_back(aLine);
			for (; iter1 != iter_end1; iter1++)
			{
				TRACE ("%f,%f,%f\n", (*iter1).x, (*iter1).y, (*iter1).z);
			}	

			std::vector <vgKernel::Vec3> ::iterator iter2 = ptCircleCentre3DArray.begin();
			std::vector <vgKernel::Vec3> ::iterator iter_end2 = ptCircleCentre3DArray.end();
			aLine.PointArray.assign(iter2, iter_end2);
			ptLinesCurveCentre.push_back(aLine);


			CalVertexesNormal();
			std::vector <vgKernel::Vec3> ::iterator iter3 = ptVertexNormalArray.begin();
			std::vector <vgKernel::Vec3> ::iterator iter_end3 = ptVertexNormalArray.end();
			aLine.PointArray.assign(iter3, iter_end3);
			ptPipeLinesNormal.push_back(aLine);

			ptCentre3DArray.clear();
			ptVertexNormalArray.clear();
			ptCircleCentre3DArray.clear();
		}


		//DrawPipeSection();
		glFlush();
	}

	void PipeLineObject::CalculateCoordinateOnPipeLine(vgKernel::Vec3 pt3D1, vgKernel::Vec3 pt3D2, vgKernel::Vec3 pt3D3, std::vector<vgKernel::Vec3>& pt3DArray)
	{
		vgKernel::Vec3  ptCurveB3D,ptCurveE3D,ptCircleCenter3D;

		vgKernel::Vec3  Line1Normal,Line2Normal;

		double   dAngleAtTwoLines,dLengthBtoM,dLengthMtoE,dLengthcurvebeginTomiddle,dLengthmiddleTocurveend;

		dLengthBtoM = sqrt(pow((pt3D2.x-pt3D1.x),2)+pow((pt3D2.y-pt3D1.y),2)+pow((pt3D2.z-pt3D1.z),2));	
		dLengthMtoE = sqrt(pow((pt3D3.x-pt3D2.x),2)+pow((pt3D3.y-pt3D2.y),2)+pow((pt3D3.z-pt3D2.z),2));	

		dAngleAtTwoLines = CalculateAngleBetweenTwoLines(pt3D1,pt3D2,pt3D3);

		dLengthcurvebeginTomiddle = m_dRadius*tan((PI-dAngleAtTwoLines)/2.0);	
		dLengthmiddleTocurveend = dLengthcurvebeginTomiddle;

		if(dLengthBtoM < dLengthcurvebeginTomiddle)
			return;

		Line1Normal.x = pt3D1.x-pt3D2.x;
		Line1Normal.y = pt3D1.y-pt3D2.y;
		Line1Normal.z = pt3D1.z-pt3D2.z;

		Line2Normal.x = pt3D3.x-pt3D2.x;
		Line2Normal.y = pt3D3.y-pt3D2.y;
		Line2Normal.z = pt3D3.z-pt3D2.z;


		ptCurveB3D.x = pt3D2.x - dLengthcurvebeginTomiddle/dLengthBtoM*(pt3D2.x-pt3D1.x);
		ptCurveB3D.y = pt3D2.y - dLengthcurvebeginTomiddle/dLengthBtoM*(pt3D2.y-pt3D1.y);
		ptCurveB3D.z = pt3D2.z - dLengthcurvebeginTomiddle/dLengthBtoM*(pt3D2.z-pt3D1.z);

		ptCurveE3D.x = pt3D2.x - dLengthmiddleTocurveend/dLengthMtoE*(pt3D2.x-pt3D3.x);
		ptCurveE3D.y = pt3D2.y - dLengthmiddleTocurveend/dLengthMtoE*(pt3D2.y-pt3D3.y);
		ptCurveE3D.z = pt3D2.z - dLengthmiddleTocurveend/dLengthMtoE*(pt3D2.z-pt3D3.z);

		//if(fabs(ptCurveB3D.x) < 1e+10 && fabs(ptCurveB3D.y) < 1e+10 && fabs(ptCurveB3D.z) < 1e+10)
			pt3DArray.push_back(ptCurveB3D);

		//double k1,k2,k3,D;
		double k1 = 0.0;
		double k2 = 0.0;
		double k3 = 0.0;
		double D = 0.0;
		vgKernel::Vec3 planeNormal;

		planeNormal.x = Line1Normal.y*Line2Normal.z - Line1Normal.z*Line2Normal.y;
		planeNormal.y = Line1Normal.z*Line2Normal.x - Line1Normal.x*Line2Normal.z;
		planeNormal.z = Line1Normal.x*Line2Normal.y - Line1Normal.y*Line2Normal.x;

		k1 = pt3D2.x * planeNormal.x + pt3D2.y * planeNormal.y + pt3D2.z * planeNormal.z;
		k2 = ptCurveB3D.x * Line1Normal.x + ptCurveB3D.y * Line1Normal.y + ptCurveB3D.z*Line1Normal.z;
		k3 = ptCurveE3D.x * Line2Normal.x + ptCurveE3D.y * Line2Normal.y + ptCurveE3D.z*Line2Normal.z;

		D = planeNormal.x * Line1Normal.y * Line2Normal.z + planeNormal.y*Line1Normal.z*Line2Normal.x+planeNormal.z*Line1Normal.x*Line2Normal.y
			-planeNormal.z * Line1Normal.y * Line2Normal.x - planeNormal.y*Line1Normal.x*Line2Normal.z-planeNormal.x*Line1Normal.z*Line2Normal.y;	

		ptCircleCenter3D.x = (k1*Line1Normal.y*Line2Normal.z+planeNormal.y*Line1Normal.z*k3+planeNormal.z*k2*Line2Normal.y
			-planeNormal.z*Line1Normal.y*k3-planeNormal.y*k2*Line2Normal.z-k1*Line1Normal.z*Line2Normal.y)/D;

		ptCircleCenter3D.y = (planeNormal.x*k2*Line2Normal.z+k1*Line1Normal.z*Line2Normal.x+planeNormal.z*Line1Normal.x*k3
			-planeNormal.z*k2*Line2Normal.x-k1*Line1Normal.x*Line2Normal.z-planeNormal.x*Line1Normal.z*k3)/D;

		ptCircleCenter3D.z = (planeNormal.x*Line1Normal.y*k3+planeNormal.y*k2*Line2Normal.x+k1*Line1Normal.x*Line2Normal.y
			-k1*Line1Normal.y*Line2Normal.x-planeNormal.y*Line1Normal.x*k3-planeNormal.x*k2*Line2Normal.y)/D;

		ptCircleCentre3DArray.push_back(ptCircleCenter3D);

		int nTotalPointNums = 4;
		double dLengthtemp1,dLengthtemp2,dXjunction,dYjunction,dZjunction,dLengthmiddleTocirclecenter;
		vgKernel::Vec3 pt3D;

		dLengthtemp1 = m_dRadius*tan((PI - dAngleAtTwoLines)/nTotalPointNums);
		dLengthtemp2 = m_dRadius/cos((PI - dAngleAtTwoLines)/nTotalPointNums);

		dXjunction = ptCurveB3D.x - dLengthtemp1 * (ptCurveB3D.x - pt3D2.x) / dLengthcurvebeginTomiddle;
		dYjunction = ptCurveB3D.y - dLengthtemp1 * (ptCurveB3D.y - pt3D2.y) / dLengthcurvebeginTomiddle;
		dZjunction = ptCurveB3D.z - dLengthtemp1 * (ptCurveB3D.z - pt3D2.z) / dLengthcurvebeginTomiddle;

		pt3D.x = ptCircleCenter3D.x - m_dRadius * (ptCircleCenter3D.x - dXjunction)/dLengthtemp2;
		pt3D.y = ptCircleCenter3D.y - m_dRadius * (ptCircleCenter3D.y - dYjunction)/dLengthtemp2;
		pt3D.z = ptCircleCenter3D.z - m_dRadius * (ptCircleCenter3D.z - dZjunction)/dLengthtemp2;

		//if(fabs(pt3D.x) < 1e+10 && fabs(pt3D.y) < 1e+10 && fabs(pt3D.z) < 1e+10)		//防止异常
			pt3DArray.push_back(pt3D);

		dLengthmiddleTocirclecenter = m_dRadius/cos((PI - dAngleAtTwoLines)/2.0);	//middle与圆心之间的距离

		pt3D.x = ptCircleCenter3D.x - m_dRadius*(ptCircleCenter3D.x - pt3D2.x) / dLengthmiddleTocirclecenter;	//middle所对应的等分点坐标dX2oncurve,dY2oncurve,dZ2oncurve
		pt3D.y = ptCircleCenter3D.y - m_dRadius*(ptCircleCenter3D.y - pt3D2.y) / dLengthmiddleTocirclecenter;
		pt3D.z = ptCircleCenter3D.z - m_dRadius*(ptCircleCenter3D.z - pt3D2.z) / dLengthmiddleTocirclecenter;

		//if(fabs(pt3D.x) < 1e+10 && fabs(pt3D.y) < 1e+10 && fabs(pt3D.z) < 1e+10)
			pt3DArray.push_back(pt3D);	

		dXjunction = ptCurveE3D.x - dLengthtemp1 * (ptCurveE3D.x - pt3D2.x) / dLengthmiddleTocurveend;
		dYjunction = ptCurveE3D.y - dLengthtemp1 * (ptCurveE3D.y - pt3D2.y) / dLengthmiddleTocurveend;
		dZjunction = ptCurveE3D.z - dLengthtemp1 * (ptCurveE3D.z - pt3D2.z) / dLengthmiddleTocurveend;

		pt3D.x = ptCircleCenter3D.x - m_dRadius * (ptCircleCenter3D.x - dXjunction)/dLengthtemp2;		//此为middle与t2之间的等分点
		pt3D.y = ptCircleCenter3D.y - m_dRadius * (ptCircleCenter3D.y - dYjunction)/dLengthtemp2;
		pt3D.z = ptCircleCenter3D.z - m_dRadius * (ptCircleCenter3D.z - dZjunction)/dLengthtemp2;

		//if(fabs(pt3D.x) < 1e+10 && fabs(pt3D.y) < 1e+10 && fabs(pt3D.z) < 1e+10)
			pt3DArray.push_back(pt3D);

		//if(fabs(ptCurveE3D.x) < 1e+10 && fabs(ptCurveE3D.y) < 1e+10 && fabs(ptCurveE3D.z) < 1e+10)
			pt3DArray.push_back(ptCurveE3D);

	}

	double PipeLineObject::CalculateAngleBetweenTwoLines(vgKernel::Vec3 pt1, vgKernel::Vec3 pt2, vgKernel::Vec3 pt3)
	{
		double dCosAlfa;
		double dN1[3],dN2[3];
		dN1[0] = pt3.x - pt2.x; dN1[1] = pt3.y - pt2.y; dN1[2] = pt3.z - pt2.z;
		dN2[0] = pt1.x - pt2.x; dN2[1] = pt1.y - pt2.y; dN2[2] = pt1.z - pt2.z;
		double dS1 = sqrt(dN1[0]*dN1[0] + dN1[1]*dN1[1] +dN1[2]*dN1[2]);
		double dS2 = sqrt(dN2[0]*dN2[0] + dN2[1]*dN2[1] +dN2[2]*dN2[2]);
		dCosAlfa = (dN1[0]*dN2[0] + dN1[1]*dN2[1] + dN1[2]*dN2[2])/(dS1*dS2);
		dCosAlfa = acos(dCosAlfa);
		return dCosAlfa;

	}

	void PipeLineObject::DrawPipeSection()
	{

		//TRACE ("%d\n", ptLines3d.size());
		for(int m = 0; m < ptLines3d.size(); m ++)
		{
			glColor3f(0.0f, 0.0f, 1.0f);

			UINT nNormalID = 0;

			std::vector <vgKernel::Vec3> ::iterator iter1 = ptLines3d[m].PointArray.begin();
			std::vector <vgKernel::Vec3> ::iterator iter_end1 = ptLines3d[m].PointArray.end();
			ptCentre3DArray.assign(iter1, iter_end1);

			//ptCentre3DArray.Copy(ptLines3d[m].PointArray);
			std::vector <vgKernel::Vec3> ::iterator iter2 = ptPipeLinesNormal[m].PointArray.begin();
			std::vector <vgKernel::Vec3> ::iterator iter_end2 = ptPipeLinesNormal[m].PointArray.end();
			ptVertexNormalArray.assign(iter2, iter_end2);

			//ptVertexNormalArray.Copy(ptPipeLinesNormal[m].PointArray);
			std::vector <vgKernel::Vec3> ::iterator iter3 = ptLinesCurveCentre[m].PointArray.begin();
			std::vector <vgKernel::Vec3> ::iterator iter_end3 = ptLinesCurveCentre[m].PointArray.end();
			ptCircleCentre3DArray.assign(iter3, iter_end3);

			//ptCircleCentre3DArray.Copy(ptLinesCurveCentre[m].PointArray);

			double dCosAngles[3][3] = {0,0,0,0,0,0,0,0,0};		
			CalculateRotateParameter(ptCentre3DArray[0],ptCentre3DArray[1],dCosAngles);

			int nSurfaceNum = 10;
			std::vector <vgKernel::Vec3> bottomArray3D,topArray3D;
			vgKernel::Vec3  ptemp3D,pt3d;

			double dInitialAngle=0.0;

			for(int i = 0;i < nSurfaceNum;i++)
			{
				ptemp3D.x = m_dRadius*cos(dInitialAngle);
				ptemp3D.y = m_dRadius*sin(dInitialAngle);
				ptemp3D.z = 0.0;

				pt3d.x = ptCentre3DArray[0].x + dCosAngles[0][0] * ptemp3D.x + dCosAngles[0][1] * ptemp3D.y + dCosAngles[0][2] * ptemp3D.z;
				pt3d.y = ptCentre3DArray[0].y + dCosAngles[1][0] * ptemp3D.x + dCosAngles[1][1] * ptemp3D.y + dCosAngles[1][2] * ptemp3D.z;
				pt3d.z = ptCentre3DArray[0].z + dCosAngles[2][0] * ptemp3D.x + dCosAngles[2][1] * ptemp3D.y + dCosAngles[2][2] * ptemp3D.z;
				bottomArray3D.push_back(pt3d);

				dInitialAngle += 2 * PI / nSurfaceNum;
			}

			if(ptCentre3DArray.size() == 2)
			{
				CalNextNodeOnBeeline(ptCentre3DArray[0],ptCentre3DArray[1],bottomArray3D,topArray3D);

				glBegin(GL_QUAD_STRIP);
				for(int j = 0; j < nSurfaceNum; j++)
				{			
					glNormal3d(ptVertexNormalArray[nNormalID].x,ptVertexNormalArray[nNormalID].y,ptVertexNormalArray[nNormalID].z);
					glVertex3d(bottomArray3D[j].x,bottomArray3D[j].y,bottomArray3D[j].z);

					glNormal3d(ptVertexNormalArray[nNormalID + nSurfaceNum].x,ptVertexNormalArray[nNormalID + nSurfaceNum].y,ptVertexNormalArray[nNormalID + nSurfaceNum].z);
					glVertex3d(topArray3D[j].x,topArray3D[j].y,topArray3D[j].z);

					nNormalID ++;
				}
				glNormal3d(ptVertexNormalArray[nNormalID - nSurfaceNum].x,ptVertexNormalArray[nNormalID - nSurfaceNum].y,ptVertexNormalArray[nNormalID - nSurfaceNum].z);
				glVertex3d(bottomArray3D[0].x,bottomArray3D[0].y,bottomArray3D[0].z);

				glNormal3d(ptVertexNormalArray[nNormalID].x,ptVertexNormalArray[nNormalID].y,ptVertexNormalArray[nNormalID].z);
				glVertex3d(topArray3D[0].x,topArray3D[0].y,topArray3D[0].z);
				glEnd();
			}
			else
			{
				int idPlane = 0;	
				unsigned int idCentre = -1;	
				unsigned int idDot = 0;
				vgKernel::Vec3 ptPlaneNormal,ptCurveTangent;

				for( long int i = 0; i < ptCentre3DArray.size() - 1; i++)
				{
					if(idDot % 5 == 0 && i != ptCentre3DArray.size() - 2)
					{
						CalNextNodeOnBeeline(ptCentre3DArray[i],ptCentre3DArray[i + 1],bottomArray3D,topArray3D);

						CalPlaneNormal(ptCentre3DArray[i],ptCentre3DArray[i + 1],ptCentre3DArray[i + 5],ptPlaneNormal);

						idDot += 1;
						idCentre += 1;
					}
					else if(idDot % 5 == 0 && i == ptCentre3DArray.size() - 2)
					{
						CalNextNodeOnBeeline(ptCentre3DArray[i],ptCentre3DArray[i + 1],bottomArray3D,topArray3D);					
					}
					else
					{		
						CalCurveTangent(ptPlaneNormal,ptCircleCentre3DArray[idCentre],ptCentre3DArray[i+1],ptCurveTangent);

						CalNextNodeOnCurve(ptCentre3DArray[i],ptCentre3DArray[i + 1],bottomArray3D,topArray3D,ptCurveTangent);

						idDot += 1;
					}

					glBegin(GL_QUAD_STRIP);
					for(int j = 0; j < nSurfaceNum; j++)
					{			
						glNormal3d(ptVertexNormalArray[nNormalID].x,ptVertexNormalArray[nNormalID].y,ptVertexNormalArray[nNormalID].z);
						glVertex3d(bottomArray3D[j].x,bottomArray3D[j].y,bottomArray3D[j].z);

						glNormal3d(ptVertexNormalArray[nNormalID + nSurfaceNum].x,ptVertexNormalArray[nNormalID + nSurfaceNum].y,ptVertexNormalArray[nNormalID + nSurfaceNum].z);
						glVertex3d(topArray3D[j].x,topArray3D[j].y,topArray3D[j].z);

						nNormalID ++;
					}
					glNormal3d(ptVertexNormalArray[nNormalID - nSurfaceNum].x,ptVertexNormalArray[nNormalID - nSurfaceNum].y,ptVertexNormalArray[nNormalID - nSurfaceNum].z);
					glVertex3d(bottomArray3D[0].x,bottomArray3D[0].y,bottomArray3D[0].z);

					glNormal3d(ptVertexNormalArray[nNormalID].x,ptVertexNormalArray[nNormalID].y,ptVertexNormalArray[nNormalID].z);
					glVertex3d(topArray3D[0].x,topArray3D[0].y,topArray3D[0].z);

					glEnd();

					std::vector <vgKernel::Vec3> ::iterator iter = topArray3D.begin();
					std::vector <vgKernel::Vec3> ::iterator iter_end = topArray3D.end();
					bottomArray3D.assign(iter, iter_end);					
				}	
				bottomArray3D.clear();
				topArray3D.clear();
				ptCentre3DArray.clear();
				ptVertexNormalArray.clear();
			}
		}
	}

	void PipeLineObject::CalculateRotateParameter(vgKernel::Vec3 ptBottom,vgKernel::Vec3 ptTop,double dCosAxesAngles[][3])
	{
		double dS,dCosAlfa,dAlfa;
		dS = sqrt((ptTop.x - ptBottom.x)*(ptTop.x - ptBottom.x) + (ptTop.y - ptBottom.y)*(ptTop.y - ptBottom.y) + (ptTop.z - ptBottom.z)*(ptTop.z - ptBottom.z));
		dCosAlfa = (ptTop.z - ptBottom.z) / dS;
		dCosAxesAngles[2][2] = dCosAlfa;

		dCosAlfa = (ptTop.x - ptBottom.x) / dS;
		dCosAxesAngles[0][2] = dCosAlfa;

		dCosAlfa = (ptTop.y - ptBottom.y) / dS;
		dCosAxesAngles[1][2] = dCosAlfa;

		dCosAxesAngles[0][0] = 0.0;	

		dCosAlfa = sqrt(1 - dCosAxesAngles[1][2] * dCosAxesAngles[1][2] - dCosAxesAngles[0][0] * dCosAxesAngles[1][0]);
		dCosAxesAngles[1][1] = dCosAlfa;

		if(ptTop.y - ptBottom.y == 0 && ptTop.z - ptBottom.z == 0)
		{
			dCosAxesAngles[1][0] = 0.0;	
			dCosAxesAngles[2][0] = 1.0;	
		}
		else
		{
			dAlfa = CalAzimuth(ptTop.y - ptBottom.y,ptBottom.z - ptTop.z);
			dCosAlfa = cos(dAlfa);
			dCosAxesAngles[1][0] = dCosAlfa;

			dCosAlfa = cos(PI / 2 - dAlfa);
			dCosAxesAngles[2][0] = dCosAlfa;
		}

		dCosAlfa = -sqrt(1 - dCosAxesAngles[2][2] * dCosAxesAngles[2][2] - dCosAxesAngles[2][0] * dCosAxesAngles[2][0]);
		dCosAxesAngles[2][1] = dCosAlfa;

		if(dCosAxesAngles[1][2] < 0)
			dCosAlfa = sqrt(1 - dCosAxesAngles[0][2] * dCosAxesAngles[0][2] - dCosAxesAngles[0][0] * dCosAxesAngles[0][0]);
		else
			dCosAlfa = -sqrt(1 - dCosAxesAngles[0][2] * dCosAxesAngles[0][2] - dCosAxesAngles[0][0] * dCosAxesAngles[0][0]);
		dCosAxesAngles[0][1] = dCosAlfa;
	}

	double PipeLineObject::CalAzimuth(double Dx, double Dy)
	{
		double m_dAlfa;

		if(fabs(Dy)<0.001)
		{
			if(Dx>0)
				m_dAlfa = PI/2.0;
			else
				m_dAlfa = PI*3.0/2.0;
		}
		else
		{
			m_dAlfa = atan(Dx/Dy);
			if(Dy<0.0)
				m_dAlfa += PI;
			else
			{
				if(Dx<0.0)
					m_dAlfa += 2*PI;
			}
		}

		return m_dAlfa;
	}

	void PipeLineObject::CalVertexesNormal()
	{
		long int i = 0 ;
		double dCosAngles[3][3] = {0,0,0,0,0,0,0,0,0};
		CalculateRotateParameter(ptCentre3DArray[0],ptCentre3DArray[1],dCosAngles);

		int nSurfaceNum = 10;
		std::vector <vgKernel::Vec3>ptBegin3DArray,ptMiddle3DArray,ptEnd3DArray;
		vgKernel::Vec3  ptemp3D,pt3d;

		int idPlane1,idPlane2,idPlane3;
		vgKernel::Vec3 ptNormal1,ptNormal2,ptNormal3,ptNormal4;
		vgKernel::Vec3 ptVertexNormal;

		double dInitialAngle=0.0;

		for(int i = 0;i < nSurfaceNum;i++)
		{
			ptemp3D.x = m_dRadius*cos(dInitialAngle);
			ptemp3D.y = m_dRadius*sin(dInitialAngle);
			ptemp3D.z = 0.0;

			pt3d.x = ptCentre3DArray[0].x + dCosAngles[0][0] * ptemp3D.x + dCosAngles[0][1] * ptemp3D.y + dCosAngles[0][2] * ptemp3D.z;
			pt3d.y = ptCentre3DArray[0].y + dCosAngles[1][0] * ptemp3D.x + dCosAngles[1][1] * ptemp3D.y + dCosAngles[1][2] * ptemp3D.z;
			pt3d.z = ptCentre3DArray[0].z + dCosAngles[2][0] * ptemp3D.x + dCosAngles[2][1] * ptemp3D.y + dCosAngles[2][2] * ptemp3D.z;
			ptBegin3DArray.push_back(pt3d);

			dInitialAngle += 2 * PI / nSurfaceNum;
		}

		//CString centerNum;
		//centerNum.Format("%d", ptCentre3DArray.size());
		//AfxMessageBox(centerNum);

		if(ptCentre3DArray.size() == 2)
		{
			CalNextNodeOnBeeline(ptCentre3DArray[0],ptCentre3DArray[1],ptBegin3DArray,ptEnd3DArray);

			for( long int i = 0; i < nSurfaceNum; i++)
			{
				idPlane1 = i -1;		idPlane2 = i;	idPlane3 = i + 1;
				if(idPlane1 == -1) idPlane1 = nSurfaceNum - 1;
				if(idPlane3 == nSurfaceNum) idPlane3 = 0;

				CalPlaneNormal(ptBegin3DArray[idPlane1],ptBegin3DArray[idPlane2],ptEnd3DArray[idPlane2],ptNormal1);
				CalPlaneNormal(ptEnd3DArray[idPlane2],ptBegin3DArray[idPlane2],ptBegin3DArray[idPlane3],ptNormal2);

				ptVertexNormal.x = (ptNormal1.x + ptNormal2.x) / 2;
				ptVertexNormal.y = (ptNormal1.y + ptNormal2.y) / 2;
				ptVertexNormal.z = (ptNormal1.z + ptNormal2.z) / 2;

				ptVertexNormalArray.push_back(ptVertexNormal);

				CalPlaneNormal(ptEnd3DArray[idPlane3],ptEnd3DArray[idPlane2],ptBegin3DArray[idPlane2],ptNormal2);
				CalPlaneNormal(ptBegin3DArray[idPlane2],ptEnd3DArray[idPlane2],ptEnd3DArray[idPlane1],ptNormal1);

				ptVertexNormal.x = (ptNormal1.x + ptNormal2.x) / 2;
				ptVertexNormal.y = (ptNormal1.y + ptNormal2.y) / 2;
				ptVertexNormal.z = (ptNormal1.z + ptNormal2.z) / 2;

				ptVertexNormalArray.push_back(ptVertexNormal);
			}			
		}
		else
		{
			int idPlane = 0;
 			unsigned int idCentre = 0;
			unsigned int idDot = 1;
			vgKernel::Vec3 ptPlaneNormal,ptCurveTangent;

			CalNextNodeOnBeeline(ptCentre3DArray[0],ptCentre3DArray[1],ptBegin3DArray,ptMiddle3DArray);
			
			CalPlaneNormal(ptCentre3DArray[0],ptCentre3DArray[1],ptCentre3DArray[5],ptPlaneNormal);

			for(i = 0; i < nSurfaceNum; i++)
			{
				idPlane1 = i -1;		idPlane2 = i;	idPlane3 = i + 1;
				if(idPlane1 == -1) idPlane1 = nSurfaceNum - 1;
				if(idPlane3 == nSurfaceNum) idPlane3 = 0;
				CalPlaneNormal(ptBegin3DArray[idPlane1],ptBegin3DArray[idPlane2],ptMiddle3DArray[idPlane2],ptNormal1);
				CalPlaneNormal(ptMiddle3DArray[idPlane2],ptBegin3DArray[idPlane2],ptBegin3DArray[idPlane3],ptNormal2);

				ptVertexNormal.x = (ptNormal1.x + ptNormal2.x) / 2;
				ptVertexNormal.y = (ptNormal1.y + ptNormal2.y) / 2;
				ptVertexNormal.z = (ptNormal1.z + ptNormal2.z) / 2;

				ptVertexNormalArray.push_back(ptVertexNormal);
			}

			TRACE ("%d\n", ptCircleCentre3DArray.size());
			TRACE ("%d\n", ptCentre3DArray.size());

			for( i = 1; i < ptCentre3DArray.size() - 1; i++)
			{
				if(idDot % 5 == 0 && i != ptCentre3DArray.size() - 2)
				{
					CalNextNodeOnBeeline(ptCentre3DArray[i],ptCentre3DArray[i + 1],ptMiddle3DArray,ptEnd3DArray);

					CalPlaneNormal(ptCentre3DArray[i],ptCentre3DArray[i + 1],ptCentre3DArray[i + 5],ptPlaneNormal);

					idDot += 1;
					idCentre += 1;
				}
				else if(idDot % 5 == 0 && i == ptCentre3DArray.size() - 2)
				{
					CalNextNodeOnBeeline(ptCentre3DArray[i],ptCentre3DArray[i + 1],ptMiddle3DArray,ptEnd3DArray);					
				}
				else
				{
					//TRACE ("%d\n", idCentre);
					CalCurveTangent(ptPlaneNormal,ptCircleCentre3DArray[idCentre],ptCentre3DArray[i+1],ptCurveTangent);

					CalNextNodeOnCurve(ptCentre3DArray[i],ptCentre3DArray[i + 1],ptMiddle3DArray,ptEnd3DArray,ptCurveTangent);

					idDot += 1;
				}

				for(int j = 0; j < nSurfaceNum; j++)
				{
					idPlane1 = j -1;		idPlane2 = j;	idPlane3 = j + 1;
					if(idPlane1 == -1) idPlane1 = nSurfaceNum - 1;
					if(idPlane3 == nSurfaceNum) idPlane3 = 0;
					CalPlaneNormal(ptMiddle3DArray[idPlane1],ptMiddle3DArray[idPlane2],ptEnd3DArray[idPlane2],ptNormal1);
					CalPlaneNormal(ptEnd3DArray[idPlane2],ptMiddle3DArray[idPlane2],ptMiddle3DArray[idPlane3],ptNormal2);
					CalPlaneNormal(ptMiddle3DArray[idPlane3],ptMiddle3DArray[idPlane2],ptBegin3DArray[idPlane2],ptNormal3);
					CalPlaneNormal(ptBegin3DArray[idPlane2],ptMiddle3DArray[idPlane2],ptMiddle3DArray[idPlane1],ptNormal4);

					ptVertexNormal.x = (ptNormal1.x + ptNormal2.x + ptNormal3.x + ptNormal4.x) / 4;
					ptVertexNormal.y = (ptNormal1.y + ptNormal2.y + ptNormal3.y + ptNormal4.y) / 4;
					ptVertexNormal.z = (ptNormal1.z + ptNormal2.z + ptNormal3.z + ptNormal4.z) / 4;

					ptVertexNormalArray.push_back(ptVertexNormal);
				}

				std::vector <vgKernel::Vec3> ::iterator iter1 = ptMiddle3DArray.begin();
				std::vector <vgKernel::Vec3> ::iterator iter_end1 = ptMiddle3DArray.end();
				ptBegin3DArray.assign(iter1, iter_end1);
				
				std::vector <vgKernel::Vec3> ::iterator iter2 = ptEnd3DArray.begin();
				std::vector <vgKernel::Vec3> ::iterator iter_end2 = ptEnd3DArray.end();
				ptMiddle3DArray.assign(iter2, iter_end2);
				
			}

			for(int i = 0; i < nSurfaceNum; i++)
			{
				idPlane1 = i -1;		idPlane2 = i;	idPlane3 = i + 1;
				if(idPlane1 == -1) idPlane1 = nSurfaceNum - 1;
				if(idPlane3 == nSurfaceNum) idPlane3 = 0;		
				CalPlaneNormal(ptMiddle3DArray[idPlane3],ptMiddle3DArray[idPlane2],ptBegin3DArray[idPlane2],ptNormal2);
				CalPlaneNormal(ptBegin3DArray[idPlane2],ptMiddle3DArray[idPlane2],ptMiddle3DArray[idPlane1],ptNormal1);

				ptVertexNormal.x = (ptNormal1.x + ptNormal2.x) / 2;
				ptVertexNormal.y = (ptNormal1.y + ptNormal2.y) / 2;
				ptVertexNormal.z = (ptNormal1.z + ptNormal2.z) / 2;

				ptVertexNormalArray.push_back(ptVertexNormal);
			}
		}

	}

	void PipeLineObject::CalPlaneNormal(vgKernel::Vec3 &ptTop1,vgKernel::Vec3 &ptIntersect,vgKernel::Vec3 &ptTop2,vgKernel::Vec3 &ptPlaneNormal)
	{
		vgKernel::Vec3 Line1Normal,Line2Normal;
		double dS;

		Line1Normal.x = ptTop1.x - ptIntersect.x;
		Line1Normal.y = ptTop1.y - ptIntersect.y;
		Line1Normal.z = ptTop1.z - ptIntersect.z;

		Line2Normal.x = ptTop2.x - ptIntersect.x;
		Line2Normal.y = ptTop2.y - ptIntersect.y;
		Line2Normal.z = ptTop2.z - ptIntersect.z;

		ptPlaneNormal.x = Line1Normal.y * Line2Normal.z - Line2Normal.y * Line1Normal.z;
		ptPlaneNormal.y = Line1Normal.z * Line2Normal.x - Line2Normal.z * Line1Normal.x;
		ptPlaneNormal.z = Line1Normal.x * Line2Normal.y - Line2Normal.x * Line1Normal.y;

		dS = sqrt(pow(ptPlaneNormal.x,2) + pow(ptPlaneNormal.y,2) + pow(ptPlaneNormal.z,2));

		ptPlaneNormal.x /= dS;
		ptPlaneNormal.y /= dS;
		ptPlaneNormal.z /= dS;
	}

	void PipeLineObject::CalCurveTangent(vgKernel::Vec3& ptPlaneNormal,vgKernel::Vec3& ptCurveCentre,vgKernel::Vec3& ptPoint3D,vgKernel::Vec3& ptCurveTangent)
	{
		int mark;
		double D1,D2,D3;
		D1 = ptPlaneNormal.y * (ptPoint3D.z - ptCurveCentre.z) - ptPlaneNormal.z * (ptPoint3D.y - ptCurveCentre.y);
		D2 = ptPlaneNormal.x * (ptPoint3D.z - ptCurveCentre.z) - ptPlaneNormal.z * (ptPoint3D.x - ptCurveCentre.x);
		D3 = ptPlaneNormal.x * (ptPoint3D.y - ptCurveCentre.y) - ptPlaneNormal.y * (ptPoint3D.x - ptCurveCentre.x);

		if(fabs(D1) > 1e-10)	mark = 1;
		else if(fabs(D2) > 1e-10)	mark = 2;
		else mark = 3;

		switch(mark)
		{
		case 1:
			{
				ptCurveTangent.x = 1;

				ptCurveTangent.y = (-ptPlaneNormal.x * (ptPoint3D.z - ptCurveCentre.z) - ptPlaneNormal.z * 
					(ptCurveCentre.x - ptPoint3D.x)) / D1;

				ptCurveTangent.z = (ptPlaneNormal.y * (ptCurveCentre.x - ptPoint3D.x) + ptPlaneNormal.x * 
					(ptPoint3D.y - ptCurveCentre.y)) / D1;
				break;
			}
		case 2:
			{
				ptCurveTangent.y = 1;

				ptCurveTangent.x = (-ptPlaneNormal.y * (ptPoint3D.z - ptCurveCentre.z) - ptPlaneNormal.z * 
					(ptCurveCentre.y - ptPoint3D.y)) / D2;

				ptCurveTangent.z = (ptPlaneNormal.x * (ptCurveCentre.y - ptPoint3D.y) + ptPlaneNormal.y * 
					(ptPoint3D.x - ptCurveCentre.x)) / D2;
				break;
			}
		case 3:
			{
				ptCurveTangent.z = 1;

				ptCurveTangent.x = (-ptPlaneNormal.z * (ptPoint3D.y - ptCurveCentre.y) - ptPlaneNormal.y * 
					(ptCurveCentre.z - ptPoint3D.z)) / D3;

				ptCurveTangent.y = (ptPlaneNormal.x * (ptCurveCentre.z - ptPoint3D.z) + ptPlaneNormal.z * 
					(ptPoint3D.x - ptCurveCentre.x)) / D3;
				break;
			}
		}


	}

	void PipeLineObject::CalNextNodeOnBeeline(vgKernel::Vec3 FCentre3D,vgKernel::Vec3 NCentre3D,std::vector<vgKernel::Vec3>& FirstArray3D,std::vector<vgKernel::Vec3>& NextArray3D)
	{
		vgKernel::Vec3 lineNormalBToT;
		double k1 = 0.0;
		double k2 = 0.0;
		double k3 = 0.0;
		double D1 = 0.0;
		double D2 = 0.0;
		double D3 = 0.0;
		//k2,k3,D1,D2,D3;
		vgKernel::Vec3 pt3d;

		NextArray3D.clear();

		lineNormalBToT.x = NCentre3D.x - FCentre3D.x;
		lineNormalBToT.y = NCentre3D.y - FCentre3D.y;
		lineNormalBToT.z = NCentre3D.z - FCentre3D.z;

		for(int i = 0; i < FirstArray3D.size(); i++)
		{
			//利用克莱姆法则计算下一个管点处边缘上的坐标
			int mark;
			D1 = pow(lineNormalBToT.x,3) + lineNormalBToT.x * pow(lineNormalBToT.y,2) + lineNormalBToT.x * pow(lineNormalBToT.z,2);
			D2 = lineNormalBToT.y * pow(lineNormalBToT.z,2) + lineNormalBToT.y * pow(lineNormalBToT.x,2) + pow(lineNormalBToT.y,3);
			D3 = -lineNormalBToT.z * pow(lineNormalBToT.x,2) - lineNormalBToT.z * pow(lineNormalBToT.y,2) + pow(lineNormalBToT.z,3); 

			if(fabs(D1) > 1e-10)
				mark = 1;
			else if(fabs(D2) > 1e-10)
				mark = 2;
			else
				mark = 3;
			switch(mark)
			{
			case 1:
				{
					k1 = FirstArray3D[i].x * lineNormalBToT.y - FirstArray3D[i].y * lineNormalBToT.x;
					k2 = FirstArray3D[i].x * lineNormalBToT.z - FirstArray3D[i].z * lineNormalBToT.x;
					k3 = NCentre3D.x * lineNormalBToT.x + NCentre3D.y * lineNormalBToT.y + NCentre3D.z * lineNormalBToT.z;

					pt3d.x = (k3 * pow(lineNormalBToT.x,2) + k1 * lineNormalBToT.x * lineNormalBToT.y + k2 * lineNormalBToT.x * lineNormalBToT.z) / D1;
					pt3d.y = (k2 * lineNormalBToT.y * lineNormalBToT.z - k1 * pow(lineNormalBToT.x,2) + k3 * lineNormalBToT.x * lineNormalBToT.y - k1 * pow(lineNormalBToT.z,2)) / D1;
					pt3d.z = (k1 * lineNormalBToT.y * lineNormalBToT.z - k2 * pow(lineNormalBToT.x,2) - k2 * pow(lineNormalBToT.y,2) + k3 * lineNormalBToT.x * lineNormalBToT.z) / D1;
					break;
				}
			case 2:
				{
					k1 = FirstArray3D[i].x * lineNormalBToT.y - FirstArray3D[i].y * lineNormalBToT.x;
					k2 = FirstArray3D[i].y * lineNormalBToT.z - FirstArray3D[i].z * lineNormalBToT.y;
					k3 = NCentre3D.x * lineNormalBToT.x + NCentre3D.y * lineNormalBToT.y + NCentre3D.z * lineNormalBToT.z;

					pt3d.x = (k1 * pow(lineNormalBToT.z,2) + k3 * lineNormalBToT.x * lineNormalBToT.y + k1 * pow(lineNormalBToT.y,2) + k2 * lineNormalBToT.x * lineNormalBToT.z) / D2;
					pt3d.y = (k2 * lineNormalBToT.y * lineNormalBToT.z - k1 * lineNormalBToT.x * lineNormalBToT.y + k3 * pow(lineNormalBToT.y,2)) / D2;
					pt3d.z = (k3 * lineNormalBToT.y * lineNormalBToT.z - k2 * pow(lineNormalBToT.x,2) - k1 * lineNormalBToT.x * lineNormalBToT.z - k2 * pow(lineNormalBToT.y,2)) / D2;
					break;
				}
			case 3:
				{
					k2 = FirstArray3D[i].y * lineNormalBToT.z - FirstArray3D[i].z * lineNormalBToT.y;
					k2 = FirstArray3D[i].x * lineNormalBToT.z - FirstArray3D[i].z * lineNormalBToT.x;
					k3 = NCentre3D.x * lineNormalBToT.x + NCentre3D.y * lineNormalBToT.y + NCentre3D.z * lineNormalBToT.z;

					pt3d.x = (-k3 * lineNormalBToT.x * lineNormalBToT.z - k2 * pow(lineNormalBToT.y,2) + k1 * lineNormalBToT.x * lineNormalBToT.y - k2 * pow(lineNormalBToT.z,2)) / D3;
					pt3d.y = (-k1 * pow(lineNormalBToT.x,2) - k3 * lineNormalBToT.y * lineNormalBToT.z + k2 * lineNormalBToT.x * lineNormalBToT.y - k1 * pow(lineNormalBToT.z,2)) / D3;
					pt3d.z = (k2 * lineNormalBToT.x * lineNormalBToT.z + k1 * lineNormalBToT.y * lineNormalBToT.z * k3 * pow(lineNormalBToT.z,2)) / D3;
					break;
				}
			}
			NextArray3D.push_back(pt3d);
		}
	}

	void PipeLineObject::CalNextNodeOnCurve(vgKernel::Vec3 FCentre3D,vgKernel::Vec3 NCentre3D,std::vector <vgKernel::Vec3>& FirstArray3D,std::vector <vgKernel::Vec3>& NextArray3D,vgKernel::Vec3& ptCurveTangent)
	{
		vgKernel::Vec3 lineNormalBToT;
		double k1,k2,k3,D;
		vgKernel::Vec3 pt3d;

		NextArray3D.clear();

		lineNormalBToT.x = NCentre3D.x - FCentre3D.x;
		lineNormalBToT.y = NCentre3D.y - FCentre3D.y;
		lineNormalBToT.z = NCentre3D.z - FCentre3D.z;

		for(int i = 0; i < FirstArray3D.size(); i++)
		{
			//利用克莱姆法则计算下一个管点处边缘上的坐标
			k1 = FirstArray3D[i].x * lineNormalBToT.y - FirstArray3D[i].y * lineNormalBToT.x;
			k2 = FirstArray3D[i].x * lineNormalBToT.z - FirstArray3D[i].z * lineNormalBToT.x;
			k3 = NCentre3D.x * ptCurveTangent.x + NCentre3D.y * ptCurveTangent.y + NCentre3D.z * ptCurveTangent.z;

			D = pow(lineNormalBToT.x,2) * ptCurveTangent.x + lineNormalBToT.x * lineNormalBToT.y * ptCurveTangent.y + lineNormalBToT.x * lineNormalBToT.z * ptCurveTangent.z;

			pt3d.x = (k3 * pow(lineNormalBToT.x,2) + k1 * lineNormalBToT.x * ptCurveTangent.y + k2 * lineNormalBToT.x * ptCurveTangent.z) / D;
			pt3d.y = (k2 * lineNormalBToT.y * ptCurveTangent.z - k1 * lineNormalBToT.x * ptCurveTangent.x + k3 * lineNormalBToT.x * lineNormalBToT.y - k1 * lineNormalBToT.z * ptCurveTangent.z) / D;
			pt3d.z = (k1 * ptCurveTangent.y * lineNormalBToT.z - k2 * lineNormalBToT.x * ptCurveTangent.x - k2 * lineNormalBToT.y * ptCurveTangent.y + k3 * lineNormalBToT.x * lineNormalBToT.z) / D;

			NextArray3D.push_back(pt3d);
		}
	}

	void PipeLineObject::calContactVertexesNormal(vgKernel::Vec3 ptTest1, vgKernel::Vec3 ptTest2, double m_dContactRadius)
	{
		long int i = 0 ;
		double dCosAngles[3][3] = {0,0,0,0,0,0,0,0,0};
		CalculateRotateParameter(ptTest1, ptTest2, dCosAngles);

		int nSurfaceNum = 10;
		std::vector <vgKernel::Vec3> ptBegin3DArray,ptMiddle3DArray,ptEnd3DArray;
		vgKernel::Vec3  ptemp3D,pt3d;

		int idPlane1,idPlane2,idPlane3;
		vgKernel::Vec3 ptNormal1,ptNormal2,ptNormal3,ptNormal4;
		vgKernel::Vec3 ptVertexNormal;

		double dInitialAngle=0.0;

		for (int i = 0; i < nSurfaceNum; i++)
		{
			ptemp3D.x = m_dContactRadius*cos(dInitialAngle);
			ptemp3D.y = m_dContactRadius*sin(dInitialAngle);
			ptemp3D.z = 0.0;

			pt3d.x = ptTest1.x + dCosAngles[0][0] * ptemp3D.x + dCosAngles[0][1] * ptemp3D.y + dCosAngles[0][2] * ptemp3D.z;
			pt3d.y = ptTest1.y + dCosAngles[1][0] * ptemp3D.x + dCosAngles[1][1] * ptemp3D.y + dCosAngles[1][2] * ptemp3D.z;
			pt3d.z = ptTest1.z + dCosAngles[2][0] * ptemp3D.x + dCosAngles[2][1] * ptemp3D.y + dCosAngles[2][2] * ptemp3D.z;
			ptBegin3DArray.push_back(pt3d);

			dInitialAngle += 2 * PI / nSurfaceNum;
		}

		CalNextNodeOnBeeline(ptTest1, ptTest2,ptBegin3DArray,ptEnd3DArray);

		for( long int i = 0; i < nSurfaceNum; i++)
		{
			idPlane1 = i -1;		idPlane2 = i;	idPlane3 = i + 1;
			if(idPlane1 == -1) idPlane1 = nSurfaceNum - 1;
			if(idPlane3 == nSurfaceNum) idPlane3 = 0;

			CalPlaneNormal(ptBegin3DArray[idPlane1],ptBegin3DArray[idPlane2],ptEnd3DArray[idPlane2],ptNormal1);
			CalPlaneNormal(ptEnd3DArray[idPlane2],ptBegin3DArray[idPlane2],ptBegin3DArray[idPlane3],ptNormal2);

			ptVertexNormal.x = (ptNormal1.x + ptNormal2.x) / 2;
			ptVertexNormal.y = (ptNormal1.y + ptNormal2.y) / 2;
			ptVertexNormal.z = (ptNormal1.z + ptNormal2.z) / 2;

			ptContactVertexNormalArray.push_back(ptVertexNormal);

			CalPlaneNormal(ptEnd3DArray[idPlane3],ptEnd3DArray[idPlane2],ptBegin3DArray[idPlane2],ptNormal2);
			CalPlaneNormal(ptBegin3DArray[idPlane2],ptEnd3DArray[idPlane2],ptEnd3DArray[idPlane1],ptNormal1);

			ptVertexNormal.x = (ptNormal1.x + ptNormal2.x) / 2;
			ptVertexNormal.y = (ptNormal1.y + ptNormal2.y) / 2;
			ptVertexNormal.z = (ptNormal1.z + ptNormal2.z) / 2;

			ptContactVertexNormalArray.push_back(ptVertexNormal);
		}			

	}

	void PipeLineObject::drawContactPipeLine(CString flag, vgKernel::Vec3 ptTest1, vgKernel::Vec3 ptTest2, double m_dContactRadius)
	{
		UINT nNormalID = 0;
		double dCosAngles[3][3] = {0,0,0,0,0,0,0,0,0};		
		CalculateRotateParameter(ptTest1,ptTest2,dCosAngles);

		int nSurfaceNum = 10;
		std::vector <vgKernel::Vec3> bottomArray3D,topArray3D;
		vgKernel::Vec3  ptemp3D,pt3d;

		double dInitialAngle=0.0;

		for(int i = 0;i < nSurfaceNum;i++)
		{
			ptemp3D.x = m_dContactRadius*cos(dInitialAngle);
			ptemp3D.y = m_dContactRadius*sin(dInitialAngle);
			ptemp3D.z = 0.0;

			pt3d.x = ptTest1.x + dCosAngles[0][0] * ptemp3D.x + dCosAngles[0][1] * ptemp3D.y + dCosAngles[0][2] * ptemp3D.z;
			pt3d.y = ptTest1.y + dCosAngles[1][0] * ptemp3D.x + dCosAngles[1][1] * ptemp3D.y + dCosAngles[1][2] * ptemp3D.z;
			pt3d.z = ptTest1.z + dCosAngles[2][0] * ptemp3D.x + dCosAngles[2][1] * ptemp3D.y + dCosAngles[2][2] * ptemp3D.z;
			bottomArray3D.push_back(pt3d);

			dInitialAngle += 2 * PI / nSurfaceNum;
		}


			CalNextNodeOnBeeline(ptTest1, ptTest2, bottomArray3D, topArray3D);

			glColor3f(0.0f, 0.8f, 0.5f);
			glBegin(GL_QUAD_STRIP);
			for(int j = 0; j < nSurfaceNum; j++)
			{			
				glNormal3d(ptContactVertexNormalArray[nNormalID].x,ptContactVertexNormalArray[nNormalID].y,ptContactVertexNormalArray[nNormalID].z);
				glVertex3d(bottomArray3D[j].x,bottomArray3D[j].y,bottomArray3D[j].z);

				glNormal3d(ptContactVertexNormalArray[nNormalID + nSurfaceNum].x,ptContactVertexNormalArray[nNormalID + nSurfaceNum].y,ptContactVertexNormalArray[nNormalID + nSurfaceNum].z);
				glVertex3d(topArray3D[j].x,topArray3D[j].y,topArray3D[j].z);

				nNormalID ++;
			}
			glNormal3d(ptContactVertexNormalArray[nNormalID - nSurfaceNum].x,ptContactVertexNormalArray[nNormalID - nSurfaceNum].y,ptContactVertexNormalArray[nNormalID - nSurfaceNum].z);
			glVertex3d(bottomArray3D[0].x,bottomArray3D[0].y,bottomArray3D[0].z);

			glNormal3d(ptContactVertexNormalArray[nNormalID].x,ptContactVertexNormalArray[nNormalID].y,ptContactVertexNormalArray[nNormalID].z);
			glVertex3d(topArray3D[0].x,topArray3D[0].y,topArray3D[0].z);
			glEnd();

			std::vector <vgKernel::Vec3> ::iterator bottom_iter = bottomArray3D.begin();
			std::vector <vgKernel::Vec3> ::iterator bottom_iter_end = bottomArray3D.end();

			std::vector <vgKernel::Vec3> ::iterator top_iter = topArray3D.begin();
			std::vector <vgKernel::Vec3> ::iterator top_iter_end = topArray3D.end();

			if (flag == "middle")
			{

				for (; bottom_iter != bottom_iter_end; bottom_iter ++)
				{
					midPipeArray3D.push_back((*bottom_iter));
				}

				for (; top_iter != top_iter_end; top_iter ++)
				{
					midPipeArray3D.push_back((*top_iter));
				}

			}

			if (flag == "front" )
			{
				for (; bottom_iter != bottom_iter_end; bottom_iter ++)
				{
					frontPipeArray3D.push_back((*bottom_iter));
				}

				for (; top_iter != top_iter_end; top_iter ++)
				{
					frontPipeArray3D.push_back((*top_iter));
				}

			}

			if (flag == "back")
			{
				for (; bottom_iter != bottom_iter_end; bottom_iter ++)
				{
					backPipeArrray3D.push_back((*bottom_iter));
				}

				for (; top_iter != top_iter_end; top_iter ++)
				{
					backPipeArrray3D.push_back((*top_iter));
				}
			}
	}

	void PipeLineObject::drawContactPipeLine()
	{
		std::vector <vgKernel::Vec3> ::iterator iterMid = midPipeArray3D.begin();
		std::vector <vgKernel::Vec3> ::iterator iterMid_end = midPipeArray3D.end();

		std::vector <vgKernel::Vec3> ::iterator iterFront = frontPipeArray3D.begin();
		std::vector <vgKernel::Vec3> ::iterator iterFront_end = frontPipeArray3D.end();

		std::vector <vgKernel::Vec3> ::iterator iterBack = frontPipeArray3D.begin();
		std::vector <vgKernel::Vec3> ::iterator iterBack_end = frontPipeArray3D.end();

		int j = 0;

		if (!midPipeArray3D.empty() && !frontPipeArray3D.empty())
		{
			glBegin(GL_TRIANGLE_STRIP);		
			for (int i = 10; i < 20; i++)
			{
				glVertex3f(midPipeArray3D[i].x, midPipeArray3D[i].y, midPipeArray3D[i].z);
				glVertex3f(frontPipeArray3D[j].x, frontPipeArray3D[j].y, frontPipeArray3D[j].z);
				j++;
			}
			glVertex3f(midPipeArray3D[10].x, midPipeArray3D[10].y, midPipeArray3D[10].z);
			glVertex3f(frontPipeArray3D[0].x, frontPipeArray3D[0].y, frontPipeArray3D[0].z);

			glEnd();
		}
	}


}//end namespace
