#pragma once

#include <vgMod/vgdepDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkColorVal.h>
#include <vgKernel/vgkRenderer.h>

#include <map>

using std::map;


namespace vgAutoBuild
{

	const vgKernel::RendererType RENDERER_TYPE_AUTOSOLIDBUILD = 7001;

	typedef std::vector<vgKernel::Vec3>	PointsArray;

	class VGDEP_EXPORT SolidColorIndex
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

	class VGDEP_EXPORT SolidBuildNode : public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( SolidBuildNode )

	public:
		SolidBuildNode(PointsArray polygon);

		SolidBuildNode()
		{

		}

		virtual ~SolidBuildNode()
		{

		}

		int getFloor() { return m_floor; }
		
		void setFloor(int f); 
		
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

		float getHeightPerLayer(){ return m_heightPerFloor; }

		void setHeightPerLayer(float height);
	
		void colorSolidByHeight(bool bIfMultiColor = false);

	public:
		void setColor(vgKernel::ColorVal val);
		vgKernel::ColorVal getColor();

	public:

		// 使用display list来创建
		void renderUsingDisplayList();

		virtual int getNumOfPoints()
		{
			return m_innerPolygon.size();
		}

		// 渲染一次. 为了创建display list
		void renderOnceForDisplayList();  

		virtual void invalidateRendering();

		void initialise();
	protected:

		vgKernel::ColorVal lookupColor(int floor, int pointIndex);

		PointsArray m_innerPolygon;

		float m_heightPerFloor;

		int m_floor;

		GLuint _callListId;
		
		vgKernel::ColorVal m_defaultColor;

		std::map<int, vgKernel::ColorVal> m_colorMap;

		std::map<int, vgKernel::ColorVal> m_colorMapOld;


	public:
		//继承自Renderer接口

		virtual String getName()
		{
			return _meshName;
		}

		virtual String* getNamePtr()
		{
			return &_meshName;
		}

		virtual void setName( const String& newname )
		{
			_meshName = newname;
		}

		virtual vgKernel::UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		virtual void translate(const float& x, const float& y, const float& z);

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z);

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z);

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) ;

		virtual vgKernel::Box getBoundingBox()
		{
			return _dynamicBox;
		}

		virtual long getNumOfTriangles()
		{
			return _numberOfTriangles;
		}

		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  );

		virtual void render();

		virtual void computeBoundingBox();

	public:
		//读写接口
		void	writeToFile( CFile &fp );
		bool	readFromFile( CFile &fp );

	private:
		 String _meshName;

		 vgKernel::Box _dynamicBox;
		 vgKernel::Box _staticBox;

		 vgKernel::Mat4 _matrix;

		 long	_numberOfTriangles;

		 vgKernel::UniqueID _uniqueID;

		 float _squaredDistanceToViewer;


	};

	VGK_RENDERER_OUT_DECLARE( SolidBuildNode )

}
