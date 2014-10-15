


#ifndef __VGSHAPELAYERENTRY_H__
#define __VGSHAPELAYERENTRY_H__

#include <vgKernel/vgkForward.h>
#include <vgShape/vgshLayer.h>
#include "vgRendererEntry.h"



#define VGSH_LAYER_ENTRY_PENWIDTH "Line Width"
#define VGSH_LAYER_ENTRY_PENCOL "Line Color"
#define VGSH_LAYER_ENTRY_DRAWFILL "Draw Fill"
#define VGSH_LAYER_ENTRY_FILLCOL "Fill Color"

	/**
		@date 	2008/09/11  20:49	
		@author  leven

		@brief 	

		@see    
	*/
	class ShapeLayerEntry :	public RendererEntry
	{
	public:

		ShapeLayerEntry( vgShape::Layer* layer_renderer )
			: RendererEntry( VG_ENTRY_SHAPE_LAYER , layer_renderer )
		{
			_layer = layer_renderer;
			assert( layer_renderer != NULL );
		}

		virtual ~ShapeLayerEntry(void)
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

		vgShape::Layer* getLayerPtr()
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

		vgShape::Layer* _layer;

		COLORREF _colorRef;


		int _geometriesNum;
		int _selectedGeoNum;

		double _penwidth;
		COLORREF _pencolor;
		bool _drawFill;
		COLORREF _fillcolor;
	};



#endif // end of __VGSHAPELAYERENTRY_H__