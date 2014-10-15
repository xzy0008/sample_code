
#ifndef __VGDYNAMICTEXTURENODE_H__
#define __VGDYNAMICTEXTURENODE_H__


#include <vgCore/vgPrerequisites.h>
#include <vgMod/vgObjNode.h>
#include <vgTex/tvgDynamicTexture.h>
namespace vgMod {

	using namespace vgCore;

	/**
		@date 	2009/03/30  16:46	
		@author  YUXIN
	
		@brief 	
	
		@see    
	*/
	class DynamicTexNode : public ObjectNode
	{

	public:
		DynamicTexNode(int nVersionMod = VERSION_1);
		~DynamicTexNode();
	
	
	public:

		void setDefault();
		//------------------------------------------
		// 模型数据没有删除.只是删除cg等信息
		//------------------------------------------
		void destroy();

		virtual void Render();

		virtual	unsigned long PositDataToNode(char *data );
	
		virtual void WriteNodeToVG(CFile &fp);


		bool recreate(const String& decalmap );

		virtual vgKernel::StringVector getTexNameVec();

	public:

  		DynamicTexture *m_dyntexture;

		std::string m_StrDtx;

		std::string m_StrDtx_basename;


		// 是否初始化了
		bool mIsInited;

		vgCore::TexturePtr pTexture;

	};
	
	
	
}// end of namespace vgCore

#endif // end of __VGAVINODE_H__