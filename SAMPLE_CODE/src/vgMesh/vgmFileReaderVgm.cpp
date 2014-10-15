


#include <vgStableHeaders.h>
#include <vgMesh/vgmFileReaderVgm.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgMesh {


	//VgmDataStructPtrVec*	FileReaderVgm::m_pDataStructPtrVec	= NULL;
	//VgmBriefPtrVec*			FileReaderVgm::m_pBriefPtrVec		= NULL;
	//CFile*					FileReaderVgm::m_pFile				= NULL;

	////复制文件的函数---------------------------------------------------
	//BOOL CommonCopyFile(CString SourceFileName, CString DestFileName)
	//{
	//	CFile sourceFile ;
	//	CFile destFile ;
	//	CFileException ex;
	//	if (!sourceFile.Open((LPCTSTR)SourceFileName,CFile::modeRead | CFile::shareDenyWrite, &ex))
	//	{
	//		TCHAR szError[1024];
	//		ex.GetErrorMessage(szError, 1024);
	//		CString ErrorMsg = "打开文件：" ;
	//		ErrorMsg += SourceFileName ;
	//		ErrorMsg += "失败。\n错误信息为：\n" ;
	//		ErrorMsg += szError ;
	//		AfxMessageBox(ErrorMsg);
	//		return FALSE ;
	//	}
	//	else
	//	{
	//		if (!destFile.Open((LPCTSTR)DestFileName, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex))
	//		{
	//			TCHAR szError[1024];
	//			ex.GetErrorMessage(szError, 1024);
	//			CString ErrorMsg = "创建文件：" ;
	//			ErrorMsg += DestFileName ;
	//			ErrorMsg += "失败。\n错误信息为：\n" ;
	//			ErrorMsg += szError ;
	//			AfxMessageBox(ErrorMsg);
	//			sourceFile.Close();
	//			return FALSE ;
	//		}

	//		BYTE buffer[4096];
	//		DWORD dwRead;
	//		do
	//		{
	//			dwRead = sourceFile.Read(buffer, 4096);
	//			destFile.Write(buffer, dwRead);
	//		}
	//		while (dwRead > 0);   
	//		destFile.Close();
	//		sourceFile.Close();
	//	}
	//	return TRUE ;
	//}
	////----------------------------------------------------------------
	VgmBriefPtrVec*			FileReaderVgm::getVgmBriefFromFile(
		const String& absolute_file_path )
	{
		String filename = absolute_file_path;
		assert( filename.empty() == false );

		if ( filename.empty() == true )
		{
			return NULL;
		}

		vgKernel::StreamReaderPtr pstream  = 
			vgKernel::StreamReaderFactory::createFromFile( filename );
		
		if ( pstream.isNull() == true )
		{
			return NULL;
		}

		long wholefilesize = pstream->size();

		assert( pstream.isNull() == false );

		VgmHeader vgmheader;

		pstream->read( &vgmheader , sizeof( vgmheader ) );

		//------------------------------------------
		// 1.首先做必要的检查工作
		//------------------------------------------
		// 检查校验码

#if 0
		DWORD checksum;
		bool checkres = CrcUtility::getFileCrc32Code( filename , checksum );
		if ( checkres == false )
		{
			MessageBox( NULL , "校验VGM文件格式时发生错误" , "Error" , MB_OK );
			return NULL;
		}

		if ( checksum != 0xFFFFFFFF )
		{
			MessageBox( NULL , "VGM文件校验失败,文件可能损坏" , "Error" , MB_OK );
			return NULL;
		}
#endif

		// 检查fourCC
		if ( String( vgmheader._fourCC ) != "VGM" )
		{
			MessageBox( NULL , "非VGM文件格式" , "Error" , MB_OK );
			return NULL;
		}

		// 检查version
		if ( vgmheader._version != 1 )
		{
			assert(0);
			MessageBox( NULL , "VGM文件格式损坏或版本过旧" , "Error" , MB_OK );
			return NULL;
		}

		// 检查文件头长度
		if ( vgmheader._sizeOfHeader != sizeof( VgmHeader ) )
		{
			assert(0);
			MessageBox( NULL , "VGM文件格式损坏或版本过旧" , "Error" , MB_OK );
			return NULL;
		}

		// 检查brief长度
		if( vgmheader._lengthOfOneBrief != sizeof( VgmBrief ) )
		{
			  assert(0);
			MessageBox( NULL , "VGM文件格式损坏或版本过旧" , "Error" , MB_OK );
			return NULL;
		}

		// 校验文件长度
		if ( vgmheader._sizeOfWholeFile != wholefilesize )
		{
			assert(0);
			MessageBox( NULL , "VGM文件格式损坏或版本过旧" , "Error" , MB_OK );
			return NULL;
		}

		//------------------------------------------
		// 2.开始读取brief
		//------------------------------------------
		assert( vgmheader._numberOfBriefs >= 0 );
		assert( vgmheader._lengthOfOneBrief == sizeof( VgmBrief ) );

		VgmBriefPtrVec* ret( new VgmBriefPtrVec );
		//m_pBriefPtrVec = new VgmBriefPtrVec;

		for ( int i = 0 ; i < vgmheader._numberOfBriefs ; ++ i )
		{
			VgmBrief* brief = new VgmBrief;

			size_t readnum = 
				pstream->read( brief , vgmheader._lengthOfOneBrief );

			assert( readnum == vgmheader._lengthOfOneBrief );

			ret->push_back( VgmBriefPtr( brief ) );
		}

		pstream->close();
		return ret;
	}
//	//----------------------------------------------------------------
//	VgmDataStructPtrVec*	FileReaderVgm::getVgmDataStructByBrief(
//		const String& absolute_file_path)
//	{
//		m_pDataStructPtrVec = new VgmDataStructPtrVec;	
//		m_pBriefPtrVec		= FileReaderVgm::getVgmBriefFromFile(absolute_file_path);
//		
//		m_pFile = new CFile;
//		m_pFile->Open(absolute_file_path.c_str(), CFile::modeReadWrite);
//		
//		for(VgmBriefPtrVec::iterator	iter = m_pBriefPtrVec->begin();
//			iter != m_pBriefPtrVec->end(); iter++)
//		{
//			VgmDataStruct* pDataStruct = new VgmDataStruct;
//
//			m_pFile->Seek((*iter)->_positionOfMeshData[ VGLOD_CLEAR ], CFile::begin);
//
//			m_pFile->Read( &pDataStruct->_dataType , sizeof( pDataStruct->_dataType ) );
//
//			m_pFile->Read( &pDataStruct->_renderType , sizeof( pDataStruct->_renderType ) );
//
//			m_pFile->Read( &pDataStruct->_layersOfTexture , sizeof( pDataStruct->_layersOfTexture ) );
//
//			m_pFile->Read( &pDataStruct->_numberOfVertexElements , sizeof( pDataStruct->_numberOfVertexElements ) );
//			m_pFile->Read( &pDataStruct->_sizeOfVertexElements , sizeof( pDataStruct->_sizeOfVertexElements ) );
//			pDataStruct->_vertexElements = new	char[pDataStruct->_sizeOfVertexElements * pDataStruct->_numberOfVertexElements];
//			m_pFile->Read( (char*)pDataStruct->_vertexElements , 
//				pDataStruct->_sizeOfVertexElements * pDataStruct->_numberOfVertexElements );
//			
//			if( sizeof(VgmVertexElement1) == pDataStruct->_sizeOfVertexElements)
//			{
//				pDataStruct->_vertexElements = (VgmVertexElement1*)pDataStruct->_vertexElements;
//			}
//			else
//			{
//				pDataStruct->_vertexElements = (VgmVertexElement2*)pDataStruct->_vertexElements;
//			}
//
//
//			m_pFile->Read( &pDataStruct->_numberOfMetaFaces , sizeof( pDataStruct->_numberOfMetaFaces ) );
//			pDataStruct->_metaFaces = new VgmMetaFaceStruct[pDataStruct->_numberOfMetaFaces];
//
//			VgmMetaFaceStruct* refMetaFaceStruct = NULL;
//			for ( int i = 0 ; i < pDataStruct->_numberOfMetaFaces ; ++i )
//			{
//				//_metaFaces[i].writeToStream( pwriter );
//				refMetaFaceStruct =	&pDataStruct->_metaFaces[i];
//				m_pFile->Read( (char*)refMetaFaceStruct->_colorRGBA , sizeof( refMetaFaceStruct->_colorRGBA ) );
//
//				m_pFile->Read( &refMetaFaceStruct->_numberOfTexture , 4 );
//				refMetaFaceStruct->_textureFileName = new char*[refMetaFaceStruct->_numberOfTexture];
//				
//// 				void * p = malloc(128);
//// 				assert(p);
//
//				//refMetaFaceStruct->_textureFileName = (char**)malloc(4);
//				
//				if (refMetaFaceStruct->_textureFileName == NULL)
//				{
//					AfxMessageBox("Memory error");
//				}
//
//				m_pFile->Read( &refMetaFaceStruct->_sizeOfOneTexName , VGM_TEXTURE_NAME_LENGTH );
//				assert( refMetaFaceStruct->_sizeOfOneTexName == VGM_TEXTURE_NAME_LENGTH );
//
//				for ( int i = 0 ; i < refMetaFaceStruct->_numberOfTexture ; ++i )
//				{
//					assert( refMetaFaceStruct->_textureFileName[i] == NULL );
//					refMetaFaceStruct->_textureFileName[i] = new char[VGM_TEXTURE_NAME_LENGTH];
//					//refMetaFaceStruct->_textureFileName[i] = (char*)malloc(64);
//
//					m_pFile->Read( (char*)refMetaFaceStruct->_textureFileName[i] , 64 );
//				}
//
//				m_pFile->Read( &refMetaFaceStruct->_numberOfFaceIndex , sizeof( refMetaFaceStruct->_numberOfFaceIndex ) );
//				m_pFile->Read( &refMetaFaceStruct->_sizeOfFaceIndex , sizeof( refMetaFaceStruct->_sizeOfFaceIndex ) );
//				int sizeInt = refMetaFaceStruct->_sizeOfFaceIndex;
//				sizeInt = sizeInt;
//
//				refMetaFaceStruct->_faceIndex = new VgmFaceIndex[refMetaFaceStruct->_sizeOfFaceIndex];
//
//				assert( refMetaFaceStruct->_faceIndex != NULL );
//				m_pFile->Read( (char*)refMetaFaceStruct->_faceIndex , 
//					refMetaFaceStruct->_numberOfFaceIndex * refMetaFaceStruct->_sizeOfFaceIndex );
//			}
//
//			m_pDataStructPtrVec->push_back( VgmDataStructPtr( pDataStruct ) );
//		}
//		
//		//m_pFile->Close();
//
//		return	m_pDataStructPtrVec;
//	}
//	//----------------------------------------------------------------
//	bool	FileReaderVgm::writeVgmBriefToFile(
//		const String& absolute_file_path )
//	{
//		/*CFile cFile;
//		m_pFile->Open(absolute_file_path.c_str(), CFile::modeWrite |
//			CFile::shareExclusive);
//		//m_pFile->Open(absolute_file_path.c_str(), CFile::modeRead);
//		//m_pFile->Close();
//		m_pFile->Seek(sizeof(VgmHeader), CFile::begin);*/
//
//		VgmHeader vgmheader;
//		m_pFile->Seek(0, CFile::begin);
//		m_pFile->Read( &vgmheader , sizeof( vgmheader ) );
//
//		m_pFile->Seek(vgmheader._positionOfBriefs, CFile::begin);
//		for(VgmBriefPtrVec::iterator	iter = m_pBriefPtrVec->begin();
//			iter != m_pBriefPtrVec->end(); iter++)
//		{
//			VgmBrief* pBrief = iter->getPointer();
//			m_pFile->Write( (char*)pBrief, sizeof(VgmBrief));
//			long test ;
//			test = sizeof(VgmBrief);
//			test = test;
//		}
//		//m_pFile->Close();
//		return true;
//	}
//	//----------------------------------------------------------------
//	bool	FileReaderVgm::writeCrcCheckCodeToFile(
//		const String& absolute_file_path )
//	{
//		
//
//		vgKernel::StreamWriterPtr pwriter;
//		//------------------------------------------
//		// 5.最后写校验码
//		//------------------------------------------
//		// 校验码
//		// 最后取反(手动校验码只要直接写到文件尾即可)
//		// 写到文件末尾,这样使得vgm校验后都为0xFFFFFFFF
//		DWORD crcCheckSum;
//
//		CrcUtility::initCrc32Code( crcCheckSum );
//
//		//vgKernel::StreamReaderPtr pvgmreader = 
//		//	vgKernel::StreamReaderFactory::createFromFile( absolute_file_path );
//
//		////assert( pvgmreader->size() == filesize );
//		//long	filesize, beginpos, endpos;
//		//pvgmreader->seek( 0 );
//		//beginpos	= pvgmreader->tell();
//		//filesize	= pvgmreader->size();
//		//pvgmreader->seek( filesize );
//		//endpos		= pvgmreader->tell();
//		long	filesize, beginpos, endpos;
//		beginpos = m_pFile->Seek(0, CFile::begin);
//		endpos	 = m_pFile->Seek(0, CFile::end);
//		filesize = endpos - beginpos - 4;
//
//		char* buf = new char[filesize];
//		m_pFile->Seek(0, CFile::begin);
//		size_t readnum = m_pFile->Read( buf , filesize );
//		assert( readnum == filesize );
//
//
//		for ( int i = 0 ; i < filesize ; ++i )
//		{
//			byte* curbyte = i + (byte*)buf;
//			CrcUtility::calculateCrc32Code( *curbyte , crcCheckSum );
//		}
//
//		//crcCheckSum = ~crcCheckSum;
//
//		// 写到文件尾
//		//pvgmreader->close();
//
//		m_pFile->Seek(0, CFile::begin);
//		m_pFile->Write(buf, filesize);
//		m_pFile->Seek(filesize, CFile::begin);
//		m_pFile->Write((char*)&crcCheckSum , sizeof( DWORD ));
//		/*pwriter = vgKernel::StreamWriterFactory::createFromFile( absolute_file_path );
//		assert( pwriter.isNull() == false );
//
//		pwriter->write( buf , filesize );
//
//		pwriter->seek( endpos );
//		pwriter->write( (char*)&crcCheckSum , sizeof( DWORD ) );*/
//
//		delete[] buf;
//		buf = NULL;
//
//		return true;
//	}
//
//	bool	FileReaderVgm::reCalculateBoundingBox(
//		const String& absolute_file_path)
//	{		
//		// Step1: 获取VGM的 索引 以及 点、面数据
//		FileReaderVgm::getVgmDataStructByBrief(absolute_file_path);
//
//		// Step2: 重新计算包围盒
//		VgmDataStructPtrVec::iterator	iterData  = m_pDataStructPtrVec->begin();
//		VgmBriefPtrVec::iterator		iterBrief = m_pBriefPtrVec->begin();
//		for(;
//			iterData != m_pDataStructPtrVec->end(); 
//			iterData++, iterBrief++)
//		{
//			(*iterBrief)->_staticBoundingBox = vgKernel::Box(INT_MAX);
//
//			for( int indexMetaFace = 0 ; indexMetaFace < (*iterData)->_numberOfMetaFaces ; ++indexMetaFace )
//			{
//				VgmMetaFaceStruct*	refMetaFaceStruct =	&((*iterData)->_metaFaces[indexMetaFace]);
//				for( int indexFace = 0 ; indexFace < refMetaFaceStruct->_numberOfFaceIndex ; ++indexFace )
//				{
//					int vertIndex ;
//					vgKernel::Vec3	tempVec;
//
//					vertIndex = refMetaFaceStruct->_faceIndex[indexFace]._point0;
//					tempVec = vgKernel::Vec3(
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionX,
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionY,
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionZ);
//					(*iterBrief)->_staticBoundingBox.merge( tempVec );
//					
//					vertIndex = refMetaFaceStruct->_faceIndex[indexFace]._point1;
//					tempVec = vgKernel::Vec3(
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionX,
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionY,
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionZ);
//					(*iterBrief)->_staticBoundingBox.merge( tempVec );
//
//					vertIndex = refMetaFaceStruct->_faceIndex[indexFace]._point2;
//					tempVec = vgKernel::Vec3(
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionX,
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionY,
//						((vgMesh::VgmVertexElement1*)(*iterData)->_vertexElements)[vertIndex].positionZ);
//					(*iterBrief)->_staticBoundingBox.merge( tempVec );
//				}//for(Face)
//			}//for(MetaFace)
//
//			(*iterBrief)->_dynamicBoundingBox = (*iterBrief)->_staticBoundingBox;
//		}//for(VgmData)
//
//		// Step3: 重写索引(主要是为了重写包围盒)
//		FileReaderVgm::writeVgmBriefToFile(absolute_file_path);
//
//		return true;
//	}
//
//	//----------------------------------------------------------------
//	bool	FileReaderVgm::upgradeVgm(
//		const String& absolute_file_path , String newOutputDir)
//	{
//		String	destiPath = 
//			vgKernel::StringUtility::getPathFromAbsoluteFilename(absolute_file_path);
//		String	filename =
//			vgKernel::StringUtility::getFilenameFromAbsolutePath(absolute_file_path);
//		destiPath += newOutputDir ;
//		CreateDirectory(destiPath.c_str(), NULL);
//
//		destiPath = destiPath + "\\" + filename; 
//		CommonCopyFile(absolute_file_path.c_str(), destiPath.c_str());
//		
//		bool ret = 
//			reCalculateBoundingBox((const String)destiPath);//在这替换其他需要升级的数据块更新
//			
//		
//
//		writeCrcCheckCodeToFile((const String)destiPath);
//		
//		if (m_pFile)
//		{
//			m_pFile->Close();
//			delete	m_pFile;
//			m_pFile = NULL;
//		}		
//		if (m_pBriefPtrVec)
//		{
//			delete	m_pBriefPtrVec;
//			m_pBriefPtrVec = NULL;
//		}
//		if (m_pDataStructPtrVec)
//		{
//			delete	m_pDataStructPtrVec;
//			m_pDataStructPtrVec = NULL;
//		}
//		
//		
//		return ret;
//	}

}// end of namespace vgMesh
