// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>
#if 0
#include "CommandWnd.h"



#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSelectManager.h>


#include <vgUIController/vgUIController.h>
#include <vgEntry/vgEntryFactory.h>
#include <vgEntry/vgShapeDataSourceEntry.h>


// 主菜单显示的TEXT
std::string s_menuName = "矢量分析(&V)";

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_SHP_LOAD			= ::RegisterWindowMessage( _T("ID_SHP_LOAD") )  ;
const static UINT ID_SHP_LOAD_GRID		= ::RegisterWindowMessage( _T("ID_SHP_LOAD_GRID") )  ;
const static UINT ID_SHP_MODE_EDIT		= ::RegisterWindowMessage( _T("ID_SHP_MODE_EDIT") )  ;
const static UINT ID_SHP_SAVE			= ::RegisterWindowMessage( _T("ID_SHP_SAVE") )  ;
const static UINT ID_SHP_TRANSLATE_ORIGIN= ::RegisterWindowMessage( _T("ID_SHP_TRANSLATE_ORIGIN") )  ;
const static UINT ID_SHP_ATTACH_TERRAIN	= ::RegisterWindowMessage( _T("ID_SHP_ATTACH_TERRAIN") )  ;


IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_SHP_LOAD, OnShpLoad ) 
	ON_REGISTERED_MESSAGE( ID_SHP_LOAD_GRID, OnShpLoadGrid ) 
	ON_REGISTERED_MESSAGE( ID_SHP_MODE_EDIT, OnShpModeEdit ) 
	ON_REGISTERED_MESSAGE( ID_SHP_SAVE, OnShpSave ) 
	ON_REGISTERED_MESSAGE( ID_SHP_TRANSLATE_ORIGIN, OnShpTraslateToOrigin ) 
	ON_REGISTERED_MESSAGE( ID_SHP_ATTACH_TERRAIN, OnShpAttachTerrain ) 
END_MESSAGE_MAP()

// CCommandWnd message handlers
//----------------------------------------------------------------
LRESULT CCommandWnd::OnShpLoad( WPARAM wParam, LPARAM lParam )
{
	vgKernel::StringVector strExts;
	strExts.push_back("shp");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	importFiles(strVec);

	return 0;
}

LRESULT CCommandWnd::OnShpLoadGrid( WPARAM wParam, LPARAM lParam )
{
	vgKernel::StringVector strExts;
	strExts.push_back("shp");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	importFiles(strVec, true);

	return 0;
}

//----------------------------------------------------------------
bool CCommandWnd::importFiles( const vgKernel::StringVector& strvec,
							   bool bSpecial/* = false*/)
{
	//------------------------------------------
	// 开始导入
	//------------------------------------------
	if( strvec.empty() )
		return false;

	String ext = vgKernel::StringUtility::getFileExtension( strvec[0] );

	std::ostringstream o;
	o	<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
	o << "\t\t正在执行 导入" << ext << "操作:\n";
#else
	o << "\t\tImporting "<< ext << ":\n";
#endif
	o	<< "-----------------------------------------------------------\n" ;
	VGK_SHOW( o.str() );


	bool ret = true;

	vgKernel::StringVector::const_iterator iter = strvec.begin();
	vgKernel::StringVector::const_iterator iter_end = strvec.end();


	for ( ; iter != iter_end ; ++ iter )
	{
		if ( importFile( *iter , bSpecial) == false )
		{
			ret = false;
		}

	}// for

	// 重新构树
	vgKernel::RendererManager::getSingleton().invalidate();


	std::ostringstream oEnd;
	oEnd<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
	oEnd<< "\t\t完成执行 导入"<< ext << "操作!\n";
#else
	oEnd<< "\t\tImport "<< ext << " Completed!\n";
#endif
	oEnd<< "-----------------------------------------------------------\n" ;
	VGK_SHOW( oEnd.str() );

	vgKernel::SystemUtility::setCurrentDirectory(strvec[0]);

	return ret;
}

//----------------------------------------------------------------
bool CCommandWnd::importFile( const String& impFile,
							  bool bSpecial/* = false*/ )
{
	if ( importFileImpl( impFile , bSpecial) == true )
	{	
		std::ostringstream oEnd;
		oEnd << "\t成功导入文件:"<< impFile << " \n";
		VGK_SHOW( oEnd.str() );
		return true;
	}
	else
	{
		std::ostringstream oEnd;
		oEnd << "\t导入文件:"<< impFile << " 失败\n";
		VGK_SHOW( oEnd.str() );
		return false;
	}
}	
//----------------------------------------------------------------
bool CCommandWnd::importFileImpl( const String& filename,
								  bool bSpecial/* = false*/ )
{
	vgShape::DataSourcePtr psource;
	
	if (!bSpecial)
	{
		psource = vgShape::ShapeManager::getSingleton().openShapeFile( filename );
	} 
	else
	{
		psource = vgShape::ShapeManager::getSingleton().openShapeFileSpecially( filename );
	}

	if ( psource.isNull() )
	{
		return false;
	}
#if 1
	addShpToUI( psource );
#else
	vgShape::LayerPtrVector* layers = psource->getLayerPtrVector();
	assert( layers != NULL );
	if ( layers == NULL )
	{
		return false;
	}

	for ( int i = 0 ; i < layers->size() ; ++ i  )
	{
		vgShape::LayerPtr la = (*layers)[i];

#if 0
		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( la.getPointer() );

		vgUI::UIController::getSingleton().AddNode(ds , entry );
#endif
		//------------------------------------------
		// 向RendererManager中添加renderer
		//------------------------------------------
		vgKernel::RendererQueue* queue = 
			vgKernel::RendererManager::getSingleton().addRenderer( la.getPointer() );

		assert( queue != NULL );
	}
#endif
	return true;
}
#if 1
//----------------------------------------------------------------
bool CCommandWnd::addShpToUI(vgShape::DataSourcePtr psource)
{

	// 添加datasourceetnry
	ShapeDataSourceEntry* ds = 
		new ShapeDataSourceEntry( psource );

	vgUI::UIController::getSingleton().addEntryToRootByName(
		"Shape", ds );

	// 向UI中添加vgBaseEntry
	vgShape::LayerPtrVector* layers = psource->getLayerPtrVector();
	assert( layers != NULL );
	if ( layers == NULL )
	{
		return false;
	}

	for ( int i = 0 ; i < layers->size() ; ++ i  )
	{
		vgShape::LayerPtr la = (*layers)[i];


		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( la.getPointer() );
		
		if (entry)
		{
			vgUI::UIController::getSingleton().AddNode(ds , entry );
		}

		//------------------------------------------
		// 向RendererManager中添加renderer
		//------------------------------------------
		vgKernel::RendererQueue* queue = 
			vgKernel::RendererManager::getSingleton().addRenderer( la.getPointer() );

		assert( queue != NULL );
	}

	return true;

}
#endif

//----------------------------------------------------------------
LRESULT CCommandWnd::OnShpSave( WPARAM wParam, LPARAM lParam )
{
	return 0;
}

LRESULT CCommandWnd::OnShpTraslateToOrigin( WPARAM wParam, LPARAM lParam )
{
	return 0;
}

LRESULT CCommandWnd::OnShpAttachTerrain( WPARAM wParam, LPARAM lParam )
{
	return 0;
}

LRESULT CCommandWnd::OnShpModeEdit( WPARAM wParam, LPARAM lParam )
{
	vgKernel::Renderer* pRenderer = vgKernel::SelectManager::getSingleton().
		getSelectedRendererByType(vgShape::RENDERER_TYPE_SHAPE_LAYER);

	if (!pRenderer)
	{
		return false;
	}

	vgShape::ShapeManager::getSingleton().setSelectMode( pRenderer,
		!vgShape::ShapeManager::getSingleton().getSelectFlag() );

	return 0;
}
// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("导入SHP文件(&Read SHP File)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_SHP_LOAD;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("导入SHP网格文件(Read &Grid SHP File)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SHP_LOAD_GRID;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("切换至编辑模式(Turn to &Edit Mode)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SHP_MODE_EDIT;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("保存SHP文件(&Save As Shape)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SHP_SAVE;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("移至地形原点(Translate To &Origin)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SHP_TRANSLATE_ORIGIN;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("矢量图层贴地(&Attach To Terrain)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SHP_ATTACH_TERRAIN;
	(*NextMenuID)++;

	return true;
}

bool GetUserMenuCheck(UINT ID)
{

	if (ID == ID_SHP_MODE_EDIT)
	{
		return	vgShape::ShapeManager::getSingleton().getSelectFlag();
	}

	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{

	// 默认菜单开启
	return true;
}
#endif