// OutPutImage: interface for the SmallMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPASSMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_)
#define AFX_COMPASSMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace vgLogo{


class VGL_EXPORT  CompassLogo : public LogoHandle
{	
public:

		CompassLogo();

		virtual ~CompassLogo();

public:

	virtual void render();

	virtual void loadTexture( vgKernel::StringVector fileNames );

public:

	void initcompass();

private:

	void render( GLuint _textureID );

	virtual void unloadData();  //∏∏¿‡LogoHandleºÃ≥–∂¯¿¥

	void renderbegin();

	void rotateangle( float &_x, float &_y, float _angle );
	
	void recalculate();
private:

	float m_zRot;

	bool b_rotate;

	float  radio;

	float logomultiview;

	float m_viewWidth;  
	float m_viewHeight;  

	map<string, GLuint>  m_texNameIDMap;

};
}
#endif // !defined(AFX_VGSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_)
