



#ifndef __VGIMPORTLISTCTRL_H__
#define __VGIMPORTLISTCTRL_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStringPairVector.h>
#include "vgReportCtrl.h"
	
using namespace vgKernel;


class ListCtrlItem
{
public:
	ListCtrlItem()
	{
		
	}
	~ListCtrlItem()
	{
		
	}

public:
	String _metaDemFilename;
	String _demFilepath;
	String _metaImgFilename;
	String _imageFilePath;
};

typedef std::map<String,ListCtrlItem> ListCtrlItemMap;
typedef std::pair<ListCtrlItemMap::iterator,bool > ListCtrlItemInsertRes;

class CImportListCtrl : public CReportCtrl
{
public:
	CImportListCtrl();
	~CImportListCtrl();

public:

	void initialise();

	void updateDems( const StringVectorPtr& dems );
	void updateImage( const StringVectorPtr& imgs );

	void clearAll();


	ListCtrlItemMap* getItems()
	{
		assert( _items != NULL );
		return _items;
	}

	vgKernel::StringPairVector* getStringPairVec();

	vgKernel::StringVectorPtr getDemFileNameVector();

	bool checkValid();
private:

	void invalidate();

private:

	ListCtrlItemMap* _items;
};
	

	


#endif // end of __VGIMPORTLISTCTRL_H__