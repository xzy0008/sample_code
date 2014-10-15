



#include <vgStableHeaders.h>
#include <vgImage/vgiIoRequestExtractVgi.h>
#include <vgKernel/vgkStreamWriter.h>


namespace vgImage {
	
	
	
	//----------------------------------------------------------------
	IoRequestExtractVgi::IoRequestExtractVgi( String vgipath , vgAsyn::FileInfo* fileinfo ) : IoRequest( fileinfo ) ,
		_vgiPath( vgipath )
	{
		// 设为异步模式
		setAsynchronousMode( false );
	}
	//----------------------------------------------------------------
	bool IoRequestExtractVgi::anotherThreadHandler()
	{
		char* buf = _buffer;
		const long size = _fileInfo->_fileSize;
		const String& metafilename = _fileInfo->_metaFileName;
		const String& vgipath  = _vgiPath;

		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile(
			vgipath + "\\" + metafilename );

		assert( pwriter.isNull() == false );

		long writenum = pwriter->write( buf , size );

		if ( writenum != size )
		{
			std::ostringstream o;
			o << "解压过程中,保存文件" << metafilename << "时出错.";
			MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
			return false;
		}

		//------------------------------------------
		// 下面这一句可以做测试
		//------------------------------------------
		//dispatchMainThreadFunc();

		delete this;

		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestExtractVgi::mainThreadHandler()
	{
		//delete this;

		//MessageBox( NULL , "报喜!" , "" , MB_OK );

		return true;
	}

	//----------------------------------------------------------------

}// end of namespace vgImage
