#pragma once

#include "vgBaseEntry.h"
#include <vgKernel/vgkUniqueID.h>
#include <vgMesh/vgmMeshItem.h>
//*#include "vgUIController.h"*/
#include <vgKernel/vgkRendererObserver.h>
#include "vgPropertyPage.h"
#include <vgCoordinate.h>
#include <vgDatabaseEntry.h>

#include "vgDatabasePage.h"

class vgMeshEntry : public vgDatabaseEntry
{
public:
	vgMeshEntry( vgMesh::MeshItem* meshitem );

	virtual ~vgMeshEntry(void)
	{
		((vgMesh::MeshItem*)m_Renderer)->unregisterObserver( this );
	}



	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void* param);

	void UpDataProp() {}

	CMenu* GetContextMenu();

	// 单选时增加Tab页面，含DatabaseTabPage
	virtual void AddSingleTabPage();

	// 多选时增加Tab页面
	virtual void AddGroupTabPage();

public:

	bool _visible;

	// 单选时被修改数据的副本
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_posZMinus;

	float squareDistNear;
	float squareDistFar;

	string  strNumberOfTran;

	bool _isLodMesh;

protected:
	// 覆写的两个PropertyChanged函数，分别处理single和Group的PropertyChanged
	virtual void OnGroupPropertyChanged(string paramName);

	virtual void OnSinglePropertyChanged(string paramName);

private:
	// 用户自定义函数，实现Mesh特定的Group编辑功能
	void OnGroupChanged(float sdx, float sdy, float sdz);

private:

	// group编辑的数据
	static float s_group_posX;
	static float s_group_posY;
	static float s_group_posZ;
	static float s_group_posZMinus;


	static float   s_group_squareDistNear;
	static float   s_group_squareDistFar;

	static string  s_group_item_name;

	static bool    s_group_onEdit;

	static bool s_isLodMesh;

	//颜色编辑
	COLORREF _colorRef;
	float m_fColorRatio;

};