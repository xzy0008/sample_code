#pragma once 

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

	
namespace vgGIS3D {

 
	class OgrUtility
	{
	private:
		OgrUtility()
		{
			
		}
	public:
		~OgrUtility()
		{
			
		}
	

	public:


		static bool copyDataSource( OGRDataSource *poSrcDS,
			OGRDataSource *poDstDS );

		static int TranslateLayer( OGRDataSource *poSrcDS, 
			OGRLayer * poSrcLayer,
			OGRDataSource *poDstDS,
			char **papszLCO,
			const char *pszNewLayerName,
			int bTransform, 
			OGRSpatialReference *poOutputSRS,
			OGRSpatialReference *poSourceSRS,
			char **papszSelFields,
			int bAppend, int eGType, int bOverwrite ,
			bool append_vrgis_field = true ,
			bool force_to_3d = true );


		// ´úÌæprintfµÄº¯Êý
		static void printMsg(const char *format, ...);

	private:

		static int nGroupTransactions;

		static int bPreserveFID;
		static int nFIDToFetch;

		static int bSkipFailures;
	};
	
	
}// end of namespace  
	

 