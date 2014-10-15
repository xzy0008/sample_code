

#ifndef __VGMVGFILEWRITERVGUPDATE_H__
#define __VGMVGFILEWRITERVGUPDATE_H__

#include <vgMod/vgFileWriterVG.h>

namespace vgMod{

	using namespace vgCore;
	
	/**
	@date 	2009/03/02  19:12	
	@author  lss

	@brief 	

	@see    
	*/
	class	 VGDEP_EXPORT FileWriterVGUpdate : public FileWriterVG
	{
	public:
		FileWriterVGUpdate();
		~FileWriterVGUpdate();

	protected:
		virtual	bool	writeOherModulesToVg();

		virtual	bool	writeOherModulesDirectly();

	};
}//namespace vgMod

#endif//__VGMVGFILEWRITERVGUPDATE_H__
