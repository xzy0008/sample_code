

#pragma once


#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiDataSource.h>


class OGRGeometry;

namespace vgGIS3D {

 
	class VGG_EXPORT ShapeReader
	{
	private:
		ShapeReader()
		{
			
		}
	public:
		~ShapeReader()
		{
			
		}
	
		static void addFloorProp(string prop)
		{
			m_floorProp.push_back(prop);
		}

		static vector<string> getFloorProp()
		{
			return m_floorProp;
		}

		static void addFloorHeightProp(string prop)
		{
			m_floorHeightProp.push_back(prop);
		}

		static void removeFloorProp(string prop)
		{}

		static void removeFloorHeightProp(string prop)
		{}

		static string s_3dSolidFloorFiledName;
		static string s_3dSolidHeightFiledName;
		static vector<string>	m_floorProp;
		static vector<string>	m_floorHeightProp;

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
	

	
	
	
}// end of namespace  
 