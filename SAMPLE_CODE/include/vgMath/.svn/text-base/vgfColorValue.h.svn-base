/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFCOLORVALUE_H__
#define __VGFCOLORVALUE_H__

#include <vgMath/vgfPrerequisites.h>


namespace vgMath {

	/**
		@date 	2007/02/28  22:28	
		@author  leven
	
		@brief 	
		
		表征颜色值的量.由四个量r,g,b,a.

		这个量可以在OpenGL程序中重定义,但因为此类大部分为数值计算,故放入数学库.

		Color is represented as 4 components, each of which is a
		Realing-point value from 0.0 to 1.0.

		The 3 'normal' colour components are red, green and blue, a higher
		number indicating greater amounts of that component in the colour.
		The forth component is the 'alpha' value, which represents
		transparency. In this case, 0.0 is completely transparent and 1.0 is
		fully opaque.
	
		@see    
	*/
    class VgfExport ColorValue
    {
    public:

		///成员变量.
        Real r,g,b,a;


        static const ColorValue ZERO;
        static const ColorValue Black;
        static const ColorValue White;
        static const ColorValue Red;
        static const ColorValue Green;
        static const ColorValue Blue;
		static const ColorValue Yellow;

		///默认为白色.
	    explicit ColorValue( Real red = 1.0f,
				    Real green = 1.0f,
				    Real blue = 1.0f,
				    Real alpha = 1.0f ) : r(red), g(green), b(blue), a(alpha)
        { }

		virtual ~ColorValue()
		{
		}

	    bool operator==(const ColorValue& rhs) const;
	    bool operator!=(const ColorValue& rhs) const;



	    /** Retrieves colour as RGBA.
	    */
	    RGBA getAsRGBA(void) const;

	    /** Retrieves colour as ARGB.
	    */
	    ARGB getAsARGB(void) const;

		/** Retrieves colour as BGRA.
		*/
		BGRA getAsBGRA(void) const;

		/** Retrieves colours as ABGR */
	    ABGR getAsABGR(void) const;

	    /** Sets colour as RGBA.
	    */
        void setAsRGBA(const RGBA val);

	    /** Sets colour as ARGB.
	    */
        void setAsARGB(const ARGB val);

		/** Sets colour as BGRA.
		*/
		void setAsBGRA(const BGRA val);

	    /** Sets colour as ABGR.
	    */
        void setAsABGR(const ABGR val);

		/// leven add
		/// 得到RGBQUAD数据类型.此函数可用于和SDK程序的交互.
		inline RGBQUAD getAsRGBQUAD(void) const
		{
			RGBQUAD result;
			uint8 val8;

			// Convert to 32bit pattern
			// (ARGB = 8888)

			// Alpha
			val8 = static_cast<uint8>(a * 255);
			result.rgbReserved = val8;
			// Red
			val8 = static_cast<uint8>(r * 255);
			result.rgbRed = val8;

			// Green
			val8 = static_cast<uint8>(g * 255);
			result.rgbGreen = val8;

			// Blue
			val8 = static_cast<uint8>(b * 255);
			result.rgbBlue = val8;

			return result;
		}



		///格式化,将RGBA的值限制在[0,1]内.
        /** Clamps colour value to the range [0, 1].
        */
        void saturate(void)
        {
            if (r < 0)
                r = 0;
            else if (r > 1)
                r = 1;

            if (g < 0)
                g = 0;
            else if (g > 1)
                g = 1;

            if (b < 0)
                b = 0;
            else if (b > 1)
                b = 1;

            if (a < 0)
                a = 0;
            else if (a > 1)
                a = 1;
        }

        /** As saturate, except that this colour value is unaffected and
            the saturated colour value is returned as a copy. */
        ColorValue saturateCopy(void) const
        {
            ColorValue ret = *this;
            ret.saturate();
            return ret;
        }

		/// Array accessor operator
		inline Real operator [] ( const size_t i ) const
		{
			assert( i < 4 );

			return *(&r+i);
		}

		/// Array accessor operator
		inline Real& operator [] ( const size_t i )
		{
			assert( i < 4 );

			return *(&r+i);
		}

		/// Pointer accessor for direct copying
		inline Real* ptr()
		{
			return &r;
		}
		/// Pointer accessor for direct copying
		inline const Real* ptr() const
		{
			return &r;
		}

		
		// arithmetic operations
        inline ColorValue operator + ( const ColorValue& rkVector ) const
        {
            ColorValue kSum;

            kSum.r = r + rkVector.r;
            kSum.g = g + rkVector.g;
            kSum.b = b + rkVector.b;
            kSum.a = a + rkVector.a;

            return kSum;
        }

        inline ColorValue operator - ( const ColorValue& rkVector ) const
        {
            ColorValue kDiff;

            kDiff.r = r - rkVector.r;
            kDiff.g = g - rkVector.g;
            kDiff.b = b - rkVector.b;
            kDiff.a = a - rkVector.a;

            return kDiff;
        }

        inline ColorValue operator * (const Real fScalar ) const
        {
            ColorValue kProd;

            kProd.r = fScalar*r;
            kProd.g = fScalar*g;
            kProd.b = fScalar*b;
            kProd.a = fScalar*a;

            return kProd;
        }

        inline ColorValue operator * ( const ColorValue& rhs) const
        {
            ColorValue kProd;

            kProd.r = rhs.r * r;
            kProd.g = rhs.g * g;
            kProd.b = rhs.b * b;
            kProd.a = rhs.a * a;

            return kProd;
        }

        inline ColorValue operator / ( const ColorValue& rhs) const
        {
            ColorValue kProd;

            kProd.r = rhs.r / r;
            kProd.g = rhs.g / g;
            kProd.b = rhs.b / b;
            kProd.a = rhs.a / a;

            return kProd;
        }

        inline ColorValue operator / (const Real fScalar ) const
        {
            assert( fScalar != 0.0 );

            ColorValue kDiv;

            Real fInv = 1.0 / fScalar;
            kDiv.r = r * fInv;
            kDiv.g = g * fInv;
            kDiv.b = b * fInv;
            kDiv.a = a * fInv;

            return kDiv;
        }

        inline friend ColorValue operator * (const Real fScalar, const ColorValue& rkVector )
        {
            ColorValue kProd;

            kProd.r = fScalar * rkVector.r;
            kProd.g = fScalar * rkVector.g;
            kProd.b = fScalar * rkVector.b;
            kProd.a = fScalar * rkVector.a;

            return kProd;
        }

        // arithmetic updates
        inline ColorValue& operator += ( const ColorValue& rkVector )
        {
            r += rkVector.r;
            g += rkVector.g;
            b += rkVector.b;
            a += rkVector.a;

            return *this;
        }

        inline ColorValue& operator -= ( const ColorValue& rkVector )
        {
            r -= rkVector.r;
            g -= rkVector.g;
            b -= rkVector.b;
            a -= rkVector.a;

            return *this;
        }

        inline ColorValue& operator *= (const Real fScalar )
        {
            r *= fScalar;
            g *= fScalar;
            b *= fScalar;
            a *= fScalar;
            return *this;
        }

        inline ColorValue& operator /= (const Real fScalar )
        {
            assert( fScalar != 0.0 );

            Real fInv = 1.0 / fScalar;

            r *= fInv;
            g *= fInv;
            b *= fInv;
            a *= fInv;

            return *this;
        }

		///依照HSB设置value,只改变RGB,并不改变alpha值.(计算过程暂时不明)
		/** Set a colour value from Hue, Saturation and Brightness.
		@param hue Hue value, scaled to the [0,1] range as opposed to the 0-360
		@param saturation Saturation level, [0,1]
		@param brightness Brightness level, [0,1]
		*/
		void setHSB(Real hue, Real saturation, Real brightness);


		/** Function for writing to a stream.
		*/
		inline VgfExport friend StdOStream& operator <<
			( StdOStream& o, const ColorValue& c )
		{
			o << _T( "ColorValue(" ) << c.r << _T( ", " ) << c.g 
				<< _T( ", " ) << c.b << _T( ", " ) << c.a << _T( ")" );
			return o;
		}


		//inline void useBind() const
		//{
		//	glColor4f( r , g , b , a);
		//}

		inline String getDetails() const
		{
			StdOStringStream o;
			//o << "ColorValue(" << r << ", " << g << ", " << b << ", " << a << ")";
			o << (*this);
			return o.str();
		}
    };

	
	
	
}

#endif // end of __VGFCOLORVALUE_H__