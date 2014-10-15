#pragma once

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>

namespace vgAutoBuild {

	/**
	@date 	2009/07/30
	@author  ZSC

	@brief 	

	@see    
	*/
	class  VGDEP_EXPORT AutoBuildSaver
	{
	public:
		AutoBuildSaver()
		{

		}
		~AutoBuildSaver()
		{

		}

	public:

		static bool writeAutoBuildToFile( 
			CFile& file, const String& attachDataPath);

		static bool readAutoBuildFromFile( 
			CFile& file, const String& attachDataPath);

		static bool writeAutoBuildToFile( 
			const String& save_absolute_path, const String& attachDataPath);

		static bool readAutoBuildFromFile(
			const String& save_absolute_path, const String& attachDataPath);

	private:


	};


}// end of namespace
