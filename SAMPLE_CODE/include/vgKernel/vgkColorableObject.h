


#ifndef __VGKCOLORABLEOBJECT_H__
#define __VGKCOLORABLEOBJECT_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRgbaQuad.h>
#include <vgKernel/vgkColorVal.h>
	
namespace vgKernel {

	/**
		@date 	2009/05/05  9:57	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class ColorableObject
	{
	public:
		ColorableObject()
			: _color(0,0,0,0)
		{

		}
		virtual ~ColorableObject()
		{
			
		}
	
	public:
	
		bool isColorable() const
		{
			return _color.alpha != 0;
		}

		void setColorable( bool enable )
		{
			_color.alpha = ( enable ? 255 : 0 );
		}

		void setColorableValue( RgbaQuad color )
		{
			_color = color;
		}
	
		ColorVal getColorVal()
		{
			ColorVal ret;
			ret.setAsRGBQUAD( *_color.getRGBQUAD() );
			return ret;
		}

		RgbaQuad* getRgbaQuadRef()
		{
			return &_color;
		}

		RgbaQuad getRgbaQuad()
		{
			return _color;
		}

	private:
	
		RgbaQuad _color;
	
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKCOLORABLEOBJECT_H__