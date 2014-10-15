


#ifndef __VGKVEC3_H__
#define __VGKVEC3_H__

#include <vgKernel/vgkForward.h>
#include <sstream>

namespace vgKernel {

	class  VGK_EXPORT Vec3
	{
	public:

		union
		{
			struct
			{  float x , y , z;  };
			float v[3];
		};

	public:

		inline Vec3()
			: x( 0.0 ), y( 0.0 ), z( 0.0 )
		{
		}

		inline Vec3( const float fX, const float fY, const float fZ )
			: x( fX ), y( fY ), z( fZ )
		{
		}

		inline explicit Vec3( const float vec[3] )
			: x( vec[0] ),
			y( vec[1] ),
			z( vec[2] )
		{
		}

		inline explicit Vec3( const int vec[3] )
		{
			x = (float)vec[0];
			y = (float)vec[1];
			z = (float)vec[2];
		}

		inline explicit Vec3( float* const r )
			: x( r[0] ), y( r[1] ), z( r[2] )
		{
		}

		inline explicit Vec3( const float scaler )
			: x( scaler )
			, y( scaler )
			, z( scaler )
		{
		}

		inline Vec3( const Vec3& rkVector )
			: x( rkVector.x ), y( rkVector.y ), z( rkVector.z )
		{
		}

		inline float operator [] ( const size_t i ) const;
		inline float& operator [] ( const size_t i );


		///operator操作函数重写
		inline Vec3& operator = ( const Vec3& rkVector );
		inline Vec3& operator = ( const float fScaler );
		inline bool operator == ( const Vec3& rkVector ) const;
		inline bool operator != ( const Vec3& rkVector ) const;
		inline Vec3 operator + ( const Vec3& rkVector ) const;
		inline Vec3 operator - ( const Vec3& rkVector ) const;
		inline Vec3 operator * ( const float fScalar ) const;
		inline Vec3 operator / ( const float fScalar ) const;
		inline Vec3 operator * ( const Vec3& rkVector) const;
		inline Vec3 operator / ( const Vec3& rkVector) const;

		///应当注意的情况:当操作数为空时.
		inline const Vec3& operator + () const;
		inline Vec3 operator - () const;

		///当操作数为左操作数时,注意为友元函数.
		inline friend Vec3 operator * ( const float fScalar, const Vec3& rkVector );
		inline friend Vec3 operator / ( const float fScalar, const Vec3& rkVector );
		inline friend Vec3 operator + (const Vec3& lhs, const float rhs);
		inline friend Vec3 operator + (const float lhs, const Vec3& rhs);
		inline friend Vec3 operator - (const Vec3& lhs, const float rhs);
		inline friend Vec3 operator - (const float lhs, const Vec3& rhs);

		///另外高级的应用
		// arithmetic updates
		inline Vec3& operator += ( const Vec3& rkVector );
		inline Vec3& operator += ( const float fScalar );
		inline Vec3& operator -= ( const Vec3& rkVector );
		inline Vec3& operator -= ( const float fScalar );
		inline Vec3& operator *= ( const float fScalar );
		inline Vec3& operator *= ( const Vec3& rkVector );
		inline Vec3& operator /= ( const float fScalar );
		inline Vec3& operator /= ( const Vec3& rkVector );

		///长度函数
		inline float length () const;

		///时常用到长度的平方,比如比较的时候
		inline float squaredLength () const;


		///距离函数,计算2个向量间的距离
		inline float distance(const Vec3& rhs) const;
		inline float squaredDistance(const Vec3& rhs) const;


		///计算2点间的点乘.
		inline float dotProduct(const Vec3& vec) const;
		inline float absDotProduct(const Vec3& vec) const;

		///标准化向量,注意:			
		///1. 此时可以杜绝0向量的情况.
		///2. 含有返回值,返回值为先前向量的长度,注意不是vector3,若要返回vector3 ,请使用normalisedRef().
		inline float normalise();

		///返回经过单位化的向量引用.
		inline Vec3& normalisedRef();

		///计算叉乘
		inline Vec3 crossProduct( const Vec3& rkVector ) const;

		///返回相加向量和的一半.
		inline Vec3 midPoint( const Vec3& vec = ZERO ) const;

		///比较函数
		inline bool operator < ( const Vec3& rhs ) const;
		inline bool operator > ( const Vec3& rhs ) const;

		///取与操作数相比较而得到的最小值,并且赋予本身
		inline Vec3 makeFloor( const Vec3& cmp );

		///取与操作数相比较而得到的最大值,赋予本身,返回自身值.
		inline Vec3 makeCeil( const Vec3& cmp );
		inline Vec3 ceilProduct( const Vec3& c ) const;
		inline Vec3 floorProduct( const Vec3& c ) const;

		///得到一个正交向量.注意,此时的正交向量并不确定,欲得到准确的正交向量,请使用4元数.
		inline Vec3 perpendicular(void) const;


		/** Returns true if this vector is zero length. */
		inline bool isZeroLength(void) const;

		/** As normalise, except that this vector is unaffected and the
		normalised vector is returned as a copy. */
		inline Vec3 normalisedCopy(void) const;

		///计算反射向量
		///注意:
		///1.此时normal要为单位向量
		///2.通常情况下容易和入射向量弄混,请注意各自的方向.
		inline Vec3 reflect(const Vec3& normal) const;


		inline bool operator <= ( const Vec3& rhs ) const;
		inline bool operator >= ( const Vec3& rhs ) const;

		inline  void  reset( const float& X ,
			const float& Y ,const float& Z )
		{
			this->x = X;
			this->y = Y;
			this->z = Z;
		}

		String getDetails() const
		{
			std::ostringstream o;
			o << /*"Vec3:(" <<*/ "  ( " << x << "  ,  " << y << "  ,  " << z << " )";
			return o.str();
		}

		void setLength(float len)
		{
			float scale = (len / length());

			this->x *= scale;
			this->y *= scale;
			this->z *= scale;

		}

	public:			

		static const Vec3 ZERO;
		static const Vec3 UNIT_X;
		static const Vec3 UNIT_Y;
		static const Vec3 UNIT_Z;
		static const Vec3 NEGATIVE_UNIT_X;
		static const Vec3 NEGATIVE_UNIT_Y;
		static const Vec3 NEGATIVE_UNIT_Z;
		static const Vec3 UNIT_SCALE;

	};

	//std::ostream& operator<< ( std::ostream& o, Vec3 vec3 )
	//{
	//	o << vec3.getDetails();
	//	return o;
	//}

	///inline 函数实现.
	#include "vgkVec3.inl"

	
}// end of namespace vgKernel
	


#endif // end of __VGKVEC3_H__