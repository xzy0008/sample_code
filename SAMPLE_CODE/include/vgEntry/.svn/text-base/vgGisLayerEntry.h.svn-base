#pragma once

#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiLayer.h>
#include "vgRendererEntry.h"



#define VGSH_LAYER_ENTRY_PENWIDTH "Line Width"
#define VGSH_LAYER_ENTRY_PENCOL "Line Color"
#define VGSH_LAYER_ENTRY_DRAWFILL "Draw Fill"
#define VGSH_LAYER_ENTRY_FILLCOL "Fill Color"


 
	class  VGG_EXPORT GisLayerEntry :	public RendererEntry
	{
	public:

		GisLayerEntry( vgGIS3D::Layer* layer_renderer )
			: RendererEntry( layer_renderer )
		{
			_layer = layer_renderer;
			assert( layer_renderer != NULL );
		}

		virtual ~GisLayerEntry(void)
		{

		}

		/**
			继承UpdateObserver的接口
		*/
		virtual void onUpdate()
		{
			updateUIFromInternal();
		}

		// 用于Object修改后更新Node
		virtual void onChanged(int eventId, void *param);

		vgGIS3D::Layer* getLayerPtr()
		{
			assert( _layer != NULL );
			return _layer;
		}
	protected:

		virtual PropertiesParamVector& pushPropertiesParam( 
			PropertiesParamVector& params );

		virtual void updateUIFromInternal();

		virtual void updateInternalFromUI( const String& changed_param_name );

		
		/**
			@author  	lss
			@brief		使支持扩展属性项
		*/
		virtual void pushPropertiesEx(PropertiesParamVector& params )	{}

		virtual void updateInternalEx( )	{}
	private:



	private:

		vgGIS3D::Layer* _layer;

		COLORREF _colorRef;

		bool _enableDepth;

		int _geometriesNum;
		int _selectedGeoNum;

		double _penwidth;
		COLORREF _pencolor;
		bool _drawFill;
		COLORREF _fillcolor;
	};
