


#ifndef __VGKCONVERTUTILITY_H__
#define __VGKCONVERTUTILITY_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2008/09/24  9:19	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class ConvertUtility
	{
	private:
		ConvertUtility(){};
		~ConvertUtility(){};


	public:

		//template< typename Source >
		//static String textCast(const Source &arg)
		//{
		//	std::ostringstream result;
		//	result << arg;

		//	return result.str();
		//}

		template< typename Target, typename Source >
		static Target textCast(const Source &arg)
		{
			std::stringstream sstream;
			sstream << arg ;

			Target result;
			sstream >> result;

			return result;
		}
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKCONVERTUTILITY_H__