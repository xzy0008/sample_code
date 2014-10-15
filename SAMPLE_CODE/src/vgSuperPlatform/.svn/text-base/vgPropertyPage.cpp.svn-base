// vgPropertyPage.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgUIController.h"
#include "vgFrameWork.h"
#include "vgPropertyPage.h"
#include "vgTabDef.h"

// vgPropertyPage 对话框

IMPLEMENT_DYNAMIC(vgPropertyPage, CDialog)

vgPropertyPage::vgPropertyPage(CWnd* pParent /*=NULL*/)
	: CDialog(vgPropertyPage::IDD, pParent)
{

}

vgPropertyPage::~vgPropertyPage()
{
}

void vgPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void vgPropertyPage::AdjustLayout()
{
	CRect rectClient;
	GetClientRect (rectClient);
	m_wndPropList.SetWindowPos (NULL,
		rectClient.left, 
		rectClient.top, 
		rectClient.Width(),
		rectClient.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void vgPropertyPage::ConnectNode(vgBaseEntry* node, PropertiesParam* propParam, int numOfProp)
{
	CBCGPProp*	pGroup = NULL;
	CBCGPProp*  prop = NULL;
	CBCGPProp*	option = NULL;

	bool		*ptrBool;
	long		*ptrInt;
	float		*ptrFloat;
	double		*ptrDouble;
	string		*ptrStr;

	m_pNode	= node;
	m_pPropParam = propParam;
	m_numOfParam = numOfProp;

	// 不使用Vector生成 兼容以前模式
	m_useVectorParam = false;

//  测试决定是否打开
//	m_wndPropList.RemoveAll();

	for (int i = 0; i< numOfProp; i++)
	{
		 switch (propParam[i].typeId)
		 {
		 case PROP_ITEM_GROUP: 
				if (pGroup != NULL)
					m_wndPropList.AddProperty(pGroup);
				pGroup = new CBCGPProp(propParam[i].label.c_str());
				propParam[i].pProp = pGroup;

				break;
		 case PROP_ITEM_DATA:
				if (pGroup != NULL)
				{
					switch (propParam[i].dataType)
					{
					case PROP_DATA_BOOL:
						ptrBool = (bool*)propParam[i].connectedPtr;
						prop = 	new CBCGPProp(propParam[i].label.c_str(),
											    (_variant_t)(*ptrBool), 
											     propParam[i].comment.c_str());
						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;
					
					case PROP_DATA_INT:
						ptrInt = (long*)propParam[i].connectedPtr;
						
						prop  = new CBCGPProp(propParam[i].label.c_str(), 
												(_variant_t)(*ptrInt), 
												 propParam[i].comment.c_str() );
						prop->EnableSpinControl(TRUE, LONG_MIN, LONG_MAX);
						
						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;
					
					case PROP_DATA_FLOAT:
						ptrFloat = (float*)propParam[i].connectedPtr;
						prop = new CBCGPProp(propParam[i].label.c_str(),
													(_variant_t)(*ptrFloat), 
													propParam[i].comment.c_str());

						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;

					case PROP_DATA_DOUBLE:
						ptrDouble = (double*)propParam[i].connectedPtr;
						prop = new CBCGPProp(propParam[i].label.c_str(),
												(_variant_t)(*ptrDouble), 
												propParam[i].comment.c_str());
						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;

					case PROP_DATA_STR:
						ptrStr = (string*)propParam[i].connectedPtr;
						prop = new CBCGPProp(propParam[i].label.c_str(),
												(*ptrStr).c_str(), 
												propParam[i].comment.c_str());

						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;

					case PROP_DATA_OPTION_START:
						ptrStr = (string*)propParam[i].connectedPtr;
						option = new CBCGPProp (propParam[i].label.c_str(),
													(*ptrStr).c_str(),
													propParam[i].comment.c_str());
						propParam[i].pProp = option;

						break;

					case PROP_DATA_OPTION_ITEM:
						option->AddOption(propParam[i].label.c_str());
						break;
					
					case PROP_DATA_OPTION_END:
						option->AllowEdit (FALSE);
						pGroup->AddSubItem(option);

						break;

					case PROP_DATA_CONST_STR:

						ptrStr = (string*)propParam[i].connectedPtr;
						prop = new CBCGPProp(propParam[i].label.c_str(),
							(*ptrStr).c_str(), 
							propParam[i].comment.c_str());
						
						prop->AllowEdit(false);
						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;

					case PROP_DATA_COLOR:

						ptrInt = (long*)propParam[i].connectedPtr;

						prop  = new CBCGPColorProp(propParam[i].label.c_str(), 
							(COLORREF)(*ptrInt), NULL ,
							propParam[i].comment.c_str() );
#if VGK_LANG_CHS
						((CBCGPColorProp*)prop)->EnableOtherButton (_T("其他"));
#else
						((CBCGPColorProp*)prop)->EnableOtherButton (_T("Other"));
#endif

						pGroup->AddSubItem(prop);
						propParam[i].pProp = prop;

						break;

					default:
						//TRACE("Unknow Data Type \n");
						break;
					} // end inner switch
					
				} // end if 
				break;
			
		 default:
				//TRACE("Unknow Item Type \n");
			 break;
		 }
	}

	if (pGroup != NULL)
		m_wndPropList.AddProperty(pGroup);
}


void vgPropertyPage::ConnectNode(vgBaseEntry* node, vector<PropertiesParam>* propParam)
{
	CBCGPProp*	pGroup = NULL;
	CBCGPProp*  prop = NULL;
	CBCGPProp*	option = NULL;

	bool		*ptrBool;
	long		*ptrInt;
	float		*ptrFloat;
	double		*ptrDouble;
	string		*ptrStr;

	m_pNode	= node;
	// 	m_pPropParam = propParam;
	// 	m_numOfParam = propParam;
	m_pPropVector = propParam;

	// 使用Vector生成属性页
	m_useVectorParam = true;

	//  测试决定是否打开
	//	m_wndPropList.RemoveAll();

	for (int i = 0; i< propParam->size(); i++)
	{
		switch ((*propParam)[i].typeId)
		{
		case PROP_ITEM_GROUP: 
			if (pGroup != NULL)
				m_wndPropList.AddProperty(pGroup);
			pGroup = new CBCGPProp((*propParam)[i].label.c_str());
			(*propParam)[i].pProp = pGroup;

			break;
		case PROP_ITEM_DATA:
			if (pGroup != NULL)
			{
				switch ((*propParam)[i].dataType)
				{
				case PROP_DATA_BOOL:
					ptrBool = (bool*)(*propParam)[i].connectedPtr;
					prop = 	new CBCGPProp((*propParam)[i].label.c_str(),
						(_variant_t)(*ptrBool), 
						(*propParam)[i].comment.c_str());
					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				case PROP_DATA_INT:
					ptrInt = (long*)(*propParam)[i].connectedPtr;

					prop  = new CBCGPProp((*propParam)[i].label.c_str(), 
						(_variant_t)(*ptrInt), 
						(*propParam)[i].comment.c_str() );
					prop->EnableSpinControl(TRUE, LONG_MIN, LONG_MAX);

					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				case PROP_DATA_FLOAT:
					ptrFloat = (float*)(*propParam)[i].connectedPtr;
					prop = new CBCGPProp((*propParam)[i].label.c_str(),
						(_variant_t)(*ptrFloat), 
						(*propParam)[i].comment.c_str());

					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				case PROP_DATA_DOUBLE:
					ptrDouble = (double*)(*propParam)[i].connectedPtr;
					prop = new CBCGPProp((*propParam)[i].label.c_str(),
						(_variant_t)(*ptrDouble), 
						(*propParam)[i].comment.c_str());
					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				case PROP_DATA_STR:
					ptrStr = (string*)(*propParam)[i].connectedPtr;
					prop = new CBCGPProp((*propParam)[i].label.c_str(),
						(*ptrStr).c_str(), 
						(*propParam)[i].comment.c_str());

					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				case PROP_DATA_OPTION_START:
					ptrStr = (string*)(*propParam)[i].connectedPtr;
					option = new CBCGPProp ((*propParam)[i].label.c_str(),
						(*ptrStr).c_str(),
						(*propParam)[i].comment.c_str());
					(*propParam)[i].pProp = option;

					break;

				case PROP_DATA_OPTION_ITEM:
					option->AddOption((*propParam)[i].label.c_str());
					break;

				case PROP_DATA_OPTION_END:
					option->AllowEdit (FALSE);
					pGroup->AddSubItem(option);

					break;

				case PROP_DATA_CONST_STR:

					ptrStr = (string*)(*propParam)[i].connectedPtr;
					prop = new CBCGPProp((*propParam)[i].label.c_str(),
						(*ptrStr).c_str(), 
						(*propParam)[i].comment.c_str());

					prop->AllowEdit(false);
					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				case PROP_DATA_COLOR:

					ptrInt = (long*)(*propParam)[i].connectedPtr;

					prop  = new CBCGPColorProp((*propParam)[i].label.c_str(), 
						(COLORREF)(*ptrInt), NULL ,
						(*propParam)[i].comment.c_str() );

					((CBCGPColorProp*)prop)->EnableOtherButton (_T("其他"));

					pGroup->AddSubItem(prop);
					(*propParam)[i].pProp = prop;

					break;

				default:
					//TRACE("Unknow Data Type \n");
					break;
				} // end inner switch

			} // end if 
			break;

		default:
			//TRACE("Unknow Item Type \n");
			break;
		}
	}

	if (pGroup != NULL)
		m_wndPropList.AddProperty(pGroup);
}


BEGIN_MESSAGE_MAP(vgPropertyPage, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()



// vgPropertyPage 消息处理程序

int vgPropertyPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properies Grid \n");
		return -1;      // fail to create
	}

	AdjustLayout ();
	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();

	return 0;
}

void vgPropertyPage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	AdjustLayout();
}



LRESULT vgPropertyPage::OnPropertyChanged(WPARAM w, LPARAM l)
{
	CBCGPProp	*pProp = (CBCGPProp*)l;
	_variant_t	var = pProp->GetValue(); 
	string		name(pProp->GetName());
	
	// //TRACE("Name is %s \n", name);
	CString		cstr;
	string		*ptrStr;	
	int			*ptrInt;
	long		*ptrLong;
	float		*ptrFloat;
	double		*ptrDouble;
	bool		*ptrBool;

	if (! m_useVectorParam)
	{
		// 兼容原有数组版本
		// 根据name对比Label 根据vt类型转换 设置相应指针
		for (int i=0; i<m_numOfParam; i++)
		{
			if(m_pPropParam[i].label == name)
			{
				TRACE("%s 被更新 \n", name.c_str());
 				switch (var.vt)
 				{
 				case VT_BSTR:			//var is BSTR type
 					ptrStr = (string*)(m_pPropParam[i].connectedPtr);
 					cstr = var.bstrVal;
 					*ptrStr = cstr.GetString();
 					break;
 
 				case VT_I2:				//var is short int type
 					ptrInt = (int*)(m_pPropParam[i].connectedPtr);
 					*ptrInt = var.iVal;
 					break;
 
 				case VT_I4:				//var is long int type
 					ptrLong = (long*)(m_pPropParam[i].connectedPtr);
 					*ptrLong = var.lVal;
 					break;
 
 				case VT_R4:				//var is float type
 					ptrFloat = (float*)(m_pPropParam[i].connectedPtr);
 					*ptrFloat = var.fltVal;
 					break;
 
 				case VT_R8:				//var is double type
 					ptrDouble = (double*)(m_pPropParam[i].connectedPtr);
 					*ptrDouble = var.dblVal;
 					break;
 
 				case VT_BOOL:     //var is  VARIANT_BOOL
 					ptrBool = (bool*)(m_pPropParam[i].connectedPtr);
 					*ptrBool = (var.boolVal != 0);
 					break;
 
 				default:
 					//TRACE("Unknown type %d\n",var.vt);
 					break;
 				}

				vgUIController::GetInstance()->GetCurrentSelectedNode()->OnPropertyChanged(name);
				return NULL;
			}
		}
	}
	else
	{	
		// 新的Vector版本
		for (int i=0; i<m_pPropVector->size(); i++)
		{
			if((*m_pPropVector)[i].label == name)
			{
				//TRACE("%s 被更新 \n", name.c_str());
				switch (var.vt)
				{
				case VT_BSTR:			//var is BSTR type
					ptrStr = (string*)((*m_pPropVector)[i].connectedPtr);
					cstr = var.bstrVal;
					*ptrStr = cstr.GetString();
					break;

				case VT_I2:				//var is short int type
					ptrInt = (int*)((*m_pPropVector)[i].connectedPtr);
					*ptrInt = var.iVal;
					break;

				case VT_I4:				//var is long int type
					ptrLong = (long*)((*m_pPropVector)[i].connectedPtr);
					*ptrLong = var.lVal;
					break;

				case VT_R4:				//var is float type
					ptrFloat = (float*)((*m_pPropVector)[i].connectedPtr);
					*ptrFloat = var.fltVal;
					break;

				case VT_R8:				//var is double type
					ptrDouble = (double*)((*m_pPropVector)[i].connectedPtr);
					*ptrDouble = var.dblVal;
					break;

				case VT_BOOL:     //var is  VARIANT_BOOL
					ptrBool = (bool*)((*m_pPropVector)[i].connectedPtr);
					*ptrBool = (var.boolVal != 0);
					break;

				default:
					//TRACE("Unknown type %d\n",var.vt);
					break;
				}

				vgUIController::GetInstance()->GetCurrentSelectedNode()->OnPropertyChanged(name);
				return NULL;
			}
		}	
	}

	return NULL;
}


// 只适用于数组生成版本 
// LRESULT vgPropertyPage::OnPropertyChanged(WPARAM w, LPARAM l)
// {
// 	CBCGPProp	*pProp = (CBCGPProp*)l;
// 	_variant_t	var = pProp->GetValue(); 
// 	string		name(pProp->GetName());
// 	
// 	// //TRACE("Name is %s \n", name);
// 	CString		cstr;
// 	string		*ptrStr;	
// 	int			*ptrInt;
// 	long		*ptrLong;
// 	float		*ptrFloat;
// 	double		*ptrDouble;
// 	bool		*ptrBool;
// 
// 	// 根据name对比Label 根据vt类型转换 设置相应指针
// 	for (int i=0; i<m_numOfParam; i++)
// 	{
// 		if(m_pPropParam[i].label == name)
// 		{
// 			//TRACE("%s 被更新 \n", name.c_str());
// 			switch (var.vt)
// 			{
// 			case VT_BSTR:			//var is BSTR type
// 				ptrStr = (string*)(m_pPropParam[i].connectedPtr);
// 				cstr = var.bstrVal;
// 				*ptrStr = cstr.GetString();
// 				break;
// 
// 			case VT_I2:				//var is short int type
// 				ptrInt = (int*)(m_pPropParam[i].connectedPtr);
// 				*ptrInt = var.iVal;
// 				break;
// 
// 			case VT_I4:				//var is long int type
// 				ptrLong = (long*)(m_pPropParam[i].connectedPtr);
// 				*ptrLong = var.lVal;
// 				break;
// 
// 			case VT_R4:				//var is float type
// 				ptrFloat = (float*)(m_pPropParam[i].connectedPtr);
// 				*ptrFloat = var.fltVal;
// 				break;
// 
// 			case VT_R8:				//var is double type
// 				ptrDouble = (double*)(m_pPropParam[i].connectedPtr);
// 				*ptrDouble = var.dblVal;
// 				break;
// 
// 			case VT_BOOL:     //var is  VARIANT_BOOL
// 				ptrBool = (bool*)(m_pPropParam[i].connectedPtr);
// 				*ptrBool = (var.boolVal != 0);
// 				break;
// 
// 			default:
// 				//TRACE("Unknown type %d\n",var.vt);
// 				break;
// 			}
// 			
// 			vgUIController::GetInstance()->GetCurrentSelectedNode()->OnPropertyChanged(name);
// 			return NULL;
// 		}
// 	}
// 	
// 	return NULL;
// }