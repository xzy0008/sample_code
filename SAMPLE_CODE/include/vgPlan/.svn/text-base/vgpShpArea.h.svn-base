#pragma once

#include <gdal/ogr_api.h>
#include <gdal/ogrsf_frmts.h>
#include <vgKernel/vgkMat4.h>

namespace vgPlan
{
 	class vgShpArea
 	{
 	public:
 
		vgShpArea();

 		virtual ~vgShpArea();
 
 		bool setGeometry(OGRGeometry* pGeom, const vgKernel::Mat4 &mat);
 
 		bool setGeometry( OGRGeometry *pGemo )
 		{
 			if (m_pGeometry != NULL)
 			{
 				delete m_pGeometry;
 				m_pGeometry = NULL;
 			}

 			m_pGeometry = pGemo;
 
 			return true;
 		}
 
 		OGREnvelope getEnvelope()
 		{
 			OGREnvelope result;
 
 			if (m_pGeometry != NULL)
 			{
 				m_pGeometry->getEnvelope(&result);
 			}
 
 			return result;
 		}
 
 		OGRGeometry* getGeometry()
 		{
 			return m_pGeometry;
 		}
 
 		void setName(string name)
 		{ 
 			m_areaName = name;
 		}
 
 		string getName()
 		{
 			return m_areaName;
 		}

		double getArea()
		{
			OGRPolygon *pPoly = dynamic_cast<OGRPolygon*>(m_pGeometry);

			if (pPoly == NULL)
			{
				return 0;
			}
			else
			{
				return pPoly->get_Area();
			}
		}
		
		virtual void render();

		void setRenderFlag(bool bRender)
		{
			m_renderFlag = bRender;
		}

 	protected:
 
 		OGRGeometry* m_pGeometry;
		
		vector<vgKernel::Vec3> m_pointVec;

 		string m_areaName;
			
		bool m_renderFlag;
 	};
}