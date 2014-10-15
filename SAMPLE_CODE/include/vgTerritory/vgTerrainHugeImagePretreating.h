





#ifndef __VGTERRITORY_TERRAINHUGEIMAGEPRETREATING_H__
#define __VGTERRITORY_TERRAINHUGEIMAGEPRETREATING_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>


namespace vgTerritory {

	/**
		@date 	2007/04/13  17:00	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class HugeImagePretreating
	{
	public:
		HugeImagePretreating()
		{

		}
		~HugeImagePretreating()
		{

		}
		

		/// 初始化生成参数.
		bool initialiseParameters( const long& width ,
			const long& height , 
			const String& ext ,
			const String& prefix , 
			const bool& iflog )
		{
			assert( mAimFileOptionPtr.isNull() );

			if ( !mAimFileOptionPtr.isNull() )
			{
				return false;
			}

			this->mAimFileOptionPtr.bind( new AimFileBlocksOption );
			this->mAimFileOptionPtr->setParameters( width , height ,ext , prefix ,iflog );

			return true;
		}

		/// 初始化文件名称参数.
		bool initInputFileNames(
			const TCHAR** const &chararray ,
			const long& col ,
			const long& row , 
			const bool& loginfo = true );


		bool initInputFileNames( const FileNamesInfoPtr& inputFileInfo )
		{
			if ( inputFileInfo.isNull() )
			{
				return false;
			}
			this->mInputFileInfoPtr = inputFileInfo;
			return true;
		}

		bool processCalculatingAndSaving()
		{
			assert( !this->mAimFileOptionPtr.isNull() );

			this->mOutputFileInfoPtr = 
				processResizingHugeImageWithSave( mInputFileInfoPtr , mAimFileOptionPtr );
			
			if ( mOutputFileInfoPtr.isNull() )
			{
				return false;
			}
			return true;
		}

		bool processCalculating();

		FileNamesInfoPtr getCalculatedFileInfo()
		{
			return this->mOutputFileInfoPtr;
		}
	
		void clear() 
		{
			this->mAimFileOptionPtr.setNull();
			this->mInputFileInfoPtr.setNull();
			this->mOutputFileInfoPtr.setNull();
		}

	private:

	public:

		/// 处理输入的文件列表,根据AimFileBlocksOptionPtr的内容,对其进行Resize
		/// 操作.返回为产生后的文件列表,若为空,则表示产生失败.
		static FileNamesInfoPtr  processResizingHugeImageWithSave( 
			const FileNamesInfoPtr& pFileInfo ,
			const AimFileBlocksOptionPtr& pAimFileInfo );

		static FileNamesInfoPtr  processResizingHugeImageWithoutSave( 
			const FileNamesInfoPtr& pFileInfo ,
			const AimFileBlocksOptionPtr& pAimFileInfo );
	
		/// use for processResizingHugeImage() functions only
		static inline FileNamesInfoPtr  emptyFileInfoReturn(
			const String& errorString = _T("") )
		{
			if ( errorString == _T("") )
			{
				// do nothing 
				return FileNamesInfoPtr();
			}
			else
			{
				VGK_WARN(Warning::WARN_INTERNAL_WARNING ,
					Warning::BUTTON_NONE ,
					errorString, 
					_T("HugeImagePretreating::processResizingHugeImage()"));
				return FileNamesInfoPtr();
			}
		}
	
	private:

		FileNamesInfoPtr  mInputFileInfoPtr;
		FileNamesInfoPtr  mOutputFileInfoPtr;

		AimFileBlocksOptionPtr mAimFileOptionPtr;

	};
	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_TERRAINHUGEIMAGEPRETREATING_H__