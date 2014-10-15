#pragma once

#include "vgBaseEntry.h"
#include <vgKernel/vgkUniqueID.h>
#include <vgGIS3D/vgVertexString.h >
#include <vgKernel/vgkRendererObserver.h>
#include "vgPropertyPage.h"



class vgVecStringEntry : public vgBaseEntry
{
public:
	const static int s_NumOfParam = 3;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgVecStringEntry(vgGIS3D::VertexStringClass *vsc);


	virtual ~vgVecStringEntry(void);


	void AddNodeTabs();
	virtual String GetName()
	{
		return "矢量";
	}


	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode,被vgUIController调用 修改Node后重新设置Object 和TreeItem
	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void* param);

	void UpDataProp() {}

	CMenu* GetContextMenu()
	{
		return NULL;
	}

private:
	// group列表
	//vector<vgMeshEntry*> s_mesh_item_list;

	//string  s_group_item_name;
	vgGIS3D::VertexStringClass *m_VecStringClass;

	String m_sCaption;

	BOOL m_visible;
};

