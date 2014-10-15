


#include <vgStableHeaders.h>
#include <vgModel/vgmoFileDefinitionMod.h>

#include <vgModel/vgmoFileReaderMod.h>
#include <vgModel/vgmoFileWriterModToVmd.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgModel {
	
	
	
	
	//----------------------------------------------------------------
	bool FileWriterModToVmd::writeToVmdFileFromModStream(
		const vgKernel::StreamReaderPtr preader ,
		const String& save_absolute_path, const float& lod0_factor , 
		const float& lod1_factor ,
		const float& squareDistNear , const float& squareDistFar )
	{
		assert( squareDistNear < squareDistFar );
		assert( squareDistFar > 0 );
		assert( squareDistNear > 0 );

		//------------------------------------------
		// 首先做检查
		//------------------------------------------
		if ( lod0_factor != 0.0f || lod1_factor != 0.0f )
		{
			MessageBox( NULL , "输入的参数不正确" , "Error" , MB_OK );
			return false;
		}

		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( save_absolute_path );

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		ModObjPtrVector* modobjs = 
			FileReaderMod::readFromStream( preader );

		if ( modobjs == NULL )
		{
			return false;
		}

		assert( pwriter.isNull() == false );


		size_t objnum = modobjs->size();
		long beginpos = pwriter->tell();
		long filesize = 0;

		assert( objnum > 0 );




		//------------------------------------------
		// 1.首先写Vmd头文件
		//------------------------------------------
		VmdHeader *vmdheader = new VmdHeader;
		VmdBrief *vmdbriefs = new VmdBrief[objnum];
		VmdDataStruct *vmddatas = new VmdDataStruct[objnum];

		//------------------------------------------
		// 赋值lod的参数
		//------------------------------------------
		for ( size_t i = 0 ; i < objnum ; ++i )
		{
			vmdbriefs[i]._squaredDistanceOfLodFar = squareDistFar;
			vmdbriefs[i]._squaredDistanceOfLodNear = squareDistNear;
		}

		// 先写,之后重写以更改
		pwriter->write( (char*)vmdheader , sizeof( VmdHeader) );

		vmdheader->_positionOfBriefs = pwriter->tell();
		vmdheader->_numberOfBriefs = objnum;

		pwriter->write( (char*)vmdbriefs , sizeof( VmdBrief ) * objnum );

		// 分别拷贝数据,并清理mod数据
		for ( size_t i = 0 ; i < objnum ; ++i )
		{
			vmdbriefs[i].getInfoFromModObject( (*modobjs)[i].getPointer() );

			vmdbriefs[i].setClassName( typeid(ModelItem).name() );

			vmddatas[i].getInfoFromModObject( (*modobjs)[i].getPointer() );

			(*modobjs)[i].setNull();
		}

		delete modobjs;

		//------------------------------------------
		// 2.写VmdData
		//------------------------------------------
		for ( size_t i = 0 ; i < objnum ; ++i )
		{


			//------------------------------------------
			// 在这里创建lod并写入文件
			//------------------------------------------
			//VmdDataStruct* lod0 = 
			//	getVmdDataStructByLodParam( &vmddatas[i] , lod0_factor , &vmdbriefs[i]);
			//assert( lod0 != NULL );

			//VmdDataStruct* lod1 = 
			//	getVmdDataStructByLodParam( &vmddatas[i] , lod1_factor , &vmdbriefs[i]);
			//assert( lod1 != NULL );

			long databegpos = pwriter->tell();
			long datalen = vmddatas[i].writeToStream( pwriter );

			long lod1begpos = pwriter->tell();
			datalen += /*lod1->writeToStream( pwriter )*/0;

			long lod0begpos = pwriter->tell();
			datalen += /*lod0->writeToStream( pwriter )*/0;

			long dataendpos = pwriter->tell();
			assert( (databegpos + datalen ) == dataendpos );

			pwriter->flush();

			// update brief
			vmdbriefs[i]._positionOfFile		= databegpos;
			vmdbriefs[i]._lengthOfFile			= datalen;

			// 最清晰一级
			vmdbriefs[i]._positionOfModelData = databegpos;
			vmdbriefs[i]._lengthOfModelData	= lod1begpos - databegpos;
			//vmdbriefs[i]._positionOfModelDataPlus[2] = lod1begpos;
			//vmdbriefs[i]._lengthOfModelPlus[2]		= 0;

			//// 中间级
			//vmdbriefs[i]._positionOfModelData[1]	= lod1begpos;
			//vmdbriefs[i]._lengthOfModelData[1]		= lod0begpos - lod1begpos;
			//vmdbriefs[i]._positionOfModelDataPlus[1] = lod0begpos;
			//vmdbriefs[i]._lengthOfModelPlus[1]		= 0;

			//// 最不清晰一级
			//vmdbriefs[i]._positionOfModelData[0]	= lod0begpos;
			//vmdbriefs[i]._lengthOfModelData[0]		= dataendpos - lod0begpos;
			//vmdbriefs[i]._positionOfModelDataPlus[0] = dataendpos;
			//vmdbriefs[i]._lengthOfModelPlus[0]		= 0;

			//------------------------------------------
			// 清空这些数据
			//------------------------------------------
			vmddatas[i].destroy();

			//if (&vmddatas[i] != lod0)
			//{
			//	delete lod0;
			//}
			//if (&vmddatas[i] != lod1)
			//{
			//	delete lod1;
			//}
		}

		long endpos = pwriter->tell();


		// update header
		// 注意要加上校验码,4个字节
		vmdheader->_sizeOfWholeFile = endpos - beginpos + 4;
		assert( vmdheader->_sizeOfWholeFile > 4 );
		filesize = vmdheader->_sizeOfWholeFile - 4;

		//------------------------------------------
		// 3.重新写header 和 brief
		//------------------------------------------
		pwriter->seek( beginpos );
		pwriter->write( (char*)vmdheader , sizeof( VmdHeader) );
		pwriter->write( (char*)vmdbriefs , sizeof( VmdBrief ) * objnum );
		pwriter->seek( endpos );


		//------------------------------------------
		// 4.最后清理临时数据
		//------------------------------------------
		delete vmdheader;
		delete[] vmdbriefs;
		delete[] vmddatas;

		//------------------------------------------
		// 5.最后写校验码
		//------------------------------------------
		// 校验码
		// 最后取反(手动校验码只要直接写到文件尾即可)
		// 写到文件末尾,这样使得vgm校验后都为0xFFFFFFFF
		DWORD crcCheckSum;

		CrcUtility::initCrc32Code( crcCheckSum );

		pwriter->close();

		vgKernel::StreamReaderPtr pvgmreader = 
			vgKernel::StreamReaderFactory::createFromFile( save_absolute_path );

		assert( pvgmreader->size() == filesize );
		char* buf = new char[filesize];
		pvgmreader->seek( beginpos );
		size_t readnum = pvgmreader->read( buf , filesize );
		assert( readnum == filesize );


		for ( int i = 0 ; i < filesize ; ++i )
		{
			char* curbyte = i + (char*)buf;
			CrcUtility::calculateCrc32Code( *curbyte , crcCheckSum );
		}

		//crcCheckSum = ~crcCheckSum;

		// 写到文件尾
		pvgmreader->close();

		pwriter = vgKernel::StreamWriterFactory::createFromFile( save_absolute_path );
		assert( pwriter.isNull() == false );

		pwriter->write( buf , filesize );

		pwriter->seek( endpos );
		pwriter->write( (char*)&crcCheckSum , sizeof( DWORD ) );

		delete[] buf;
		buf = NULL;




		return true;
	}
	//----------------------------------------------------------------
	bool FileWriterModToVmd::writeToVmdFromStringPairs( 
		const vgKernel::StringPairVector& inputpairs, const float& lod0_factor , 
		const float& lod1_factor ,
		const float& squareDistNear , const float& squareDistFar  )
	{
		if ( inputpairs.empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 确定process的进度条
		//------------------------------------------
		int processCounter = 0;
		this->notifyProcessObserversStart( "开始生成读取mod文件..." ,0,inputpairs.size() - 1 );


		StringPairVector::const_iterator iter = inputpairs.begin();
		StringPairVector::const_iterator iter_end = inputpairs.end();

		bool sucess = true;

		for ( ; iter != iter_end ; ++iter )
		{
			String src = iter->first;
			String dst = iter->second;

			std::ostringstream o;
			o << "正在处理:" << src;
			notifyProcessObserversPos( o.str() , processCounter++);

			vgKernel::StreamReaderPtr preader = 
				vgKernel::StreamReaderFactory::createFromFile( src );

			assert( preader.isNull() == false );

			if ( preader.isNull() == true )
			{
				return false;
			}

			bool ret = vgModel::FileWriterModToVmd::writeToVmdFileFromModStream(
				preader , dst , lod0_factor , lod1_factor , 
				squareDistNear , squareDistFar );

			assert( ret == true );
			if ( ret == false )
			{
				return false;
			}
		}

		std::ostringstream o;
		o << "操作成功完成,共" << inputpairs.size() << "个文件";

		notfiyProcessObserversFinish( o.str() );

		return true;
	}
}// end of namespace vgModel
