


#ifndef __VGSHAPELAYERENTRYEX_H__
#define __VGSHAPELAYERENTRYEX_H__

#include "vgShapeLayerEntry.h"


	/**
		@action		creation
		@date 		2009/03/30  15:39	
		@author  	lss
	
		@brief 	
	
		@see    
		*/
	class  VGSH_EXPORT ShapeLayerEntryEx :	public ShapeLayerEntry
	{
	public:

		ShapeLayerEntryEx( vgShape::Layer* layer_renderer )
			: ShapeLayerEntry( layer_renderer )
		{

		}

		virtual ~ShapeLayerEntryEx(void)
		{

		}

	protected:
		virtual void pushPropertiesEx(PropertiesParamVector& params );

		virtual void updateInternalEx( );
	protected:
		String	_keyFieldName;
	};



#endif // end of __VGSHAPELAYERENTRY_H__