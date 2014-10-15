/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFVECTOR2_H__
#define __VGFVECTOR2_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfMath.h>


namespace vgMath {


	/**
		@date 	2007/02/19  23:16	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	/** Standard 2-dimensional vector.
	@remarks
	A direction in 2D space represented as distances along the 2
	orthoganal axes (x, y). Note that positions, directions and
	scaling factors can be represented by a vector, depending on how
	you interpret the values.
	*/
	class VgfExport Vector2
	{
	public:

		union
		{
			struct
			{  Real x , y ;  };
			Real v[2];
		};	

	public:
		inline Vector2()
			: x( 0.0 ), y( 0.0 )
		{
		}

		inline Vector2(const Real fX, const Real fY )
			: x( fX ), y( fY )
		{
		}

		inline explicit Vector2( const Real scaler )
			: x( scaler), y( scaler )
		{
		}

		inline explicit Vector2( const Real afCoordinate[2] )
			: x( afCoordinate[0] ),
			y( afCoordinate[1] )
		{
		}

		inline explicit Vector2( const int afCoordinate[2] )
		{
			x = (Real)afCoordinate[0];
			y = (Real)afCoordinate[1];
		}

		inline explicit Vector2( Real* const r )
			: x( r[0] ), y( r[1] )
		{
		}

		inline Vector2( const Vector2& rkVector )
			: x( rkVector.x ), y( rkVector.y )
		{
		}

		inline Real operator [] ( const size_t i ) const;
		inline Real& operator [] ( const size_t i );

		/// Pointer accessor for direct copying
		inline Real* ptr();
		/// Pointer accessor for direct copying
		inline const Real* ptr() const;

		/** Assigns the value of the other vector.
		@param
		rkVector The other vector
		*/
		inline Vector2& operator = ( const Vector2& rkVector );
		inline Vector2& operator = ( const Real fScalar);
		inline bool operator == ( const Vector2& rkVector ) const;
		inline bool operator != ( const Vector2& rkVector ) const;


		// arithmetic operations
		inline Vector2 operator + ( const Vector2& rkVector ) const;
		inline Vector2 operator - ( const Vector2& rkVector ) const;
		inline Vector2 operator * ( const Real fScalar ) const;
		inline Vector2 operator * ( const Vector2& rhs) const;
		inline Vector2 operator / ( const Real fScalar ) const;
		inline Vector2 operator / ( const Vector2& rhs) const;
		inline const Vector2& operator + () const;
		inline Vector2 operator - () const;

		// overloaded operators to help Vector2
		inline friend Vector2 operator * ( const Real fScalar, const Vector2& rkVector );
		inline friend Vector2 operator / ( const Real fScalar, const Vector2& rkVector );
		inline friend Vector2 operator + (const Vector2& lhs, const Real rhs);
		inline friend Vector2 operator + (const Real lhs, const Vector2& rhs);
		inline friend Vector2 operator - (const Vector2& lhs, const Real rhs);
		inline friend Vector2 operator - (const Real lhs, const Vector2& rhs);

		// arithmetic updates
		inline Vector2& operator += ( const Vector2& rkVector );
		inline Vector2& operator += ( const Real fScaler );
		inline Vector2& operator -= ( const Vector2& rkVector );
		inline Vector2& operator -= ( const Real fScaler );
		inline Vector2& operator *= ( const Real fScalar );
		inline Vector2& operator *= ( const Vector2& rkVector );
		inline Vector2& operator /= ( const Real fScalar );
		inline Vector2& operator /= ( const Vector2& rkVector );

		/** Returns the length (magnitude) of the vector.
		@warning
		This operation requires a square root and is expensive in
		terms of CPU operations. If you don't need to know the exact
		length (e.g. for just comparing lengths) use squaredLength()
		instead.
		*/
		inline Real length () const;

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
		inline Real dotProduct(const Vector2& vec) const;

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

		inline Vector2& normalisedRef();


		/** Returns a vector at a point half way between this and the passed
		in vector.
		*/
		inline Vector2 midPoint( const Vector2& vec ) const;

		/** Returns true if the vector's scalar components are all greater
		that the ones of the vector it is compared against.
		*/
		inline bool operator < ( const Vector2& rhs ) const;

		/** Returns true if the vector's scalar components are all smaller
		that the ones of the vector it is compared against.
		*/
		inline bool operator > ( const Vector2& rhs ) const;

		/** Sets this vector's components to the minimum of its own and the
		ones of the passed in vector.
		@remarks
		'Minimum' in this case means the combination of the lowest
		value of x, y and z from both vectors. Lowest is taken just
		numerically, not magnitude, so -1 < 0.
		*/
		inline void makeFloor( const Vector2& cmp );

		/** Sets this vector's components to the maximum of its own and the
		ones of the passed in vector.
		@remarks
		'Maximum' in this case means the combination of the highest
		value of x, y and z from both vectors. Highest is taken just
		numerically, not magnitude, so 1 > -3.
		*/
		inline void makeCeil( const Vector2& cmp );

		/** Generates a vector perpendicular to this vector (eg an 'up' vector).
		@remarks
		This method will return a vector which is perpendicular to this
		vector. There are an infinite number of possibilities but this
		method will guarantee to generate one of them. If you need more
		control you should use the Quaternion class.
		*/
		inline Vector2 perpendicular(void) const;

		///二维面上的叉乘,返回为一个数值.此值是2个向量所围的面积.
		/** Calculates the 2 dimensional cross-product of 2 vectors, which results
		in a single floating point value which is 2 times the area of the triangle.
		*/
		inline Real crossProduct( const Vector2& rkVector ) const;

		/** Generates a new random vector which deviates from this vector by a
		given angle in a random direction.
		@remarks
		This method assumes that the random number generator has already
		been seeded appropriately.
		@param
		angle The angle at which to deviate in radians
		@param
		up Any vector perpendicular to this one (which could generated
		by cross-product of this vector and any other non-colinear
		vector). If you choose not to provide this the function will
		derive one on it's own, however if you provide one yourself the
		function will be faster (this allows you to reuse up vectors if
		you call this method more than once)
		@returns
		A random vector which deviates from this vector by angle. This
		vector will not be normalised, normalise it if you wish
		afterwards.
		*/
		inline Vector2 randomDeviant( Real angle) const;

		/** Returns true if this vector is zero length. */
		inline bool isZeroLength(void) const;

		/** As normalise, except that this vector is unaffected and the
		normalised vector is returned as a copy. */
		inline Vector2 normalisedCopy(void) const;

		/** Calculates a reflection vector to the plane with the given normal .
		@remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
		*/
		inline Vector2 reflect(const Vector2& normal) const;

		// special points
		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;
		static const Vector2 NEGATIVE_UNIT_X;
		static const Vector2 NEGATIVE_UNIT_Y;
		static const Vector2 UNIT_SCALE;

		/** Function for writing to a stream.
		*/
		inline VgfExport friend StdOStream& operator <<
			( StdOStream& o, const Vector2& v );

		/// 输出测试函数.
		inline String getDetails() const
		{
			StdOStringStream o;
			//o << "Vector2( " << x << " , " << y <<  " )";
			o << (*this);
			return o.str();
		}

		inline Vector2 floorProduct( const Vector2& c ) const
		{
			Vector2 cmp = c;
			if( cmp.x > x ) cmp.x = x;
			if( cmp.y > y ) cmp.y = y;
			return cmp;
		}

		inline Vector2 ceilProduct( const Vector2& c ) const
		{
			Vector2 cmp = c;
			if( cmp.x < x ) cmp.x = x;
			if( cmp.y < y ) cmp.y = y;
			return cmp;
		}

	};

	#include <vgMath/vgfVector2Impl.inl>
	
}

#endif // end of __VGFVECTOR2_H__