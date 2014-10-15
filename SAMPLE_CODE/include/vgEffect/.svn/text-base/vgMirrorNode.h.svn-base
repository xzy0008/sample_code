





#ifndef __VGMIRRORNODE_H__
#define __VGMIRRORNODE_H__







#include <vgCore/vgPrerequisites.h>
#include <vgMod/vgObjNode.h>
#include <vgTex/tvgMirrorGpuProgram.h>
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

	class MirrorNode : public ObjectNode
	{

	public:
		MirrorNode(int nVersionMod = VERSION_1);
		~MirrorNode();
	
	
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
		
		virtual vgKernel::StringVector getTexNameVec();

	public:

		bool initImpl();

		void setCamera( vgCam::CamManager* camera )
		{
			this->mpEyeCamera = camera;
		}

		vgCam::CamManager *mpEyeCamera;

		MirrorGpuProgram *mpWaterProgram;

		std::string  m_StrEnvMap[6];
		std::string m_StrBumpMap;
		std::string m_StrDecalMap;
		float m_fBrightness;

		// 是否初始化了
		bool mIsInited;
	
	};
	
	
	
}// end of namespace vgCore


#endif // end of __VGMIRRORNODE_H__
