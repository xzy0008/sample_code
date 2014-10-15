


#ifndef __VGTGEODEMOVERVIEW_H__
#define __VGTGEODEMOVERVIEW_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>
#include <ximage.h>
	
namespace vgTerritory {

	using namespace vgKernel;

	/**
		@date 	2008/09/22  8:52	
		@author  leven
	
		@brief 	默认传入的都是黑白的.byte数据结构.
	
		@see    
	*/
	class GeoDemOverview
	{
	public:
		GeoDemOverview( void* bytes , long width , 
			long height , ImageRect absolute_rect , double minelevation , 
			double maxelevation )
		{
			_cximage = NULL;

			_cximage = new CxImage;

			// 坐标轴在左上,upsidedown应为true
			bool createok = _cximage->CreateFromArray(
				(BYTE*)bytes , width , height , 8 , width * 1 , true );
			
			assert( createok == true );

			_absoluteRect = absolute_rect;

			_minElevation = minelevation;
			_maxElevation = maxelevation;
			
		}
		~GeoDemOverview()
		{
			
			if ( _cximage != NULL )
			{
				delete _cximage;
				_cximage = NULL;
			}
		}
	
	public:

		bool isEmpty()
		{
			return _absoluteRect.isEmpty();
		}

		bool saveToFile( const String save_file_path )
		{
			assert( _cximage != NULL );
			assert( _cximage->IsValid() == true );

			return _cximage->Save( save_file_path.c_str() , CXIMAGE_FORMAT_JPG );
		}

		void setRect( const ImageRect& rect )
		{
			_absoluteRect = rect;
		}

		void draw( HDC hdc );


	private:
	
		ImageRect _absoluteRect;

		double _minElevation;
		double _maxElevation;

		CxImage *_cximage;
	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEODEMOVERVIEW_H__