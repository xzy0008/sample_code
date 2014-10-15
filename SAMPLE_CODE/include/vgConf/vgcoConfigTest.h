



#ifndef __VGCOCONFIGTEST_H__
#define __VGCOCONFIGTEST_H__

#define VGCO_TEST		1


#if VGCO_TEST


#include <vgKernel/vgkForward.h>

	
namespace vgConf {

	/**
		@date 	2008/12/04  19:08	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class ConfigTest
	{
	private:
		ConfigTest()
		{
			
		}
		~ConfigTest()
		{
			
		}
	

	public:

		static void runTestOnce();

	
	
	};
	
	
}// end of namespace vgConf
	


#endif

#endif // end of __VGCOCONFIGTEST_H__