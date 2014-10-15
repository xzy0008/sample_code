#include <vgStableHeaders.h>




#include <vgDatabase/vgResultGridControl.h>
#include <vgDatabase/vgdProfileManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSelectManager.h>

#include <vgCam/vgcaCamManager.h>


#include <vgCam/vgcaCamFacade.h>



BEGIN_MESSAGE_MAP(ResultGridControl, CBCGPADOGridCtrl)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_DBC_POP_DELETE, OnMenuDelete)

	ON_COMMAND(ID_POPUP_TOOBJECT, &ResultGridControl::OnPopupToobject)
END_MESSAGE_MAP()


void ResultGridControl::OnContextMenu(CWnd* pWnd, CPoint pos)
{
	// AfxMessageBox("On Context menu");

 	CMenu popMenu;
 
 	popMenu.LoadMenu(IDR_DBC_POP);
 	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);
}

void ResultGridControl::OnMenuDelete()
{
	for (int nIndex =0;nIndex < GetRowCount();nIndex++)
	{
		if (IsRowSelected(nIndex))
		{
			RemoveRow(nIndex);

			return ;
		}
	}
}


void ResultGridControl::OnPopupToobject()
{
	// TODO: 在此添加命令处理程序代码
	CString primaryid;
	String  str;
	CString Cstr;

	vgDatabase::QueryProfile pQueryProfile = vgDatabase::ProfileManager::getSingleton().GetCurProfile();

	primaryid = pQueryProfile.GetShowNameFromQueryName(pQueryProfile.GetPrimaryId());

	for (int nIndex =0;nIndex < GetRowCount();nIndex++)
	{
		if (IsRowSelected(nIndex))
		{
			CBCGPGridRow* pRow; 
			pRow = GetRow(nIndex);

			for (int i = 0; i < GetColumnCount();i++)
			{
				if (GetColumnName(i) == primaryid)
				{
					Cstr = pRow->GetItem(i)->GetValue();
					str = Cstr.GetString();
				}
			}					
		}
	}

	VGK_SHOW("切换至物体 \n");


	vgKernel::Renderer* pRenderer = vgKernel::RendererManager::getSingleton().getRendererbyName(str);
	
	//==============================================================YXDBNAME1	
	if (pRenderer != NULL )
	{	
		vgKernel::SelectManager::getSingleton().clearSelection();

		vgKernel::SelectManager::getSingleton().addSelection(pRenderer);	
		vgKernel::SelectManager::getSingleton().updateBox();

		vgCam::CamFacade::gotoRenderer( pRenderer );
	}
	else
	{
		AfxMessageBox("场景中无所查物体");
		return;
	}

}
