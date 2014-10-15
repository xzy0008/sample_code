


#ifndef __VGBASEENTRYEX_H__
#define __VGBASEENTRYEX_H__

#include <vgKernel/vgkForward.h>
#include "vgBaseEntry.h"
#include "vgPropertyPage.h"
#include "vgTabDef.h"

	

	/**
		@date 	2008/09/11  20:49	
		@author  leven

		@brief 	
		BaseEntry扩展类

		继承此类的只要书写

			virtual String GetName(); // 可选

			virtual PropertiesParamVector& pushPropertiesParam( 
			PropertiesParamVector& params ); // 必须

			virtual void updateUIFromInternal(); // 可选

			virtual void updateInternalFromUI();// 可选

		这几个函数即可.

		@see    
	*/
	class vgBaseEntryEx :	public vgBaseEntry 
	{
	public:

		vgBaseEntryEx( vgEntryType type ,vgKernel::Renderer* renderer );
		virtual ~vgBaseEntryEx(void);

		virtual void AddNodeTabs();

		virtual int GetSelectedImage() { return 0; }
		virtual int GetUnSelectedImage() { return 1; }

		virtual void OnPropertyChanged(string paramName);

		// 继承自Changed，用于Object修改后更新Node
		virtual void onChanged(int eventId, void *param){}


		PropertiesParamVector& getPropertiesParamVector()
		{
			return _params;
		}

	protected:

		virtual PropertiesParamVector& pushPropertiesParam( 
			PropertiesParamVector& params ) = 0;

		virtual void updateUIFromInternal() {}

		virtual void updateInternalFromUI( const String& changed_param_name ) {}

	protected:

		void* getConnectPtrByName( const String& param_name );

	private:

		static PropertiesParamVector _params;
	};


#endif // end of __VGBASEENTRYEX_H__