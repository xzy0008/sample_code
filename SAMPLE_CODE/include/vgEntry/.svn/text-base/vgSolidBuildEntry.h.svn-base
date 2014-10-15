

#pragma once

#include <vgEntry/vgBaseEntry.h>
#include <vgKernel/vgkUniqueID.h>

#include <vgKernel/vgkRendererObserver.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgEntry/vgDatabaseEntry.h>
#include <vgAutoBuild/vgSolidBuildNode.h>

namespace vgCore{



	class  VGDEP_EXPORT vgSolidBuildEntry :	public vgDatabaseEntry
	{
	public:
		vgSolidBuildEntry(  vgAutoBuild::SolidBuildNode* pObject = NULL);

		virtual ~vgSolidBuildEntry(void)
		{
			((vgAutoBuild::SolidBuildNode*)m_Renderer)->unregisterObserver( this );
		}

		void AddSingleTabPage();

		void AddGroupTabPage(); 

		void OnSinglePropertyChanged(string paramName);

		void OnGroupPropertyChanged(string paramName);

		int GetSelectedImage() { return 1; }

		int GetUnSelectedImage() { return 2; }

		// 继承自Changed，用于Object修改后更新Node
		void onChanged(int eventId, void *param);

		void UpDataProp() {}

		CMenu* GetContextMenu();

	private:

		void getData();
		void getGroupData();

		// 被修改数据的副本
		GLfloat m_posX;
		GLfloat m_posY;
		GLfloat m_posZ, m_posZMinus;
		
		int m_floor;
		int m_heightPerFloor;

		string m_sCaption;

		int m_groupFloor;
		int m_groupHeightPerFloor;

		COLORREF _colorRef;
		float m_fColorRatio;

		COLORREF _groupColorRef;
		float m_fGroupColorRatio;
	};


}//namespace vgCore
