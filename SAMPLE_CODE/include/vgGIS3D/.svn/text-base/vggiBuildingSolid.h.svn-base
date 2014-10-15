#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiPolygon.h>
#include <vgKernel/vgkColorVal.h>

#include <map>

using std::map;


namespace vgGIS3D
{
	class VGG_EXPORT SolidColorIndex
	{
	public:
		int floorNum;
		int pointIndex;

		SolidColorIndex(int f, int p)
		{
			floorNum = f;
			pointIndex = p;
		}

		inline bool operator == ( const SolidColorIndex& sc ) const
		{
			return (floorNum == sc.floorNum) && (pointIndex == sc.pointIndex);
		}

		inline bool operator < ( const SolidColorIndex& sc) const 
		{
			if (floorNum < sc.floorNum)
			{
				return true;
			}

			if (floorNum == sc.floorNum && pointIndex < sc.pointIndex)
			{
				return true;
			}

			return false;
		}
	} ;

	class VGG_EXPORT BuildingSolid : public Geometry
	{
	public:
		BuildingSolid( OGRFeature* feature, 
			Layer* father_layer );
		virtual ~BuildingSolid()
		{

		}

		GeomtryType getType() { return GEOMTRY_BUILDING_SOLID; }

		//------------------------------------------
		// 得到每个field的信息要
		//------------------------------------------
		//getFieldInfo

		int getFloor() { return m_floor; }
		
		void setFloor(int f) 
		{
			m_floor = f; 
		}
		
		vgKernel::ColorVal getColor(int floorNum, int pointIdex) { return lookupColor(floorNum, pointIdex); }

		// 设置某一层的颜色
		void setFloorColor(int floorNum, vgKernel::ColorVal color, bool updateNow = true);

		// 设置某层上一个点的颜色
		void setColorByIndex(int floorNum, int pointIndex, vgKernel::ColorVal color, bool updateNow = true);

		// 设置整体颜色
		void setSolidColor(vgKernel::ColorVal color, bool updateNow = true);		

		//还原到修改前颜色
		void revertSolidColor();

		vgKernel::ColorVal getFloorColor(int floor);

		float getHeightPerLayer()
		{
			return m_heightPerFloor;
		}

		void setHeightPerLayer(float height)
		{
			m_heightPerFloor = height;
		}
	
		std::vector<RingStruct>& getRingStructVec()
		{
			return m_innerPolygon.getRings();
		}

		void colorSolidByHeight(bool bIfMultiColor = false);

		// Added By FengYK @2010-05-05 21:22
		double getPlaneArea(); // 获得投影到平面的面积,经测试是准确的

	public:

		// 使用display list来创建
		virtual void renderUsingDisplayList();

		OGRFeaturePtr getOGRFeaturePtr()
		{
			return m_innerPolygon.getOGRFeaturePtr();
		}

		// 注意, 客户端负责删除.
		OGRFeature* getOGRFeature()
		{
			return m_innerPolygon.getOGRFeature();
		}

		// 注意, 参数要客户端删除.
		void setFeature( OGRFeature* feature )
		{
			m_innerPolygon.setFeature(feature);
		}

		virtual int getNumOfPoints()
		{
			return m_innerPolygon.getNumOfPoints();
		}

		virtual vgKernel::Box getEnvelope3f()
		{
			return m_innerPolygon.getEnvelope3f();
		}

		virtual Box3d getEnvelope3d()
		{
			return m_innerPolygon.getEnvelope3d();
		}

		// 渲染一次. 为了创建display list
		virtual void renderOnceForDisplayList();  
// 		{
// 			m_innerPolygon.renderOnceForDisplayList();
// 		}

		// 通过OGRFeature来读取数据
		virtual bool readDataFromOGRFeature()
		{
			return m_innerPolygon.readDataFromOGRFeature();
		}

		// 删除临时数据.
		// 注意, 可以再读取的.
		virtual void clearRecoverableData()
		{
			m_innerPolygon.clearRecoverableData();
		}

		virtual bool testIntersect( const RayLine3d& rayline )
		{
			return m_innerPolygon.testIntersect(rayline);
		}

		virtual void renderInSelectedMode()
		{
			m_innerPolygon.renderInSelectedMode();
		}

		virtual bool attachToTerrain()
		{
			return m_innerPolygon.attachToTerrain();
		}

		virtual void invalidateRendering();

		virtual Layer* getFatherLayer()
		{
			return m_innerPolygon.getFatherLayer();
		}

		virtual DrawingDescriptor* getDrawingDescriptor()
		{
			return m_innerPolygon.getDrawingDescriptor();
		}

		//virtual OGREnvelope getEnvelope2f() = 0;

	protected:

		vgKernel::ColorVal lookupColor(int floor, int pointIndex);

		Polygon m_innerPolygon;

		float m_heightPerFloor;

		int m_floor;

		GLuint _callListId;
		
		vgKernel::ColorVal m_defaultColor;

		std::map<int, vgKernel::ColorVal> m_colorMap;

		std::map<int, vgKernel::ColorVal> m_colorMapOld;
	};
}
