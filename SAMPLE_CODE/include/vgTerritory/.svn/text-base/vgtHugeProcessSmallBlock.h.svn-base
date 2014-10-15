


#ifndef __VGTHUGEPROCESSSMALLBLOCK_H__
#define __VGTHUGEPROCESSSMALLBLOCK_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>
#include <vgTerritory/vgtHugeProcessCutBlock.h>
#include <vgTerritory/vgtHugeProcessGlobal.h>

	
namespace vgTerritory {


	namespace HugeProcess 
	{

		using namespace vgKernel;

		class FileBlock;

		class SmallBlock
		{
		public:
			SmallBlock( long worldnumX,  long worldnumY , Global* global );
			~SmallBlock()
			{
				
			}

			ImageRect getAbsoluteRect() const
			{ 
				return _absoluteRect;
			}

			// 返回值若为false,表示没有相交量.
			bool testIntersects( std::vector<FileBlock*>& input_file_blocks );


			bool testIntersects( std::vector<CutBlock*>& input_cut_blocks );


			// 将cutblocks进行overlap,返回的是保存后的文件名.
			String overlapCutBlocks();

 

			String getDstFilename();

		private:
		
			Global* _global;

			ImageRect _absoluteRect;

			long _worldNumX;
			long _worldNumY;
		

			std::vector<FileBlock*> _intersectFileBlocks;

			std::vector<CutBlock*> _insideCutBlocks;
		};
		
	}
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSSMALLBLOCK_H__