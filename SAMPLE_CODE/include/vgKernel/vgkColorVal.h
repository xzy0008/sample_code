


#ifndef __VGKCOLORVAL_H__
#define __VGKCOLORVAL_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2007/02/28  22:28	
		@author  xy

		@brief 	

		表征颜色值的量.由四个量r,g,b,a.

		@see    
	*/
	class  VGK_EXPORT ColorVal
	{
	public:

		///成员变量.
		float r,g,b,a;


		static const ColorVal ZERO;
		static const ColorVal Black;
		static const ColorVal White;
		static const ColorVal Red;
		static const ColorVal Green;
		static const ColorVal Blue;
		static const ColorVal Yellow;

		static const ColorVal DEFAULT;

		///默认为白色.
		explicit ColorVal() : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
		{ }

		explicit ColorVal( float red,
			float green ,
			float blue,
			float alpha) : r(red), g(green), b(blue), a(alpha)
		{ }

		virtual ~ColorVal()
		{
		}

		bool operator==(const ColorVal& rhs) const;
		bool operator!=(const ColorVal& rhs) const;

		RGBQUAD getAsRGBQUAD(void) const;
		void setAsRGBQUAD( const RGBQUAD& new_color );

		/**
		由于COLORREF是没有alpha属性的.这里做折中操作.
		*/
		COLORREF getAsColorRef( const bool& getalpha = false ) const;
		void setAsColorRef( const COLORREF& new_color , const bool& setalpha = false );

		///格式化,将RGBA的值限制在[0,1]内.
		void saturate(void);

		ColorVal saturateCopy(void) const
		{
			ColorVal ret = *this;
			ret.saturate();
			return ret;
		}

		/// Array accessor operator
		inline float operator [] ( const size_t i ) const
		{
			assert( i < 4 );

			return *(&r+i);
		}

		/// Array accessor operator
		inline float& operator [] ( const size_t i )
		{
			assert( i < 4 );

			return *(&r+i);
		}

		/// Pointer accessor for direct copying
		inline float* ptr()
		{
			return &r;
		}
		/// Pointer accessor for direct copying
		inline const float* ptr() const
		{
			return &r;
		}

		// arithmetic operations
		inline ColorVal operator + ( const ColorVal& rkVector ) const
		{
			ColorVal kSum;

			kSum.r = r + rkVector.r;
			kSum.g = g + rkVector.g;
			kSum.b = b + rkVector.b;
			kSum.a = a + rkVector.a;

			return kSum;
		}

		inline ColorVal operator - ( const ColorVal& rkVector ) const
		{
			ColorVal kDiff;

			kDiff.r = r - rkVector.r;
			kDiff.g = g - rkVector.g;
			kDiff.b = b - rkVector.b;
			kDiff.a = a - rkVector.a;

			return kDiff;
		}

		inline ColorVal operator * (const float fScalar ) const
		{
			ColorVal kProd;

			kProd.r = fScalar*r;
			kProd.g = fScalar*g;
			kProd.b = fScalar*b;
			kProd.a = fScalar*a;

			return kProd;
		}

		inline ColorVal operator * ( const ColorVal& rhs) const
		{
			ColorVal kProd;

			kProd.r = rhs.r * r;
			kProd.g = rhs.g * g;
			kProd.b = rhs.b * b;
			kProd.a = rhs.a * a;

			return kProd;
		}

		inline ColorVal operator / ( const ColorVal& rhs) const
		{
			ColorVal kProd;

			kProd.r = rhs.r / r;
			kProd.g = rhs.g / g;
			kProd.b = rhs.b / b;
			kProd.a = rhs.a / a;

			return kProd;
		}

		inline ColorVal operator / (const float fScalar ) const
		{
			assert( fScalar != 0.0 );

			ColorVal kDiv;

			float fInv = 1.0f / fScalar;
			kDiv.r = r * fInv;
			kDiv.g = g * fInv;
			kDiv.b = b * fInv;
			kDiv.a = a * fInv;

			return kDiv;
		}

		inline friend ColorVal operator * (const float fScalar, const ColorVal& rkVector )
		{
			ColorVal kProd;

			kProd.r = fScalar * rkVector.r;
			kProd.g = fScalar * rkVector.g;
			kProd.b = fScalar * rkVector.b;
			kProd.a = fScalar * rkVector.a;

			return kProd;
		}

		// arithmetic updates
		inline ColorVal& operator += ( const ColorVal& rkVector )
		{
			r += rkVector.r;
			g += rkVector.g;
			b += rkVector.b;
			a += rkVector.a;

			return *this;
		}

		inline ColorVal& operator -= ( const ColorVal& rkVector )
		{
			r -= rkVector.r;
			g -= rkVector.g;
			b -= rkVector.b;
			a -= rkVector.a;

			return *this;
		}

		inline ColorVal& operator *= (const float fScalar )
		{
			r *= fScalar;
			g *= fScalar;
			b *= fScalar;
			a *= fScalar;
			return *this;
		}

		inline ColorVal& operator /= (const float fScalar )
		{
			assert( fScalar != 0.0 );

			float fInv = 1.0f / fScalar;

			r *= fInv;
			g *= fInv;
			b *= fInv;
			a *= fInv;

			return *this;
		}

		inline void useBind( bool useAlpha = false )
		{
			if ( useAlpha )
			{
				glColor4f( r, g , b , a );
			}
			else
			{
				glColor3f( r, g, b );
			}
		}

		inline String getDetails() const
		{
			std::ostringstream o;
			o << _T( "ColorVal(" ) << r << _T( ", " ) << g 
				<< _T( ", " ) << b << _T( ", " ) << a << _T( ")" );

			return o.str();
		}
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKCOLORVAL_H__