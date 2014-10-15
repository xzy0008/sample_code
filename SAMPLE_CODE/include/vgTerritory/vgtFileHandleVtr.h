


#ifndef __VGTERRITORY_TFILEHANDLEVTR_H__
#define __VGTERRITORY_TFILEHANDLEVTR_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaFileHandle.h>
#include <vgTerritory/vgtElevationItem.h>

	
namespace vgTerritory {

	/**
		@date 	2008/09/02  9:31	
		@author  leven
	
		@brief 	注意!文件的打开为可读可写的方式.
		在这个方式下,文件不能被共享!
	
		@see    
	*/
	class  VGT_EXPORT FileHandleVtr : public vgAsyn::FileHandle
	{
	public:
		FileHandleVtr( String filepath )
			: FileHandle( filepath )
		{
			_nextHandle = NULL;
			_type = FILEHANDLE_TYPE_VTR;
		}
		virtual ~FileHandleVtr()
		{
			close();
		}
	

	public:

		FileHandleVtr* getNextFileHandle()
		{
			return _nextHandle;
		}

		virtual bool exist( const String& metafilename );

		virtual vgKernel::StringVector* listMetaFileNames();

		virtual bool open();

		virtual void close();

		
		virtual bool extractToMultipleFiles( const String& save_multiple_file_path );


		ElevationItem* getElevationItem( const String& metafilename );

		VtrHeaderPtr getHeader() const
		{
			assert( _vtrFileHeader.isNull() == false );
			return _vtrFileHeader;
		}

		ElevationItemMap* getElevationItemsPtr()
		{
			return &_elevItems;
		}

		// 得到Y轴的最大scale,通过这个参数可以优化渲染
		float getMaxScaleY();

		/**
			如果有下一个vtr文件, 则尝试打开
		*/
		FileHandleVtr* openNextVtrFile();

		String getNextFilePath();

		String getTerrainName() const
		{
			assert( _vtrFileHeader.isNull() == false );
			return _vtrFileHeader->name;
		}

	private:

		void dropItemsData();

	private:

		ElevationItemMap _elevItems;
	
		VtrHeaderPtr _vtrFileHeader;
		FileHandleVtr* _nextHandle;
	};
	

	typedef std::map<String, FileHandleVtr*> FileHandleVtrPtrMap;
	typedef std::pair<FileHandleVtrPtrMap::iterator , bool >  FileHandleVtrPtrMapInsertRes;

	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TFILEHANDLEVTR_H__