/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGCONVERTIONUTIL_H__
#define __VGCONVERTIONUTIL_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgException.h>
//#include <vgStandardHeaders.h>


namespace vgCore {

	/**
		@date 	2007/02/27  10:29	
		@author  leven

		@brief 	转换类的封装.其中textCast用到的是boost::lexical_cast<>模版方法(精度已经定义).
			
			考虑以后是否还要用到boost::numeric_cast...

		@see   boost::lexical_cast
	*/
	class ConvertUtil
	{
	private:
		ConvertUtil(){};
		~ConvertUtil(){};
	
	public:

#if _MSC_VER > 1200	

		template<typename Source>
		static String textCast(const Source &arg)
		{
			return lexical_cast<String , Source>(arg);
		}

		/*
		//模版类方法,其中用到下面的boost::lexical_cast
		template<typename Target, typename Source>
		static Target textCast(const Source &arg)
		{
			return lexical_cast<Target,Source>(arg);
		}
		*/

		/* 一个简单的实现.
		template< typename Target, typename Source >
		static Target textCast(const Source &arg)
		{
			std::stringstream sstream;
			sstream << arg ;

			Target result;
			sstream >> result;

			return result;
		}
		*/
#else

		template< typename Source >
		static String textCast(const Source &arg)
		{
			std::ostringstream result;
			result << arg;

			return result.str();
		}

#endif

	};

#if _MSC_VER > 1200	

	//以下为原始的的boost::lexical_cast实现.
	template <class T> 
	struct is_pointer 
	{ 
		static const bool value = false;
	};
	template <class T> 
	struct is_pointer<T*> 
	{ 
		static const bool value = true; 
	};

	
	namespace detail // selectors for choosing stream character type
	{
		template<typename Type>
		struct stream_char
		{
			typedef char type;
		};


		template<>
		struct stream_char<wchar_t>
		{
			typedef wchar_t type;
		};


		template<>
		struct stream_char<wchar_t *>
		{
			typedef wchar_t type;
		};

		template<>
		struct stream_char<const wchar_t *>
		{
			typedef wchar_t type;
		};

		template<>
		struct stream_char<std::wstring>
		{
			typedef wchar_t type;
		};


		template<typename TargetChar, typename SourceChar>
		struct widest_char
		{
			typedef TargetChar type;
		};

		template<>
		struct widest_char<char, wchar_t>
		{
			typedef wchar_t type;
		};
	}

	namespace detail // stream wrapper for handling lexical conversions
	{
		template<typename Target, typename Source>
		class lexical_stream
		{
		private:
			typedef typename widest_char<
				typename stream_char<Target>::type,
				typename stream_char<Source>::type>::type char_type;

		public:
			lexical_stream()
			{
				stream.unsetf(std::ios::skipws);

				if(std::numeric_limits<Target>::is_specialized)
					stream.precision(std::numeric_limits<Target>::digits10 + 1);
				else if(std::numeric_limits<Source>::is_specialized)
					stream.precision(std::numeric_limits<Source>::digits10 + 1);
			}
			~lexical_stream()
			{

			}
			bool operator<<(const Source &input)
			{
				return !(stream << input).fail();
			}
			template<typename InputStreamable>
			bool operator>>(InputStreamable &output)
			{
				return !is_pointer<InputStreamable>::value &&
					stream >> output &&
					stream.get() ==std::char_traits<char_type>::eof();
			}
			bool operator>>(std::string &output)
			{
				output = stream.str();
				return true;
			}

			bool operator>>(std::wstring &output)
			{
				output = stream.str();
				return true;
			}

		private:
			std::stringstream stream;

		};
	}

	namespace detail
	{
		template<class T>
		struct array_to_pointer_decay
		{
			typedef T type;
		};

		template<class T, std::size_t N>
		struct array_to_pointer_decay<T[N]>
		{
			typedef const T * type;
		};
	}

	template<typename Target, typename Source>
	Target lexical_cast(const Source &arg)
	{
		typedef typename detail::array_to_pointer_decay<Source>::type NewSource;

		detail::lexical_stream<Target, NewSource> interpreter;
		Target result;

		if(!(interpreter << arg && interpreter >> result))
			//throw (bad_lexical_cast(typeid(NewSource), typeid(Target)));
		{
			VG_EXCEPT(Exception::ERR_INVALIDPARAMS,"textCast error,params must go wrong." ,"ConvertionUtil::textCast<>");
		}
		return result;
	}


	//原来的bad_lexical_cast.此处更改为自定义的Exception.
	/*
	 exception used to indicate runtime lexical_cast failure
	class bad_lexical_cast : public std::bad_cast
	{
	public:
		bad_lexical_cast() :
		  source(&typeid(void)), target(&typeid(void))
		  {
		  }
		  bad_lexical_cast(
			  const std::type_info &source_type,
			  const std::type_info &target_type) :
		  source(&source_type), target(&target_type)
		  {
		  }
		  const std::type_info &source_type() const
		  {
			  return *source;
		  }
		  const std::type_info &target_type() const
		  {
			  return *target;
		  }
		  virtual const char *what() const throw()
		  {
			  return "bad lexical cast: "
				  "source type value could not be interpreted as target";
		  }
		  virtual ~bad_lexical_cast() throw()
		  {
		  }
	private:
		const std::type_info *source;
		const std::type_info *target;
	};
	*/

	
#endif //_MSC_VER > 1200	

} // end of namespace vgCore

#endif // end of __VGCONVERTIONUTIL_H__