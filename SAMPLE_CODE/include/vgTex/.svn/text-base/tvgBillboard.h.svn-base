

#ifndef __TVGBILLBOARD_H__
#define __TVGBILLBOARD_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgString.h>
#include <vgTex/tvgStringUtil.h>
#include <vgTex/tvgTexture.h>
#include <vgCore/vgSharedPtr.h>


namespace vgCore {


	/**
		@date 	2007/04/28  21:12	
		@author  Leven
			
		@brief 	面片类,可用于树的产生或者任何希望面向使用者的物体.
			
		@see    BillboardSet
	*/
	class  VGDEP_EXPORT Billboard
	{
	public:

		/**
			billboard的渲染方式.

			RENDERTYPE_EYE_ORIENTED
				始终朝向观察者,无论在什么角度.

			RENDERTYPE_ROTATE_Y
				朝向观察者,但在y轴方向固定.

			RENDERTYPE_HOLD_STILL
				不动的billboard,此时方便点击选择.

		*/
		enum  RenderTypes
		{
			RENDERTYPE_EYE_ORIENTED,
			RENDERTYPE_ROTATE_Y ,
			RENDERTYPE_HOLD_STILL
		};


		

		Billboard();

		Billboard( String uniname , String texUniName , Vector3 pos )
		{
			/// this must be less efficient ,but more clear.
			this->setParametersDefault();
			this->create( uniname , texUniName , pos );
		}

		Billboard( String uniname , TexturePtr ptex , Vector3 pos )
		{
			/// this must be less efficient ,but more clear.
			this->setParametersDefault();
			this->create( uniname , ptex , pos );
		}

		~Billboard();
	
		
		/**
			转换billboard的渲染方式.
		*/
		void	reverseRenderType();

		/**
			通过参数来创建一个billboard.
				
			@param	uniname 为其拟定为唯一的名称,这里使用的是指针的形式.
			@param	ptex 面片上的纹理指针.
			@param	pos 位置.默认为原点.
		*/
		void create( const StringPtr& uniname ,
			const TexturePtr& ptex , const Vector3& pos = Vector3::ZERO );

		/**
			通过参数来创建一个billboard.
				
			@param	uniname 为其拟定为唯一的名称.
			@param	ptex 面片上的纹理指针.
			@param	pos 位置.默认为原点.
		*/
		void create( const String& uniname , const TexturePtr& ptex ,
			const Vector3& pos = Vector3::ZERO );

		/**
			通过参数来创建一个billboard.
				
			@param	uniname 为其拟定为唯一的名称
			@param	texUniName 面片上的纹理的唯一名称.函数中会自动索取纹理.
			@param	pos 位置.默认为原点.
				
			@returns	void 
		*/
		void create( const String& uniname ,
			const String& texUniName , const Vector3& pos = Vector3::ZERO );

		/**
			通过一系列的参数来设置billboard.
				
			@note	如果有必要,可以提供默认值.
				
			@param	uniname 设置唯一的名称,方面查找.
			@param	ptex 纹理指针.
			@param	pos billboard的位置.
			@param	selected 是否被选中.
			@param	visible 是否可见.
			@param	rendertype 渲染的方式.
			@param	width 宽度.
			@param	height 高度.
			@param	upVector 向上的向量,用于Rotate Y 方式.
				
			@returns	void 
		*/
		void setParameters( const StringPtr& uniname ,
			const TexturePtr& ptex , const Vector3& pos ,
			const bool& selected , const bool& visible ,
			const RenderTypes& rendertype ,
			const Real& width , const Real& height ,
			const Vector3& upVector );

		/**
			渲染函数,将billboard渲染到屏幕上.
		*/
		void	draw();

		/**
			设置面片的缩放值.
		*/
		void	setScale( const Real& scale );

		
		friend istream& operator >> ( istream& in , Billboard& bbd );

		friend ostream& operator << ( ostream& out , Billboard& bbd );



	private:
	public:

		/**
			通过texturePtr自动更新billboard的大小.
		*/
		void  autoUpdateRect();

		/**
			设置默认的参数.
		*/
		void setParametersDefault();

		/**
			使用RENDERTYPE_EYE_ORIENTED方式渲染实体.
		*/
		void	drawUsingEyeOriented() const;

		/**
			使用RENDERTYPE_ROTATE_Y方式渲染实体.
		*/
		void	drawUsingRotatedY() const;

		/**
			使用RENDERTYPE_HOLD_STILL方式渲染实体.
		*/
		void	drawUsingHoldStill() const;

		/**
			使用RENDERTYPE_EYE_ORIENTED方式渲染边框.
		*/
		void	drawEdgeUsingEyeOriented() const;

		/**
			使用RENDERTYPE_HOLD_STILL方式渲染边框.
		*/
		void	drawEdgeUsingHoldStill() const;

		/**
			使用RENDERTYPE_ROTATE_Y方式渲染边框.
		*/
		void	drawEdgeUsingRotateY() const;

		/**
			设置渲染的开始时段.
		*/
		void	drawingBegin() const;

		/**
			设置渲染的末尾时段.
		*/
		void	drawingEnd() const;

		/**
			通过载入当前的矩阵来更新当前的视点信息.
		*/
		void	updateCurrentViewVectors();

		/**
			通过ModelViewMatrix来抽取各向量信息.
				
			@param	right 当前视点的向右向量值
			@param	up 当前视点的朝向
			@param	direction 当前视点的向上向量

			@returns	void 
		*/
		static void	extractVectorFromModelViewMatrix(
			Vector3& right , Vector3& up , Vector3& direction );

	public:

		/**
			得到具体的信息.
		*/
		String getDetails() const;

		// 关于旋转轴的set和get方法.
		const Vector3		getRotatedAxis() const;
		Vector3&		getRotatedAxis();
		void		setRotatedAxis( const Vector3& val );


		/**
			得到唯一名称.
		*/
		const StringPtr		getUniqueNamePtr() const;

		// 关于visible的set和get方法.
		const bool		getIfVisible() const;
		bool&		getIfVisible();
		void		setIfVisible( const bool& val );


		// 关于position的set和get方法.
		const Vector3		getPosition() const;
		Vector3&		getPosition();
		void		setPosition( const Vector3& val );


		// 关于IfSelected的set和get方法.
		const bool		getIfSelected() const;
		bool&		getIfSelected();
		void		setIfSelected( const bool& val );


		// 关于TexturePtr的set和get方法.
		const TexturePtr		getTexturePtr() const;
		TexturePtr&		getTexturePtr();
		void		setTexturePtr( const TexturePtr& val );


		// 关于RenderType的set和get方法.
		const RenderTypes getRenderType() const;
		RenderTypes&	getRenderType();
		void		setRenderType( 
			const RenderTypes& val );
	

		/**
			得到面片的高度.
		*/
		const Real		getHeight() const;

		/**
			得到面片高度的引用.
		*/
		Real&		getHeight();


		/**
			设置面片的高度.
		*/
		void		setHeight( const Real& val );

		/**
			得到面片的宽度.
		*/
		const Real		getWidth() const;

		/**
			得到面片宽度的引用.
		*/
		Real&		getWidth();

		/**
			设置面片的宽度.
		*/
		void		setWidth( const Real& val );

	public:

		/// 像素到3D单位的转换因子
		static  Real	 PIXCEL_TO_FLOAT_FACTOR; 

		/// 默认的生成billboard的宽度(包括无纹理的时候)
		static  Real	 DEFAULT_RECT_WIDTH;

		/// 默认的生成billboard的高度(包括无纹理的时候)
		static  Real	 DEFAULT_RECT_HEIGHT;

	private:
			
		/// 理应在Guid继承体系中完成.
		//uint		mUniqueID;

		StringPtr	mUniqueNamePtr;
		Vector3		mPosition;	

		/**
			旋转轴,仅用于RENDERTYPE_ROTATE_Y方式.
			used for rotated Y drawing
		*/
		Vector3		mRotatedAxis;

		/// 是否被选择了.
		bool		mIfSelected;

		/// 是否显示.
		bool		mIfVisible;	

		/// 此面片的纹理指针.
		TexturePtr	mTexturePtr;


		Real		mScale;



		/// 高度
		Real		mWidth;

		/// 高度
		Real		mHeight;

		/// 渲染出来的边框颜色.
		static vgMath::ColorValue	msEdgeColor;

		/// billboard的渲染方式.
		RenderTypes	mRenderType;

		/// 当前视点的向右向量值.
		mutable  Vector3	mCurrentViewRight;

		/// 当前视点的朝向.
		mutable  Vector3	mCurrentViewDirection;

		/// 当前视点的向上向量.
		mutable  Vector3	mCurrentViewUp;
	};
	

	/**
		@date 	2007/04/28  21:29	
		@author  Leven
			
		@brief 	定义面片类的指针.
			
		@see    SharedPtr
	*/
	typedef  SharedPtr<Billboard>  BillboardPtr;
	
	
}// end of namespace vgCore

#endif // end of __TVGBILLBOARD_H__