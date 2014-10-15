#pragma once

#include <vgPlan/vgpDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>

namespace vgPlan
{

	/**
	@date 	2009/06/29  16:21	
	@author  ZSC

	@brief 	

	@see    
	*/
	class PlanPlugin : public vgKernel::Plugin
	{
	public:
		PlanPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~PlanPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGP_DLL_NAME;
		}

		virtual bool initInOpenGL(){ return true; }

		virtual void render();

		virtual void renderEnd(){}


		virtual bool uninitInOpenGL(){ return true; }

		virtual void reset(){}

		virtual void readProject(  const String& projpath ,
			const String& projname ){}

		virtual void saveProject(  const String& projpath ,
			const String& projname ){}

		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

	};
}