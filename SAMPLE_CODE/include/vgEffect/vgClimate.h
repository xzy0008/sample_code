// vgClimate.h: interface for the vgClimate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGSPECIAL_H__C7A8CD62_E5C2_4169_8131_E3097DF28E65__INCLUDED_)
#define AFX_VGSPECIAL_H__C7A8CD62_E5C2_4169_8131_E3097DF28E65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vgKernel/vgkForward.h>

#include "vgRain.h"
#include "vgSnow.h"
#include "vgFog.h"
#include <vgCam/vgcaCamManager.h>


namespace vgMod
{

	class VGDEP_EXPORT	vgClimate  
	{
	public:
		vgClimate();
		virtual ~vgClimate();

		void reset();

	public:
		vgRain *vgrain;
		vgSnow *vgsnow;
		vgFog  *vgfog;

		//vgWater m_Water;
	public:
		 vgCam::CamManager *pCurrentCamera;

		//	2008Äê5ÔÂ23ÈÕ19:51:20 add by lss
		bool	m_bFog;
	public:	
		void init( vgCam::CamManager* camera );
		void render();
	public:
		void rainon();
		void rainoff();
		void snowon();
		void snowoff();
		void fogon();
		void fogoff();

	public:
		void WriteToFile(CFile &fp);
		void ReadFromFile(CFile &pfile);

		void ReadFogSwich(CFile &pfile);
	};// class vgClimate

}// namespace vgCore
#endif // !defined(AFX_VGSPECIAL_H__C7A8CD62_E5C2_4169_8131_E3097DF28E65__INCLUDED_)
