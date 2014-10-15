


#ifndef __VGTGEOBLOCK_H__
#define __VGTGEOBLOCK_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtGeoGlobalData.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgTerritory/vgVgtrFile.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>
#include <ximage.h>

	
namespace vgTerritory {

	using namespace vgImage;

	/**
		@date 	2008/09/23  15:28	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GeoBlock
	{
	public:

		/**
			block_i和block_j分别是对应的block在全局中的位置.
			根据文件名得到level信息和block_i, block_j
		*/
		GeoBlock( GeoGlobalData* global_data , 
			String imgpath);

		
		~GeoBlock();
 
	public:

		bool open();

		/**
			将图缩小一倍.
		*/
		bool resize();

		// 保存在temp path
		bool saveToVgtr( String& out_vgtrname , String& out_debugimagename );
		
		fileBlock* getFileBlock();

		/**
			检查是否是全空的图像.
		*/
		bool isEmpty();
		
		String getFilePath() const 
		{
			return _imgFilepath;
		}

	private:

		VgtrFilePtr generateVgtr();
		
		CximageWrapperPtr generateDebugImgUsingVgtr( VgtrFilePtr vgtrfile );

		void setDefault();
	
	private:

		bool _isOriginImage;
	
		long _level;

		long _width;
		long _height;

		float* _buffer;
		long	_bufferSizeInFloat;

		long _blockPosX;
		long _blockPosY;

		String _imgFilepath;

		GeoGlobalData* _globalData;
	
	};
	

	typedef std::vector<GeoBlock*> GeoBlockPtrVec;
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEOBLOCK_H__