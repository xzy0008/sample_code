
#ifndef   _VGVEC3_H_INCLUDED_
#define   _VGVEC3_H_INCLUDED_	
/**********************************************************************
*<
vgVec3.h:	三维点或向量的数据结构声明
主要内容是： 点结构体
*>	
**********************************************************************/

//////////////////////////////////////////////////////////////////////////
// 点结构
// class CVector2
// class CVector3

namespace vgMath {

	struct CVector2
	{
		float x,y;
	};

	struct	CVector3
	{
		union{
			struct{float x, y, z;};
			float vert[3];
		};

		CVector3(float xRef , float yRef, float zRef)
			:x(xRef), y(yRef), z(zRef)	{	}

		CVector3(float xRef = 0.0f)
			:x(xRef), y(xRef), z(xRef)	{	}

		CVector3(CVector3& pointRef)
		{	
			*this = pointRef;
		}

		CVector3& operator=(CVector3& pointRef)
		{
			x = pointRef.x;
			y = pointRef.y;
			z = pointRef.z;

			return *this;
		}


		void	narrow(CVector3& pointRef);

		void	enlarge(CVector3& pointRef);
		
		
		friend CVector3	operator + (CVector3& point1, CVector3& point2);

		friend CVector3	operator * (CVector3& point1, float scaleRef);
		
		float	length();

		friend CVector3 subVector(CVector3 vPoint1, CVector3 vPoint2);
		friend float	dotProduct(CVector3 vVector1, CVector3 vVector2);
		friend CVector3 crossProduct(CVector3 vVector1, CVector3 vVector2);

		CVector3 normalize();

		CVector3 formatAsVG();

	};// class CVector3

}// namespace vgMath

#endif	//_VGVEC3_H_INCLUDED_	