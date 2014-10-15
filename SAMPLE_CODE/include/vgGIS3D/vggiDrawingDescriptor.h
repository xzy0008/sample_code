#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkColorVal.h>


class OGRFeature;
class OGRStyleMgr;

namespace vgGIS3D {

	class Geometry;

	/**
		@date 	2009/03/02  20:11	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGG_EXPORT DrawingDescriptor
	{
	public:
		DrawingDescriptor( Geometry* father );
		~DrawingDescriptor();

	public:

		void setNewFatherGeometry(Geometry *father)
		{
			_father = father;
		}

		bool importFromOGRFeature( OGRFeature* feature );
		
		bool importFromString( const String& str );

		vgKernel::ColorVal getFillingColorVal();
		
		COLORREF getFillColorRef()
		{
			return _fillColor;
		}

		vgKernel::ColorVal getPenColorVal();
		COLORREF  getPenColorRef()
		{
			return _penColor;
		}
	
		double getPenWidth();
		bool isDrawFilling();


		void setPenWidth( const double& wid );
		void setPenColor( COLORREF col );
		void setDrawingFill( bool draw );
		void setFillColor( COLORREF col );

	private:

		void updateOGRStyleMgrFromParams();

		void dumpOGRStyleStringToOGRFeature();

		static String getStringFromColorRef( COLORREF col );

	private:
	
		double _penWidth;
		COLORREF _penColor; 

		// ÊÇ·ñäÖÈ¾ÄÚ²¿
		bool _drawFilling;

		COLORREF _fillColor;

		OGRStyleMgr   *_styleMgr;

		Geometry* _father;
	};
	
	
}// end of namespace   