#pragma once
#include "vgbasednode.h"
#include "vgRootTabPage.h"

class vgRootNode : public vgBasedNode
{
public:
	vgRootNode(string nameId);

	virtual ~vgRootNode(void);

	void AddNodeTabs();

	int GetUnSelectedImage() { return 0; }

	int GetSelectedImage() { return 0; }

	void Render() {}

protected:
	vgRootTabPage *m_pRootTab;
};
