


#ifndef __VGTHUGEPROCESSCUTBLOCK_H__
#define __VGTHUGEPROCESSCUTBLOCK_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>
	
#include <vgTerritory/vgtHugeProcessGlobal.h>


namespace vgTerritory {

	namespace HugeProcess
	{
		using namespace vgKernel;

		class SmallBlock;

		class CutBlock
		{
		public:
			CutBlock( String filename , ImageRect abs_rect  ,  Global* global)
			{
				_global = global;
				//assert( SystemUtility::checkFileExist( filename ) == true );
				_filePath = filename;
				_absoluteRect = abs_rect;
			}
			~CutBlock()
			{
				
			}
		
			String getFilePath() const
			{
				return _filePath;
			}

			ImageRect getAbsoluteRect() const
			{
				return _absoluteRect;
			}

		public:

			Global* _global;

			String _filePath;
			ImageRect _absoluteRect;

			std::vector<SmallBlock*> _intersectSmallBlocks;
		};

		

	}
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSCUTBLOCK_H__