


#include <vgStableHeaders.h>
#include <vgDtxCreater/vgiFileWriterDtx.h>
#include <vgImage/vgiImageUtility.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStringUtility.h>

	//复制文件的函数
	BOOL CommonCopyFile(CString SourceFileName, CString DestFileName)
	{
		CFile sourceFile ;
		CFile destFile ;
		CFileException ex;
		if (!sourceFile.Open((LPCTSTR)SourceFileName,CFile::modeRead | CFile::shareDenyWrite, &ex))
		{
			TCHAR szError[1024];
			ex.GetErrorMessage(szError, 1024);
			CString ErrorMsg = "打开文件：" ;
			ErrorMsg += SourceFileName ;
			ErrorMsg += "失败。\n错误信息为：\n" ;
			ErrorMsg += szError ;
			AfxMessageBox(ErrorMsg);
			return FALSE ;
		}
		else
		{
			if (!destFile.Open((LPCTSTR)DestFileName, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex))
			{
				TCHAR szError[1024];
				ex.GetErrorMessage(szError, 1024);
				CString ErrorMsg = "创建文件：" ;
				ErrorMsg += DestFileName ;
				ErrorMsg += "失败。\n错误信息为：\n" ;
				ErrorMsg += szError ;
				AfxMessageBox(ErrorMsg);
				sourceFile.Close();
				return FALSE ;
			}

			BYTE buffer[4096];
			DWORD dwRead;
			do
			{
				dwRead = sourceFile.Read(buffer, 4096);
				destFile.Write(buffer, dwRead);
			}
			while (dwRead > 0);   
			destFile.Close();
			sourceFile.Close();
		}
		return TRUE ;
	}


	//----------------------------------------------------------------
	bool FileWriterDtx::writeToDtxFile( 
		const vgKernel::StringVectorPtr  input_image,
		const FrameVectorPtr input_frame , 
		const String& output_filename ,
		const int& ratio ,
		const bool& empty_not_insert /*= false */)
	{
		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( vgKernel::StringUtility::getFileExtension( output_filename ) != "dtx" )
		{
			return false;
		}

		if ( input_image.isNull() == true )
		{
			MessageBox( NULL , "输入image序列为空" , "Error" , MB_OK );
			return false;
		}

		if ( input_image->empty() == true )
		{
			MessageBox( NULL , "输入image序列为空" , "Error" , MB_OK );
			return false;
		}


		//------------------------------------------
		// 确定process的进度条
		// 最后加2分别是文件开始的工作和文件收尾的工作
		//------------------------------------------
		int processCounter = 0;
		this->notifyProcessObserversStart( "开始生成vgi文件..." ,0,
			(input_image->size()) * 2 - 1 + 2 );

		//------------------------------------------
		// 首先检查文件名是否过长,是否有重名
		//------------------------------------------
		{
			std::set<String> names;
			std::pair<std::set<String>::iterator , bool > result;
			vgKernel::StringVector::iterator iter = input_image->begin();
			vgKernel::StringVector::iterator iter_end  =input_image->end();

			for (  ;iter != iter_end ; ++ iter )
			{

				String filename =
					vgKernel::StringUtility::getFilenameFromAbsolutePath( *iter );
				vgKernel::StringUtility::toLowerCase( filename );

				if ( filename.size() >= DTX_FILENAME_LENGTH )
				{
					std::ostringstream o;
					o << "含有文件名过长的dds文件:" << filename ;
					MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
					return false;
				}

				result = names.insert( filename );

				if ( result.second == false )
				{
					std::ostringstream o;
					o << "含有重名image文件(注意,vgi文件区分大小写): " <<  filename;
					MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
					return false;
				}
			}
		}


		//------------------------------------------
		// 然后检查是否覆盖文件
		//------------------------------------------
		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( output_filename ,true);

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		if ( pwriter->isValid() == false )
		{
			return false;
		}

		this->notifyProcessObserversPos( "开始写dtx文件" , processCounter ++ );

		//------------------------------------------
		// 其次开始写文件,写入dtx
		//------------------------------------------
		std::vector<String> validList;
		DtxHeader header;
		vgKernel::StringVector errList;

		//------------------------------------------
		// 1.先预写一边header
		// brief写在最后即可.
		//------------------------------------------
		long filebegin = pwriter->tell();
		assert( filebegin == 0 );
		pwriter->write( &header , sizeof( DtxHeader ) );

		// 写data数据区
		{
			header.ratio = ratio;

			FrameVector::iterator iter = input_frame->begin();
			FrameVector::iterator iter_end = input_frame->end();


			for (  ;iter != iter_end;  iter++ )
			{

				this->notifyProcessObserversPos( "正在预处理" , processCounter ++ );

				long writenum = pwriter->write( &(*iter), sizeof(SingleFrame) );
				assert( writenum == sizeof(SingleFrame) );

				if ( writenum != sizeof(SingleFrame) )
				{
					MessageBox( NULL , "致命错误" , "Error" , MB_OK );
					return false;
				}

				header.totaltime += (*iter).timelength;
				header.framecount++;

			}

			vgKernel::StringVector::iterator iter_image     = input_image->begin();
			vgKernel::StringVector::iterator iter_image_end = input_image->end();

			for ( ; iter_image != iter_image_end; iter_image++ )
			{
				this->notifyProcessObserversPos( "正在复制" + (*iter_image), processCounter ++ );

				//复制文件
				String destfilepath = vgKernel::StringUtility::getPathFromAbsoluteFilename(output_filename);
				String destfilename = vgKernel::StringUtility::getFilenameFromAbsolutePath(*iter_image);
				destfilename = destfilepath + "\\" + destfilename;

				BOOL save_ret = CommonCopyFile( (*iter_image).c_str() , destfilename.c_str() );
				//assert( save_ret == TRUE );
				if (save_ret == FALSE)
				{
					break;
				}

				if (!save_ret)
				{
					errList.push_back( *iter_image );
					continue;
				}

				// 插入队列
				validList.push_back( *iter_image );
			}


		}

		if ( validList.empty() == true )
		{
			MessageBox( NULL , "无有效的image文件输入." , "Error" , MB_OK );
			return false;
		}

		//------------------------------------------
		// 重写header
		//------------------------------------------
		pwriter->seek( filebegin );
		pwriter->write( &header , sizeof( DtxHeader ) );

		pwriter->close();

		//------------------------------------------
		// 清理工作并生成report
		//------------------------------------------
		String outputmsg;

		if ( errList.empty() == false )
		{
			std::ostringstream o;

			o << "保存失败的列表:\n";

			vgKernel::StringVector::iterator iter = errList.begin();
			vgKernel::StringVector::iterator iter_end  = errList.end();

			for (  ;iter != iter_end ; ++ iter )
			{
				o << *iter << "\n";
			}

			outputmsg	+= o.str();
			outputmsg	+= "\n\n";
		}


		// 生成报告
		std::ostringstream o;
		o << "处理完成,成功" << validList.size() <<
			"个文件,失败:" << errList.size() << "个文件.";

		this->notfiyProcessObserversFinish( o.str() );

		MessageBox(NULL, o.str().c_str(), "生成报告", MB_OK);

		return true;
	}
	//----------------------------------------------------------------
