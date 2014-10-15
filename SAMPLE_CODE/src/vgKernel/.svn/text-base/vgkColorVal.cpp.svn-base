



#include <vgStableHeaders.h>
#include <vgKernel/vgkColorVal.h>


#define VG_COLORREF_RGBA(r,g,b,a)    \
	((COLORREF)((((BYTE)(r)|((WORD)((BYTE)(g))<<8)) \
	|(((DWORD)(BYTE)(b))<<16)))\
	|(((DWORD)(BYTE)(a))<<24))


#define VG_COLORREF_GetRValue(rgba)      (LOBYTE(rgba))
#define VG_COLORREF_GetGValue(rgba)      (LOBYTE(((WORD)(rgba)) >> 8))
#define VG_COLORREF_GetBValue(rgba)      (LOBYTE((rgba)>>16))
#define VG_COLORREF_GetAValue(rgba)      (LOBYTE((rgba)>>24))


namespace vgKernel {
	


	const ColorVal ColorVal::ZERO = ColorVal( 0.0 ,0.0, 0.0 , 0.0 );
	const ColorVal ColorVal::DEFAULT = ColorVal( 0.5 ,0.6, 0.8 , 1.0 );
	const ColorVal ColorVal::Black = ColorVal(0.0,0.0,0.0 , 1.0 );
	const ColorVal ColorVal::White = ColorVal(1.0,1.0,1.0 , 1.0 );
	const ColorVal ColorVal::Red = ColorVal(1.0,0.0,0.0 , 1.0 );
	const ColorVal ColorVal::Green = ColorVal(0.0,1.0,0.0 , 1.0 );
	const ColorVal ColorVal::Blue = ColorVal(0.0,0.0,1.0 , 1.0 );
	const ColorVal ColorVal::Yellow = ColorVal(1.0,1.0,0.0 , 1.0 );

	//---------------------------------------------------------------------
	bool ColorVal::operator==(const ColorVal& rhs) const
	{
		return (r == rhs.r &&
			g == rhs.g &&
			b == rhs.b &&
			a == rhs.a);
	}
	//---------------------------------------------------------------------
	bool ColorVal::operator!=(const ColorVal& rhs) const
	{
		return !(*this == rhs);
	}
	//----------------------------------------------------------------
	void ColorVal::saturate( void )
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
	//----------------------------------------------------------------
	RGBQUAD ColorVal::getAsRGBQUAD( void ) const
	{
		RGBQUAD result;
		typedef unsigned char uint8;
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
	//----------------------------------------------------------------
	void ColorVal::setAsRGBQUAD( const RGBQUAD& new_color )
	{
		r = new_color.rgbRed / 255.0f;
		g = new_color.rgbGreen / 255.0f;
		b = new_color.rgbBlue / 255.0f;
		a = new_color.rgbReserved / 255.0f;
	}
	//----------------------------------------------------------------
	COLORREF ColorVal::getAsColorRef(  const bool& getalpha/* = false */) const
	{
		RGBQUAD quad = getAsRGBQUAD();

		if ( getalpha )
		{
			return  VG_COLORREF_RGBA( quad.rgbRed ,quad.rgbGreen ,quad.rgbBlue , 
				quad.rgbReserved);
		}
		else
		{
			return  VG_COLORREF_RGBA( quad.rgbRed ,quad.rgbGreen ,quad.rgbBlue , 
				/*quad.rgbReserved */0);
		}

	}
	//----------------------------------------------------------------
	void ColorVal::setAsColorRef( const COLORREF& new_color ,
		const bool& setalpha /*= false*/ )
	{
		r = VG_COLORREF_GetRValue( new_color ) / 255.0f;
		g = VG_COLORREF_GetGValue( new_color )/ 255.0f;
		b = VG_COLORREF_GetBValue( new_color )/ 255.0f;

		if ( setalpha )
		{
			a = VG_COLORREF_GetAValue( new_color )/ 255.0f;
		}

		return;
	}
	//----------------------------------------------------------------
	
	
}// end of namespace vgKernel
