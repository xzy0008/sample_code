


#ifndef __VGKBOX_H__
#define __VGKBOX_H__


#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkMat4.h>


namespace vgKernel {

	/**
		@date 	2008/07/02  10:06	
		@author  xy

		@brief 	

		@see    
	*/
	class VGK_EXPORT Box
	{
	public:
		Box()
		{

		}
		Box( Vec3 maxvert , Vec3 minvert )
			:_maxVertex( maxvert )
			,_minVertex( minvert )
		{
		}

		Box( float maxx ,float maxy , float maxz,
			float minx, float miny , float minz )
			:_maxVertex( maxx , maxy , maxz )
			,_minVertex( minx, miny , minz )
		{
		}

		Box(float flt)
			:_maxVertex(-flt, -flt, -flt)
			,_minVertex(flt, flt, flt)
		{
		}
		~Box()
		{

		}

		inline Box& operator=(const Box& rhs)
		{
			_maxVertex = rhs._maxVertex;
			_minVertex = rhs._minVertex;

			return *this;
		}

		inline const Vec3 getCenter(void) const
		{
			return (_minVertex + _maxVertex) / 2.0f;
		}

		inline const Vec3 getSize(void) const
		{
			return _maxVertex - _minVertex;
		}

		inline const Vec3 getMinimum() const 
		{
			return _minVertex;
		}

		inline const Vec3 getMaximum() const
		{
			return _maxVertex;
		}

		inline void setMaximum(Vec3 vec)
		{
			_maxVertex = vec;
		}

		inline void setMinimum(Vec3 vec)
		{
			_minVertex = vec;
		}

		inline Vec3 getCorner( const int& cornerNum )
		{
			switch(cornerNum)
			{
			case 0:
				return _minVertex;
			case 1:
				return Vec3(_minVertex.x, _maxVertex.y, _minVertex.z);
			case 2:
				return Vec3(_maxVertex.x, _maxVertex.y, _minVertex.z);
			case 3:
				return Vec3(_maxVertex.x, _minVertex.y, _minVertex.z);
			case 7:
				return Vec3(_maxVertex.x, _minVertex.y, _maxVertex.z);
			case 6:
				return Vec3(_minVertex.x, _minVertex.y, _maxVertex.z);
			case 5:
				return Vec3(_minVertex.x, _maxVertex.y, _maxVertex.z);
			case 4:
				return _maxVertex;
			default:
				return Vec3();
			}
		}

		inline void matrixTranslation(const vgKernel::Mat4& mat)
		{
			float x, y, z;
			Vec3 pointBuffer[8];

			for (int i=0; i<8; i++)
			{
				pointBuffer[i] = getCorner(i);
			}

			for (int i=0; i<8; i++)
			{
				x = mat._m[0] * pointBuffer[i].x + mat._m[4] * pointBuffer[i].y + mat._m[8] * pointBuffer[i].z + mat._m[12];
				y = mat._m[1] * pointBuffer[i].x + mat._m[5] * pointBuffer[i].y + mat._m[9] * pointBuffer[i].z + mat._m[13];
				z = mat._m[2] * pointBuffer[i].x + mat._m[6] * pointBuffer[i].y + mat._m[10] * pointBuffer[i].z + mat._m[14];
				
				pointBuffer[i].x = x;
				pointBuffer[i].y = y;
				pointBuffer[i].z = z;
			}
						
			_minVertex = pointBuffer[0];
			_maxVertex = pointBuffer[0];
			_minVertex.z = z;

			for (int i=0; i<8; i++)
			{
				if (_minVertex.x > pointBuffer[i].x)
				{
					_minVertex.x = pointBuffer[i].x;
				}
				if (_minVertex.y > pointBuffer[i].y)
				{
					_minVertex.y = pointBuffer[i].y;
				}
				if (_minVertex.z > pointBuffer[i].z)
				{
					_minVertex.z = pointBuffer[i].z;
				}

				if (_maxVertex.x < pointBuffer[i].x)
				{
					_maxVertex.x = pointBuffer[i].x;
				}
				if (_maxVertex.y < pointBuffer[i].y)
				{
					_maxVertex.y = pointBuffer[i].y;
				}
				if (_maxVertex.z < pointBuffer[i].z)
				{
					_maxVertex.z = pointBuffer[i].z;
				}
			}
		}


#ifndef VGK_NO_OPENGL

		// only for test
		inline void render()
		{
			glPushAttrib(GL_CURRENT_BIT);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_1D);
			glPushMatrix();

			glColor3f(1,0,0);
			//glColor3f(_colorRed, _colorYel, _colorBlu);

			glLineWidth(1.0);

			Vec3& m_max = _maxVertex;
			Vec3& m_min = _minVertex;

			glBegin(GL_LINES);
			{

				glVertex3f( m_max.x , m_max.y , m_max.z );
				glVertex3f( m_min.x , m_max.y , m_max.z );

				glVertex3f( m_max.x , m_max.y , m_max.z );
				glVertex3f( m_max.x , m_min.y , m_max.z );

				glVertex3f( m_max.x , m_max.y , m_max.z );
				glVertex3f( m_max.x , m_max.y , m_min.z );

				glVertex3f( m_min.x , m_min.y , m_min.z );
				glVertex3f( m_max.x , m_min.y , m_min.z );

				glVertex3f( m_min.x , m_min.y , m_min.z );
				glVertex3f( m_min.x , m_max.y , m_min.z );

				glVertex3f( m_min.x , m_min.y , m_min.z );
				glVertex3f( m_min.x , m_min.y , m_max.z );

				glVertex3f( m_min.x , m_max.y , m_max.z );
				glVertex3f( m_min.x , m_max.y , m_min.z );

				glVertex3f( m_min.x , m_max.y , m_max.z );
				glVertex3f( m_min.x , m_min.y , m_max.z );


				glVertex3f( m_max.x , m_min.y , m_max.z );
				glVertex3f( m_max.x , m_min.y , m_min.z );

				glVertex3f( m_max.x , m_min.y , m_max.z );
				glVertex3f( m_min.x , m_min.y , m_max.z );

				glVertex3f( m_max.x , m_min.y , m_min.z );
				glVertex3f( m_max.x , m_max.y , m_min.z );

				glVertex3f( m_min.x , m_max.y , m_min.z );
				glVertex3f( m_max.x , m_max.y , m_min.z );
			}
			glEnd();

			glPopMatrix();

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_1D);
			glPopAttrib();

		}

#endif

		// add by lss when 2008-10-7 15:22:39
		inline void merge(const Box& rhs)
		{
			_minVertex.makeFloor(rhs._minVertex);
			_minVertex.makeFloor(rhs._maxVertex);
			_maxVertex.makeCeil(rhs._maxVertex);
			_maxVertex.makeCeil(rhs._minVertex);
		}
		inline void merge(const Vec3& rhs)
		{
			_minVertex.makeFloor(rhs);
			_maxVertex.makeCeil(rhs);
		}

		inline Vec3 getHalfSize(void) const
		{
			return (_maxVertex - _minVertex) * 0.5;
		}

		inline bool intersects(const Box& b2) const
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

		String getDetails();
	public:

		Vec3 _minVertex;
		Vec3 _maxVertex;


	public:

		static const Box NULL_BOX;
	};




}// end of namespace vgKernel



#endif // end of __VGKBOX_H__