// vgFrameWork.h : main header file for the vgFrameWork application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "res.h"       // main symbols


// CvgFrameWorkApp:
// See vgFrameWork.cpp for the implementation of this class
//

class CvgFrameWorkApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CvgFrameWorkApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


	bool _enablePackage;


private:

	HINSTANCE    m_hinstBCGCBRes;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
//	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

protected:
	void registerDotVGForVRGIS();
	void loadSceneByConfig(const String& configFile);
	bool loadVgByConfig( const String& filePath );
	bool loadModByConfig( const String& filePath, const String& iniFilePath);
	void registerForVRGIS();
	void registerPlayerForVRGIS();


};

extern CvgFrameWorkApp theApp;