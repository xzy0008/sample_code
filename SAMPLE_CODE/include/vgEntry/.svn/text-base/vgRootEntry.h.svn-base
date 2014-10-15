#pragma once
#include <vgEntry/vgBaseEntry.h>
#include <vgUIController/vgRootTabPage.h>
#include <string>

using std::string;

class  VGUI_EXPORT vgRootEntry : public vgBaseEntry 
{
public:
	vgRootEntry(string name = "root")
		: m_name(name), vgBaseEntry( NULL )
	{
		m_pRootTab = NULL;
	}

	virtual ~vgRootEntry(void)
	{

	}

	virtual void onChanged(int eventId, void *param)
	{

	}

	virtual String GetName()
	{
		return m_name;
	}

	virtual bool canBeDeletedDirectly()
	{
		return true;
	}

	void AddNodeTabs();

	int GetUnSelectedImage() { return 0; }

	int GetSelectedImage() { return 0; }

	void OnPropertyChanged(string paramName) {}

	CMenu* GetContextMenu();

protected:
	vgRootTabPage *m_pRootTab;
	string		  m_name;
};
