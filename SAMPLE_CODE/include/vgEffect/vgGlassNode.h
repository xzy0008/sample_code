




#ifndef __VGGLASSNODE_H__
#define __VGGLASSNODE_H__


#include <vgCore/vgPrerequisites.h>
#include <vgMod/vgObjNode.h>

#include <vgCam/vgcaCamManager.h>

namespace vgMod {

	using namespace vgCore;
	/**
	@date 	2008/02/27  16:46	
	@author  leven

	@brief 	

	@see    
	*/
	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/

	class GlassNode : public ObjectNode
	{

	public:
		GlassNode(int nVersionMod = VERSION_1);
		~GlassNode();


	public:

		void setDefault();
		//------------------------------------------
		// 模型数据没有删除.只是删除cg等信息
		//------------------------------------------
		void destroy();

		virtual void Render();

		virtual	unsigned long PositDataToNode(char *data );

		virtual void WriteNodeToVG(CFile &fp);


		bool recreate(vgCam::CamManager *camera , const vgCore::StringVector& strvec , const String& bumpmap , 
			const String& decalmap , const float& bumpscale);

		virtual void	assignTexture(int i );

		virtual vgKernel::StringVector getTexNameVec();

	public:



		std::string m_StrDecalMap;
		float m_fBumpScale;

		// 是否初始化了
		bool mIsInited;

	private:

		GLuint _brightfloorspheremapid;
		float _constColor[4];

		bool initWaterImpl();

	};



}// end of namespace vgMod
#endif // end of __VGGLASSNODE_H__