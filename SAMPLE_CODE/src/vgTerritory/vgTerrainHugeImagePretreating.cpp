



#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainHugeImagePretreating.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiFreeImageWrapper.h>




namespace vgTerritory {
	

	//----------------------------------------------------------------
	FileNamesInfoPtr HugeImagePretreating::processResizingHugeImageWithSave( 
		const FileNamesInfoPtr& pFileInfo ,  const AimFileBlocksOptionPtr& pAimFileInfo )
	{
		assert( !pFileInfo.isNull() );
		assert( !pAimFileInfo.isNull() );

		FileNamesInfoPtr resultFileInfo( new FileNamesInfo );

		resultFileInfo->columnNum = pFileInfo->columnNum;
		resultFileInfo->rowNum = pFileInfo->rowNum;

		const std::vector<String> &stringVec = pFileInfo->filenameVector;

		const long& col = pFileInfo->columnNum;
		const long& row = pFileInfo->rowNum;

		const long& aimWidth = pAimFileInfo->aimFileWidth;
		const long& aimHeight = pAimFileInfo->aimFileHeight;

		/// The resizing function is only supported in NormalImage.
		//CximageWrapperPtr pTempImage( new CximageWrapper );
		FreeImageWrapperPtr pTempImage( new FreeImageWrapper );

		for ( int y = 0 ; y < row ; ++ y )
		{
			for ( int x = 0 ; x < col ; ++ x )
			{
				/// 这里的越界检查是否是抛出异常???????
				const String &file = stringVec.at( y * col + x );
				const String& aimFilename = pAimFileInfo->getAimFileName( x , y );

				assert( file != _T("") );

				/// now load
				if( pTempImage->loadFromFile( file ) == false )
				{
					VGK_EXCEPT(Exception::ERR_FILE_NOT_FOUND,
						 _T("文件载入失败!"),
						 _T("HugeImagePretreating::processResizingHugeImage()"));

					return emptyFileInfoReturn();
				}
				
				if ( pTempImage->resize( ImageSize( aimWidth , aimHeight ) ) == false )
				{
					VGK_EXCEPT(Exception::ERR_INVALID_STATE,
						 _T("文件转换大小时出错!"),
						 _T("HugeImagePretreating::processResizingHugeImage()"));

					return emptyFileInfoReturn();
				}
			
				if ( pTempImage->saveToDdsFile( aimFilename ,
					FreeImageWrapper::DDS_FORMAT_DXT1 ) == false )
				{
					VGK_EXCEPT(Exception::ERR_INVALID_STATE,
						 _T("文件保存失败!"),
						 _T("HugeImagePretreating::processResizingHugeImage()"));

					return emptyFileInfoReturn();
				}

				resultFileInfo->filenameVector.push_back( aimFilename );

				// make img empty
				pTempImage->release();

			}// end of row x
		}// end of col y
				
		return resultFileInfo;
	}
	//----------------------------------------------------------------
	bool HugeImagePretreating::initInputFileNames( 
		const TCHAR** const &chararray ,  const long& col , 
		const long& row , const bool& loginfo /*= true */ )
	{
		if ( !mInputFileInfoPtr.isNull() )
		{
			VGK_EXCEPT(Exception::ERR_INVALID_STATE ,
				 _T("自身不为空,已被初始化. The self data struct must be inited.") ,
				 _T("HugeImagesProcessor::initialiseFileNames"));
			return false;
		}
		this->mInputFileInfoPtr = HugeImageUtil::createFileNamesInfoFormArray(
			chararray , col , row , false );
		if ( mInputFileInfoPtr.isNull() )
		{
			return false;
		}

		if ( loginfo )
		{
			LogManager::getSingleton().logMessage(mInputFileInfoPtr->getDetails());
		}
		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagePretreating::processCalculating()
	{
		this->mOutputFileInfoPtr = processResizingHugeImageWithoutSave( mInputFileInfoPtr , mAimFileOptionPtr );
		return true;
	}
	//----------------------------------------------------------------
	FileNamesInfoPtr HugeImagePretreating::processResizingHugeImageWithoutSave( 
		const FileNamesInfoPtr& pFileInfo ,  const AimFileBlocksOptionPtr& pAimFileInfo )
	{
		assert( !pFileInfo.isNull() );
		assert( !pAimFileInfo.isNull() );

		FileNamesInfoPtr resultFileInfo( new FileNamesInfo );

		resultFileInfo->columnNum = pFileInfo->columnNum;
		resultFileInfo->rowNum = pFileInfo->rowNum;

		const std::vector<String> &stringVec = pFileInfo->filenameVector;

		const long& col = pFileInfo->columnNum;
		const long& row = pFileInfo->rowNum;

		const long& aimWidth = pAimFileInfo->aimFileWidth;
		const long& aimHeight = pAimFileInfo->aimFileHeight;

		for ( int y = 0 ; y < row ; ++ y )
		{
			for ( int x = 0 ; x < col ; ++ x )
			{
				const String &file = stringVec.at( y * col + x );
				const String& aimFilename = pAimFileInfo->getAimFileName( x , y );

				assert( file !=  _T("") );

				resultFileInfo->filenameVector.push_back( aimFilename );

			}// end of row x
		}// end of col y

		return resultFileInfo;
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory
