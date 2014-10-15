#pragma once
#include <vgGIS/vggisDefinition.h>

namespace vgGIS3D
{
	class VGG_EXPORT RouteInfo
	{
	public:
		RouteInfo()
		{
			m_routeLength = 0;
		}

		void addPoint(vgKernel::Vec3 point)
		{
			m_routePointVec.push_back(point);
		}

		vgKernel::Vec3 getStartPoint()
		{
			return m_routePointVec[0];
		}

		vgKernel::Vec3 getEndPoint()
		{
			if (m_routePointVec.size() == 0)
			{
				return vgKernel::Vec3(0,0,0);
			}

			return m_routePointVec[m_routePointVec.size()-1];
		}

		vector<vgKernel::Vec3>* getPointVecPtr()
		{
			return &m_routePointVec;
		}

	protected:
		vector<vgKernel::Vec3> m_routePointVec;

		double m_routeLength;
	};
}