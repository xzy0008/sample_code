
#pragma once

#include <vgGis/vggisDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiVec3d.h>
#include <vgKernel/vgkBox.h>



namespace vgGIS3D {


	class  VGG_EXPORT Box3d
	{
	public:
		Box3d()
		{

		}
		Box3d( Vec3d maxvert , Vec3d minvert )
			:_maxVertex( maxvert )
			,_minVertex( minvert )
		{
		}
		Box3d( double maxx ,double maxy , double maxz,
			double minx, double miny , double minz )
			:_maxVertex( maxx , maxy , maxz )
			,_minVertex( minx, miny , minz )
		{
		}
		Box3d(double flt)
			:_maxVertex(-flt, -flt, -flt)
			,_minVertex(flt, flt, flt)
		{
		}
		~Box3d()
		{

		}

		inline Box3d& operator=(const Box3d& rhs)
		{
			_maxVertex = rhs._maxVertex;
			_minVertex = rhs._minVertex;

			return *this;
		}

		inline const Vec3d getCenter(void) const
		{
			return (_minVertex + _maxVertex) / 2.0f;
		}

		inline const Vec3d getSize(void) const
		{
			return _maxVertex - _minVertex;
		}

		inline const Vec3d getMinimum() const 
		{
			return _minVertex;
		}

		inline const Vec3d getMaximum() const
		{
			return _maxVertex;
		}

		inline void setMaximum(Vec3d vec)
		{
			_maxVertex = vec;
		}

		inline void setMinimum(Vec3d vec)
		{
			_minVertex = vec;
		}

		inline Vec3d getCorner( const int& cornerNum )
		{
			switch(cornerNum)
			{
			case 0:
				return _minVertex;
			case 1:
				return Vec3d(_minVertex.x, _maxVertex.y, _minVertex.z);
			case 2:
				return Vec3d(_maxVertex.x, _maxVertex.y, _minVertex.z);
			case 3:
				return Vec3d(_maxVertex.x, _minVertex.y, _minVertex.z);
			case 7:
				return Vec3d(_maxVertex.x, _minVertex.y, _maxVertex.z);
			case 6:
				return Vec3d(_minVertex.x, _minVertex.y, _maxVertex.z);
			case 5:
				return Vec3d(_minVertex.x, _maxVertex.y, _maxVertex.z);
			case 4:
				return _maxVertex;
			default:
				return Vec3d();
			}
		}

		void matrixTranslation(const vgKernel::Mat4& mat);
		// only for test
		void render()
		{
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_1D);
			glPushMatrix();

			glColor3f(1,0,0);
			//glColor3f(_colorRed, _colorYel, _colorBlu);

			glLineWidth(1.0);

			Vec3d& m_max = _maxVertex;
			Vec3d& m_min = _minVertex;

			glBegin(GL_LINES);
			{

				glVertex3d( m_max.x , m_max.y , m_max.z );
				glVertex3d( m_min.x , m_max.y , m_max.z );

				glVertex3d( m_max.x , m_max.y , m_max.z );
				glVertex3d( m_max.x , m_min.y , m_max.z );

				glVertex3d( m_max.x , m_max.y , m_max.z );
				glVertex3d( m_max.x , m_max.y , m_min.z );

				glVertex3d( m_min.x , m_min.y , m_min.z );
				glVertex3d( m_max.x , m_min.y , m_min.z );

				glVertex3d( m_min.x , m_min.y , m_min.z );
				glVertex3d( m_min.x , m_max.y , m_min.z );

				glVertex3d( m_min.x , m_min.y , m_min.z );
				glVertex3d( m_min.x , m_min.y , m_max.z );

				glVertex3d( m_min.x , m_max.y , m_max.z );
				glVertex3d( m_min.x , m_max.y , m_min.z );

				glVertex3d( m_min.x , m_max.y , m_max.z );
				glVertex3d( m_min.x , m_min.y , m_max.z );


				glVertex3d( m_max.x , m_min.y , m_max.z );
				glVertex3d( m_max.x , m_min.y , m_min.z );

				glVertex3d( m_max.x , m_min.y , m_max.z );
				glVertex3d( m_min.x , m_min.y , m_max.z );

				glVertex3d( m_max.x , m_min.y , m_min.z );
				glVertex3d( m_max.x , m_max.y , m_min.z );

				glVertex3d( m_min.x , m_max.y , m_min.z );
				glVertex3d( m_max.x , m_max.y , m_min.z );
			}
			glEnd();

			glPopMatrix();

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_1D);

		}

		// add by lss when 2008-10-7 15:22:39
		inline void merge(const Box3d& rhs)
		{
			_minVertex.makeFloor(rhs._minVertex);
			_minVertex.makeFloor(rhs._maxVertex);
			_maxVertex.makeCeil(rhs._maxVertex);
			_maxVertex.makeCeil(rhs._minVertex);
		}
		inline void merge(const Vec3d& rhs)
		{
			_minVertex.makeFloor(rhs);
			_maxVertex.makeCeil(rhs);
		}

		inline Vec3d getHalfSize(void) const
		{
			return (_maxVertex - _minVertex) * 0.5;
		}

		inline bool intersects(const Box3d& b2) const
		{
			// Use up to 6 separating planes
			if (_maxVertex.x < b2._minVertex.x)
				return false;
			if (_maxVertex.y < b2._minVertex.y)
				return false;
			if (_maxVertex.z < b2._minVertex.z)
				return false;

			if (_minVertex.x > b2._maxVertex.x)
				return false;
			if (_minVertex.y > b2._maxVertex.y)
				return false;
			if (_minVertex.z > b2._maxVertex.z)
				return false;

			// otherwise, must be intersecting
			return true;
		}

		inline bool intersectsIn2D(const Box3d b2) const
		{
			if (_maxVertex.x < b2._minVertex.x)
				return false;

			if (_minVertex.x > b2._maxVertex.x)
				return false;

			if (_maxVertex.z < b2._minVertex.z)
				return false;

			if (_minVertex.z > b2._maxVertex.z)
				return false;

			return true;
		}

		String getDetails();

		vgKernel::Box getBoxFloat()
		{
			return vgKernel::Box( 
				_maxVertex.getVec3Float() , _minVertex.getVec3Float() );
		}

		vgKernel::Box getPipeLineBoxFloat(double pipeRadius)
		{
			//Vec3d maxVertex;
			//Vec3d minVertex;
			maxPipeVertex.x = _maxVertex.x + pipeRadius;
			maxPipeVertex.y = _maxVertex.y + pipeRadius;
			maxPipeVertex.z = _maxVertex.z + pipeRadius;

			minPipeVertex.x = _minVertex.x - pipeRadius;
			minPipeVertex.y = _minVertex.y - pipeRadius;
			minPipeVertex.z = _minVertex.z - pipeRadius;

			return vgKernel::Box(
				maxPipeVertex.getVec3Float(), minPipeVertex.getVec3Float());
		}

		// 查看点是否在本rect内. 注意,是2D区域内的XZ
		bool testInside2D(const Vec3d& point3d) const
		{
			int i = 0;
			if (_maxVertex[i] <= point3d[i] || _minVertex[i] >= point3d[i])
			{
				return false;
			}

			i = 2;

			if (_maxVertex[i] <= point3d[i] || _minVertex[i] >= point3d[i])
			{
				return false;
			}

			return true;
		}


	public:

		Vec3d _minVertex;
		Vec3d _maxVertex;

		Vec3d maxPipeVertex;     //add by KingHj  转成管线后的shape包围盒
		Vec3d minPipeVertex;

		static const Box3d NULL_BOX;
	};


	
	
}// end of namespace vgShape
	

 