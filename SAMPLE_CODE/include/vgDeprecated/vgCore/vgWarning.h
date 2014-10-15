

#ifndef __VGWARNING_H__
#define __VGWARNING_H__

#include <vgCore/vgPrerequisites.h>


namespace vgCore {

	/// 感觉写这个Warning类还是很有必要的.原因:
	///   1.功能上分工的需要.以后为了节省存储可能要写入文件,
	/// 这个功能理应在这个类里面实现.还有其他的功能如读入,序列化
	/// 等等.
	///   2.必要时也需要抛出Warning异常,这会区别于Exception而作
	/// 特殊的处理.
	///   3.通过日志文件读入后,要创建一个struct包含单个Warning信息,
	/// 做这个类还是必要的.
	/// 参见:Exception类.
	class  VGDEP_EXPORT Warning
	{
	public:

		enum WarningCodes 
		{
			/// 写入文件失败.
			/// 推荐对应关系: retry , cancel
			WARN_CANNOT_WRITE_TO_FILE,
			/// 不推荐的状态,虽然可以强制运行.
			/// 推荐对应关系: ok , cancel
			WARN_INVALID_STATE,
			/// 不推荐的传入参数,也许可以运行.
			/// 推荐对应关系: ok , cancel
			WARN_INVALIDPARAMS,
			/// 没有查找到相关资源,询问是否采用默认方式或者其他处理.
			/// 推荐对应关系: retry , cancel
			WARN_ITEM_NOT_FOUND,
			/// 文件未正常读取,询问取消还是采用默认空白文件.
			/// 推荐对应关系: retry , cancel
			WARN_FILE_NOT_FOUND,
			/// 内部Warning,通常用于debug模式.
			/// 推荐对应关系: ok
			WARN_INTERNAL_WARNING,
			/// 实现不充分,可能引发错误,Warning一下.
			/// 推荐对应关系: ok
			WARN_IMPLEMENT_ILL,	
		};


/// vc 6.0 会不认识MB_CANCELTRYCONTINUE
#if _MSC_VER == 1200	 
#define MB_CANCELTRYCONTINUE  MB_RETRYCANCEL
#define IDTRYAGAIN			IDRETRY
#define IDCONTINUE			IDIGNORE
#endif

		/**

		BUTTON_ABORT_RETRY_IGNORE
		强制退出,重试,忽略

		BUTTON_CANCEL_TRY_CONTINUE
		取消,重试,忽略

		BUTTON_HELP	
		帮助.(可与其他项进行与操作)

		BUTTON_OK			
		确定.

		BUTTON_CANCEL
		取消

		BUTTON_RETRY_CANCEL
		重试,取消

		BUTTON_YES_NO
		是,否

		BUTTON_YES_NO_CANCEL
		是,否,取消

		BUTTON_NONE
		不产生任何对话框,默认为写入日志.

		*/
		enum WarningButtonCodes
		{
			BUTTON_ABORT_RETRY_IGNORE	= MB_ABORTRETRYIGNORE,
			BUTTON_CANCEL_TRY_CONTINUE	= MB_CANCELTRYCONTINUE,
			BUTTON_HELP					= MB_HELP,
			BUTTON_OK					= MB_OK,
			BUTTON_CANCEL				= MB_OKCANCEL,
			BUTTON_RETRY_CANCEL			= MB_RETRYCANCEL,
			BUTTON_YES_NO				= MB_YESNO,
			BUTTON_YES_NO_CANCEL		= MB_YESNOCANCEL,
			BUTTON_NONE					= 0x00000040L
		};

		enum WarningReturnCode {
			/// 关闭警告继续执行.
			RETURN_IGNORE,
			/// 抛出异常,终止运行.
			RETURN_ABORT,
			/// 重试运行.
			RETURN_RETRY,
			RETURN_OK,
			/// 中断运行.比如用在处理一大堆文件时,处理到中间退出.
			RETURN_CANCEL,
			RETURN_YES,
			RETURN_NO,
			RETURN_CONTINUE,

			RETURN_NONE
		};


		/** Default constructor.
		*/
		Warning( int number, const String& description, const String& source );

		/** Advanced constructor.
		*/
		Warning( int number, const String& description, const String& source, const char* type, const char* file, long line );

		/** Copy constructor.
		*/
		Warning(const Warning& rhs);


		void operator = (const Warning& rhs);

		virtual const String& getFullDescription(void) const;

		/** Gets the error code.
		*/
		virtual int getNumber(void) const throw();

		string getNumberAsString(void) const ;

		/** Gets the source function.
		*/
		virtual const String &getSource() const { return source; }

		/** Gets source file name.
		*/
		virtual const String &getFile() const { return file; }

		/** Gets line number.
		*/
		virtual long getLine() const { return line; }


		virtual const String &getDescription(void) const { return description; }

		const char* what() const throw() { return getFullDescription().c_str(); }

		/// 子类可以继承重写此方法.如果没有重写,则为默认弹出Warning的方式.
		virtual int showWarning(const int& flag = BUTTON_OK ) const
		{
			if ( (flag & BUTTON_NONE) != 0 )
			{
				return RETURN_NONE;
			}
			int val = MessageBox( NULL , this->what() , typeName.c_str() , flag | MB_ICONWARNING );
			return getWarningReturnFromWin32Btn( val );
		}

	protected:
		long line;
		///种类:WarningCodes
		int number;		
		String typeName;
		String description;
		String source;
		String file;
		mutable String fullDesc;

		inline int showWin32MessageBox(const int& btn_type) const
		{
			return MessageBox( NULL , this->what() , typeName.c_str() ,
				btn_type );
		}

		int getWarningReturnFromWin32Btn(const int& val) const;
	};



	/// 用于重载函数所做的必要配置.
	template <int num>
	struct WarningCodeType
	{
		enum { number = num };
	};


	class  IOWarning : public Warning
	{
	public:
		IOWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "IOWarning", file, line) {}
	};
	class  InvalidStateWarning : public Warning
	{
	public:
		InvalidStateWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "InvalidStateWarning", file, line) {}
	};
	class  InvalidParametersWarning : public Warning
	{
	public:
		InvalidParametersWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "InvalidParametersWarning", file, line) {}
	};
	class  ItemNotFoundWarning : public Warning
	{
	public:
		ItemNotFoundWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "ItemNotFoundWarning", file, line) {}
	};
	class  FileNotFoundWarning : public Warning
	{
	public:
		FileNotFoundWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "FileNotFoundWarning", file, line) {}
	};
	class  InternalWarning : public Warning
	{
	public:
		InternalWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "InternalWarning", file, line) {}
	};
	class  ImplementIllWarning : public Warning 
	{
	public:
		ImplementIllWarning(int number, const String& description, const String& source, const char* file, long line)
			: Warning(number, description, source, "ImplementIllWarning", file, line) {}
	};



	/// 在这里先不用那么复杂的创建很多Warning类的派生.
	/// 只是简单的实现即可.
	class WarningFactory
	{
	public:
		WarningFactory()
		{

		}
		~WarningFactory()
		{

		}

		static int  makeWarning(
			WarningCodeType<Warning::WARN_CANNOT_WRITE_TO_FILE> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = IOWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}
		static int  makeWarning(
			WarningCodeType<Warning::WARN_INVALID_STATE> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = InvalidStateWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}
		static int  makeWarning(
			WarningCodeType<Warning::WARN_INVALIDPARAMS> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = InvalidParametersWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}
		static int  makeWarning(
			WarningCodeType<Warning::WARN_ITEM_NOT_FOUND> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = ItemNotFoundWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}
		static int  makeWarning(
			WarningCodeType<Warning::WARN_FILE_NOT_FOUND> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = FileNotFoundWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}
		static int  makeWarning(
			WarningCodeType<Warning::WARN_INTERNAL_WARNING> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = InternalWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}
		static int  makeWarning(
			WarningCodeType<Warning::WARN_IMPLEMENT_ILL> code ,
			const int& flag , const String& desc, 
			const String& src, const char* file, long line)
		{
			const Warning& warn = ImplementIllWarning(code.number, desc, src, file, line);
			return warn.showWarning( flag );
		}

	};



}// end of namespace vgCore

#define VG_WARN(num, flags, description, src) vgCore::WarningFactory::makeWarning( \
	vgCore::WarningCodeType<num>(), flags,description, src, __FILE__, __LINE__ );



#endif // end of __VGWARNING_H__