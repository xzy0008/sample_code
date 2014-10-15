




#ifndef __VGUSGUIMANAGER_H__
#define __VGUSGUIMANAGER_H__


#include <vgUserInterface/vgusDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkSingleton.h>

	
namespace vgUserInterface {



	class TreePanel;


	/**
		@date 	2009/06/23  10:11	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGUS_EXPORT GuiManager :
		public vgKernel::Singleton<GuiManager>
	{
		friend class vgKernel::Singleton<GuiManager>;
	private:
		GuiManager();

	public:
		virtual~GuiManager()
		{
			assert( _absGuiFac == NULL );
			assert( _treePanel == NULL );
			VGK_TRACE(_T("GuiManager destroyed."));
		}
	
	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown();
	
	public:

		TreePanel* getTreePanel()
		{
			return _treePanel;
		}




	private:
	
		TreePanel* _treePanel;

		
		AbstractGuiFactory* _absGuiFac;
	};
	
	
}// end of namespace vgUserInterface
	


#endif // end of __VGUSGUIMANAGER_H__