// vgClimate.cpp: implementation of the vgClimate class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>

#include <vgEffect/vgClimate.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace vgMod
{

	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////
	vgClimate::vgClimate()
	{
		vgrain	=	NULL;
		vgsnow	=	NULL;
		vgfog	=	NULL;		
		//		m_Water	=	NULL;		
		pCurrentCamera	=	NULL;

		m_bFog	=	false;
	}

	vgClimate::~vgClimate()
	{
		delete	vgrain;
		delete	vgsnow;
		delete  vgfog;
		vgrain = NULL;
		vgsnow = NULL;
		vgfog = NULL;
		//		delete	m_Water;
	}
	//////////////////////////////////////////////////////////////////////
	// Operations
	//////////////////////////////////////////////////////////////////////	
	void vgClimate::init(vgCam::CamManager* camera )
	{
		if(!camera)
			return;
		vgrain = new	vgRain;
		vgsnow = new	vgSnow;
		vgfog  = new	vgFog;

		//		m_Water = new	vgWater;

		pCurrentCamera = camera;
		//m_Water.setCamera(camera);

		//		m_Water->IniWater();

		vgfog->Initialize();
		vgsnow->Initialize();
		vgrain->SetPosition( Vector3(			vgCam::CamManager::getSingleton().getCurrentPosition().x ,
			vgCam::CamManager::getSingleton().getCurrentPosition().y ,
			vgCam::CamManager::getSingleton().getCurrentPosition().z ) );
		vgrain->Initialize();
	}// void vgClimate::init(CameraNode *camera)

	void vgClimate::render()
	{//this->mpEyeCamera = camera	

		//m_Water.Render();	
		vgrain->SetPosition( Vector3(			vgCam::CamManager::getSingleton().getCurrentPosition().x ,
			vgCam::CamManager::getSingleton().getCurrentPosition().y ,
			vgCam::CamManager::getSingleton().getCurrentPosition().z ) );
		vgrain->Render();
		vgsnow->Render();

		return;		
	}// void vgClimate::render()

	void vgClimate::rainon()
	{
		vgrain->m_bStopSE = FALSE;
		return;

	}

	void vgClimate::rainoff()
	{
		vgrain->m_bStopSE = TRUE;
		return;
	}

	void vgClimate::snowon()
	{
		vgsnow->m_bStopSE = FALSE;
		return;
	}

	void vgClimate::snowoff()
	{
		vgsnow->m_bStopSE = TRUE;
		return;
	}

	void vgClimate::fogon()
	{
		m_bFog	=	true;

		vgfog->m_bStopSE = FALSE ;

		glEnable(GL_FOG);
		glClearColor(vgfog->fogColorVar[0], vgfog->fogColorVar[1], 
			vgfog->fogColorVar[2], vgfog->fogColorVar[3]);	

		return;
	}

	void vgClimate::fogoff()
	{
		m_bFog	=	true;

		vgfog->m_bStopSE = TRUE ;

		glDisable(GL_FOG);
		glClearColor(0.5f,0.6f,0.8f,1.0f);

		return;
	}

	void vgClimate::WriteToFile(CFile &fp)
	{

		//m_Water.WriteNodeToVG(fp);

		fp.Write(&m_bFog , sizeof( bool ) );
		return;
	}

	void vgClimate::ReadFromFile(CFile &pfile)
	{	
		//m_Water.recreateNewWater();
		//m_Water.setCamera( pCurrentCamera );
		//m_Water.ReadDataFromFile( pfile );

		
		return;
	}

	void vgClimate::ReadFogSwich(CFile &pfile)
	{
		pfile.Read(&m_bFog , sizeof( bool ) );
		if ( m_bFog )
		{
			glEnable(GL_FOG);
			glClearColor(vgfog->fogColorVar[0], vgfog->fogColorVar[1], 
				vgfog->fogColorVar[2], vgfog->fogColorVar[3]);	
		}
		else
		{
			glDisable(GL_FOG);
			glClearColor(0.5f,0.6f,0.8f,1.0f);
		}
	}

	void vgClimate::reset()
	{
		rainoff();
		snowoff();
		fogoff();
	}
}// namespace vgCore