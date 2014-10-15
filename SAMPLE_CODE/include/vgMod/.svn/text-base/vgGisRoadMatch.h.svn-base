

#pragma once

#include "vgMod/vgObjNode.h" 

const vgKernel::RendererType RENDERER_TYPE_GISMATCH = 5044;

namespace vgMod
{

	class VGDEP_EXPORT GisRoadMatch:public vgMod::ObjectNode
	{
		VGK_RENDERER_IN_DECLARE(GisRoadMatch)
	public:
		GisRoadMatch(); 
		~GisRoadMatch();

	public:
	public:
		char m_matchname[20];

		int m_id;

		float m_width;

		float m_luya;

		string m_texname;

		float m_texdensity;

		float m_height;

		float m_bili;

		vector<Vector3> matchpath;

		vector<Vector3> RenderPoints;

		vector<Vector3> LuyaPoints1, LuyaPoints2;

		vector<float> uv_u1;

		vector<float> uv_u2;


		bool b_render;

		vgCore::TexturePtr pTexture;

		Vector3 tempPoint;

		void AccessPoint(CPoint &pp);
		void Processport();
		void GenRoadWithPoints();

		int  GetRenderPointsize(){ return  RenderPoints.size(); }

		void Render();
		Vector3 GalPoint(Vector2 &V1, Vector2 &V2, Vector2 &V3, float &y);
		float mathcal1(Vector2 &V1, Vector2 &V2);
		void RenderLuya1();
		void RenderRoadSurface();
		void RenderLuya2();
		void calUV();
		void SaveMatchTovg(CFile &fp);
		void ReadMatchToscene(CFile &fp, String readPath);//YX
		void RenderPointAndLine();
		void SetTempPoint(CPoint &pp);


		// ---------------------------------------------------------------------- [9/23/2008 YX]
		virtual void translate(const float& x, const float& y, const float& z) ;
		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z) ;
		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) ;
		virtual std::pair<bool, float> testIntersectWithTriangles( const vgKernel::Ray& ray );
		virtual BoundingBox ComputeBoundBox();
		//virtual Vector3 getVertexElementPosition(int i);
		//-------------------------------------------------------------------------[10/3/2008 LSS]
		float	GetHeight(void)		{	return m_height;}
		void	SetHeight(float h)	{	m_height = h;	ComputeBoundBox();}
		void	scaleVector3Array( Vector3 scale , Vector3 centerVec, vector<Vector3>& vecVec );
		void	rotatePointArray( short axis, float angle ,Vector3 centerVec, vector<Vector3>& vecVec   );
		void	traslateVector3Array( Vector3 offset, vector<Vector3>& vecVec);
		float	GetWidth(void)		{	return m_width;}
		void	SetWidth(float w,Vector3 center)	
		{	
			m_width = w;

			ComputeBoundBox();
		}
		float   GetDensity(void)	{  return m_texdensity;}
		void    SetDensity(float d )
		{
			m_texdensity = d;

			ComputeBoundBox();
		}

		float   GetLuyaHeight(void)	{ return m_luya;}  
		void    SetLuyaHeight(float h )
		{
			m_luya = h;

			ComputeBoundBox();
		}

		void ReGenRoadWithPoints();
	
		void addPoint( vgKernel::Vec3 _point );
		//-------------------------------------------------------------------------------
		String m_folderpath;
	};



	VGK_RENDERER_OUT_DECLARE( GisRoadMatch )
		typedef std::vector<GisRoadMatch*>	GismatchPtrVec;	
	typedef std::vector<GisRoadMatch*>::iterator	GismatchPtrVecItr;	


}
