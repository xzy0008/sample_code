


#include <vgStableHeaders.h>
#include <vgModel/vgmoFileWriterVmd.h>
#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgModel/vgmoFileReaderMod.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgModel {



	//----------------------------------------------------------------
	vgKernel::StringVectorPtr FileWriterVmd::writeToVmdFileFromModelItemMap( 
		ModelItemMap* items , const String& save_absolute_path  )
	{
		if ( items == NULL )
		{
			return vgKernel::StringVectorPtr();
		}

		vgKernel::StreamWriterPtr pwriter =
			vgKernel::StreamWriterFactory::createFromFile( save_absolute_path );

		if ( pwriter.isNull() == true )
		{
			return vgKernel::StringVectorPtr();
		}

		assert( items != NULL );
		assert( pwriter.isNull() == false );

		long filebeg = pwriter->tell();
		bool result = true;
		long items_size  = items->size();

		VmdHeader *vgmheader = new VmdHeader;
		VmdBrief* briefs = new VmdBrief[ items_size ];

		//------------------------------------------
		// 1.得到brief序列
		//------------------------------------------
		ModelItemMap::iterator iter = items->begin();
		ModelItemMap::iterator iter_end = items->end();

		for ( int i = 0; iter != iter_end ; ++ iter , ++i )
		{
			bool dumpret = iter->second->dumpInfoToVmdBrief( &briefs[i] );

			if ( dumpret == false )
			{
				result = false;
				MessageBox( NULL , "导出vmd时出错" , "error" , MB_OK );
				break;
			}
		}

		//------------------------------------------
		// 2.首先写Vmd头文件
		//------------------------------------------
		// 先写,之后重写以更改
		pwriter->write( (char*)vgmheader , sizeof( VmdHeader) );

		vgmheader->_positionOfBriefs = pwriter->tell();
		vgmheader->_numberOfBriefs = items_size;

		//------------------------------------------
		// 3.开始预写一遍briefs
		//------------------------------------------
		pwriter->write( (char*)briefs , sizeof( VmdBrief ) * items_size );

		vgKernel::StringVectorPtr ptexlist( new vgKernel::StringVector );
		//------------------------------------------
		// 4.写整个文件数据
		//------------------------------------------
		{
			assert( items->size() == items_size );
			ModelItemMap::iterator iter = items->begin();
			ModelItemMap::iterator iter_end = items->end();

			for ( int i = 0; iter != iter_end ; ++ iter , ++i )
			{
				long databegpos = pwriter->tell();

				char* buf  = NULL;
				long buf_len = 0;

				bool dumpret = iter->second->dumpFileInfoToBuffer(
					buf , buf_len );

				if ( dumpret == false )
				{
					delete buf;
					result = false;
					MessageBox( NULL , "导出vmd数据区时出错" , "error" , MB_OK );
					break;
				}

				assert( buf != NULL );
				assert( buf_len > 0 );

				vgAsyn::FileInfo* clearestinfo = iter->second->getDataFileInfoRef();

				assert( clearestinfo != NULL );

				// 声明栈上变量,可自动删除buf
				// 这里注意,为何要去fileinfo,是因为buf是包含有lod的整个数据块
				ModelRenderWayVertexArray renderway( buf, clearestinfo->_fileSize );

				bool initok = renderway.initialise();

				if ( initok == false )
				{
					delete buf;
					result = false;
					MessageBox( NULL , "导出vmd时出错" , "error" , MB_OK );
					break;
				}

				renderway.dumpTextureNameList( ptexlist );

				pwriter->write( buf , buf_len );
				long dataendpos = pwriter->tell();

				assert( buf_len == ( dataendpos - databegpos ) );
				//------------------------------------------
				// 这里注意,根据旧的length长度来计算新的position即可.
				// length信息不需要更新
				//------------------------------------------
				// update brief
				//briefs[i]._staticBoundingBox	= renderway.getBoundingBox();
				//briefs[i]._dynamicBoundingBox	= briefs[i]._staticBoundingBox;
				//briefs[i]._dynamicBoundingBox.matrixTranslation(briefs[i]._multMatrix);


				briefs[i]._positionOfFile		= databegpos;

				briefs[i]._positionOfModelData	= databegpos;
				//briefs[i]._positionOfModelDataPlus[2] = databegpos + 
				//	briefs[i]._lengthOfModelData[2];

				//briefs[i]._positionOfModelData[1]	= briefs[i]._positionOfModelData[2]+
				//	briefs[i]._lengthOfModelData[2];
				//briefs[i]._positionOfModelDataPlus[1] = briefs[i]._positionOfModelData[1]+
				//	briefs[i]._lengthOfModelData[1];

				//briefs[i]._positionOfModelData[0] = briefs[i]._positionOfModelData[1]+
				//	briefs[i]._lengthOfModelData[1];
				//briefs[i]._positionOfModelDataPlus[0] = dataendpos;

				assert( briefs[i]._lengthOfFile	== buf_len );
			}
		}

		//------------------------------------------
		// 5.更新header
		//------------------------------------------
		long fileend = pwriter->tell();

		// update header
		vgmheader->_sizeOfWholeFile = fileend - filebeg + 4;
		assert( vgmheader->_sizeOfWholeFile > 4 );

		//------------------------------------------
		// 6.重新写header 和 brief
		//------------------------------------------
		// 计算校验和
		// 检验和
		DWORD checksum;
		CrcUtility::initCrc32Code( checksum );


		for ( int i = 0 ; i < sizeof( VmdHeader ) ; ++i )
		{
			CrcUtility::calculateCrc32Code( *((char*)vgmheader + i) , checksum );
		}	
		for ( int i = 0 ; i < sizeof( VmdBrief ) * items_size ; ++ i )
		{
			CrcUtility::calculateCrc32Code( *((char*)briefs + i) , checksum );
		}


		{
			ModelItemMap::iterator iter = items->begin();
			ModelItemMap::iterator iter_end = items->end();
			for (; iter != iter_end ; ++ iter)
			{
				char* buf  = NULL;
				long buf_len = 0;

				bool dumpret = iter->second->dumpFileInfoToBuffer(
					buf , buf_len );

				assert( dumpret == true );


				// 计算校验和
				for ( int i = 0 ; i < buf_len ; ++ i )
				{
					CrcUtility::calculateCrc32Code( *(buf + i) , checksum );
				}


				delete[] buf;
			}
		}


		pwriter->seek( filebeg );
		pwriter->write( (char*)vgmheader , sizeof( VmdHeader) );
		pwriter->write( (char*)briefs , sizeof( VmdBrief ) * items_size );
		pwriter->seek( fileend );

		//checksum = ~checksum;
		pwriter->write( (char*)&checksum , sizeof( DWORD ) );
		pwriter->close();

		pwriter.setNull();

		//------------------------------------------
		// 7.清理操作
		//------------------------------------------
		delete vgmheader;
		vgmheader = NULL;

		delete[] briefs;
		briefs = NULL;

		//------------------------------------------
		// 8.通过校验码检查文件的完整性
		//------------------------------------------
		DWORD lastcheck;

		bool getcoderet = CrcUtility::getFileCrc32Code( save_absolute_path , lastcheck );

		if ( getcoderet == false )
		{
			MessageBox( NULL , "校验文件时失败", "Error" , MB_OK );
			return vgKernel::StringVectorPtr();
		}

		if ( lastcheck != 0xFFFFFFFF )
		{
			MessageBox( NULL , "保存文件失败,请重新保存", "Error" , MB_OK );
			return vgKernel::StringVectorPtr();
		}

		if ( result == true )
		{
			return ptexlist;
		}
		else
		{
			return vgKernel::StringVectorPtr();
		}
	}
	//----------------------------------------------------------------



}// end of namespace vgModel
