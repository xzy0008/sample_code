


#ifndef __VGTHUGEPROCESSGLOBAL_H__
#define __VGTHUGEPROCESSGLOBAL_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>

	
namespace vgTerritory {


	namespace HugeProcess 
	{

		using namespace vgKernel;



		class Global
		{
		public:
			Global();
			~Global();
		
			bool isValid() const
			{
				return _isValid;
			}

		public:

			bool _removeTempFiles;
			bool _removeInputFiles;

			String _tempExtension;

			String _tempPath;

			long _smallBlockWidth;

			bool _isValid;

			long _widthAndHeightAddition;
		
			ImageRect _worldRect;

			// 输出前缀,如"test_level0"
			String _outputPrefix;

			// 输出扩展名,如"dds"
			String _outputExtension;

			unsigned char _filledColor[4];
		};
		
	}
	
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSGLOBAL_H__