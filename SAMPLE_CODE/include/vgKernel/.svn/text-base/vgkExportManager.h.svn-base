
#ifndef __VGKEXPORTMANAGER_H__
#define __VGKEXPORTMANAGER_H__

#include <vgKernel/vgkSingleton.h>



namespace vgKernel {

	/**
	@date 	2010/05/07  14:55	
	@author  ytf

	@brief 	

	@see    
	*/
	class  VGK_EXPORT ExportManager : public vgKernel::Singleton<ExportManager>
	{
		friend class vgKernel::Singleton<ExportManager>;
	private:
		ExportManager() 
			: vgKernel::Singleton<ExportManager>( VGK_SINGLETON_LEFE_EXPORTMANAGER )
		{
		}

		virtual~ExportManager()
		{
			
		}

		HRESULT  AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...);//m 为导出excel添加的一个函数；

	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown() 
		{
			return true;
		}

	public:

		bool ExportToWord();

		bool ExportToExcel();
	};
}// end of namespace vgKernel



#endif // end of __VGKLOGMANAGER_H__