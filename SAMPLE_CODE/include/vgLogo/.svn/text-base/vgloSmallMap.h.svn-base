// OutPutImage: interface for the SmallMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGdddSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_)
#define AFX_VGdddSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vgLogo/vgloDefinition.h>
#include <vgLogo/vgloLogoHandle.h>

#include <vgKernel/vgkInputSystem.h>

#include <vgKernel/vgkVec3.h>

#include <map>

using namespace std;



namespace vgLogo{


class VGL_EXPORT SmallMapLogo : public LogoHandle, public vgKernel::InputHandler
{
public:

	SmallMapLogo();

	virtual ~SmallMapLogo();

public:

	virtual void render();

	virtual void loadTexture( vgKernel::StringVector fileNames );

	virtual void setRenderState( bool _render ) ;

	//InputHandler ¼Ì³Ð¶øÀ´
	virtual void OnLButtonDown(UINT nFlags, CPoint position);

	virtual void OnMouseMove(UINT nFlags, CPoint position);

	bool getdatasign( ){ return b_hasscenedata; }



public:

	void OutPutHawkeyeMapInSky( string _filepath );

private:

	void initsmallmap();

	bool CaptureGLBufferToBMP(String filename,   
												int x, int y, int width, int height);

	void OutPutSmallmapImage( string _filepath );

	void DrawSmallmap(float camerax,float cameraz);

	void recalculate();

	void initscenedata();

	void calculatesceneradiomap();

	void calculatecurrentpoint();

	bool Isinsmallmapregion( float _x, float _y ); 

	vgKernel::Vec3 get3dVecFrom2d( const CPoint& point_2d );
	
	void changesceneposition( float _x, float _y );
private:

	float m_lengthradiowidth;

	float m_sceneradiomapx, m_sceneradiomapy;

	float m_FrustumAngle;

	float m_currentpointx, m_currentpointy;

	float m_mousepointx, m_mousepointy;

private:

	float xlengthIn3dscene,ylengthIn3dscene;

	float xcenterIn3dscene,ycenterIn3dscene;

	float zcenterIn3dscene;

private:

	char * imageData;

	char m_transparency;

	bool b_hasscenedata;

	bool b_initialized;

private:
	
	map<string, GLuint>  m_texNameIDMap;

	float radio;

	float m_viewWidth;  

	float m_viewHeight; 

	float logomultiview;

};
}

#endif // !defined(AFX_VGSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_)
