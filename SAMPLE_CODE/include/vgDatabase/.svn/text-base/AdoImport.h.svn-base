////////////////////////////////////////////////////////////////////////////
//
//  AdoImport.h: 为支持数据库访问技术ADO 导入必要的头文件＆DLL
//
////////////////////////////////////////////////////////////////////////////

#ifndef _ADOIMPORT_H_INCLUDED_
	#define _ADOIMPORT_H_INCLUDED_

//	#include <afx.h>		 // 引入CString类, 将使用
//	#include <afxdisp.h>     // 引入COleDateTime类, 将使用
	
 //   #pragma message ("确认到 Project.Settings.C/C++.Precompile Headers选项下 选择第二项")
	//#pragma message ("若要同时包含adox.h ado.h两个头文件, 确保adox.h顺序在先") 

	#pragma warning (disable: 4146)
	#import "c:\Program Files\Common Files\system\ado\msadox.dll" 
	// 定义了ADOX类库
	#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "ADOEOF")
	// 定义了ADO类库
	#import "c:\Program Files\Common Files\system\ado\msjro.dll" no_namespace rename("ReplicaTypeEnum", "_ReplicaTypeEnum")					
	// 定义了压缩&修复mdb文件类	
	#pragma warning (default: 4146)

#endif //#ifndef _ADOIMPORT_H_INCLUDED_