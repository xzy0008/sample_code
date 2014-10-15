#pragma once

#include <vgGIS3D/vggiDataSource.h>
#include <vgGIS3D/vggiLayer.h>

#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

namespace vgGIS3D
{

	class DxfReader
	{
	public:
		static bool ReaderFromFile(string filePath);

	private:

	private:

		static LayerPtrVector* readLayersFromDataSource( OGRDataSource* source , 
			const OGRGeometry* geo_filter = NULL,
			const bool& use_special_polygon = false );

		static LayerPtr readLayerFromOGRLayer( OGRLayer* ogr_layer , 
			const OGRGeometry* geo_filter = NULL ,
			const bool& use_special_polygon = false );
	};
}