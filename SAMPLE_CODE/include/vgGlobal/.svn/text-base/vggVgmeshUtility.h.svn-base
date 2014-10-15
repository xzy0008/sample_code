

#ifndef __VGMESHUTILITY_H__
#define __VGMESHUTILITY_H__

#include <vgGlobal/vgglDefinition.h>

namespace vgGlobal{

	//using namespace vgXXX;
	
	
	class	VGGL_EXPORT MeshUtility
	{
	public:
		MeshUtility();
		~MeshUtility();

		//原来GlobalFacade七个函数转移到这里
	public:
		static bool importImageFile();
		static bool saveModelFileOnly();
		static bool saveModelAndImage();

		//带参读写vgm和vgi
		static bool importModelFileOnly( String VgmPathName);
		static bool importImageFileOnly(String VgiPathName);
		static void importModelAndImage(String readPath);

		static bool saveModelAndImage(String savePath);

		static bool collectModelAndImage(String savePath);
		static bool	importModelAndImagePreVersion(String readPath, String strheader);

		// 设置切块保存模式--中间层调用
		static void setSaveMode( bool bMode );
	};
}//namespace vgGlobal

#endif//__VGMESHUTILITY_H__