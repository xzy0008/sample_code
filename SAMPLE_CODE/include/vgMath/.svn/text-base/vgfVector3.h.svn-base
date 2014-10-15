/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFVECTOR3_H__
#define __VGFVECTOR3_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfMath.h>

#include <vgKernel/vgkVec3.h>

namespace vgMath {

	/**
		@date 	2007/02/19  23:11	
		@author  leven
	
		@brief 	3元向量类.为提高效率,大部分使用inline实现,于是有了Vector3Impl.inl的
		由来.
	
		@see   Matrix3 Vector2
	*/
	class VgfExport Vector3
	{
	public:

		///成员变量,用此种方式声明可提高访问的方式.
		union
		{
			struct
			{  Real x , y , z;  };
			Real v[3];
		};

	public:

		///各种构造函数,满足应用,注意默认的Vector3产生的为0向量.
		inline Vector3()
			: x( 0.0 ), y( 0.0 ), z( 0.0 )
		{
		}

		inline Vector3( const Real fX, const Real fY, const Real fZ )
			: x( fX ), y( fY ), z( fZ )
		{
		}

		inline explicit Vector3( const Real vec[3] )
			: x( vec[0] ),
			y( vec[1] ),
			z( vec[2] )
		{
		}

		inline explicit Vector3( const int vec[3] )
		{
			x = (Real)vec[0];
			y = (Real)vec[1];
			z = (Real)vec[2];
		}

		inline explicit Vector3( Real* const r )
			: x( r[0] ), y( r[1] ), z( r[2] )
		{
		}

		inline explicit Vector3( const Real scaler )
			: x( scaler )
			, y( scaler )
			, z( scaler )
		{
		}

		inline Vector3( const Vector3& rkVector )
			: x( rkVector.x ), y( rkVector.y ), z( rkVector.z )
		{
		}

		inline Vector3( const vgKernel::Vec3& rkVector )
			: x( rkVector.x ), y( rkVector.y ), z( rkVector.z )
		{
		}

		inline Real operator [] ( const size_t i ) const;
		inline Real& operator [] ( const size_t i );

		///求地址操作
		inline Real* ptr();
		inline const Real* ptr() const;

		///operator操作函数重写
		inline Vector3& operator = ( const Vector3& rkVector );
		inline Vector3& operator = ( const vgKernel::Vec3& rkVector );

		inline Vector3& operator = ( const Real fScaler );
		inline bool operator == ( const Vector3& rkVector ) const;
		inline bool operator != ( const Vector3& rkVector ) const;
		inline Vector3 operator + ( const Vector3& rkVector ) const;
		inline Vector3 operator - ( const Vector3& rkVector ) const;
		inline Vector3 operator * ( const Real fScalar ) const;

		///一般用不到
		inline Vector3 operator * ( const Vector3& rhs) const;
		inline Vector3 operator / ( const Real fScalar ) const;
		inline Vector3 operator / ( const Vector3& rhs) const;

		///应当注意的情况:当操作数为空时.
		inline const Vector3& operator + () const;
		inline Vector3 operator - () const;

		///当操作数为左操作数时,注意为友元函数.
		inline friend Vector3 operator * ( const Real fScalar, const Vector3& rkVector );
		inline friend Vector3 operator / ( const Real fScalar, const Vector3& rkVector );
		inline friend Vector3 operator + (const Vector3& lhs, const Real rhs);
		inline friend Vector3 operator + (const Real lhs, const Vector3& rhs);
		inline friend Vector3 operator - (const Vector3& lhs, const Real rhs);
		inline friend Vector3 operator - (const Real lhs, const Vector3& rhs);

		///另外高级的应用
		// arithmetic updates
		inline Vector3& operator += ( const Vector3& rkVector );
		inline Vector3& operator += ( const Real fScalar );
		inline Vector3& operator -= ( const Vector3& rkVector );
		inline Vector3& operator -= ( const Real fScalar );
		inline Vector3& operator *= ( const Real fScalar );
		inline Vector3& operator *= ( const Vector3& rkVector );
		inline Vector3& operator /= ( const Real fScalar );
		inline Vector3& operator /= ( const Vector3& rkVector );

		///长度函数
		/** Returns the length (magnitude) of the vector.
		@warning
		This operation requires a square root and is expensive in
		terms of CPU operations. If you don't need to know the exact
		length (e.g. for just comparing lengths) use squaredLength()
		instead.
		*/
		inline Real length () const;

		///时常用到长度的平方,比如比较的时候
		/** Returns the square of the length(magnitude) of the vector.
		@remarks
		This  method is for efficiency - calculating the actual
		length of a vector requires a square root, which is expensive
		in terms of the operations required. This method returns the
		square of the length of the vector, i.e. the same as the
		length but before the square root is taken. Use this if you
		want to find the longest / shortest vector without incurring
		the square root.
		*/
		inline Real squaredLength () const;


		///距离函数,计算2个向量间的距离
		///注意此时消耗cpu资源很大,如果仅仅为了比较2点间的距离,用squaredDistance()
		/** Returns the distance to another vector.
		@warning
		This operation requires a square root and is expensive in
		terms of CPU operations. If you don't need to know the exact
		distance (e.g. for just comparing distances) use squaredDistance()
		instead.
		*/
		inline Real distance(const Vector3& rhs) const;

		/** Returns the square of the distance to another vector.
		@remarks
		This method is for efficiency - calculating the actual
		distance to another vector requires a square root, which is
		expensive in terms of the operations required. This method
		returns the square of the distance to another vector, i.e.
		the same as the distance but before the square root is taken.
		Use this if you want to find the longest / shortest distance
		without incurring the square root.
		*/
		inline Real squaredDistance(const Vector3& rhs) const;


		///计算2点间的点乘.
		/** Calculates the dot (scalar) product of this vector with another.
		@remarks
		The dot product can be used to calculate the angle between 2
		vectors. If both are unit vectors, the dot product is the
		cosine of the angle; otherwise the dot product must be
		divided by the product of the lengths of both vectors to get
		the cosine of the angle. This result can further be used to
		calculate the distance of a point from a plane.
		@param
		vec Vector with which to calculate the dot product (together
		with this one).
		@returns
		A float representing the dot product value.
		*/
		inline Real dotProduct(const Vector3& vec) const;


		///用于"vgPlane.cpp  85行"
		/** Calculates the absolute dot (scalar) product of this vector with another.
		@remarks
		This function work similar dotProduct, except it use absolute value
		of each component of the vector to computing.
		@param
		vec Vector with which to calculate the absolute dot product (together
		with this one).
		@returns
		A Real representing the absolute dot product value.
		*/
		inline Real absDotProduct(const Vector3& vec) const;

		///标准化向量,注意:			
		///1. 此时可以杜绝0向量的情况.
		///2. 含有返回值,返回值为先前向量的长度,注意不是vector3,若要返回vector3 ,请使用normalisedRef().
		/** Normalises the vector.
		@remarks
		This method normalises the vector such that it's
		length / magnitude is 1. The result is called a unit vector.
		@note
		This function will not crash for zero-sized vectors, but there
		will be no changes made to their components.
		@returns The previous length of the vector.
		*/
		inline Real normalise();

		///返回经过单位化的向量引用.
		inline Vector3& normalisedRef();

		///计算叉乘
		inline Vector3 crossProduct( const Vector3& rkVector ) const;

		///返回相加向量和的一半.
		/** Returns a vector at a point half way between this and the passed
		in vector.
		*/
		inline Vector3 midPoint( const Vector3& vec = ZERO ) const;

		///比较函数
		/** Returns true if the vector's scalar components are all greater
		that the ones of the vector it is compared against.
		*/
		inline bool operator < ( const Vector3& rhs ) const;

		/** Returns true if the vector's scalar components are all smaller
		that the ones of the vector it is compared against.
		*/
		inline bool operator > ( const Vector3& rhs ) const;

		///取与操作数相比较而得到的最小值,并且赋予本身
		/** Sets this vector's components to the minimum of its own and the
		ones of the passed in vector.
		@remarks
		'Minimum' in this case means the combination of the lowest
		value of x, y and z from both vectors. Lowest is taken just
		numerically, not magnitude, so -1 < 0.
		*/
		inline Vector3 makeFloor( const Vector3& cmp );

		///取与操作数相比较而得到的最大值,赋予本身,返回自身值.
		/** Sets this vector's components to the maximum of its own and the
		ones of the passed in vector.
		@remarks
		'Maximum' in this case means the combination of the highest
		value of x, y and z from both vectors. Highest is taken just
		numerically, not magnitude, so 1 > -3.
		*/
		inline Vector3 makeCeil( const Vector3& cmp );
		inline Vector3 ceilProduct( const Vector3& c ) const;
		inline Vector3 floorProduct( const Vector3& c ) const;

		///得到一个正交向量.注意,此时的正交向量并不确定,欲得到准确的正交向量,请使用4元数.
		/** Generates a vector perpendicular to this vector (eg an 'up' vector).
		@remarks
		This method will return a vector which is perpendicular to this
		vector. There are an infinite number of possibilities but this
		method will guarantee to generate one of them. If you need more
		control you should use the Quaternion class.
		*/
		inline Vector3 perpendicular(void) const;


		/** Returns true if this vector is zero length. */
		inline bool isZeroLength(void) const;

		/** As normalise, except that this vector is unaffected and the
		normalised vector is returned as a copy. */
		inline Vector3 normalisedCopy(void) const;

		///计算反射向量
		///注意:
		///1.此时normal要为单位向量
		///2.通常情况下容易和入射向量弄混,请注意各自的方向.
		/** Calculates a reflection vector to the plane with the given normal .
		@remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
		*/
		inline Vector3 reflect(const Vector3& normal) const;

		/** Returns whether this vector is within a positional tolerance
		of another vector.
		@param rhs The vector to compare with
		@param tolerance The amount that each element of the vector may vary by
		and still be considered equal
		*/
		inline bool positionEquals(const Vector3& rhs, Real tolerance = 1e-03) const;
		inline bool operator <= ( const Vector3& rhs ) const;

		/** Returns true if the vector's scalar components are all smaller
		that the ones of the vector it is compared against.
		*/
		inline bool operator >= ( const Vector3& rhs ) const;


		///计算叉乘的符号重载
		inline Vector3 operator ^ ( const Vector3 &rhs ) const;



		inline  void  reset( const Real& X ,
			const Real& Y ,const Real& Z )
		{
			this->x = X;
			this->y = Y;
			this->z = Z;
		}

		inline String getDetails() const
		{
			StdStringStream o;
			//o << "Vector3( " <<  x << " , " << y << " , " << z << " )";
			o << (*this);
			return o.str();
		}

		///输出函数,方便测试
		inline /*VgfExport*/ friend StdOStream& operator <<
			( StdOStream& o, const Vector3& v );
		inline friend StdIStream& operator >> ( StdIStream& in , Vector3& v );

#ifdef UNICODE
		inline /*VgfExport*/ friend std::ostream& operator <<
			( std::ostream& o, const Vector3& v );
		inline friend std::istream& operator >> ( std::istream& in , Vector3& v );
#endif

	public:			

		///特别的单位向量,做为储存常量.
		// special points
		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 UNIT_SCALE;

	};

	///inline 函数实现.
	#include <vgMath/vgfVector3Impl.inl>

	typedef	std::vector<Vector3>	Vector3Vec;
}

#endif // end of __VGFVECTOR3_H__