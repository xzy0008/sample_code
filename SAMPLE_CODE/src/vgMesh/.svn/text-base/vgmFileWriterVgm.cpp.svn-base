


#include <vgStableHeaders.h>
#include <vgMesh/vgmFileWriterVgm.h>
#include <vgMesh/vgmFileDefinitionVgm.h>
#include <vgMesh/vgmFileReaderMod.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgMesh {



	//----------------------------------------------------------------
	vgKernel::StringVectorPtr FileWriterVgm::writeToVgmFileFromMeshItemMap( 
		MeshItemMap* items , const String& save_absolute_path  )
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

		VgmHeader *vgmheader = new VgmHeader;
		VgmBrief* briefs = new VgmBrief[ items_size ];

		//------------------------------------------
		// 1.得到brief序列
		//------------------------------------------
		MeshItemMap::iterator iter = items->begin();
		MeshItemMap::iterator iter_end = items->end();

		for ( int i = 0; iter != iter_end ; ++ iter , ++i )
		{
			bool dumpret = iter->second->dumpInfoToVgmBrief( &briefs[i] );

			if ( dumpret == false )
			{
				result = false;
				MessageBox( NULL , "导出vgm时出错" , "error" , MB_OK );
				break;
			}
		}

		//------------------------------------------
		// 2.首先写Vgm头文件
		//------------------------------------------
		// 先写,之后重写以更改
		pwriter->write( (char*)vgmheader , sizeof( VgmHeader) );

		vgmheader->_positionOfBriefs = pwriter->tell();
		vgmheader->_numberOfBriefs = items_size;

		//------------------------------------------
		// 3.开始预写一遍briefs
		//------------------------------------------
		pwriter->write( (char*)briefs , sizeof( VgmBrief ) * items_size );

		vgKernel::StringVectorPtr ptexlist( new vgKernel::StringVector );
		//------------------------------------------
		// 4.写整个文件数据
		//------------------------------------------
		{
			assert( items->size() == items_size );
			MeshItemMap::iterator iter = items->begin();
			MeshItemMap::iterator iter_end = items->end();

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
					MessageBox( NULL , "导出vgm数据区时出错" , "error" , MB_OK );
					break;
				}

				assert( buf != NULL );
				assert( buf_len > 0 );

				vgAsyn::FileInfo* clearestinfo = iter->second->getFileInfoByLod(
					VGLOD_CLEAR );

				assert( clearestinfo != NULL );

				// 声明栈上变量,可自动删除buf
				// 这里注意,为何要去fileinfo,是因为buf是包含有lod的整个数据块
				MeshRenderWayVertexArray renderway( buf, clearestinfo->_fileSize );

				bool initok = renderway.initialise();

				if ( initok == false )
				{
					delete buf;
					result = false;
					MessageBox( NULL , "导出vgm时出错" , "error" , MB_OK );
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

				briefs[i]._positionOfMeshData[2]	= databegpos;
				briefs[i]._positionOfMeshDataPlus[2] = databegpos + 
					briefs[i]._lengthOfMeshData[2];

				briefs[i]._positionOfMeshData[1]	= briefs[i]._positionOfMeshData[2]+
					briefs[i]._lengthOfMeshData[2];
				briefs[i]._positionOfMeshDataPlus[1] = briefs[i]._positionOfMeshData[1]+
					briefs[i]._lengthOfMeshData[1];

				briefs[i]._positionOfMeshData[0] = briefs[i]._positionOfMeshData[1]+
					briefs[i]._lengthOfMeshData[1];
				briefs[i]._positionOfMeshDataPlus[0] = dataendpos;

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


		for ( int i = 0 ; i < sizeof( VgmHeader ) ; ++i )
		{
			CrcUtility::calculateCrc32Code( *((char*)vgmheader + i) , checksum );
		}	
		for ( int i = 0 ; i < sizeof( VgmBrief ) * items_size ; ++ i )
		{
			CrcUtility::calculateCrc32Code( *((char*)briefs + i) , checksum );
		}


		{
			MeshItemMap::iterator iter = items->begin();
			MeshItemMap::iterator iter_end = items->end();
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
		pwriter->write( (char*)vgmheader , sizeof( VgmHeader) );
		pwriter->write( (char*)briefs , sizeof( VgmBrief ) * items_size );
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



}// end of namespace vgMesh
