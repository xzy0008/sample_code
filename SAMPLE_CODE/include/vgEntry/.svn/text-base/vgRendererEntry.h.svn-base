


#ifndef __VGRENDERERENTRY_H__
#define __VGRENDERERENTRY_H__

#include <vgKernel/vgkForward.h>
#include <vgEntry/vgEntryUtility.h>

	
	/**
		@date 	2008/09/11  20:49	
		@author  leven

		@brief 	

		@see    
	*/
	class  VGUI_EXPORT RendererEntry :	public vgBaseEntryEx
	{
	public:

		RendererEntry( vgKernel::Renderer* renderer );

		virtual ~RendererEntry(void)
		{
			if ( getRender() != NULL )
			{
				getRender()->unregisterObserver( this );
			}
		}


		// 用于Object修改后更新Node
		virtual void onChanged(int eventId, void *param);

		virtual String GetName()
		{
			return  getRender()->getName();
		}

	protected:

		virtual PropertiesParamVector& pushPropertiesParam( 
			PropertiesParamVector& params );

		virtual void updateUIFromInternal();

		virtual void updateInternalFromUI( const String& changed_param_name );



	protected:

		String _typeidOfRenderer;

		int _numOfTriangles;
		int _rendererType;
		String _rendererName;

		bool _visible;
		int _renderingPriority;

		String _boundingBoxDetails;

		float _lenX;
		float _lenY;
		float _lenZ;

		vgKernel::Vec3 _openGLPos;
		vgKernel::Vec3 _gisCoordinate;

		String _uniqueIdStr;
	};



#endif // end of __VGRENDERERENTRY_H__