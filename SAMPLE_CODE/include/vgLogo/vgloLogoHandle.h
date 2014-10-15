

#ifndef __VGLOGOHANDLE_H__
#define __VGLOGOHANDLE_H__

#include <vgLogo/vgloDefinition.h>
#include <vgKernel/vgkVec2.h>

namespace vgLogo {  
	

	/**
	@date 	2009/11/27  9:53	
	@author  ZhouZY

	@brief 	

	@see    
	*/

	enum VaryType
	{
		WIDTH,     //viewport[2]  视口宽度变化 
		HEIGHT,    //viewport[3]  视口高度变化
		BOTH,      //宽度，高度都变化
		NONE       //无变化 
	};

	class VGL_EXPORT  LogoHandle
	{

	public:
		LogoHandle() 
		{
			m_bRender = false;
			m_bSubRender = false;
			m_textureID = NULL;
			m_currentTexID = 0;
			m_logoWidth = 0;
			m_logoHeight = 0;

			m_originalWidth = 0.0;
			m_originalHeith = 0.0;

			m_bFirst = true;
			m_wCounter = 1;
			m_hCounter = 1;
		}

		virtual ~LogoHandle() {}

	public:

		virtual void reset() {}

		virtual void render() {}

		virtual void unloadData() {}
		virtual void loadTexture( vgKernel::StringVector fileNames ) {}

		virtual void setRenderState( bool _render ) 
		{
			m_bRender = _render;
		}
		virtual bool getRenderState() const
		{ 
			return m_bRender; 
		}
		
		void setSubRenderState( bool bRender )
		{
			m_bSubRender = bRender;
		}
		bool getSubRenderState() const
		{
			return m_bSubRender;
		}

		float getLogoHeight() const
		{
			return m_logoHeight;
		}
		void setLogoHeight( float height )
		{
			m_logoHeight = height;
		}

		void setLogoWidth( float width, float radio )
		{
			m_logoWidth = width;  //设置宽度

			float pp = radio;  //固定宽高比例

			if ( m_bFirst )  //只在初始时按比值pp计算高度
			{
				m_bFirst = false;

				m_logoHeight = m_logoWidth / pp;

				m_originalWidth = width;
				m_originalHeith = m_logoHeight;
			}
		}

		void setLogoWidth( float width )
		{
			m_logoWidth = width;  //设置宽度

			float pp = (float)1.0;  //固定宽高比例

			if ( m_bFirst )  //只在初始时按比值pp计算高度
			{
				m_bFirst = false;

				m_logoHeight = m_logoWidth / pp;
				
				m_originalWidth = width;
				m_originalHeith = m_logoHeight;
			}

		}
		float getLogoWidth() const
		{
			return m_logoWidth;
		}


		void setCenterPos( vgKernel::Vec2& pos, bool bState )
		{
			//*********************//
			//      y
			//	----㊣----               中间黑点为坐标原点（0,0）
			//	|	┇   |               水平向右为X轴正方向,
			//  |   ┇   |               X轴最大值为1.0, 最小值为-1.0
			//	┅┅●┅┅㊣ x           垂直向上为Y轴正方向,
			//  |   ┇   |               Y轴最大值为1.0, 最小值为-1.0
			//  | 	┇   |
			//  ----------	
			//*********************//

			if ( bState )  //直接赋值
			{
				m_centerPos = pos;
			}
			else  //通过传入的角点计算中心坐标
			{
				pos.x -= m_logoWidth / 2.0;
				pos.y += m_logoHeight / 2.0;
				m_centerPos = pos;

				//只有初始化时采用传角点的办法，之后须保证
				//m_originalCenterPos 不会被重新赋值 
				m_originalCenterPos = m_centerPos;  
			}
		}
		vgKernel::Vec2* getCenterPos()
		{
			return &m_centerPos;
		}


		//////////////////////////////////////////////////////////////////////////
		void setOriginalWidth( float oriWidth )
		{
			m_originalWidth = oriWidth;
		}
		float getOriginalWidth() const
		{
			return m_originalWidth;
		}
		
		void setOriginalHeight( float oriHeigth )
		{
			m_originalHeith = oriHeigth;
		}
		float getOriginalHeight() const
		{
			return m_originalHeith;
		}

		void setOriginalCenterPos( vgKernel::Vec2& pos )
		{
			m_originalCenterPos = pos;
		}
		vgKernel::Vec2& getOriginalCenterPos()
		{
			return m_originalCenterPos;
		}

		void setWCounter( int counter )
		{
			m_wCounter = counter;
		}
		short getWCounter() const
		{
			return m_wCounter;
		}

		void setHCounter( int counter )
		{
			m_hCounter = counter;
		}

		short getHCounter() const
		{
			return m_hCounter;
		}

		vgKernel::Vec2* getCornerPos() 
		{
			return &m_cornerPos;
		}

	protected:

		bool              m_bRender;      // 是否渲染此Logo
		bool              m_bSubRender;   // 子项Logo是否渲染
		GLuint*	          m_textureID;	  // Logo纹理ID	
		GLuint            m_currentTexID;     //当前纹理ID号
	
		float             m_logoWidth;    // Logo的宽度
		float             m_logoHeight;   // Logo的长度
		
		vgKernel::Vec2    m_centerPos;    // Logo的中心位置

		//以下用于平台窗口变化后计算Logo大小
		//////////////////////////////////////////////////////////////////////////

		float             m_originalWidth;    //以原始Logo宽度为基准，
		float             m_originalHeith;    //原始Logo高度                           

		vgKernel::Vec2    m_originalCenterPos;//原始中心位置，此值永远不变

		bool              m_bFirst;           //每个对象仅记录一次originalWidth,oringinalHeight

		short             m_wCounter;          //用于窗口高度变化后计算新的中心位置坐标
		short             m_hCounter;          //用于窗口变化后计算子项新的中心位置坐标

		vgKernel::Vec2    m_cornerPos;
	};

}

#endif