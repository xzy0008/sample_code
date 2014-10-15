


#ifndef __VGTGDALDATASETGUIDE_H__
#define __VGTGDALDATASETGUIDE_H__

#include <vgKernel/vgkForward.h>
#include <gdal/gdal_priv.h>
#include <gdal/ogr_spatialref.h>
	
namespace vgTerritory {

	/**
		@date 	2008/10/07  21:29	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GdalDataSetGuide
	{
	public:
		GdalDataSetGuide( GDALDataset** ppdataset )
		{
			_ppGdalDataSet = ppdataset;
			assert( *ppdataset != NULL );
		}
		~GdalDataSetGuide()
		{
			if ( *_ppGdalDataSet != NULL )
			{
				delete *_ppGdalDataSet;
				*_ppGdalDataSet = NULL;
			}
		}

		void setNull()
		{
			if ( *_ppGdalDataSet != NULL )
			{
				delete *_ppGdalDataSet;
				*_ppGdalDataSet = NULL;
			}
		}

	private:

		GDALDataset** _ppGdalDataSet;

	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGDALDATASETGUIDE_H__