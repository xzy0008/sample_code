


#ifndef __VGSHSHAPEREADER_H__
#define __VGSHSHAPEREADER_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgShape/vgshDataSource.h>

	

class OGRGeometry;

namespace vgShape {

	/**
		@date 	2009/02/16  13:50	
		@author  leven
	
		@brief 	
	
		@see    
	*/

	class ShapeReader
	{
	private:
		ShapeReader()
		{
			
		}
	public:
		~ShapeReader()
		{
			
		}
	
	
	public:
	
		/**
			注意,read_only暂时没有用
		*/
		static DataSourcePtr readFromShpFile( const String& abs_shp_path ,
			const String& temp_path , const OGRGeometry* geo_filter = NULL , 
			const bool& use_special_polygon = false );


	private:


		static LayerPtrVector* readLayersFromDataSource( OGRDataSource* source , 
			const OGRGeometry* geo_filter = NULL,
			const bool& use_special_polygon = false );
	
		static LayerPtr readLayerFromOGRLayer( OGRLayer* ogr_layer , 
			const OGRGeometry* geo_filter = NULL ,
			const bool& use_special_polygon = false );

	};
	

	
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHSHAPEREADER_H__