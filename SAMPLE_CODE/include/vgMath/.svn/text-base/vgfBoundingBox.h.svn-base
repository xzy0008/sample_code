


#ifndef __VGBOUNDRYBOX_H__
#define __VGBOUNDRYBOX_H__

#include <vgMath/vgfAxisAlignedBox.h>
#include <vgKernel/vgkForward.h> 

#include <vgKernel/vgkBox.h>

namespace vgMath{
	


	//typedef AxisAlignedBox BoundingBox;


	class BoundingBox
	{
	public:
		//BoundingBox();
		BoundingBox(Vector3 min, Vector3 max)
			:maxPoint(max), minPoint(min)		{	}		
		BoundingBox(const vgKernel::Box& rhs)
			:maxPoint(rhs._maxVertex), minPoint(rhs._minVertex)	{	}

		inline	BoundingBox(float	fltMax = INT_MAX):minPoint(fltMax), maxPoint(-fltMax) { }

		void merge(BoundingBox box);

		void merge(const vgKernel::Box& rhs);

		inline BoundingBox& operator=(const BoundingBox& rhs)
		{
			maxPoint = rhs.maxPoint;
			minPoint = rhs.minPoint;

			return *this;
		}

		inline BoundingBox& operator=(const vgKernel::Box& rhs)
		{
			maxPoint = rhs._maxVertex;
			minPoint = rhs._minVertex;

			return *this;
		}

		inline Vector3	getCenter(void)
		{
			return (minPoint + maxPoint)*0.5f;
		}

		inline Vector3	getSize(void) const
		{
			return maxPoint - minPoint;
		}

		inline	float	getArea()
		{
			Vector3	sizeVec(getSize());
			return	sizeVec.x * sizeVec.z ;
		}

		inline void		resetBox()
		{
			minPoint = INT_MAX;
			maxPoint = INT_MIN;
		}

		inline	bool	IsBoxInclude(const BoundingBox& rhs);
		inline	bool	IsBoxIntersect(  BoundingBox& rhs);
		inline	bool	IsPoint3Include(const Vector3& rhs );

		inline BoundingBox	operator + ( const Vector3& rhs );
		inline BoundingBox&	operator += ( const Vector3& rhs );
		inline BoundingBox	operator - ( const Vector3& rhs );
		inline BoundingBox&	operator -= ( const Vector3& rhs );
		inline BoundingBox	operator + ( const BoundingBox& rhs );

		inline void render()
		{
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_1D);
			glPushMatrix();

			glColor3f(1,0,0);
			//glColor3f(_colorRed, _colorYel, _colorBlu);

			glLineWidth(1.0);

			Vector3& m_max = maxPoint;
			Vector3& m_min = minPoint;

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

			//Vec3 center = getCenter();
			//glColor3f(0, 1, 0);
			//glTranslatef(center.x, center.y, center.z);
			//glutSolidSphere(5, 20, 20);

			glPopMatrix();

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_1D);

		}

	public:
		/*union
		{
			struct
			{  Vector3 minPoint , maxPoint;  };
			Vector3 Point[2];
		};*/
		Vector3 minPoint;
		Vector3 maxPoint;
	};
	inline	bool	BoundingBox::IsPoint3Include(const Vector3& rhs )
	{
		return	(this->maxPoint.x > rhs.x) 
			&&	(this->maxPoint.z > rhs.z) 
			&&	(this->minPoint.x < rhs.x)
			&&	(this->minPoint.z < rhs.z);
	}

	inline	bool	BoundingBox::IsBoxInclude(const BoundingBox& rhs)
	{
		return	(this->maxPoint > rhs.maxPoint) 
			&& (this->minPoint < rhs.minPoint);
	}

	inline	bool	BoundingBox::IsBoxIntersect( BoundingBox& rhs)
	{
		Vector3		distance1 = getCenter(), distance2;
		distance1	-= rhs.getCenter();
		distance2	= -distance1;
		distance1.makeCeil(distance2);

		return	distance1 <= this->getSize() + rhs.getSize();
	}

	inline BoundingBox BoundingBox::operator + ( const Vector3& rhs ) 
	{
		BoundingBox	tempBox(minPoint, maxPoint);
		tempBox	+= rhs;
		return  tempBox;
	}

	inline BoundingBox& BoundingBox::operator+=(const Vector3& rhs)
	{
		minPoint	= minPoint + rhs;
		maxPoint	= maxPoint + rhs;
		return  *this;
	}

	inline BoundingBox	BoundingBox::operator - ( const Vector3& rhs ) 
	{
		BoundingBox	tempBox(minPoint, maxPoint);
		tempBox	-= rhs;
		return  tempBox;
	}

	inline BoundingBox& BoundingBox::operator-=(const Vector3& rhs)
	{
		minPoint	= minPoint - rhs;
		maxPoint	= maxPoint - rhs;
		return  *this;
	}

	inline BoundingBox	BoundingBox::operator + ( const BoundingBox& rhs )
	{
		BoundingBox	tempBox(minPoint, maxPoint);
		tempBox.merge(rhs);
		return  tempBox;
	}
}

#endif // end of __VGBOUNDRYBOX_H__
