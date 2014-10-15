


#ifndef __VGDecoder3DSMANAGER_H__
#define __VGDecoder3DSMANAGER_H__


#include <vgDecoder3DSDLL/vgDecoder3DSDefinition.h>
#include <vgKernel/vgkSingleton.h>

#include <vgKernel/vgkRenderer.h>

#include <vgDecoder3DSDLL/vgDecoder3DS.h>
#if 0
namespace  vgEdit {

	/**
	@date 	2008/05/21  20:23	
	@author  leven

	@brief 	

	@see    
	*/
	class  VGDECODER3DS_EXPORT Decoder3DSManager  : 
		 public vgKernel::Singleton<Decoder3DSManager>
	{
	public:
		Decoder3DSManager();
		~Decoder3DSManager();

		bool initialise()
		{
			return true;
		}

		bool shutdown()
		{		

			return true;
		}


		bool initialise( HWND hWnd );	


	   	void unloadData();

		void reset();



	public:
		
	private:
		 HWND _hwnd ;

		 Decoder3DS	_utilityEdit;


	};




}// end of namespace 
#endif
#endif // end of __VGDecoder3DSMANAGER_H__

