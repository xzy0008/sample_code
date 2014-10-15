

#ifndef __VGSHPUTILITY_H__
#define __VGSHPUTILITY_H__
#include <vgGlobal/vgglDefinition.h>
#include <vgShape/vgshShapeManager.h>

namespace vgGlobal{

	//using namespace vgXXX;
	using namespace	vgShape;
	
	class	VGGL_EXPORT ShapeUtility
	{
	public:
		ShapeUtility();
		~ShapeUtility();

	public:
		static	bool importShpFile(const String& strFilePath, bool bSpecial = false );

		static	bool readProject( const String& strFilePath );

		static	bool convertShpToEditState();

		//// Shape Operation  
		//static  bool convertShpToEditState();
		static	bool getSelectFlag();

	private:
		static	bool addShpToUI(vgShape::DataSource* psource);

	};
}//namespace vgGlobal

#endif//__VGSHPUTILITY_H__