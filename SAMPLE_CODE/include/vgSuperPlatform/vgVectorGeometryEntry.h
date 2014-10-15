#pragma once

#include "vgBaseEntry.h"
#include "vgUIController.h"
#include <vgKernel/vgkRendererObserver.h>

#include <vgVector/vgvGeometry.h>
#include <vgVector/vgvAttribute.h>



class vgVectorGeometryEntry :	public vgDatabaseEntry
{
public:
	//const static int s_NumOfParam = 7;
	//static PropertiesParam s_ParamArray[s_NumOfParam];
	//static std::vector<PropertiesParam> _params;
	//========================================//YXDB
	virtual String GetName()
	{
		String longname = m_Renderer->getName()	;

		return longname.substr( 0 , longname.find_last_of("_")-1 );
	}
	//==============================================================
public:
	vgVectorGeometryEntry(vgVector::vgvGeometry*	pGeometry);
	virtual ~vgVectorGeometryEntry(void);

	//void AddNodeTabs();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
	//void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void *param);

	void UpDataProp() {} 

	CMenu* GetContextMenu()
	{
		return NULL;
	}

	// 单选时增加Tab页面，含DatabaseTabPage
	virtual void AddSingleTabPage();

	// 多选时增加Tab页面
	virtual void AddGroupTabPage();

protected:
	// 覆写的两个PropertyChanged函数，分别处理single和Group的PropertyChanged
	virtual void OnGroupPropertyChanged(string paramName);

	virtual void OnSinglePropertyChanged(string paramName);

private:
	// 用户自定义函数，实现Mesh特定的Group编辑功能
	void OnGroupChanged(float sdx, float sdy, float sdz);

private:

	// 被修改数据的副本
	vgKernel::Vec3	m_CenterPoint;
	bool			m_bIsVisible;

	float			m_posZMinus;

	typedef vgKernel::SharePtr<String>	ShareShringPtr;
	std::vector<ShareShringPtr>	m_strFieldPtrArray;

	//String	m_strConstShapeCount;
	std::vector<PropertiesParam> _params;
};
