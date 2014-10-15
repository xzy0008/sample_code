#ifndef __VGLOGOMANAGER_H__
#define __VGLOGOMANAGER_H__

#include <vgLogo/vgloDefinition.h>
#include <vgKernel/vgkSingleton.h>

#include <vgLogo/vgloCorpLogo.h>
#include <vgLogo/vgloMenuLogo.h>

#include <vgLogo/vgloCompass.h>
#include <vgLogo/vgloSmallMap.h>

#include <vgKernel/vgkRenderCommand.h>

namespace vgLogo {  

	/**
	@date 	2009/03/15  8:34	
	@author  yuxin

	@brief 	

	@see    
	*/

	using namespace std;

	class VGL_EXPORT  LogoManager : public vgKernel::Singleton<LogoManager>
	{

	public:
		LogoManager();
		~LogoManager();

		//由单件类继承而来
	public:
		bool initialise();

		bool shutdown();

	public:
		void initInOpenGL();
		void uninitInOpenGL();

		void reset();

		bool addLogoHandle( LogoHandle* handle );
		bool removeLogoHandle( LogoHandle* handle );

		void renderAllLogo();
		
		CorpLogo* getCorpLogoPtr()
		{
			return m_pCorpLogoRU;
		}

		MenuLogo* getMenuLogoRDPtr()
		{
			return m_pMenuLogoRD;
		}

		MenuLogo* getMenuLogoLDPtr()
		{
			return m_pMenuLogoLD;
		}

		SmallMapLogo* getSmallMapPtr()
		{
			return psmallmapRU;
		}

		bool getcompassrendersign()
		{
			if ( pcompassRU )
			{
				return pcompassRU->getRenderState();
			}
		}

		void setcompassrendersign( bool _render )
		{
			if ( pcompassRU )
			{
				pcompassRU->setRenderState( _render );
			}
		}

		bool getsmallmaprendersign()
		{
			if ( psmallmapRU)
			{
				return psmallmapRU->getRenderState();
			}
		}
		void setsmallmaprendersign( bool _render )
		{
			if ( psmallmapRU )
			{
				psmallmapRU->setRenderState( _render );
			}
		}

		bool getsmallmapdatasign()
		{
			if ( psmallmapRU )
			{
				return psmallmapRU->getdatasign();
			}
		}

		void SmallmapInit();

		void OutPutHawkeyeMapInSky( string _filename );

	private:
		CorpLogo*   m_pCorpLogoRU;  //右上角CorpLogo
		MenuLogo*   m_pMenuLogoRD;  //右下角MenuLogo
		MenuLogo*   m_pMenuLogoLD;  //左下角MenuLogo

		vgKernel::RenderCommand *m_pContourRenderCommand;
		vgLogo::CompassLogo *pcompassRU;
		vgLogo::SmallMapLogo *psmallmapRU;

		vector<LogoHandle*> m_LogoHandleList;
	};

}

#endif