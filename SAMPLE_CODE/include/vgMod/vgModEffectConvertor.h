




#ifndef __VGMODEFFECTCONVERTOR_H__
#define __VGMODEFFECTCONVERTOR_H__

#include <vgKernel/vgkForward.h>
#include <vgGlobalDefinition.h>

#include <vgMod/vgObjNode.h>


namespace vgMod {

	/**
	@date 		2009/05/19  19:42	
	@author  	lss

	@brief 	

	@see    
	*/

	class  VGDEP_EXPORT ModEffectConvertor
	{
	private: 
		ModEffectConvertor()
		{

		}
		~ModEffectConvertor()
		{

		}

	public:
		/*!
		... 转mod为特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToEffectNode2();
		
		template <typename EFFECT_TYPE , typename DLG_TYPE/*, vgCore::IMAGETYPE EFFECT_IMAGE_TYPE */>
		static ModItemPtrVec convertSelectedObjectToEffectNode();
		
		/*!
		... 转mod为水特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToWaterNode();

		/*!
		... 转mod为玻璃特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToGlassNode();

		/*!
		... 转mod为avi视频特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToAviNode();

		/*!
		... 转mod为镜面特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToMirrorNode();

		/*!
		... 转mod为金属特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToMetalNode();

		/*!
		... 转mod为光亮地面特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToFloorNode();


		/*!
		... 转mod为动态纹理特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToDynamicTexNode();

		/*!
		... 转mod为自动建模特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToAutoBuildNode();
		
		/*!
		... 转mod为天空盒特效 ...
		*/		
		static ModItemPtrVec	convertSelectedObjectToSkyboxNode();
		
	public:
		static String&	getProDataPath();
		static	void setProDataPath(String& path);

	public:
		static bool changeWaterDirec();

	protected:
		static	String	m_strProDataPath;

	};


}// end of namespace vgMod



#endif // end of __VGMODEFFECTCONVERTOR_H__