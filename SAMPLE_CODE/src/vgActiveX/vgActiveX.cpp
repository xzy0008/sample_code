// vgActiveX.cpp : Implementation of CvgActiveXApp and DLL registration.

#include <vgStableHeaders.h>
#include "vgActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CvgActiveXApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xD9D8D253, 0x2086, 0x4717, { 0xA9, 0x95, 0x63, 0x69, 0xAC, 0xF, 0x34, 0x30 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CvgActiveXApp::InitInstance - DLL initialization

BOOL CvgActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CvgActiveXApp::ExitInstance - DLL termination

int CvgActiveXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
