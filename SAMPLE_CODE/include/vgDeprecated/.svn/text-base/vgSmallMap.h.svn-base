// OutPutImage: interface for the SmallMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_)
#define AFX_VGSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace vgCore{


class SmallMap  
{
public:
	void Renderoff();
	void Renderon();
	Vector3 ImageToScene(int x, int y);
	void OutPutImage2();
	bool ChangeCameraPos(long x, long y);
	void CreatTexture();
	void DrawSmallmap(float camerax,float cameraz);
	void OutPutImage();
	SmallMap();
	virtual ~SmallMap();
	bool CaptureGLBufferToBMP(CString filename,      int x, int y,      int width, int height);
	int WriteBitmapFile(CString filename, int width, int height,char *imageData);
	void WriteToFile(CFile &fp);
	void ReadFromFile(CFile &fp);

	void SetFrustumAngle(float angle)
	{
		m_FrustumAngle = angle;
	}

	float m_bili;

	TexturePtr pTexture;

	float xlength,ylength;

	float smallmaplength,smallmapwidth;

	float xlengthIn3dscene,ylengthIn3dscene;

	float xcenterIn3dscene,ycenterIn3dscene;

	char * imageData;

	float camerax,cameray,cameraz;

	float cameraxfortrack,camerazfortrack;

	vector<Vector3> trackpoints;

	float ThecoordIn3DMappointx,ThecoordIn3DMappointy;

	float mapbili;////鹰眼与场景的比例

	float ProPointToImagex,ProPointToImagey;

	int ImageLength,ImageWidth;

//	SmallMap *vgMap;

///////////////////////////////////
	float m_FrustumAngle;

	char m_transparency;

	float m_distance;


private:
	bool b_Render;
};
}
#endif // !defined(AFX_VGSMALLMAP_H__7EFCEBBD_800B_408C_903A_CFB83EC70234__INCLUDED_)
