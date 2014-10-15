/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFVECTOR4_H__
#define __VGFVECTOR4_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfVector3.h>

namespace vgMath {

	/**
	*	@date 	2007/02/19  22:45	
	*	@author leven
	*
	*	@brief 	4-dimensional homogenous vector.用到的不多,故实现的方法较少.
	*
	*	@see    
	*/


	class VgfExport Vector4
	{
	public:
		
		union
		{
			struct
			{  Real x, y, z, w; };
			Real v[4];
		};

	public:
		inline Vector4()
			: x( 0.0 ), y( 0.0 ), z( 0.0 ), w( 0.0 )
		{
		}

		inline Vector4( const Real fX, const Real fY, const Real fZ, const Real fW )
			: x( fX ), y( fY ), z( fZ ), w( fW)
		{
		}

		inline explicit Vector4( const Real afCoordinate[4] )
			: x( afCoordinate[0] ),
			y( afCoordinate[1] ),
			z( afCoordinate[2] ),
			w( afCoordinate[3] )
		{
		}

		inline explicit Vector4( const int afCoordinate[4] )
		{
			x = (Real)afCoordinate[0];
			y = (Real)afCoordinate[1];
			z = (Real)afCoordinate[2];
			w = (Real)afCoordinate[3];
		}

		inline explicit Vector4( Real* const r )
			: x( r[0] ), y( r[1] ), z( r[2] ), w( r[3] )
		{
		}

		inline explicit Vector4( const Real scaler )
			: x( scaler )
			, y( scaler )
			, z( scaler )
			, w( scaler )
		{
		}

		inline explicit Vector4(const Vector3& rhs)
			: x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
		{
		}

		inline Vector4( const Vector4& rkVector )
			: x( rkVector.x ), y( rkVector.y ), z( rkVector.z ), w (rkVector.w)
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
		inline Vector4& operator = ( const Vector4& rkVector );
		inline Vector4& operator = ( const Real fScalar);
		inline bool operator == ( const Vector4& rkVector ) const;
		inline bool operator != ( const Vector4& rkVector ) const;
		inline Vector4& operator = (const Vector3& rhs);

		// arithmetic operations
		inline Vector4 operator + ( const Vector4& rkVector ) const;
		inline Vector4 operator - ( const Vector4& rkVector ) const;
		inline Vector4 operator * ( const Real fScalar ) const;
		inline Vector4 operator * ( const Vector4& rhs) const;
		inline Vector4 operator / ( const Real fScalar ) const;
		inline Vector4 operator / ( const Vector4& rhs) const;

		inline const Vector4& operator + () const;
		inline Vector4 operator - () const;


		inline friend Vector4 operator * ( const Real fScalar, const Vector4& rkVector );
		inline friend Vector4 operator / ( const Real fScalar, const Vector4& rkVector );
		inline friend Vector4 operator + (const Vector4& lhs, const Real rhs);
		inline friend Vector4 operator + (const Real lhs, const Vector4& rhs);
		inline friend Vector4 operator - (const Vector4& lhs, Real rhs);
		inline friend Vector4 operator - (const Real lhs, const Vector4& rhs);


		// arithmetic updates
		inline Vector4& operator += ( const Vector4& rkVector );
		inline Vector4& operator -= ( const Vector4& rkVector );
		inline Vector4& operator *= ( const Real fScalar );
		inline Vector4& operator += ( const Real fScalar );
		inline Vector4& operator -= ( const Real fScalar );
		inline Vector4& operator *= ( const Vector4& rkVector );
		inline Vector4& operator /= ( const Real fScalar );
		inline Vector4& operator /= ( const Vector4& rkVector );

		/** Calculates the dot (scalar) product of this vector with another.
		@param
		vec Vector with which to calculate the dot product (together
		with this one).
		@returns
		A float representing the dot product value.
		*/
		inline Real dotProduct(const Vector4& vec) const;

		// vector operations
		Real length () const;
		Real squaredLength () const;
		Real normalize ();

		/** Function for writing to a stream.
		*/
		inline VgfExport friend StdOStream& operator <<
			( StdOStream& o, const Vector4& v );

		inline String getDetails() const
		{
			StdOStringStream o;
			//o << "Vector4( " << x << " , " << y << " , " << z << " , " << w << " )";
			o << (*this);
			return o.str();
		}

	public:
		// special
		static const Vector4 ZERO;
		static const Vector4 ONE;     // (1,1,1,1)
	};

	#include <vgMath/vgfVector4Impl.inl>
	
	
}

#endif // end of __VGFVECTOR4_H__