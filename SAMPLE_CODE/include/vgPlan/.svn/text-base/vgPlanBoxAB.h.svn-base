
#ifndef __VGPLANSTRUCT__
#define  __VGPLANSTRUCT__

#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkVec2.h>

#include <vgKernel/vgkColorVal.h>

namespace vgPlan{

	class PlanBoundboxAB
	{
	public:
		PlanBoundboxAB();
		~PlanBoundboxAB(){};
	public:
		float area(){ return ((maxvertex.y - minvertex.y) * ( maxvertex.x - minvertex.x));}

		vgKernel::Vec2& getvertex( int num );

		void merge( vgKernel::Vec2 _vertex );

		void setminvertex( vgKernel::Vec2 _vertex );
		void setmaxvertex( vgKernel::Vec2 _vertex );

		inline PlanBoundboxAB operator = ( PlanBoundboxAB &box )
		{
			minvertex = box.minvertex;

			maxvertex = box.maxvertex;

			return *this;
		}
	private:
		vgKernel::Vec2 minvertex, maxvertex;
	};

	struct planbuildparameter 
	{
		void operator = ( planbuildparameter &aa )
		{
			_layerheight = aa._layerheight;
			_length = aa._length;
			_width = aa._width;
			_angle = aa._angle;
			_color = aa._color;
		}

		float _layerheight;
		float _length;
		float _width;
		float _angle;
		vgKernel::ColorVal _color;
	};

	struct plansceneparameter 
	{
		void operator = ( plansceneparameter &aa )
		{
			_lengthdistance = aa._lengthdistance;
			_widthdistance = aa._widthdistance;
			_capacity = aa._capacity;
			_builddensity = aa._builddensity;
			_greenbeltdensity = aa._greenbeltdensity;
			_angle = aa._angle;
		}

		float _lengthdistance;
		float _widthdistance;
		float _capacity;
		float _builddensity;
		float _greenbeltdensity;
		float _angle;
	};

	struct buildinginfo
	{
		int num;
		int layernum;
		int buildingnum;
	};


	struct Planbuildinginfo 
	{
		vgKernel::Vec3 _pos;

		int _layernum;
	};


}

#endif