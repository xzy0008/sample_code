
#include <vgStableHeaders.h>
#include "vgPatchUtility.h"

//----------------------------------------------------------------
namespace	vgUtility
{

	//----------------------------------------------------------------
	void PatchUtility::toLowerCase( String &str )
	{
		transform( str.begin(), str.end(), str.begin(), ::tolower );
	}

	//----------------------------------------------------------------
	String PatchUtility::getCurrentProcessPath()
	{
		TCHAR buf[MAX_PATH];

		DWORD strsize = GetModuleFileName( NULL, buf, MAX_PATH );

		assert( strsize < MAX_PATH );

		String::size_type found = String(buf).find_last_of( "\\/" );

		return String(buf).substr( 0 , found + 1 );

	}

	//----------------------------------------------------------------
	String PatchUtility::getCurrentProcessName()
	{
		TCHAR buf[MAX_PATH];

		DWORD strsize = GetModuleFileName( NULL, buf, MAX_PATH );

		assert( strsize < MAX_PATH );

		String abs_path = (String)(buf);
		String::size_type found = abs_path.find_last_of( "\\/" );

		return abs_path.substr( found + 1, String::npos );
	}

	//----------------------------------------------------------------
	String PatchUtility::getFileExtension( const String &filename )
	{
		String::size_type pos = filename.rfind('.');
		String ext = filename.substr(pos == String::npos ? filename.length() : pos + 1);
		transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		ext.erase(ext.find_last_not_of(' ') + 1);
		return ext;
	}

	//----------------------------------------------------------------
	String PatchUtility::getPathFromAbsoluteFilename( const String &abs_filename )
	{
		String::size_type found = abs_filename.find_last_of( "\\/" );

		return abs_filename.substr( 0 , found + 1 );
	}

	//----------------------------------------------------------------
	bool PatchUtility::copyFile( const String &src_abs_filename, const String &dst_abs_filename )
	{
#ifdef VGK_NO_SUPPORT_MFC
		assert(0);
		return true;
#else
		CFile sourceFile ;
		CFile destFile ;
		CFileException ex;

		if (!sourceFile.Open( src_abs_filename.c_str() ,
			CFile::modeRead /*| CFile::shareDenyWrite*/, &ex))
		{
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
				CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex))
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
	bool PatchUtility::createDirectory( const String &dir_path )
	{
		BOOL ret = CreateDirectory( dir_path.c_str() , NULL );

		if ( ret != FALSE )
		{
			return true;
		}

		DWORD err = GetLastError();

		if ( err == ERROR_ALREADY_EXISTS )
		{
			String msg = dir_path + " 已存在";
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.c_str(), "错误", MB_OK );
			return true;
		}

		return false;
	}

}// namespace	vgUtility

