#include <vgStableHeaders.h>
#include <vgSuperPlatform/vgGroupBasedEntry.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgUIController.h>



vector<PropertiesParam> vgGroupBasedEntry::s_GroupParamArray;

vector<PropertiesParam> vgGroupBasedEntry::s_ParamArray;

vector<vgGroupBasedEntry*> vgGroupBasedEntry::s_group_list;

void vgGroupBasedEntry::AddNodeTabs()
{
		UINT numOfSelectedItem = vgKernel::SelectManager::getSingleton().getSelectedItems().size();
		TRACE("Selected number is %d \n",numOfSelectedItem);
		UINT treeCount = vgUIController::GetInstance()->GetWorkSpaceBar()->GetTree().GetSelectedCount();

		s_group_list.clear();

		// 判断是否选择的Renderer和树节点中选择的数量一致
		//if (treeCount == numOfSelectedItem && treeCount > 1)
		if (numOfSelectedItem > 1)
		{
			CEditTreeCtrlEx* pTree = &vgUIController::GetInstance()->GetWorkSpaceBar()->GetTree(); 
			list<HTREEITEM> selectedList = pTree->GetSelectedList();
			list<HTREEITEM>::iterator iter = selectedList.begin();
			list<HTREEITEM>::iterator end  = selectedList.end();

			TRACE("%d ", selectedList.size());
			while (iter != end)
			{
				//vgMeshEntry* pMeshEntry = (vgMeshEntry*)(pTree->GetItemData(*iter));
				vgGroupBasedEntry *pGroupEntry =  (vgGroupBasedEntry*)(pTree->GetItemData(*iter));

				// vgMeshEntry* pMeshEntry = (vgMeshEntry*)(pTree->GetItemData(*iter));
				// vgGroupBasedEntry *pGroupEntry =  (vgGroupBasedEntry*)(pTree->GetItemData(*iter));
				// 保证添加进Group的Renderer都是同一个类型
				if (pGroupEntry != NULL && pGroupEntry->GetType() == this->GetType())
				{
					s_group_list.push_back(pGroupEntry);
				}
				else
				{
					s_group_list.clear();
					vgUIController::GetInstance()->RemoveAllPages();

					// 需更改的goto语句
					goto singleTabs;
					return ;
					// assert(0);
				}

				iter ++;
			}
			AddGroupTabPage();

			return ;
		}

singleTabs:
		AddSingleTabPage();
}

void vgGroupBasedEntry::OnPropertyChanged(string paramName)
{
	if (s_group_list.size() > 0)
	{
		OnGroupPropertyChanged(paramName);
	}
	else
	{
		OnSinglePropertyChanged(paramName);
	}
}
