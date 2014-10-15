


#include <vgStableHeaders.h>
#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkWarning.h>


namespace vgKernel {
	
	
	//----------------------------------------------------------------
	Warning::Warning(int num, const String& desc, const String& src) 
		:line( 0 ),
		number( num ),
		description( desc ),
		source( src )
	{
		// Log this error - not any more, allow catchers to do it
		LogManager::getSingleton().logMessage(this->getFullDescription());
	}
	//----------------------------------------------------------------
	Warning::Warning(int num, const String& desc, const String& src, 
		const char* typ, const char* fil, long lin) :
	line( lin ),
		number( num ),
		typeName(typ),
		description( desc ),
		source( src ),
		file( fil )
	{
		// Log this error, mask it from debug though since it may be caught and ignored
		if(LogManager::getSingletonPtr())
		{
			LogManager::getSingleton().logMessage(
				this->getFullDescription(), 
				LML_CRITICAL, true);
		}

	}
	//----------------------------------------------------------------
	Warning::Warning(const Warning& rhs)
		: line( rhs.line ), number( rhs.number ), description( rhs.description ), source( rhs.source ), file( rhs.file )
	{
	}
	//----------------------------------------------------------------
	void Warning::operator = ( const Warning& rhs )
	{
		description = rhs.description;
		number = rhs.number;
		source = rhs.source;
		file = rhs.file;
		line = rhs.line;
		typeName = rhs.typeName;
	}
	//----------------------------------------------------------------
	const String& Warning::getFullDescription(void) const
	{
		if (fullDesc.empty())
		{

			std::ostringstream desc;

			desc << description ;

#if _DEBUG
			desc << "\n\nDetails:\n" ;
			desc <<  "VGES WARNING(" << getNumberAsString() << ":" << typeName << "): "
				<< " in " << source;

			if( line > 0 )
			{
				desc << " at " << file << " (line " << line << ")";
			}

#endif

			fullDesc = desc.str();
		}

		return fullDesc;

	}
	//----------------------------------------------------------------
	int Warning::getNumber(void) const throw()
	{
		return number;
	}
	//----------------------------------------------------------------
	String Warning::getNumberAsString( void ) const
	{
		switch( number )
		{
			/// 写入文件失败.
			/// 对应: retry : cancel
		case WARN_CANNOT_WRITE_TO_FILE:
			return "WARN_CANNOT_WRITE_TO_FILE";

			/// 不推荐的状态:虽然可以强制运行.
			/// 对应: ok : cancel
		case WARN_INVALID_STATE:
			return "WARN_INVALID_STATE";

			/// 不推荐的传入参数:也许可以运行.
			/// 对应: ok : cancel
		case WARN_INVALIDPARAMS:
			return "WARN_INVALIDPARAMS";

			/// 没有查找到相关资源:询问是否采用默认方式或者其他处理.
			/// 对应: retry : ok : cancel
		case WARN_ITEM_NOT_FOUND:
			return "WARN_ITEM_NOT_FOUND";

			/// 文件未正常读取:询问取消还是采用默认空白文件.
			/// 对应: retry : ok : cancel
		case WARN_FILE_NOT_FOUND:
			return "WARN_FILE_NOT_FOUND";

			/// 内部Warning:通常用于debug模式.
			/// 对应: ok
		case WARN_INTERNAL_WARNING:
			return "WARN_INTERNAL_WARNING";

			/// 实现不充分:可能引发错误:Warning一下.
			/// 对应: ok
		case WARN_IMPLEMENT_ILL:	
			return "WARN_IMPLEMENT_ILL";

		default:
			return "WARN_UNKOWN";
		}
	}
	//----------------------------------------------------------------
	int Warning::getWarningReturnFromWin32Btn( const int& val ) const
	{
		switch( val )
		{
		case IDOK:
			return Warning::RETURN_OK;
		case IDCANCEL:
			return Warning::RETURN_CANCEL;
		case IDRETRY:
			return Warning::RETURN_RETRY;
		case IDYES:
			return Warning::RETURN_YES;
		case IDNO:
			return Warning::RETURN_NO;

		case IDABORT:
			return Warning::RETURN_ABORT;

		case IDIGNORE:
			return Warning::RETURN_IGNORE;
		case IDCONTINUE:
			return Warning::RETURN_CONTINUE;
		case IDTRYAGAIN:
			return Warning::RETURN_RETRY;


		default:
			return Warning::RETURN_CANCEL;
		}
	}
	//----------------------------------------------------------------
	
}// end of namespace vgKernel
