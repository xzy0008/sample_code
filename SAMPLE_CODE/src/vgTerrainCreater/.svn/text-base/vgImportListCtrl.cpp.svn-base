




#include <vgStableHeaders.h>
#include "vgImportListCtrl.h"





CImportListCtrl::CImportListCtrl()
{
	_items = new ListCtrlItemMap;
}

CImportListCtrl::~CImportListCtrl()
{

	if ( _items != NULL )
	{
		delete _items;
		_items = NULL ;
	}
}

void CImportListCtrl::updateDems( const StringVectorPtr& dems )
{

	assert( dems.isNull() == false );

	StringVector::iterator iter = dems->begin();
	StringVector::iterator iter_end = dems->end();

	for ( ; iter != iter_end ; ++iter )
	{
		String metaname = (*iter ).substr(
			(*iter).find_last_of("\\/") + 1 , String::npos );

		ListCtrlItem tmpitem;

		tmpitem._demFilepath = *iter;
		tmpitem._imageFilePath = "";
		tmpitem._metaDemFilename = metaname;
		tmpitem._metaImgFilename = "";

		ListCtrlItemInsertRes result = _items->insert( std::make_pair(
			tmpitem._metaDemFilename ,tmpitem )) ;

		if ( result.second == false )
		{
			std::ostringstream o;
			o << "含有部分重复包含项" << metaname << ",继续进行导入.";
			MessageBox( o.str().c_str() , "提示");
		}
	}

	invalidate();
}

void CImportListCtrl::updateImage( const StringVectorPtr& imgs )
{

	assert( imgs.isNull() == false );

	StringVector::iterator iter = imgs->begin();
	StringVector::iterator iter_end = imgs->end();

	for ( ; iter != iter_end ; ++iter )
	{
		String curname = *iter;

		String demname = curname.substr(
			curname.find_last_of("\\/") + 1 ,  String::npos );

		demname = demname.substr( 0 , demname.find_last_of(".") ) + ".dem";

		//------------------------------------------
		// 首先查找对应的item
		//------------------------------------------
		ListCtrlItemMap::iterator found = _items->find( demname );

		if ( found == _items->end() )
		{
			std::ostringstream o;
			o << "图像:" << *iter << "未找到对应的dem数据,继续进行导入.";
			MessageBox( o.str().c_str() ,"提示");
			continue;
		}

		found->second._imageFilePath = *iter;
		found->second._metaImgFilename = 
			(*iter).substr( 
			(*iter).find_last_of("\\/") + 1 , String::npos );
	}

	invalidate();
}

void CImportListCtrl::invalidate()
{
	DeleteAllItems();

	int itemid = 1;

	ListCtrlItemMap::iterator iter = _items->begin();
	ListCtrlItemMap::iterator iter_end = _items->end();

	for ( ; iter != iter_end ; ++ iter )
	{
		std::ostringstream o;
		o << itemid++;

		InsertItem(INT_MAX, 
			o.str().c_str() ,
			iter->first.c_str(),
			iter->second._metaImgFilename.c_str(),
			iter->second._demFilepath.c_str(),
			iter->second._imageFilePath.c_str()
			);
	}

	UpdateData( FALSE );
}

void CImportListCtrl::initialise()
{
	SetHeadings(
		_T(", 35;dem文件, 100;图像文件, 100;dem文件路径, 150;图像文件路径, 150"));


	SetGridLines(TRUE); // SHow grid lines
	//_importList.SetEditable(TRUE); // Allow sub-text edit
	SortItems(0, TRUE); // sort the 1st column, ascending

	//m_bSortable = _importList.IsSortable();
}

bool CImportListCtrl::checkValid()
{
	if ( _items->empty() == true )
	{
		return false;
	}

	ListCtrlItemMap::iterator iter = _items->begin();
	ListCtrlItemMap::iterator iter_end = _items->end();

	for ( ; iter != iter_end ; ++ iter )
	{
		if ( iter->first == "" )
		{
			return false;
		}
		 
		if ( iter->second._imageFilePath == "" )
		{
			return false;
		}

		vgKernel::StreamReaderPtr preader1 = 
			vgKernel::StreamReaderFactory::createFromFile( iter->second._demFilepath );

		if ( preader1.isNull() == true )
		{
			std::ostringstream o;
			o << "读取文件" << iter->second._demFilepath << 
				"时失败,请确认文件存在并且可以正常访问.";
			MessageBox( o.str().c_str() , "错误" );
			return false;
		}

		vgKernel::StreamReaderPtr preader2 = 
			vgKernel::StreamReaderFactory::createFromFile( iter->second._imageFilePath );

		if ( preader2.isNull() == true )
		{
			std::ostringstream o;
			o << "读取文件" << iter->second._imageFilePath << 
				"时失败,请确认文件存在并且可以正常访问.";
			MessageBox( o.str().c_str() , "错误" );
			return false;
		}
	}

	return true;
}

void CImportListCtrl::clearAll()
{
	_items->clear();
	invalidate();

}

vgKernel::StringPairVector* CImportListCtrl::getStringPairVec()
{
	assert( _items->empty() == false );

	
	vgKernel::StringPairVector* ret = new vgKernel::StringPairVector;

	ListCtrlItemMap::iterator iter = _items->begin();
	ListCtrlItemMap::iterator iter_end = _items->end();

	for ( ; iter != iter_end ; ++ iter )
	{
		ret->push_back( 
			std::make_pair(
			iter->second._demFilepath , iter->second._imageFilePath ));
	}


	return ret;
}