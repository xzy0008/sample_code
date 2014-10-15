



#ifndef __VGGSOUNDMANAGERSAVER_H__
#define __VGGSOUNDMANAGERSAVER_H__

#include <vgSound/vgSoundDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>

	
namespace vgSound {

	/**
		@date 	2009/05/11  20:32	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGSOUND_EXPORT SoundManagerSaver
	{
	public:
		SoundManagerSaver()
		{
			
		}
		~SoundManagerSaver()
		{
			
		}
	
	public:
		static bool readSoundMgrFromFile( 
			vgKernel::StreamReaderPtr preader , 
			const String& attachDataPath ,
			bool bReadDirectly = false);


		static bool writeSoundMgrToFile( 
			vgKernel::StreamWriterPtr pwriter , 
			const String& attachDataPath,
			bool bReadDerectly = false);

		static bool readSoundMgrFromFile( 
			const String& save_absolute_path ,  
			const String& attachDataPath ,
			bool bReadDirectly = false);


		static bool writeSoundMgrToFile( 
			const String& save_absolute_path ,  
			const String& attachDataPath ,
			bool bReadDerectly = false);
	private:
	
	
	};
	
	
}// end of namespace vgGlobal
	


#endif // end of __VGGCAMMANAGERSAVER_H__