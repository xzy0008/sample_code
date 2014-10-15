#pragma once

#include <vgGIS3D/vggiRouteMap.h>
#include <vgKernel/vgkSharePtr.h>

#include <vgGIS3D/vggiRouteInfo.h>

namespace vgGIS3D
{
	using vgKernel::Vec2;

	typedef struct JointDist_t
	{
		JointDist_t(int p=0, double d=0) 
		{
			pointIndex = p;
			dist = d;
		}

		int pointIndex;
		double dist;
	}JointDist;

	class JointPoint
	{
	public:

		JointPoint(vgKernel::Vec3 position, float press = 0.0)
		{
			m_pJointVec = new vector<JointDist>;
			m_pos = position;
			m_pressValue = press;     //add by KingHJ  2010.01.19  管线节点的压力值
		}

		~JointPoint()
		{
			if (m_pJointVec != NULL)
			{
				delete m_pJointVec;
			}
		}

		vgKernel::Vec3 getPos()
		{
			return m_pos;
		}
		
		void setPos(vgKernel::Vec3 pos) { m_pos = pos; }

		double connectWith(int index);
		
		bool addRoute(JointDist dst);
		bool removeRoute(int index);

		vector<JointDist>* getJointVecPointer() { return m_pJointVec; }

	public:
		double m_pressValue;
		vector<JointDist> *m_pJointVec;   //edit by KingHJ 从protected权限改为了public
		vgKernel::Vec3	m_pos;                 //edit by KingHJ 从protected权限改为了public

	protected:				
		
	};

	typedef vgKernel::SharePtr<JointPoint> JointPointPtr;

	class OGRRouteMap : public RouteMap
	{
	public:
		OGRRouteMap();

		~OGRRouteMap();

		int constructFromBreakShapeLayer(string layerName);
		int readFromFile(string filePath);
		int saveToFile(string filePath);

	public:
		
		string getName() { return m_layerName; }
		
		void render();

		void setStartPoint(vgKernel::Vec3 point);

		void setEndPoint(vgKernel::Vec3 point);

		void clearResult();

	protected:

		bool intersection(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2& re);

		int checkExist(vgKernel::Vec3 point);
		
		bool programWithDijkstra();

		vector<JointPointPtr> m_jointArray;
		vector<RouteInfo> m_routeArray;

		// 最短路径算法
		vector<int>	m_pointInRoad;

		bool m_enableResultRender;

		int m_startPointIndex;
		int m_endPointIndex;		

		string m_layerName;
	};

}