


#ifndef __VGKVEC2_H__
#define __VGKVEC2_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	class  VGK_EXPORT Vec2
	{
	public:

		union
		{
			struct
			{  float x , y ;  };
			float v[2];
		};	

	public:
		inline Vec2()
			: x( 0.0 ), y( 0.0 )
		{
		}

		inline Vec2(const float fX, const float fY )
			: x( fX ), y( fY )
		{
		}

		inline explicit Vec2( const float scaler )
			: x( scaler), y( scaler )
		{
		}

		inline explicit Vec2( const float afCoordinate[2] )
			: x( afCoordinate[0] ),
			y( afCoordinate[1] )
		{
		}

		inline explicit Vec2( const int afCoordinate[2] )
		{
			x = (float)afCoordinate[0];
			y = (float)afCoordinate[1];
		}

		inline explicit Vec2( float* const r )
			: x( r[0] ), y( r[1] )
		{
		}

		inline Vec2( const Vec2& rkVector )
			: x( rkVector.x ), y( rkVector.y )
		{
		}

		inline float operator [] ( const size_t i ) const;
		inline float& operator [] ( const size_t i );

		inline Vec2& operator = ( const Vec2& rkVector );
		inline Vec2& operator = ( const float fScalar);
		inline bool operator == ( const Vec2& rkVector ) const;
		inline bool operator != ( const Vec2& rkVector ) const;


		// arithmetic operations
		inline Vec2 operator + ( const Vec2& rkVector ) const;
		inline Vec2 operator - ( const Vec2& rkVector ) const;
		inline Vec2 operator * ( const float fScalar ) const;
		inline Vec2 operator * ( const Vec2& rhs) const;
		inline Vec2 operator / ( const float fScalar ) const;
		inline Vec2 operator / ( const Vec2& rhs) const;
		inline const Vec2& operator + () const;
		inline Vec2 operator - () const;

		// overloaded operators to help Vec2
		inline friend Vec2 operator * ( const float fScalar, const Vec2& rkVector );
		inline friend Vec2 operator / ( const float fScalar, const Vec2& rkVector );
		inline friend Vec2 operator + (const Vec2& lhs, const float rhs);
		inline friend Vec2 operator + (const float lhs, const Vec2& rhs);
		inline friend Vec2 operator - (const Vec2& lhs, const float rhs);
		inline friend Vec2 operator - (const float lhs, const Vec2& rhs);

		// arithmetic updates
		inline Vec2& operator += ( const Vec2& rkVector );
		inline Vec2& operator += ( const float fScaler );
		inline Vec2& operator -= ( const Vec2& rkVector );
		inline Vec2& operator -= ( const float fScaler );
		inline Vec2& operator *= ( const float fScalar );
		inline Vec2& operator *= ( const Vec2& rkVector );
		inline Vec2& operator /= ( const float fScalar );
		inline Vec2& operator /= ( const Vec2& rkVector );

		inline float length () const;
		inline float squaredLength () const;

		inline float dotProduct(const Vec2& vec) const;


		inline float normalise();
		inline Vec2& normalisedRef();


		inline Vec2 midPoint( const Vec2& vec ) const;

		inline bool operator < ( const Vec2& rhs ) const;
		inline bool operator > ( const Vec2& rhs ) const;

		inline void makeFloor( const Vec2& cmp );
		inline void makeCeil( const Vec2& cmp );

		inline Vec2 perpendicular(void) const;

		///二维面上的叉乘,返回为一个数值.此值是2个向量所围的面积.
		inline float crossProduct( const Vec2& rkVector ) const;

		inline bool isZeroLength(void) const;

		inline Vec2 normalisedCopy(void) const;

		inline Vec2 reflect(const Vec2& normal) const;

		/// 输出测试函数.
		inline String getDetails() const
		{
			std::ostringstream o;
			o << "Vec2( " << x << " , " << y <<  " )";
			return o.str();
		}

		inline Vec2 floorProduct( const Vec2& c ) const
		{
			Vec2 cmp = c;
			if( cmp.x > x ) cmp.x = x;
			if( cmp.y > y ) cmp.y = y;
			return cmp;
		}

		inline Vec2 ceilProduct( const Vec2& c ) const
		{
			Vec2 cmp = c;
			if( cmp.x < x ) cmp.x = x;
			if( cmp.y < y ) cmp.y = y;
			return cmp;
		}

		// special points
		static const Vec2 ZERO;
		static const Vec2 UNIT_X;
		static const Vec2 UNIT_Y;
		static const Vec2 NEGATIVE_UNIT_X;
		static const Vec2 NEGATIVE_UNIT_Y;
		static const Vec2 UNIT_SCALE;

	};

	#include "vgkVec2.inl"
	
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKVEC2_H__