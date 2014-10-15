

#ifndef __VGCORPLOGO_H__
#define __VGCORPLOGO_H__

#include <vgLogo/vgloDefinition.h>
#include <vgLogo/vgloLogoHandle.h>

using namespace std;
namespace vgLogo {  
	

	/**
	@date 	2009/11/27  9:53	
	@author  ZhouZY

	@brief 	

	@see    
	*/

	class VGL_EXPORT  CorpLogo : public LogoHandle
	{

	public:
		CorpLogo();
		virtual ~CorpLogo();

	public:

		//从父类LogoHandle继承而来
		virtual void reset();

		virtual void render();

		virtual void loadTexture( vgKernel::StringVector fileNames );

		////////////////////////////////////////////////////////////
		//自己所特有

		void loadTexture();  //保留用于读取配置文件加载贴图 

		void initCorpLogoRU();

		void setRotateState( bool _m_bRotate )
		{
			m_bRotate = _m_bRotate;
		}

		void setCurrentTexID( int id )
		{
			//m_currentTexID由为父类继承来的属性
			m_currentTexID = id;
		}

		void setCurrentTexID( string texFileName );

	private:
		//类内部调用的私有方法

		virtual void unloadData();  //父类LogoHandle继承而来

		void renderBegin();

		void recalculate();
		void recalculateData();

		void setVaryType( VaryType varyType )
		{
			m_varyType = varyType;
		}

	private:
		
		bool  m_bRotate;
		float m_zRot;

		VaryType m_varyType;   //标记视口变化

		float m_dWidth;   //默认平台渲染窗口宽度
		float m_dHeight;  //默认平台渲染窗口高度

		//每个MenuLogo对象都有以下两个数据
		int m_lastViewWidth;
		int m_lastViewHeight;

		map<string, GLuint>  m_texNameIDMap;
	};

}

#endif