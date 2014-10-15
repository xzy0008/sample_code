


#ifndef __VGIMPORTLISTCTRL2_H__
#define __VGIMPORTLISTCTRL2_H__

#include <vgKernel/vgkForward.h>

	
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStringPairVector.h>
#include "vgReportCtrl.h"

using namespace vgKernel;


class ListCtrlItem2
{
public:
	ListCtrlItem2()
	{

	}
	~ListCtrlItem2()
	{

	}

public:
	String _metaDemFilename;
	String _demFilepath;
	String _metaImgFilename;
	String _imageFilePath;
};

typedef std::map<String,ListCtrlItem2> ListCtrlItemMap2;
typedef std::pair<ListCtrlItemMap2::iterator,bool > ListCtrlItemInsertRes2;

class CImportListCtrl2 : public CReportCtrl
{
public:
	CImportListCtrl2();
	~CImportListCtrl2();

public:

	void initialise();

	void updateDems( const StringVectorPtr& dems );
	void updateImage( const StringVectorPtr& imgs );

	void clearAll();


	ListCtrlItemMap2* getItems()
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

	ListCtrlItemMap2* _items;
};


	


#endif // end of __VGIMPORTLISTCTRL2_H__