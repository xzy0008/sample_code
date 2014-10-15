


#ifndef __VGTGEODOUBLERECT_H__
#define __VGTGEODOUBLERECT_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>


	
namespace vgTerritory {

	using namespace vgKernel;

	class GeoGlobalData;

	/**
		@date 	2008/09/28  9:07	
		@author  leven
	
		@brief 	注意!!!!!!!原点在左上角

		如果输入的是以左下角为坐标系的点,则
		double _topLeftX;
		double _topLeftY;
		double _lowRightX;
		double _lowRightY;
		会反转!!!!!!!!!!!!!!!!
	
		@see    
	*/
	class GeoDoubleRect
	{
	public:
		GeoDoubleRect(
			double topLeftX, double topLeftY, double lowRightX, double lowRightY , 
			GeoGlobalData* globaldata )
		{
			setDefault();

			_globalData = globaldata;
			getAxisFlag();

			
			setRectData( topLeftX , topLeftY , lowRightX , lowRightY );

			
		}

		GeoDoubleRect(
			double topLeftX, double topLeftY, double lowRightX, double lowRightY , 
			long pixelwidth , long pixelheight , 
			GeoGlobalData* globaldata )
		{
			setDefault();

			_globalData = globaldata;
			getAxisFlag();
			
			setRectData( topLeftX , topLeftY , lowRightX , lowRightY );
			setPixelData( pixelwidth , pixelheight );

			

		}

		GeoDoubleRect(  const GeoDoubleRect& rect )
		{
			*this = rect;

			//_globalData = rect._globalData;

			//setDefault();

			//setRectData( rect._topLeftX , rect._topLeftY , rect._lowRightX , rect._lowRightY );
			//setPixelData( rect._pixelWidth , rect._pixelHeight );

			//getAxisFlag();
		}

		GeoDoubleRect( GeoGlobalData* globaldata )
		{
			setDefault();

			_globalData = globaldata;
			getAxisFlag();
		}

	public:

		GeoDoubleRect& operator = ( const GeoDoubleRect& rect )
		{
			//assert( rect.isSafe() );

			_topLeftX = rect._topLeftX;
			_topLeftY = rect._topLeftY;
			_lowRightX = rect._lowRightX;
			_lowRightY = rect._lowRightY;

			_pixelWidth = rect._pixelWidth;
			_pixelHeight = rect._pixelHeight;

			_globalData = rect._globalData;
			getAxisFlag();

			makeSafe();

			assert( isSafe() );

			return *this;
		}

		GeoDoubleRect& translate( const double& transx , 
			const double& transy )
		{
			assert( isSafe() );
			 _topLeftX += transx;
			 _topLeftY += transy;
			 _lowRightX += transx;
			 _lowRightY += transy;

			return *this;
		}

		GeoDoubleRect translateCopy( const double& transx , 
			const double& transy ) const
		{
			assert( isSafe() );
			GeoDoubleRect copy( *this );
			copy.translate( transx , transy );
			return copy;
		}

		// 注意!!得到的是左上角为原点的ImageRect
		ImageRect getImageRect( const double& pixelsizeX , 
			const double& pixelsizeY );

		bool testInside(const GeoDoubleRect& testRect) const
		{
			assert( isSafe() && "The GeoDoubleRect is not safe.");

			if ( _topLeftX > testRect._topLeftX || 
				_topLeftY > testRect._topLeftY || 
				_lowRightX < testRect._lowRightX || 
				_lowRightY < testRect._lowRightY )
			{
				return false;
			}

			return true;
		}

		bool testIntersect( const GeoDoubleRect& testRect ) const
		{
			assert( isSafe() && "The GeoDoubleRect is not safe.");

			if ( _lowRightX <= testRect._topLeftX || 
				_lowRightY <= testRect._topLeftY || 
				_topLeftX >= testRect._lowRightX ||
				_topLeftY >= testRect._lowRightY )
			{
				return false;
			}

			return true;
		}


		bool findIntersection (const GeoDoubleRect& rkBox,
			GeoDoubleRect& rkIntr) const;

		bool isSafe() const;

		void setRectData( 	double topLeftX, double topLeftY, 
			double lowRightX, double lowRightY )
		{
			_topLeftX = topLeftX;
			_topLeftY = topLeftY;
			_lowRightX = lowRightX;
			_lowRightY = lowRightY;

			makeSafe();
		}

		void setPixelData( long pixelwidth , long pixelheight )
		{
			_pixelWidth = pixelwidth;
			_pixelHeight = pixelheight;
		}

		double getTopLeftX() const
		{ 
			assert( isSafe() );
			return _topLeftX;
		}
		double getTopLeftY() const
		{
			assert( isSafe() );
			return (*_axisLeftDown == true ) ? _lowRightY : _topLeftY;
		}

		double getLowRightX() const
		{
			assert( isSafe() );
			return _lowRightX;
		}

		double getLowRightY() const
		{
			assert( isSafe() );
			return (*_axisLeftDown == true ) ? _topLeftY : _lowRightY;
		}

		long getPixelWidth() const
		{
			return _pixelWidth;
		}
		long getPixelHeight() const
		{
			return _pixelHeight;
		}

		double getWidth() const 
		{
			assert( isSafe() );
			return _lowRightX - _topLeftX;
		}
		double getHeight() const
		{
			assert( isSafe() );
			return _lowRightY - _topLeftY;
		}

	private:

		void setDefault();

		void getAxisFlag();

		void makeSafe();

	private:

		double _topLeftX;
		double _topLeftY;
		double _lowRightX;
		double _lowRightY;

		long _pixelWidth;
		long _pixelHeight;

	private:

		GeoGlobalData* _globalData;

		bool* _axisLeftDown;
	};


	typedef std::vector<GeoDoubleRect> GeoDoubleRectVec;
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEODOUBLERECT_H__