


#ifndef __VGTGEOIMAGEBLOCK_H__
#define __VGTGEOIMAGEBLOCK_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtGeoGlobalData.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgTerritory/vgVgtrFile.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>

#include <vgTerritory/vgtHugeProcessHugeJobs.h>
#include <vgTerritory/vgtHugeProcessPieceJob.h>

#include <ximage.h>

	
namespace vgTerritory {


	using namespace vgImage;

	/**
		@date 	2008/09/23  15:28	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GeoImageBlock
	{
	public:

		/**
			block_i和block_j分别是对应的block在全局中的位置.
			根据文件名得到level信息和block_i, block_j
		*/
		GeoImageBlock( GeoGlobalData* global_data , 
			String imgpath);

		
		~GeoImageBlock();
 
	public:

		bool open();

		/**
			将图缩小一倍.
		*/
		bool resize();

		
		//fileBlock* getFileBlock();

		/**
			检查是否是全空的图像.
		*/
		bool isEmpty();
		
		fileBlock* getFileBlock();

		String getFilePath() const
		{
			return _imgFilepath;
		}

	private:

		void setDefault();
	
	private:

		bool _isOriginImage;
	
		long _level;

		long _width;
		long _height;



		long _blockPosX;
		long _blockPosY;

		String _imgFilepath;

		GeoGlobalData* _globalData;
	
	};


	class GeoImageResizeJob : public HugeProcess::PieceJob
	{
	public:
		GeoImageResizeJob( GeoImageBlock* img_block , 
			HugeProcess::HugeJobs* boss )
			: PieceJob( boss )
		{
			_imgBlock = img_block;
		}
		virtual ~GeoImageResizeJob()
		{
			
		}
	
	
		virtual void doJob()
		{
			if ( _boss->getNotifier() != NULL )
			{
				_boss->getNotifier()->setCurrentProcessPos( _imgBlock->getFilePath() , 
					_boss->getCounter()->getCount() );
			}

			_imgBlock->resize();
		}

	private:
	

		GeoImageBlock* _imgBlock;
	
	};
	

	typedef std::vector<GeoImageBlock*> GeoImageBlockPtrVec;

	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEOIMAGEBLOCK_H__