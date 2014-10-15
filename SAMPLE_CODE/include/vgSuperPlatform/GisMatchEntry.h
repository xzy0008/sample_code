

#pragma once

#include "vgBaseEntry.h"
#include <vgKernel/vgkUniqueID.h>
#include <vgGIS/vggismatch.h>
#include <vgKernel/vgkRendererObserver.h> 
#include "vgPropertyPage.h"

/**
@date 	2008/09/23  9:13	
@author  YX

@brief 	

@see    
*/

namespace vgCore{ 



	class  vgGisMatchEntry :  public vgBaseEntry
	{
	public:
		const static int s_NumOfParam = 10;
		static PropertiesParam s_ParamArray[s_NumOfParam];

	public:
		vgGisMatchEntry(  vggismatch* gisMatch = NULL);

		virtual ~vgGisMatchEntry(void)
		{
			((vggismatch*)m_Renderer)->unregisterObserver( this );
		}

		void AddNodeTabs();

		int GetSelectedImage() { return 1; }

		int GetUnSelectedImage() { return 2; }

		// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
		void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

		// 继承自Changed，用于Object修改后更新Node
		void onChanged(int eventId, void *param);

		void UpDataProp() {}

		CMenu* GetContextMenu();


	private:
	//vggismatch* m_pObject;

		// 被修改数据的副本
		GLfloat m_posX;
		GLfloat m_posY;
		GLfloat m_posZ, m_posZMinus;

		GLfloat m_height;
		GLfloat m_density;
		GLfloat m_width;
		GLfloat m_luya;

		string m_sCaption;
	};


}//namespace vgCore
