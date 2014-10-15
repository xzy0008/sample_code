

#pragma once

#include <vgEntry/vgBaseEntry.h>
#include <vgKernel/vgkUniqueID.h>
//#include <vgMesh/vgmMeshItem.h>

#include <vgKernel/vgkRendererObserver.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgEntry/vgDatabaseEntry.h>
#include <vgAutoBuild/vgAutoBuildNode.h>

namespace vgCore{



	class  VGDEP_EXPORT vgAutoBuildEntry :	public vgDatabaseEntry
	{
	public:
		// 	const static int s_NumOfParam = 6;
		// 	static PropertiesParam s_ParamArray[s_NumOfParam];

	public:
		vgAutoBuildEntry(  vgAutoBuild::AutoBuildNode* pObject = NULL);

		virtual ~vgAutoBuildEntry(void)
		{
			((vgAutoBuild::AutoBuildNode*)m_Renderer)->unregisterObserver( this );
		}

		/*	void AddNodeTabs();*/

		void AddSingleTabPage();

		void AddGroupTabPage(); //  {}

		void OnSinglePropertyChanged(string paramName);

		void OnGroupPropertyChanged(string paramName);// {};

		int GetSelectedImage() { return 1; }

		int GetUnSelectedImage() { return 2; }

		// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
		//	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

		// 继承自Changed，用于Object修改后更新Node
		void onChanged(int eventId, void *param);

		void UpDataProp() {}

		CMenu* GetContextMenu();


	private:

		void getData();

		//vgMod::ObjectNode* m_pObject;

		// 被修改数据的副本
		GLfloat m_posX;
		GLfloat m_posY;
		GLfloat m_posZ, m_posZMinus;
		
		int m_size;

		string m_sCaption;
	};


}//namespace vgCore
