



#include <vgStableHeaders.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/Win32InputBox.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkInputSystem.h>

#include  <Psapi.h>
#include   <rpcdce.h>   
#pragma   comment(   lib,   "rpcrt4.lib"   )   
#pragma  comment( lib , "Psapi.lib" )


namespace vgKernel {
	
	
	//----------------------------------------------------------------
	String SystemUtility::getSystemTempPath()
	{
		//------------------------------------------
		// 添加系统temp路径
		//------------------------------------------
		const int SYSTEM_TEMP_PATH_LENGTH = 512;
		char system_temp_path[ SYSTEM_TEMP_PATH_LENGTH ];
		GetTempPath( SYSTEM_TEMP_PATH_LENGTH , system_temp_path );

		return system_temp_path;
	}
	//----------------------------------------------------------------
	bool SystemUtility::getUUID(  String& str )
	{
		UUID   _tmp_uuid;   
		unsigned char *stringuuid_in =  NULL;  

		RPC_STATUS result = UuidCreate(&_tmp_uuid);   

		if( RPC_S_OK ==  result )   
		{   
			if( RPC_S_OK != UuidToString(&_tmp_uuid,&stringuuid_in))   
			{   
				return false;   
			} 
			
			str = (char*)stringuuid_in;
			RpcStringFree(&stringuuid_in); 
			return true;

		}   

		return   false;   
	}
	//----------------------------------------------------------------
	String SystemUtility::getUUIDStr()
	{
		String tmp;

		if( getUUID(tmp) == true )
		{
			return tmp;
		}

		//------------------------------------------
		// creation failed!
		//------------------------------------------
		MessageBox(NULL , "UUID 创建失败!" , "Error" , MB_OK );
		return "";
	}
	//----------------------------------------------------------------
	String SystemUtility::getCurrentProcessName()
	{
		TCHAR buf[MAX_PATH];

		DWORD strsize = GetModuleFileName(
			NULL,
			buf,
			MAX_PATH	);

		assert( strsize < MAX_PATH );

		return StringUtility::getFilenameFromAbsolutePath( String(buf) );
	}
	//----------------------------------------------------------------
	bool SystemUtility::copyFile( const String& src_abs_filename ,
		const String& dst_abs_filename )
	{
#ifdef VGK_NO_SUPPORT_MFC
		assert(0);
		return true;
#else
		CFile sourceFile ;
		CFile destFile ;
		CFileException ex;
#if 0
		if (!sourceFile.Open( src_abs_filename.c_str() ,
			CFile::modeRead /*| CFile::shareDenyWrite*/, &ex))
		{
#else
		if (!sourceFile.Open( src_abs_filename.c_str() ,
			CFile::modeRead | CFile::shareDenyNone , &ex))
		{
#endif
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
			CString ErrorMsg = "打开文件：" ;
			ErrorMsg += src_abs_filename.c_str() ;
			ErrorMsg += "失败。\n错误信息为：\n" ;
			ErrorMsg += szError ;
			AfxMessageBox(ErrorMsg);
			return false ;
		}
		else
		{
			if (!destFile.Open( dst_abs_filename.c_str() , 
				CFile::modeWrite /*| CFile::shareExclusive*/ | CFile::modeCreate, &ex))
			{
				TCHAR szError[1024];
				ex.GetErrorMessage(szError, 1024);
				CString ErrorMsg = "创建文件：" ;
				ErrorMsg += dst_abs_filename.c_str() ;
				ErrorMsg += "失败。\n错误信息为：\n" ;
				ErrorMsg += szError ;
				AfxMessageBox(ErrorMsg);
				sourceFile.Close();
				return false ;
			}

			BYTE buffer[4096];
			DWORD dwRead;
			do
			{
				dwRead = sourceFile.Read(buffer, 4096);
				destFile.Write(buffer, dwRead);
			}
			while (dwRead > 0);   
			destFile.Close();
			sourceFile.Close();
		}
#endif
		return true ;
	}
	//----------------------------------------------------------------

	bool SystemUtility::moveFile( const String& src_abs_filename ,
		const String& dst_abs_filename )
	{
		BOOL ret = MoveFile( src_abs_filename.c_str(), dst_abs_filename.c_str() );

		return ret != FALSE;
	}

	//----------------------------------------------------------------
	bool SystemUtility::removeFile( const String& abs_filename , 
		const bool& alert )
	{
		/// use stdio.h 
		int ret_remove = 0;

#ifdef UNICODE
		assert(0);

#else
		ret_remove = ::remove( abs_filename.c_str() );
#endif

		if ( ret_remove == 0 )
		{
			/// 此时成功返回
			VGK_TRACE_SHORT( String( _T("File: ") ) + abs_filename + 
				String( _T(" has been deleted.") ) );

			return true;
		}			

		if ( alert == true )
		{
			std::ostringstream o;
			o << "删除文件:" << abs_filename << "时失败.";

			MessageBox( NULL , o.str().c_str() , "错误" , MB_OK );
		}



		return false;

	}
	//----------------------------------------------------------------
	bool SystemUtility::checkFileExist( const String& abs_filename )
	{
		vgKernel::StreamReaderPtr preader = 
			vgKernel::StreamReaderFactory::createFromFile( abs_filename );

		if ( preader.isNull() == false )
		{
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	String SystemUtility::getCurrentProcessPath()
	{
		TCHAR buf[MAX_PATH];

		DWORD strsize = GetModuleFileName(
			NULL,
			buf,
			MAX_PATH	);

		assert( strsize < MAX_PATH );

		return StringUtility::getPathFromAbsoluteFilename( String(buf) );

	}
	//----------------------------------------------------------------
	String SystemUtility::getCurrentDirectory()
	{
		const DWORD buf_len = 1024;
		char buf[ buf_len ];
		memset( buf , 0 , buf_len );

		DWORD ret = GetCurrentDirectory( buf_len , buf );

		assert( ret < buf_len );

		return buf;
	}
	//----------------------------------------------------------------
	bool SystemUtility::setCurrentDirectory( const String& filepath )
	{
		BOOL ret = SetCurrentDirectory( filepath.c_str() );

		return ret == TRUE;
	}
	//----------------------------------------------------------------
	bool SystemUtility::checkDirectoryExist( const String& dir_path )
	{	
		return GetFileAttributes( dir_path.c_str() ) != -1; 
	}
	//----------------------------------------------------------------
	bool SystemUtility::createDirectory( const String& dir_path )
	{
		BOOL ret = CreateDirectory( dir_path.c_str() , NULL );

		if ( ret != FALSE )
		{
			return true;
		}

		DWORD err = GetLastError();

		if ( err == ERROR_ALREADY_EXISTS )
		{
			VGK_TRACE_SHORT( dir_path + " 已存在" );
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool SystemUtility::removeEmptyDirectory( const String& dir_path )
	{
		BOOL ret = RemoveDirectory( dir_path.c_str() );

		return ret != FALSE;
	}	
	//----------------------------------------------------------------
	String SystemUtility::createInputBox( const String& title, 
		const String& content , bool use_multiline /*= false */ )
	{
		char buf[256]= {0};

#if VGK_NO_SUPPORT_MFC
		CWin32InputBox::InputBox( title.c_str(), 
			content.c_str(), buf, 256, use_multiline ,
			NULL );
#else

		CWin32InputBox::InputBox( title.c_str(), 
			content.c_str(), buf, 256, use_multiline ,
			AfxGetApp()->m_pMainWnd->m_hWnd );
#endif

		return String( buf );
	}

	//----------------------------------------------------------------
	bool SystemUtility::copyDirectory( const String& des_path, const String& src_path)
	{
		TCHAR szFind[MAX_PATH]; 
		String src_subpath;
		String des_subpath;

		lstrcpy(szFind, src_path.c_str()); 

		if (!isRoot(szFind)) 

			lstrcat(szFind, "\\"); 

		lstrcat(szFind, "*.*"); // 找所有文件 

		WIN32_FIND_DATA wfd; 

		HANDLE hFind = FindFirstFile(szFind, &wfd); 

		if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败 
			return false; 	
		do 
		{ 
			if (wfd.cFileName[0] == '.') 

				continue; // 过滤这两个目录 

			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{ 
				src_subpath = src_path + "\\" + wfd.cFileName;
				des_subpath = des_path + "\\" + wfd.cFileName;
				createDirectory(des_subpath);
				copyDirectory(des_subpath, src_subpath);
			} 
			else 
			{ 
				if (!isRoot(src_path.c_str())) 
				{
					String Srcpath1 = src_path + "\\" + String(wfd.cFileName);

					String Attachdata1 = des_path +"\\" + String(wfd.cFileName);

					CopyFile(Srcpath1.c_str(), Attachdata1.c_str(), true);
				}
				// 对文件进行操作 
			} 
		} while (FindNextFile(hFind, &wfd)); 

		FindClose(hFind); // 关闭查找句柄 

		return true;
	}
	//----------------------------------------------------------------
	bool SystemUtility::removeDirectory( const String& dir_path )
	{
		TCHAR szFind[MAX_PATH]; 
		String fileName;

		lstrcpy(szFind, dir_path.c_str()); 

		if (!isRoot(szFind)) 

			lstrcat(szFind, "\\"); 

		lstrcat(szFind, "*.*"); // 找所有文件 

		WIN32_FIND_DATA wfd; 

		HANDLE hFind = FindFirstFile(szFind, &wfd); 

		if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败 
			return false; 	
		do 
		{ 
			if (wfd.cFileName[0] == '.') 

				continue; // 过滤这两个目录 

			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{ 
				fileName = dir_path + "\\" + wfd.cFileName;

				removeDirectory( fileName );

				removeEmptyDirectory( fileName );
			} 
			else 
			{ 
				if (!isRoot( wfd.cFileName )) 
				{
					fileName = dir_path + "\\" + wfd.cFileName;

					removeFile( fileName, false );			
				}
				// 对文件进行操作 
			} 
		} while (FindNextFile(hFind, &wfd)); 

		FindClose(hFind); // 关闭查找句柄 

		if ( !removeEmptyDirectory( dir_path ) )
		{
			return false;
		}	
		
		return true;
		

	}
	//----------------------------------------------------------------
	StringVector	SystemUtility::getFilesOpenByDialog( const StringVector& fileExts )
	{
#ifdef VGK_NO_SUPPORT_MFC
		assert(0);
		return StringVector();
#else
		if ( fileExts.empty() )
		{
			return StringVector();
		}

		StringVector strVec;
		
		String defExts, defExt;

		for( StringVector::const_iterator itr = fileExts.begin();
			itr != fileExts.end(); itr ++ )
		{
			// %s files(*.%s)|*.%s|
			defExt = (*itr) + " files(*." 
				+ (*itr) + ")|*."
				+ (*itr) + "|";
			defExts += defExt;
		}
		defExts += "all files(*.*)|*.*|";

		CFileDialog dlgmodelFile(true, fileExts[0].c_str(),
			NULL,
			OFN_HIDEREADONLY|
			OFN_CREATEPROMPT|
			OFN_NONETWORKBUTTON|
			OFN_ALLOWMULTISELECT|   
			OFN_FILEMUSTEXIST,
			defExts.c_str() );

		DWORD   MAXFILE = 0xFFFF;   
		dlgmodelFile.m_ofn.nMaxFile=MAXFILE; 

		char*  pc = new char[MAXFILE];   


		dlgmodelFile.m_ofn.lpstrFile = pc;   
		dlgmodelFile.m_ofn.lpstrFile[0] = NULL;   
		dlgmodelFile.m_ofn.lpstrTitle="文件导入";

		if( dlgmodelFile.DoModal() == IDOK )
		{
			POSITION posi;   

			posi = dlgmodelFile.GetStartPosition();   

			while( posi != NULL )
			{   
				strVec.push_back( dlgmodelFile.GetNextPathName(posi).GetBuffer(0));
			}   

		}//if

		delete[] pc;

		return strVec;
#endif	
	}

	//----------------------------------------------------------------
	String	SystemUtility::getFileSaveByDialog( const StringVector& fileExts )
	{
#ifdef VGK_NO_SUPPORT_MFC
		assert(0);
		return String();
#else
		if ( fileExts.empty() )
		{
			return String();
		}

		String filePath;

		String defExts, defExt;

		for( StringVector::const_iterator itr = fileExts.begin();
			itr != fileExts.end(); itr ++ )
		{
			// %s files(*.%s)|*.%s|
			defExt = (*itr) + " files(*." 
				+ (*itr) + ")|*."
				+ (*itr) + "|";
			defExts += defExt;
		}
		defExts += "all files(*.*)|*.*|";

		CFileDialog dlgmodelFile(false,
			fileExts[0].c_str(),
			NULL,
			OFN_HIDEREADONLY|
			OFN_CREATEPROMPT|
			OFN_NONETWORKBUTTON,
			defExts.c_str() );

#if VGK_LANG_CHS
		dlgmodelFile.m_ofn.lpstrTitle="保存文件";
#else
		dlgmodelFile.m_ofn.lpstrTitle="Save File";
#endif


		if(dlgmodelFile.DoModal()==IDOK)
		{
			filePath = dlgmodelFile.GetPathName();
		}

		return filePath;
#endif	
	}
	//----------------------------------------------------------------
	bool SystemUtility::isRoot(LPCTSTR lpszPath)
	{
		TCHAR szRoot[4]; 
		wsprintf(szRoot, "%c:\\", lpszPath[0]); 
		return (lstrcmp(szRoot, lpszPath) == 0); 
	}

	//----------------------------------------------------------------
	bool SystemUtility::getFilesFromDirectory( const String& dir_path,
		String&	filesPathOut )
	{
		String dirPathTemp = dir_path;

		TCHAR szFind[MAX_PATH]; 

		lstrcpy(szFind, dirPathTemp.c_str()); 

		if (!isRoot(szFind)) 

			lstrcat(szFind, "\\"); 

		lstrcat(szFind, "*.*"); // 找所有文件 

		WIN32_FIND_DATA wfd; 

		HANDLE hFind = FindFirstFile(szFind, &wfd); 

		if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败 
			return false; 	
		do 
		{ 
			if (wfd.cFileName[0] == '.') 

				continue; // 过滤这两个目录 

			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{ 
				String dirPathSubTemp = dirPathTemp + "\\" + wfd.cFileName;
				
				getFilesFromDirectory(dirPathSubTemp, filesPathOut);
			} 
			else 
			{ 
				if (!isRoot(dirPathTemp.c_str())) 
				{
					String filePathTemp = dirPathTemp + "\\" + wfd.cFileName;
					filesPathOut += ";" + filePathTemp;
				}
				// 对文件进行操作 
			} 
		} while (FindNextFile(hFind, &wfd)); 

		FindClose(hFind); // 关闭查找句柄 

		return true;
	}

	//----------------------------------------------------------------
	void SystemUtility::showModelDialog( const String& msg )
	{
#ifdef VGK_NO_SUPPORT_MFC
		assert(0);
		return;
#else
		::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.c_str(),
			"VR-GIS Platform V2.0", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL );
#endif
	}
	//----------------------------------------------------------------
	int SystemUtility::talkWithModelDialog( const String& msg )
	{
#ifdef VGK_NO_SUPPORT_MFC
		assert(0);
		return -1;
#else
		return ::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.c_str(),
			"VR-GIS Platform V2.0", MB_YESNO );
#endif
	}

	//----------------------------------------------------------------
	String SystemUtility::getStringByID( int stringID )
	{
		TCHAR stBuf[SCHAR_MAX];
		String stringItem;

		stringItem = LoadString(NULL, stringID, stBuf, SCHAR_MAX) ? stBuf : NULL;

		return stringItem;
	}
	//----------------------------------------------------------------
#ifndef VGK_NO_SUPPORT_MFC
	CWnd* SystemUtility::getCurrentFrameWnd()
	{
		return AfxGetApp()->m_pMainWnd;
	}
	//----------------------------------------------------------------
	CWnd* SystemUtility::getCurrentViewWnd()
	{
		CView* pView = ((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveView(); 
		return pView;
	}
#endif
	//----------------------------------------------------------------

}// end of namespace vgKernel