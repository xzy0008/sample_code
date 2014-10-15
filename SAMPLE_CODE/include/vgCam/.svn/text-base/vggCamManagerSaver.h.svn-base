



#ifndef __VGGCAMMANAGERSAVER_H__
#define __VGGCAMMANAGERSAVER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>

	
namespace vgMod {

	/**
		@date 	2009/05/11  20:32	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT CamManagerSaver
	{
	public:
		CamManagerSaver()
		{
			
		}
		~CamManagerSaver()
		{
			
		}
	
	public:

		static bool writeCamMgrToFile( 
			vgKernel::StreamWriterPtr pwriter , const String& attachDataPath,
			bool bReadDirectly = false);

		static bool readCamMgrFromFile( 
			vgKernel::StreamReaderPtr preader , const String& attachDataPath ,
			bool bReadDirectly = false);

		static bool writeCamMgrToFile( 
			const String& save_absolute_path, const String& attachDataPath,
			bool bReadDirectly = false);

		static bool readCamMgrFromFile(
			const String& save_absolute_path, const String& attachDataPath ,
			bool bReadDirectly = false);

	private:
	
	
	};
	
	
}// end of namespace vgGlobal
	


#endif // end of __VGGCAMMANAGERSAVER_H__