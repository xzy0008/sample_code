#ifndef __VGPLANBUILDINGLLLLL__
#define __VGPLANBUILDINGLLLLL__

#include <vgKernel/vgkColorVal.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

namespace vgPlan
{
	class vgPlanbuild
	{
	public:
//		virtual void render() = 0;

// 		virtual void drawshadow( ) = 0;
// 
// 		virtual void onsunlightanalysis() = 0;

//		virtual float getbuildarea() = 0;

	public:

		void setlayerheight( float &_height ){ _layerheight = _height; }
		void setlength( float &leng ){ _length = leng ;}
		void setwidth( float &wid ){ _width = wid ; }
		void setangle( float &ang ){ _angle = ang ;}
		void setcolor( vgKernel::ColorVal &color ){ _color = color; }

		float getlayerheight(){ return _layerheight; }
		float getlength(){ return _length; }
		float getwidth(){ return _width; }
		float getangle(){ return _angle; }
		vgKernel::ColorVal &getcolor(){ return _color; }
	

	public:

		virtual vgPlanbuild *clone() = 0;				

//		virtual void setuplayernum( int _num ) = 0;
	
		virtual void setupposition( vgKernel::Vec3 &pos, int laynum ) = 0;

		OGRGeometry *getgeometry(){ return geo; }

	protected:

		float _layerheight;
		float _length;
		float _width;
		float _angle;
		vgKernel::ColorVal _color;

		OGRGeometry* geo ;


	};



}

#endif